/*
 * Copyright 2012-2014 Falltergeist Developers.
 *
 * This file is part of Falltergeist.
 *
 * Falltergeist is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Falltergeist is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Falltergeist.  If not, see <http://www.gnu.org/licenses/>.
 */

// C++ standard includes
#include <iostream>
#include <ctime>
#include <sstream>


// Falltergeist includes
#include "../Engine/ResourceManager.h"
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Location.h"
#include "../Game/GameDefines.h"
#include "../Game/GameObject.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameContainerItemObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameAmmoItemObject.h"
#include "../Game/GameDrugItemObject.h"
#include "../Game/GameKeyItemObject.h"
#include "../Game/GameWeaponItemObject.h"
#include "../Game/GameMiscItemObject.h"
#include "../Game/GameDoorSceneryObject.h"
#include "../States/CritterDialogState.h"
#include "../VM/VM.h"
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"
#include "../VM/Handlers/Opcode8002Handler.h"
#include "../VM/Handlers/Opcode8005Handler.h"
#include "../VM/Handlers/Opcode8033Handler.h"
#include "../VM/Handlers/Opcode80DEHandler.h"
#include "../VM/Handlers/OpcodeC001Handler.h"
#include "../Engine/CrossPlatform.h"

// Third party includes

namespace Falltergeist
{

VM::VM(std::shared_ptr<libfalltergeist::IntFileType> script, std::shared_ptr<void> owner)
{
    _owner = owner;
    _script = script;
    if (!_script) throw Exception("VM::VM() - script is null");
}

VM::VM(std::string filename, std::shared_ptr<void> owner)
{
    _owner = owner;
    _script = ResourceManager::intFileType(filename);
    if (!_script) throw Exception("VM::VM() - script is null: " + filename);
}

VM::~VM()
{
}


void VM::call(std::string name)
{
    try
    {
        _programCounter = _script->function(name);
        pushDataInteger(0); // arguments counter;
        pushReturnInteger(0); // return adrress
        CrossPlatform::debug("\nCALLED: " + name + " [" + _script->filename() +  "]", DEBUG_SCRIPT);
        run();
        popDataInteger(); // remove function result
        CrossPlatform::debug("Function ended", DEBUG_SCRIPT);
    }
    catch (libfalltergeist::Exception &e)
    {
        CrossPlatform::debug("Function not exist: " + name, DEBUG_SCRIPT);
    }
}

void VM::initialize()
{
    if (_initialized) return;
    _programCounter = 0;   
    run();
    popDataInteger(); // remove @start function result
}

void VM::run()
{
    while (_programCounter != _script->size())
    {
        if (_programCounter == 0 && _initialized) return;

        _script->setPosition(_programCounter);
        unsigned short opcode;
        *_script >> opcode;
        std::ostringstream ss;
        ss << "0x" << std::hex << _programCounter << " [" << opcode << "] ";
        CrossPlatform::debug(false, ss.str(), DEBUG_SCRIPT);

        std::shared_ptr<OpcodeHandler> opcodeHandler;

        switch (opcode)
        {
            // В этот switch нужно перенести те опкоды, которые теперь в виде класса
            // Это нужно из-за того что эти классы сами меняют программный счетчик
            // И нужно предотвратить его смену здесь в default
            case 0x8002:
                opcodeHandler = std::shared_ptr<Opcode8002Handler>(new Opcode8002Handler(this));
                break;
            case 0x8005:
                opcodeHandler = std::shared_ptr<Opcode8005Handler>(new Opcode8005Handler(this));
                break;
            case 0x8033:
                opcodeHandler = std::shared_ptr<Opcode8033Handler>(new Opcode8033Handler(this));
                break;
            case 0x80DE:
                opcodeHandler = std::shared_ptr<Opcode80DEHandler>(new Opcode80DEHandler(this));
                break;
            case 0xC001:
                opcodeHandler = std::shared_ptr<OpcodeC001Handler>(new OpcodeC001Handler(this));
                break;
            case 0x9001:
                _programCounter += 6;
                break;
            default:
                _programCounter += 2;
                break;
        }
        switch (opcode)
        {
            case 0x8002: break;
            case 0x8003:
                CrossPlatform::debug("unlock", DEBUG_SCRIPT);
                break;
            case 0x8004:
            {
                CrossPlatform::debug("[*] goto(addr)", DEBUG_SCRIPT);
                _programCounter = popDataInteger();
                break;
            }
            case 0x8005: break;
            case 0x800c:
            {
                CrossPlatform::debug("[*] pop_r => push_d", DEBUG_SCRIPT);
                _dataStack.push(_returnStack.pop());
                break;
            }
            case 0x800d:
            {
                CrossPlatform::debug("[*] pop_d => push_r", DEBUG_SCRIPT);
                _returnStack.push(_dataStack.pop());
                break;
            }
            case 0x8010:
            {
                CrossPlatform::debug("[*] startdone", DEBUG_SCRIPT);
                _initialized = true;
                return;
            }
            case 0x8012:
            {
                CrossPlatform::debug("[*] SVAR[number];", DEBUG_SCRIPT);
                auto number = popDataInteger();
                auto value = _dataStack.values()->at(_SVAR_base + number);
                _dataStack.push(value);
                break;
            }
            case 0x8013:
            {
                CrossPlatform::debug("[*] SVAR[num] = value", DEBUG_SCRIPT);
                auto number = popDataInteger();
                auto value = _dataStack.pop();
                _dataStack.values()->at(_SVAR_base + number) = value;
                break;
            }
            case 0x8014:
            {
                CrossPlatform::debug("[*] getExported(name)", DEBUG_SCRIPT);
                auto game = Game::getInstance();
                auto EVARS = game->location()->EVARS();
                switch (_dataStack.top()->type())
                {
                    case VMStackValue::TYPE_INTEGER:
                        _dataStack.push(EVARS->at(_script->identificators()->at(popDataInteger())));
                        break;
                    case VMStackValue::TYPE_POINTER:
                    {
                        auto string = std::static_pointer_cast<std::string>(popDataPointer());
                        _dataStack.push(EVARS->at(*string.get()));
                        break;
                    }
                    default:
                        throw Exception("VM::opcode8014 error");
                }
                break;
            }
            case 0x8015:
            {
                CrossPlatform::debug("[*] export(value, name)", DEBUG_SCRIPT);
                auto name = std::static_pointer_cast<std::string>(popDataPointer());
                auto value = _dataStack.pop();
                auto game = Game::getInstance();
                auto EVARS = game->location()->EVARS();
                EVARS->at(*(name.get())) = value;
                break;
            }
            case 0x8016:
            {
                CrossPlatform::debug("[*] export(name)", DEBUG_SCRIPT);
                auto name = std::static_pointer_cast<std::string>(popDataPointer());
                auto game = Game::getInstance();
                auto EVARS = game->location()->EVARS();
                if (EVARS->find(*(name.get())) == EVARS->end())
                {
                    EVARS->insert(std::make_pair(*(name.get()), std::shared_ptr<VMStackValue>(nullptr)));
                }
                break;
            }
            case 0x8018:
            {
                CrossPlatform::debug("[*] dswap", DEBUG_SCRIPT);
                _dataStack.swap();
                break;
            }
            case 0x8019:
            {
                CrossPlatform::debug("[*] rswap", DEBUG_SCRIPT);
                _returnStack.swap();
                break;
            }
            case 0x801a:
            {
                CrossPlatform::debug("[*] pop_d", DEBUG_SCRIPT);
                _dataStack.pop();
                break;
            }
            case 0x801b:
            {
                CrossPlatform::debug("[?] dup_r", DEBUG_SCRIPT);
                _returnStack.push(_returnStack.top());
                break;
            }
            case 0x801c:
            {
                _programCounter = popReturnInteger();
                std::ostringstream ss;
                ss << "[*] ret = 0x" << std::hex << _programCounter;
                CrossPlatform::debug(ss.str(), DEBUG_SCRIPT);
                break;
            }
            case 0x8027:
            {
                CrossPlatform::debug("[?] unknown pop_d pop_d", DEBUG_SCRIPT);
                _dataStack.pop();
                _dataStack.pop();
                break;
            }
            case 0x8028:
            {
                CrossPlatform::debug("[?] ? lookup_string_proc(? p1)", DEBUG_SCRIPT);
                popDataInteger();
                pushDataPointer(0);
                break;
            }
            case 0x8029:
            {
                _DVAR_base = popReturnInteger();
                CrossPlatform::debug("[*] DVAR restore = " + std::to_string(_DVAR_base), DEBUG_SCRIPT);
                break;
            }
            case 0x802a:
            {
                CrossPlatform::debug("[*] DVAR clear", DEBUG_SCRIPT);
                while (_dataStack.size() > _DVAR_base)
                {
                    _dataStack.pop();
                }
                break;
            }
            case 0x802b:
            {
                auto argumentsCounter = popDataInteger();
                pushReturnInteger(_DVAR_base);
                _DVAR_base = _dataStack.size() - argumentsCounter;
                CrossPlatform::debug("[*] set DVAR base = " + std::to_string(_DVAR_base), DEBUG_SCRIPT);
                break;
            }
            case 0x802c:
            {
                _SVAR_base = _dataStack.size();
                CrossPlatform::debug("[*] set SVAR_base = " + std::to_string(_SVAR_base), DEBUG_SCRIPT);
                break;
            }
            case 0x802f:
            {
                CrossPlatform::debug("[*] ifthen(address, condition)", DEBUG_SCRIPT);
                auto condition = popDataLogical();
                auto address = popDataInteger();
                if (!condition)
                {
                    _programCounter = address;
                }
                break;
            }
            case 0x8030:
            {
                CrossPlatform::debug("[*] while(address, condition)", DEBUG_SCRIPT);
                auto condition = popDataLogical();
                if (condition)
                {
                    _programCounter = popDataInteger();
                }
                break;
            }
            case 0x8031:
            {
                auto num = popDataInteger();
                auto value = _dataStack.pop();
                std::ostringstream ss;
                ss << "[*] DVAR[num] = value " << "num = " << std::hex << num << " type = " << value->type();
                CrossPlatform::debug(ss.str(), DEBUG_SCRIPT);
                _dataStack.values()->at(_DVAR_base + num) = value;
                break;
            }
            case 0x8032:
            {
                auto num = popDataInteger();
                auto value = _dataStack.values()->at(_DVAR_base + num);
                _dataStack.push(value);
                std::ostringstream ss;
                ss << "[*] DVAR[num] " << "num = " << std::hex << num << " type = " << value->type();
                CrossPlatform::debug(ss.str(), DEBUG_SCRIPT);
                break;
            }
            case 0x8033: break;
            case 0x8034:
            {
                CrossPlatform::debug("[*] neq !=", DEBUG_SCRIPT);
                switch (_dataStack.top()->type())
                {
                    case VMStackValue::TYPE_INTEGER:
                    {
                        auto p2 = popDataInteger();
                        if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER) // to check if the pointer is null
                        {
                            auto p1 = (int)(bool)popDataPointer();
                            pushDataInteger(p1 != p2);
                        }
                        else
                        {
                            auto p1 = popDataInteger();
                            pushDataInteger(p1 != p2);
                        }
                        break;
                    }
                    case VMStackValue::TYPE_POINTER:
                    {
                        auto p2 = (int)(bool)popDataPointer();
                        if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER) // to check if the pointer is null
                        {
                            auto p1 = (int)(bool)popDataPointer();
                            pushDataInteger(p1 != p2);
                        }
                        else
                        {
                            auto p1 = popDataInteger();
                            pushDataInteger(p1 != p2);
                        }
                        break;
                    }
                    case VMStackValue::TYPE_FLOAT:
                    {
                        auto p2 = popDataFloat();
                        auto p1 = popDataFloat();
                        pushDataInteger(p1 != p2);
                        break;
                    }
                }
                break;
            }
            case 0x8035:
            {
                CrossPlatform::debug("[*] leq <=", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a <= b);
                break;
            }
            case 0x8036:
            {
                CrossPlatform::debug("[*] geq >=", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a >= b);
                break;
            }
            case 0x8037:
            {
                CrossPlatform::debug("[*] lt <", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a < b);
                break;
            }
            case 0x8038:
            {
                CrossPlatform::debug("[*] gt >", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a > b);
                break;
            }
            case 0x8039:
            {
                CrossPlatform::debug("[*] plus +", DEBUG_SCRIPT);
                auto b = _dataStack.top();
                switch (b->type())
                {                    
                    case VMStackValue::TYPE_POINTER: // STRING
                    {
                        auto p2 = std::static_pointer_cast<std::string>(popDataPointer());
                        auto a = _dataStack.top();
                        switch(a->type())
                        {
                            case VMStackValue::TYPE_POINTER: // STRING + STRING
                            {
                                auto p1 = std::static_pointer_cast<std::string>(popDataPointer());
                                pushDataPointer(std::shared_ptr<std::string>(new std::string((p1 == 0 ? "" : *(p1.get())) + (p2 == 0 ? "" : *(p2.get())))));
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT: // FLOAT + STRING
                            {
                                throw Exception("VM::opcode PLUS - FLOAT+POINTER not allowed");
                            }
                            case VMStackValue::TYPE_INTEGER: // INTEGER + STRING
                            {
                                throw Exception("VM::opcode PLUS - INTEGER+POINTER not allowed");
                            }
                        }

                        break;
                    }
                    case VMStackValue::TYPE_INTEGER: // INTEGER
                    {
                        auto p2 = popDataInteger();
                        auto a = _dataStack.top();
                        switch(a->type())
                        {
                            case VMStackValue::TYPE_INTEGER: // INTEGER + INTEGER
                            {
                                auto p1 = popDataInteger();
                                pushDataInteger(p1 + p2);
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT: // FLOAT + INTEGER
                            {
                                auto p1 = popDataFloat();
                                pushDataFloat(p1 + p2);
                                break;
                            }
                            case VMStackValue::TYPE_POINTER: // STRING + INTEGER
                            {
                                auto p1 = std::static_pointer_cast<std::string>(popDataPointer());
                                pushDataPointer(std::shared_ptr<std::string>(new std::string((p1 == 0 ? "" : *(p1.get())) + std::to_string(p2))));
                                break;
                            }
                        }
                        break;
                    }
                    case VMStackValue::TYPE_FLOAT: // FLOAT
                    {
                        auto p2 = popDataFloat();
                        auto a = _dataStack.top();
                        switch(a->type())
                        {
                            case VMStackValue::TYPE_INTEGER: // INTEGER + FLOAT
                            {
                                auto p1 = popDataInteger();
                                pushDataFloat(p1 + p2);

                                break;
                            }
                            case VMStackValue::TYPE_FLOAT: // FLOAT + FLOAT
                            {
                                auto p1 = popDataFloat();
                                pushDataFloat(p1 + p2);
                                break;
                            }
                            case VMStackValue::TYPE_POINTER: // STRING + FLOAT
                            {
                                auto p1 = std::static_pointer_cast<std::string>(popDataPointer());
                                pushDataPointer(std::shared_ptr<std::string>(new std::string((p1 == 0 ? "" : *(p1.get())) + std::to_string(p2))));
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            case 0x803a:
            {
                CrossPlatform::debug("[*] minus -", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a-b);
                break;
            }
            case 0x803b:
            {
                CrossPlatform::debug("[*] mult *", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a*b);
                break;
            }
            case 0x803c:
            {
                CrossPlatform::debug("[*] div /", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a/b);
                break;
            }
            case 0x803d:
            {
                CrossPlatform::debug("[*] mod %", DEBUG_SCRIPT);
                auto b = _dataStack.pop();
                auto a = _dataStack.pop();
                auto p1 = std::dynamic_pointer_cast<VMStackIntValue>(a);
                auto p2 = std::dynamic_pointer_cast<VMStackIntValue>(b);
                pushDataInteger(p1->value()%p2->value());
                break;
            }
            case 0x803e:
            {
                CrossPlatform::debug("[*] &&", DEBUG_SCRIPT);
                auto b = popDataLogical();
                auto a = popDataLogical();
                pushDataInteger(a && b);
                break;
            }
            case 0x803f:
            {
                CrossPlatform::debug("[+] ||", DEBUG_SCRIPT);
                auto b = popDataLogical();
                auto a = popDataLogical();
                pushDataInteger(a || b);
                break;
            }
            case 0x8040:
            {
                CrossPlatform::debug("[*] &", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a & b);
                break;
            }
            case 0x8041:
            {
                CrossPlatform::debug("[*] |", DEBUG_SCRIPT);
                auto b = popDataInteger();
                auto a = popDataInteger();
                pushDataInteger(a | b);
                break;
            }
            case 0x8045:
            {
                CrossPlatform::debug("[*] !", DEBUG_SCRIPT);
                auto a = popDataLogical();
                pushDataInteger(!a);
                break;
            }
            case 0x8046:
            {
                CrossPlatform::debug("[*] - value (change sign)", DEBUG_SCRIPT);
                auto value = popDataInteger();
                pushDataInteger(-value);
                break;
            }
            case 0x80a1:
            {
                CrossPlatform::debug("[+] void giveExpPoints(int points)", DEBUG_SCRIPT);
                auto points = popDataInteger();
                auto game = Game::getInstance();
                game->player()->setExperience(game->player()->experience() + points);
                break;
            }
            case 0x80a3:
            {
                CrossPlatform::debug("[=] void play_sfx(string* p1)", DEBUG_SCRIPT);
                popDataPointer();
                break;
            }
            case 0x80a4:
            {
                CrossPlatform::debug("[+] std::string* obj_name(GameCritterObject* who)", DEBUG_SCRIPT);
                auto critter = std::static_pointer_cast<GameCritterObject>(popDataPointer());
                pushDataPointer(std::shared_ptr<std::string>(new std::string(critter->name())));
                break;
            }
            case 0x80a6:
            {
                CrossPlatform::debug("[=] int SkillPoints(int PCStatNum)", DEBUG_SCRIPT);
                popDataInteger();
                pushDataInteger(0);
                break;
            }
            case 0x80a7:
            {
                CrossPlatform::debug("[+] GameObject* tile_contains_pid_obj(int position, int elevation, int PID)", DEBUG_SCRIPT);
                auto PID = popDataInteger();
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto game = Game::getInstance();
                std::shared_ptr<GameObject> found;
                for (auto object : *game->location()->objects())
                {
                    if (object->PID() == PID && object->elevation() == elevation && object->position() == position)
                    {
                        found = object;
                    }
                }
                pushDataPointer(found);
                break;
            }
            case 0x80a8:
            {
                CrossPlatform::debug("[=] void set_map_start(int x, int y, int elev, int rot)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                break;
            }
            case 0x80a9:
            {
                CrossPlatform::debug("[+] void override_map_start(int x, int y, int elevation, int orientation)", DEBUG_SCRIPT);
                auto orientation = popDataInteger();
                auto elevation = popDataInteger();
                auto y = popDataInteger();
                auto x = popDataInteger();
                auto position = y*200 + x;
                auto game = Game::getInstance();
                auto player = game->player();
                player->setPosition(position);
                player->setOrientation(orientation);
                player->setElevation(elevation);
                break;
            }
            case 0x80aa:
            {
                CrossPlatform::debug("[+] int get_skill(GameCritterObject* who, int number) ", DEBUG_SCRIPT);
                int number = popDataInteger();
                if (number > 17) throw Exception("VM::opcode80AA - number out of range: " + std::to_string(number));
                auto object = std::static_pointer_cast<GameCritterObject>(popDataPointer());
                if (!object) throw Exception("VM::opcode80AA pointer error");
                pushDataInteger(object->skill(number));
                break;
            }
            case 0x80ab:
            {
                CrossPlatform::debug("[=] int using_skill(GameCritterObject* who, int skill)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80ac:
            {
                CrossPlatform::debug("[=] int roll_vs_skill(ObjectPtr who, int skill, int modifier)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataPointer();
                pushDataInteger(2);
                break;
            }
            case 0x80ae:
            {
                CrossPlatform::debug("[=] int do_check(ObjectPtr who, int check, int modifier)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataPointer();
                pushDataInteger(2);
                break;
            }
            case 0x80af:
            {
                CrossPlatform::debug("[*] int is_success(int val)", DEBUG_SCRIPT);
                auto value = popDataInteger();
                if (value == 2 || value == 3)
                {
                    pushDataInteger(1); // true;
                }
                else
                {
                    pushDataInteger(0);
                }
                break;
            }
            case 0x80b0:
            {
                CrossPlatform::debug("[*] int is_critical(int val)", DEBUG_SCRIPT);
                auto value = popDataInteger();
                if (value == 0 || value == 3)
                {
                    pushDataInteger(1);
                }
                else
                {
                    pushDataInteger(0);
                }
                break;
            }
            case 0x80b2:
            {
                CrossPlatform::debug("[=] void mark_area_known(int AREA_MARK_TYPE, int AreaNum, int MARK_STATE);", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataInteger();
                break;
            }
            case 0x80b4:
            {
                CrossPlatform::debug("[+] int rand(int min, int max)", DEBUG_SCRIPT);
                auto max = popDataInteger();
                auto min = popDataInteger();
                srand(time(0));
                pushDataInteger(rand()%(max - min + 1) + min);
                break;
            }
            case 0x80b6:
            {
                CrossPlatform::debug("[+] int move_to(GameObject* object, int position, int elevation)", DEBUG_SCRIPT);
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto object = std::static_pointer_cast<GameObject>(popDataPointer());
                if (!object) throw new Exception("Opcode 80b6 error");
                object->setPosition(position);
                object->setElevation(elevation);
                pushDataInteger(1);
                break;
            }
            case 0x80b7:
            {
                CrossPlatform::debug("[+] GameObject* create_object_sid(int PID, int position, int elevation, int SID)", DEBUG_SCRIPT);
                auto SID = popDataInteger();
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto PID = popDataInteger();
                auto object = Location::createObject(PID);
                object->setPosition(position);
                object->setElevation(elevation);
                if (SID > 0)
                {
                    auto intFile = ResourceManager::intFileType(SID);
                    if (intFile) object->scripts()->push_back(new VM(intFile, object));
                }
                pushDataPointer(object);
                break;
            }
            case 0x80b8:
            {
                CrossPlatform::debug("[*] void display_msg(string*)", DEBUG_SCRIPT);
                _displayString(std::static_pointer_cast<std::string>(popDataPointer()));
                break;
            }
            case 0x80b9:
                CrossPlatform::debug("script_overrides", DEBUG_SCRIPT);
                break;
            case 0x80ba:
            {
                CrossPlatform::debug("[+] int obj_is_carrying_obj_pid(GameObject* object, int PID)", DEBUG_SCRIPT);
                auto PID = popDataInteger();
                auto pointer = popDataPointer();
                int amount = 0;
                if (auto critter = std::static_pointer_cast<GameCritterObject>(pointer))
                {
                    for (auto object : *critter->inventory()) if (object->PID() == PID) amount += object->amount();
                }
                else if (auto container = std::static_pointer_cast<GameContainerItemObject>(pointer))
                {
                    for (auto object : *container->inventory()) if (object->PID() == PID) amount += object->amount();
                }
                else
                {
                    throw Exception("VM::opcode80ba - unknown object type");
                }
                pushDataInteger(amount);
                break;
            }
            case 0x80bb:
            {
                CrossPlatform::debug("[+] int tile_contains_obj_pid(int position, int elevation, int PID)", DEBUG_SCRIPT);
                auto PID = popDataInteger();
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto game = Game::getInstance();
                int found = 0;
                for (auto object : *game->location()->objects())
                {
                    if (object->PID() == PID && object->elevation() == elevation && object->position() == position)
                    {
                        found = 1;
                    }
                }
                pushDataInteger(found);
                break;
            }
            case 0x80bc:
            {
                CrossPlatform::debug("[+] GameObject* self_obj()", DEBUG_SCRIPT);
                pushDataPointer(_owner);
                break;
            }
            case 0x80bd:
            {
                CrossPlatform::debug("[=] void* source_obj()", DEBUG_SCRIPT);
                pushDataPointer(0);
                break;
            }
            case 0x80bf:
            {
                CrossPlatform::debug("[+] GameDudeObject* dude_obj()", DEBUG_SCRIPT);
                auto game = Game::getInstance();            
                pushDataPointer(game->player());
                break;
            }
            case 0x80c1:
            {
                CrossPlatform::debug("[*] LVAR[num]", DEBUG_SCRIPT);
                unsigned int num = popDataInteger();
                while (num >= _LVARS.size()) _LVARS.push_back(std::shared_ptr<VMStackIntValue>(new VMStackIntValue(0)));
                _dataStack.push(_LVARS.at(num));
                break;
            }
            case 0x80c2:
            {
                CrossPlatform::debug("[*] LVAR[num] = value", DEBUG_SCRIPT);
                auto value = _dataStack.pop();
                unsigned int num = popDataInteger();
                while (num >= _LVARS.size()) _LVARS.push_back(std::shared_ptr<VMStackIntValue>(new VMStackIntValue(0)));
                _LVARS.at(num) = value;
                break;
            }
            case 0x80c3:
            {
                CrossPlatform::debug("[?] MVAR[num]", DEBUG_SCRIPT);
                auto num = popDataInteger();
                if (num < 0)
                {
                    pushDataInteger(0);
                    break;
                }
                auto game = Game::getInstance();
                pushDataInteger(game->location()->MVAR(num));
                break;
            }
            case 0x80c4:
            {
                CrossPlatform::debug("[+] MVAR[num] = value", DEBUG_SCRIPT);
                auto value = popDataInteger();
                auto num = popDataInteger();
                auto game = Game::getInstance();
                game->location()->setMVAR(num, value);
                break;
            }
            case 0x80c5:
            {
                CrossPlatform::debug("[?] GVAR[num]", DEBUG_SCRIPT);
                auto num = popDataInteger();
                if (num < 0)
                {
                    pushDataInteger(0);
                    break;
                }
                auto game = Game::getInstance();
                pushDataInteger(game->GVAR(num));
                break;
            }
            case 0x80c6:
            {
                CrossPlatform::debug("[+] GVAR[num] = value", DEBUG_SCRIPT);
                auto value = popDataInteger();
                auto num = popDataInteger();
                auto game = Game::getInstance();
                game->setGVAR(num, value);
                break;
            }
            case 0x80c7:
            {
                CrossPlatform::debug("[*] int script_action()", DEBUG_SCRIPT);
                pushDataInteger(21);
                break;
            }
            case 0x80c8:
            {
                CrossPlatform::debug("[=] int obj_type(void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80c9:
            {
                CrossPlatform::debug("[+] int obj_item_subtype(GameItemObject* object)", DEBUG_SCRIPT);
                auto pointer = popDataPointer();
                     if (std::static_pointer_cast<GameArmorItemObject>(pointer))     pushDataInteger(0);
                else if (std::static_pointer_cast<GameContainerItemObject>(pointer)) pushDataInteger(1);
                else if (std::static_pointer_cast<GameDrugItemObject>(pointer))      pushDataInteger(2);
                else if (std::static_pointer_cast<GameWeaponItemObject>(pointer))    pushDataInteger(3);
                else if (std::static_pointer_cast<GameAmmoItemObject>(pointer))      pushDataInteger(4);
                else if (std::static_pointer_cast<GameMiscItemObject>(pointer))      pushDataInteger(5);
                else if (std::static_pointer_cast<GameKeyItemObject>(pointer))       pushDataInteger(6);
                else pushDataInteger(-1);
                break;
            }
            case 0x80ca:
            {
                CrossPlatform::debug("[+] int get_critter_stat(GameCritterObject* who, int number)", DEBUG_SCRIPT);
                int number = popDataInteger();
                auto object = std::static_pointer_cast<GameCritterObject>(popDataPointer());
                if (!object) throw Exception("VM::opcode80CA pointer error");

                switch (number)
                {
                    case 34: // gender
                    {
                        pushDataInteger(object->gender());
                        break;
                    }
                    default:
                    {
                        if (number > 6) throw Exception("VM::opcode80CA - number out of range:" + std::to_string(number));
                        pushDataInteger(object->stat(number) + object->statBonus(number));
                        break;
                    }
                }
                break;
            }
            case 0x80cb:
            {
                CrossPlatform::debug("[+] int set_critter_stat(GameCritterObject* who, int number, int value)", DEBUG_SCRIPT);
                int value = popDataInteger();
                int number = popDataInteger();
                if (number > 6) throw Exception("VM::opcode80CB - number out of range:" + std::to_string(number));
                auto object = std::static_pointer_cast<GameCritterObject>(popDataPointer());
                if (!object) throw Exception("VM::opcode80CB pointer error");
                object->setStat(number, value);
                if (std::dynamic_pointer_cast<GameDudeObject>(object))
                {
                    pushDataInteger(3); // for dude
                }
                else
                {
                    pushDataInteger(-1); // for critter
                }
                break;
            }
            case 0x80cc:
            {
                CrossPlatform::debug("[=] void animate_stand_obj(void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                break;
            }
            case 0x80ce:
            {
                CrossPlatform::debug("[=] void animate_move_obj_to_tile(void* who, int tile, int speed)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80cf:
            {
                CrossPlatform::debug("[=] int tile_in_tile_rect(int tile1, int tile2, int tile3, int tile4, int tile)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                pushDataInteger(0);
                break;
            }
            case 0x80d0:
            {
                CrossPlatform::debug("[=] void attack_complex(ObjectPtr who, int called_shot, int num_attacks, int bonus"
                        ", int min_damage, int max_damage, int attacker_results, int target_results)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80d2:
            {
                CrossPlatform::debug("[=] int tile_distance(int tile1, int tile2)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                pushDataInteger(4);
                break;
            }
            case 0x80d3:
            {
                CrossPlatform::debug("int tile_distance_objs(void* p2, void* p1)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                pushDataInteger(10);
                break;
            }
            case 0x80d4:
            {
                CrossPlatform::debug("[+] int objectPosition(GameObject* object)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameObject>(popDataPointer());
                if (!object) throw new Exception("Opcode 80d4 error");
                pushDataInteger(object->position());
                break;
            }
            case 0x80d5:
            {
                CrossPlatform::debug("[*] int tile_num_in_direction(int start_tile, int dir, int distance)", DEBUG_SCRIPT);
                auto distance = popDataInteger();
                auto dir = popDataInteger();
                auto start_tile = popDataInteger();
                pushDataInteger(_tile_num_in_direction(start_tile, dir, distance));
                break;
            }
            case 0x80d8:
            {
                CrossPlatform::debug("[=] void add_obj_to_inven(void* who, void* item)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x80d9:
            {
                CrossPlatform::debug("[=] void rm_obj_from_inven(void* who, void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x80da:
            {
                CrossPlatform::debug("[=] void wield_obj_critter(void* who, void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x80dc:
            {
                CrossPlatform::debug("[=] int obj_can_see_obj(GameObject* src_obj, GameObject* dst_obj)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                pushDataInteger(1);
                break;
            }
            case 0x80de: break;
            case 0x80df:
            {
                CrossPlatform::debug("[?] end_dialogue", DEBUG_SCRIPT);
                auto game = Game::getInstance();
                game->dialog()->close();
                game->popState();
                break;
            }
            case 0x80e1:
            {
                CrossPlatform::debug("[*] int metarule3(int meta, int p1, int p2, int p3)", DEBUG_SCRIPT);
                auto p3 = popDataInteger();
                auto p2 = popDataInteger();
                auto p1 = _dataStack.pop();
                auto meta = popDataInteger();
                pushDataInteger(_metarule3(meta, p1, p2, p3));
                break;
            }
            case 0x80e3:
            {
                CrossPlatform::debug("[=] void set_obj_visibility(void* obj, int visibility)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80e4:
            {
                CrossPlatform::debug("[=] void load_map(string* map, int param)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80e5:
            {
                CrossPlatform::debug("[=] void wm_area_set_pos(int areaIdx, int xPos, int yPos)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataInteger();
                break;
            }
            case 0x80e7:
            {
                CrossPlatform::debug("[=] int anim_busy(void* obj)", DEBUG_SCRIPT);
                popDataPointer();//auto object = (GameObject*)popDataPointer();
                //pushDataInteger(object->animationQueue()->enabled());
                break;
            }
            case 0x80e9:
            {
                CrossPlatform::debug("[*] void set_light_level(int level)", DEBUG_SCRIPT);
                auto level = popDataInteger();
                _setLightLevel(level);
                break;
            }
            case 0x80ea:
            {
                CrossPlatform::debug("[*] int gameTime()", DEBUG_SCRIPT);
                pushDataInteger(SDL_GetTicks() / 10);
                break;
            }
            case 0x80ec:
            {
                CrossPlatform::debug("[=] int elevation(void* obj)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameObject>(popDataPointer());
                if (!object) throw new Exception("Opcode 80ec error");
                pushDataInteger(object->elevation());
                break;
            }
            case 0x80ef:
                CrossPlatform::debug("void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)", DEBUG_SCRIPT);
                break;
            case 0x80f0:
            {
                CrossPlatform::debug("[=] void add_timer_event(void* obj, int time, int info)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80f1:
            {
                CrossPlatform::debug("[=] void rm_timer_event (void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                break;
            }
            case 0x80f2:
            {
                CrossPlatform::debug("[=] int game_ticks(int seconds)", DEBUG_SCRIPT);
                auto seconds = popDataInteger();
                pushDataInteger(seconds*1000);
                break;
            }
            case 0x80f3:
            {
                CrossPlatform::debug("[=] int has_trait(int type,void* who, int trait)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                popDataInteger();
                pushDataInteger(1);
                break;
            }
            case 0x80f4:
            {
                CrossPlatform::debug("[=] int destroy_object(void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80f6:
            {
                CrossPlatform::debug("[*] int game_time_hour", DEBUG_SCRIPT);
                pushDataInteger(_getTime());
                break;
            }
            case 0x80f7:
            {
                CrossPlatform::debug("[=] int fixed_param()", DEBUG_SCRIPT);
                pushDataInteger(1);
                break;
            }
            case 0x80f9:
            {
                CrossPlatform::debug("[=] void dialogue_system_enter()", DEBUG_SCRIPT);
                break;
            }
            case 0x80fa:
            {
                CrossPlatform::debug("[=] int action_being_used()", DEBUG_SCRIPT);
                pushDataInteger(1);
                break;
            }
            case 0x80fb:
            {
                CrossPlatform::debug("[=] int critter_state(void* who)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80fc:
            {
                CrossPlatform::debug("[=] void game_time_advance(int amount)", DEBUG_SCRIPT);
                popDataInteger();
                break;
            }
            case 0x80ff:
            {
                CrossPlatform::debug("[*] int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)", DEBUG_SCRIPT);
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto critter = std::static_pointer_cast<GameCritterObject>(popDataPointer());
                if (!critter) throw new Exception("Opcode 80ff error");
                critter->setElevation(elevation);
                critter->setPosition(position);
                pushDataInteger(1);
                break;
            }
            case 0x8100:
            {
                CrossPlatform::debug("[+] int obj_pid(void* obj)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameObject>(popDataPointer());
                if (!object) throw new Exception("Opcode 8100 error");
                pushDataInteger(object->PID());
                break;
            }
            case 0x8101:
            {
                CrossPlatform::debug("[=] int cur_map_index()", DEBUG_SCRIPT);
                pushDataInteger(3);
                break;
            }
            case 0x8102:
            {
                CrossPlatform::debug("[*] int critter_add_trait(void* who, int trait_type, int trait, int amount) ", DEBUG_SCRIPT);
                auto amount = popDataInteger();
                auto trait = popDataInteger();
                auto trait_type = popDataInteger();
                auto who = popDataPointer();
                pushDataInteger(_critter_add_trait(who, trait_type, trait, amount));
                break;
            }
            case 0x8105:
            {
                CrossPlatform::debug("[+] string* msgMessage(int msg_list, int msg_num);", DEBUG_SCRIPT);
                auto msgNum = popDataInteger();
                auto msgList = popDataInteger();
                pushDataPointer(std::shared_ptr<std::string>(new std::string(msgMessage(msgList, msgNum))));
                break;
            }
            case 0x8106:
            {
                CrossPlatform::debug("[=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)", DEBUG_SCRIPT);
                auto where = popDataInteger();
                auto critter = std::static_pointer_cast<GameCritterObject>(popDataPointer());
                switch (where)
                {
                    case 0: // ARMOR SLOT
                        pushDataPointer(critter->armorSlot());
                        break;
                    case 1: // RIGHT HAND SLOT
                        pushDataPointer(critter->rightHandSlot());
                        break;
                    case 2: // LEFT HAND SLOT
                        pushDataPointer(critter->leftHandSlot());
                        break;
                    case -2: // INVENTORY COUNT
                        pushDataInteger(critter->inventory()->size());
                        break;
                    default:
                        throw Exception("VM::opcode8106 error");
                }
                break;
            }
            case 0x810a:
            {
                CrossPlatform::debug("[=] void float_msg(void* who, string* msg, int type) ", DEBUG_SCRIPT);
                popDataInteger();
                _dataStack.pop(); // pointer or 0(integer)
                popDataPointer();
                break;
            }
            case 0x810c:
            {
                CrossPlatform::debug("[*] void anim(void* who, int anim, int direction)", DEBUG_SCRIPT);
                auto direction = popDataInteger();
                auto anim = popDataInteger();
                auto who = popDataPointer();
                _anim(who, anim, direction);
                break;
            }
            case 0x810b:
            {
                CrossPlatform::debug("[*] int metarule(p2, p1)", DEBUG_SCRIPT);
                auto p1 = _dataStack.pop();
                auto p2 = popDataInteger();
                pushDataInteger(_metarule(p2, p1));
                break;
            }
            case 0x810d:
            {
                CrossPlatform::debug("[=] void* obj_carrying_pid_obj(void* who, int pid)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                pushDataPointer(0);
                break;
            }
            case 0x810e:
            {
                CrossPlatform::debug("[=] void reg_anim_func(int p1, int p2)", DEBUG_SCRIPT);
                auto p2 = _dataStack.pop(); // pointer or integer
                auto p1 = popDataInteger();
                _dataStack.push(p2);
                switch (p1)
                {
                    case 0x1: // ANIM_BEGIN
                    {
                        popDataInteger();//auto p2 = popDataInteger();
                        // RB_UNRESERVED (1) - незарезервированная последовательность, может не воспроизвестись, если отсутствуют свободные слоты
                        // RB_RESERVED (2) - зарезервированная последовательность, должна воспроизвестись в любом случае
                        break;
                    }
                    case 0x2: // ANIM_CLEAR
                    {
                        popDataPointer();//auto object = (GameObject*)popDataPointer();
                        //object->animationQueue()->start();
                        break;
                    }
                    case 0x3: // ANIMATION_END
                    {
                        popDataInteger(); // always 0
                        break;
                    }
                }
                break;
            }
            case 0x810f:
            {
                CrossPlatform::debug("[=] void reg_anim_animate(void* what, int anim, int delay) ", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x8113:
            {
                CrossPlatform::debug("[=] void reg_anim_obj_move_to_tile(void* who, int dest_tile, int delay)", DEBUG_SCRIPT);
                popDataInteger(); // -1
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x8115:
            {
                CrossPlatform::debug("[*] void playMovie(movieNum)", DEBUG_SCRIPT);
                _playMovie(popDataInteger());
                break;
            }
            case 0x8116:
            {
                CrossPlatform::debug("[+] void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)", DEBUG_SCRIPT);
                auto amount = popDataInteger();
                auto item = std::static_pointer_cast<GameItemObject>(popDataPointer());
                if (!item) throw Exception("VM::opcode8116 - item not instanceof GameItemObject");
                item->setAmount(amount);
                // who can be critter or container
                auto pointer = popDataPointer();
                if (auto critter = std::static_pointer_cast<GameCritterObject>(pointer))
                {
                    critter->inventory()->push_back(item);
                }
                else if (auto container = std::static_pointer_cast<GameContainerItemObject>(pointer))
                {
                    container->inventory()->push_back(item);
                }
                else
                {
                    throw Exception("VM::opcode8116 - wrong WHO parameter");
                }
                break;
            }
            case 0x8117:
            {
                CrossPlatform::debug("[=] int rm_mult_objs_from_inven(void* who, void* obj, int count)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8118:
                CrossPlatform::debug("[*] int get_month", DEBUG_SCRIPT);
                pushDataInteger(_getMonth());
                break;
            case 0x811c:
            {
                CrossPlatform::debug("[?] gsay_start", DEBUG_SCRIPT);
                auto game = Game::getInstance();
                game->pushState(game->dialog());
                break;
            }
            case 0x811d:
            {
                CrossPlatform::debug("[?] gsay_end", DEBUG_SCRIPT);
                auto dialog = Game::getInstance()->dialog();
                if (dialog->hasAnswers())
                {
                    pushDataInteger(0);
                    return;
                }
                break;
            }
            case 0x811e:
            {
                CrossPlatform::debug("[=] void gSay_Reply(int msg_file_num, int msg_num)", DEBUG_SCRIPT);
                //Game::getInstance().dialog()->deleteAnswers();
                if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER)
                {
                    auto question = std::static_pointer_cast<std::string>(popDataPointer());
                    Game::getInstance()->dialog()->setQuestion(*(question.get()));
                }
                else
                {
                    auto msg_num = popDataInteger();
                    auto msg_file_num = popDataInteger();
                    Game::getInstance()->dialog()->setQuestion(msgMessage(msg_file_num, msg_num));
                }
                break;
            }
            case 0x8120:
            {
                CrossPlatform::debug("[=] void gSay_Message(int msg_list, int msg_num, int reaction)", DEBUG_SCRIPT);
                popDataInteger();
                _dataStack.pop(); // string or integer
                popDataInteger();
                break;
            }
            case 0x8121:
            {
                CrossPlatform::debug("[+] void giQ_Option(int iq_test, int msg_list, int msg_num, procedure target, int reaction)", DEBUG_SCRIPT);

                auto reaction = popDataInteger();
                auto function = popDataInteger();
                std::shared_ptr<std::string> text;
                if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER)
                {
                    text = std::static_pointer_cast<std::string>(popDataPointer());
                    popDataInteger(); // msg_list
                }
                else
                {
                    auto msg_num = popDataInteger();
                    auto msg_file_num = popDataInteger();
                    text = std::shared_ptr<std::string>(new std::string(msgMessage(msg_file_num, msg_num)));
                }
                auto iq = popDataInteger();
                auto game = Game::getInstance();
                if (iq >= 0)
                {
                    if (game->player()->stat(game->player()->STATS_INTELLIGENCE) >= iq)
                    {
                        auto dialog = game->dialog();
                        dialog->reactions()->push_back(reaction);
                        dialog->functions()->push_back(function);
                        dialog->addAnswer(*text);
                    }
                }
                if (iq < 0)
                {
                    if (game->player()->stat(game->player()->STATS_INTELLIGENCE) <= abs(iq))
                    {
                        auto dialog = game->dialog();
                        dialog->reactions()->push_back(reaction);
                        dialog->functions()->push_back(function);
                        dialog->addAnswer(*text);
                    }
                }

                break;
            }
            case 0x8123:
            {
                CrossPlatform::debug("[=] int GetPoison(void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8125:
            {
                CrossPlatform::debug("[=] void party_remove(void* who)", DEBUG_SCRIPT);
                popDataPointer();
                break;
            }
            case 0x8126:
            {
                CrossPlatform::debug("[+] void reg_anim_animate_forever(GameObject* obj , int delay)", DEBUG_SCRIPT);
                popDataInteger(); // delay - must be -1
                popDataPointer();//auto object = (GameObject*)popDataPointer();
                //if (object->animationQueue()->animation())
                {
                    //object->animationQueue()->stop();
                    //object->animationQueue()->setRepeat(-1); // forever
                    //object->animationQueue()->start();
                }
                break;
            }
            case 0x8128:
            {
                CrossPlatform::debug("[=] int combat_is_initialized()", DEBUG_SCRIPT);
                pushDataInteger(0);
                break;
            }
            case 0x8129:
            {
                CrossPlatform::debug("[=] void gdialog_mod_barter(int modifier)", DEBUG_SCRIPT);
                popDataInteger();
                break;
            }
            case 0x812d:
            {
                CrossPlatform::debug("[+] int is_locked(GameDoorSceneryObject* object)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameDoorSceneryObject>(popDataPointer());
                pushDataInteger(object->locked());
                break;
            }
            case 0x812e:
            {
                CrossPlatform::debug("[+] void lock(GameDoorSceneryObject* object)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameDoorSceneryObject>(popDataPointer());
                object->setLocked(true);
                break;
            }
            case 0x812f:
            {
                CrossPlatform::debug("[+] void unlock(GameDoorSceneryObject* object)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameDoorSceneryObject>(popDataPointer());
                object->setLocked(false);
                break;
            }
            case 0x8130:
            {
                CrossPlatform::debug("[+] int is_opened(GameDoorSceneryObject* object) ", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameDoorSceneryObject>(popDataPointer());
                pushDataInteger(object->opened());
                break;
            }
            case 0x8131:
            {
                CrossPlatform::debug("[+] void open(GameDoorSceneryObject* object) ", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameDoorSceneryObject>(popDataPointer());
                object->setOpened(true);
                break;
            }
            case 0x8132:
            {
                CrossPlatform::debug("[+] void close(GameDoorSceneryObject* object) ", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameDoorSceneryObject>(popDataPointer());
                object->setOpened(false);
                break;
            }
            case 0x8134:
            {
                CrossPlatform::debug("[=] void game_ui_enable()", DEBUG_SCRIPT);
                break;
            }
            case 0x8136:
            {
                CrossPlatform::debug("[=] void gfade_out(int time)", DEBUG_SCRIPT);
                popDataInteger();
                break;
            }
            case 0x8137:
            {
                CrossPlatform::debug("[=] void gfade_in(int time)", DEBUG_SCRIPT);
                popDataInteger();
                break;
            }
            case 0x8138:
            {
                CrossPlatform::debug("[=] int item_caps_total(void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8139:
            {
                CrossPlatform::debug("[=] int item_caps_adjust(void* obj, int amount)", DEBUG_SCRIPT);
                popDataInteger();
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8143:
            {
                CrossPlatform::debug("[=] void attack_setup(ObjectPtr who, ObjectPtr victim)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x8147:
            {
                CrossPlatform::debug("[=] void move_obj_inven_to_obj(void* srcObj, void* destObj)", DEBUG_SCRIPT);
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x8149:
            {
                CrossPlatform::debug("[+] int obj_art_fid(void* obj)", DEBUG_SCRIPT);
                auto object = std::static_pointer_cast<GameObject>(popDataPointer());
                if (!object) throw Exception("VM::opcode8149() - can't convert pointer to object");
                pushDataInteger(object->FID());
                break;
            }
            case 0x814b:
           {
                CrossPlatform::debug("[*] void* party_member_obj(int pid)", DEBUG_SCRIPT);
                popDataInteger();
                pushDataPointer(0);
                break;
            }
            case 0x814c:
            {
                CrossPlatform::debug("[=] int rotation_to_tile(int srcTile, int destTile)", DEBUG_SCRIPT);
                popDataInteger();
                popDataInteger();
                pushDataInteger(0);
                break;
            }
            case 0x814e:
            {
                CrossPlatform::debug("[=] void gdialog_set_barter_mod(int mod)", DEBUG_SCRIPT);
                popDataInteger();
                break;
            }
            case 0x8150:
            {
                CrossPlatform::debug("[=] int obj_on_screen(void* obj)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(1);
                break;
            }
            case 0x8151:
            {
                CrossPlatform::debug("[=] int critter_is_fleeing(void* who)", DEBUG_SCRIPT);
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8153:
            {
                CrossPlatform::debug("[=] void terminate_combat()", DEBUG_SCRIPT);
                break;
            }
            case 0x8154:
            {
                CrossPlatform::debug("[*] void debug(string*)", DEBUG_SCRIPT);
                _debugMessage(std::static_pointer_cast<std::string>(popDataPointer()));
                break;
            }
            case 0x9001:
            {
                unsigned int value;
                unsigned short nextOpcode;
                *_script >> value >> nextOpcode;

                switch(nextOpcode)
                {
                    case 0x8014: // get exported var value
                    case 0x8015: // set exported var value
                    case 0x8016: // export var
                    {
                        auto pointer = std::shared_ptr<std::string>(new std::string(_script->identificators()->at(value)));
                        pushDataPointer(pointer);
                        CrossPlatform::debug("[*] push_d *" + std::to_string((unsigned long long) pointer.get()), DEBUG_SCRIPT);
                        break;
                    }
                    default:
                    {
                        auto pointer = std::shared_ptr<std::string>(new std::string(_script->strings()->at(value)));
                        pushDataPointer(pointer);
                        CrossPlatform::debug("[*] push_d *" + std::to_string((unsigned long long) pointer.get()), DEBUG_SCRIPT);
                        break;
                     }
                }
                break;
            }
            case 0xC001: break;
            default:
            {
                std::ostringstream os;
                os << "0x" << std::hex << opcode;
                CrossPlatform::debug(os.str(), DEBUG_SCRIPT);
                throw 0;
                break;
            }
        }        
        if (opcodeHandler) opcodeHandler->run();
    }
}

int VM::popDataInteger()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = std::dynamic_pointer_cast<VMStackIntValue>(stackValue);
        auto value = stackIntValue->value();
        return value;
    }
    throw Exception("VM::popDataInteger() - stack value is not integer");
}

void VM::pushDataInteger(int value)
{
    _dataStack.push(std::shared_ptr<VMStackIntValue>(new VMStackIntValue(value)));
}

float VM::popDataFloat()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_FLOAT)
    {
        auto stackFloatValue = std::dynamic_pointer_cast<VMStackFloatValue>(stackValue);
        auto value = stackFloatValue->value();
        return value;
    }
    throw Exception("VM::popDataFloat() - stack value is not float");
}

void VM::pushDataFloat(float value)
{
    _dataStack.push(std::shared_ptr<VMStackFloatValue>(new VMStackFloatValue(value)));
}

std::shared_ptr<void> VM::popDataPointer()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_POINTER)
    {
        auto stackPointerValue = std::dynamic_pointer_cast<VMStackPointerValue>(stackValue);
        auto value = stackPointerValue->value();
        return value;
    }
    throw Exception("VM::popDataPointer() - stack value is not a pointer");
}

void VM::pushDataPointer(std::shared_ptr<void> value)
{
    _dataStack.push(std::shared_ptr<VMStackPointerValue>(new VMStackPointerValue(value)));
}

int VM::popReturnInteger()
{
    auto stackValue = _returnStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = std::dynamic_pointer_cast<VMStackIntValue>(stackValue);
        auto value = stackIntValue->value();
        return value;
    }
    throw Exception("VM::popReturnInteger() - stack value is not integer");
}

void VM::pushReturnInteger(int value)
{
    _returnStack.push(std::shared_ptr<VMStackIntValue>(new VMStackIntValue(value)));
}

bool VM::popDataLogical()
{
    switch (_dataStack.top()->type())
    {
        case VMStackValue::TYPE_FLOAT:
            return (bool) popDataFloat();
        case VMStackValue::TYPE_INTEGER:
            return (bool) popDataInteger();
        case VMStackValue::TYPE_POINTER:
            return (bool) popDataPointer();
    }
    throw Exception("VM::popDataLogical() - something strange happened");
}

int VM::_metarule(int type, std::shared_ptr<VMStackValue> value)
{
    switch(type)
    {
        case 14: // METARULE_TEST_FIRSTRUN
            // Если карта открывается в первый раз, то возвращает TRUE;
            return 1;
        case 16: // METARULE_PARTY_COUNT
            return 0;
        case 17: //  METARULE_AREA_KNOWN
            return 1;
        case 18: // METARULE_WHO_ON_DRUGS
            return 0;
        case 19: // METARULE_MAP_KNOWN
            return 1;
        case 22: // METARULE_IS_LOADGAME
            // Игра загружается?
            return 0;  // 0 - false
        case 30: // METARULE_CAR_CURRENT_TOWN
            return 0;
        case 40: // METARULE_SKILL_CHECK_TAG
            return 0;
        case 44: // METARULE_GET_WORLDMAP_XPOS
            // позиция по x на карте мира
            return 300;
        case 45: // METARULE_GET_WORLDMAP_YPOS
            // позиция по y на карте мира
            return 300;
        case 46: // METARULE_CURRENT_TOWN
            // Текущий город
            return 0;

    }
    throw Exception("VM::_metarule() - unknown type: " + std::to_string(type));
}

int VM::_getMonth()
{
    return 1; // January
}

int VM::_getTime()
{
    return 1212; //12 hours 12 minutes
}

void VM::_setLightLevel(int level)
{
    CrossPlatform::debug("     Setting light level to: " + std::to_string(level), DEBUG_SCRIPT);
}

void VM::_playMovie(int movieNum)
{

}


void VM::_displayString(std::shared_ptr<std::string> str)
{
    CrossPlatform::debug(*(str.get()), DEBUG_SCRIPT);
}

void VM::_debugMessage(std::shared_ptr<std::string> str)
{
    CrossPlatform::debug(*(str.get()), DEBUG_SCRIPT);
}

int VM::_tile_num_in_direction(int start_tile, int dir, int distance)
{
    return start_tile + 20;
}

int VM::_critter_add_trait(std::shared_ptr<void> who, int trait_type, int trait, int amount)
{
    return 0;
}

void VM::_anim(std::shared_ptr<void> who, int anim, int direction)
{
}

int VM::_metarule3(int meta, std::shared_ptr<VMStackValue> p1, int p2, int p3)
{
    switch(meta)
    {
        case 100: // rm_fixed_timer_event
            return 0;
        case 110:   // unknown
            return 0;
    }
    throw Exception("VM::_metarule3() - unknown meta: " + std::to_string(meta));

}

std::string VM::msgMessage(int msg_file_num, int msg_num)
{
    auto lst = ResourceManager::lstFileType("data/dialogs.lst");
    auto msg = ResourceManager::msgFileType("text/english/dialog/" + lst->strings()->at(msg_file_num - 1));
    return msg->message(msg_num)->text();
}

std::shared_ptr<libfalltergeist::IntFileType> VM::script()
{
    return _script;
}

unsigned int VM::programCounter()
{
    return _programCounter;
}

void VM::setProgramCounter(unsigned int value)
{
    _programCounter = value;
}

VMStack* VM::dataStack()
{
    return &_dataStack;
}

VMStack* VM::returnStack()
{
    return &_returnStack;
}

}





