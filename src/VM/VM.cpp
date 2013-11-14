/*
 * Copyright 2012-2013 Falltergeist Developers.
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


// Falltergeist includes
#include "../Engine/ResourceManager.h"
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Animation.h"
#include "../Engine/Location.h"
#include "../Engine/LocationObject.h"
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
#include "../VM/VM.h"
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"

// Third party includes

namespace Falltergeist
{

VM::VM(libfalltergeist::IntFileType* script, void* owner)
{
    _owner = owner;
    _script = script;
    if (!_script) throw Exception("VM::VM() - script is null");
}

VM::VM(std::string filename, void* owner)
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
        _pushDataInteger(0); // arguments counter;
        _pushReturnInteger(0); // return adrress
        std::cout << std::endl << "CALLED: " << name << " [" << _script->filename() <<  "]"<< std::endl;
        run();
        _popDataInteger(); // remove function result
        std::cout << "Function ended" << std::endl;
    }
    catch (libfalltergeist::Exception &e)
    {
        std::cout << "Function not exist: " << name << std::endl;
    }
}

void VM::initialize()
{
    if (_initialized) return;
    _programCounter = 0;   
    run();
    _popDataInteger(); // remove @start function result
}

void VM::run()
{
    while (_programCounter != _script->size())
    {
        if (_programCounter == 0 && _initialized) return;

        _script->setPosition(_programCounter);
        unsigned short opcode;
        *_script >> opcode;
        std::cout << "0x" << std::hex << _programCounter << " [" << opcode << "] ";
        switch (opcode)
        {
            case 0xC001:
            case 0x9001:
                _programCounter += 6;
                break;
            default:
                _programCounter += 2;
                break;
        }
        switch (opcode)
        {
            case 0x8002:
                std::cout << "lock" << std::endl;
                break;
            case 0x8003:
                std::cout << "unlock" << std::endl;
                break;
            case 0x8004:
            {
                std::cout << "[*] goto(addr)" << std::endl;
                _programCounter = _popDataInteger();
                break;
            }
            case 0x8005:
            {
                std::cout << "[*] call(0x";
                auto functionIndex = _popDataInteger();
                std::cout << std::hex << functionIndex << ") = 0x";
                _programCounter = _script->function(functionIndex);
                std::cout << _programCounter << std::endl;
                break;
            }
            case 0x800c:
            {
                std::cout << "[*] pop_r => push_d" << std::endl;
                _dataStack.push(_returnStack.pop());
                break;
            }
            case 0x800d:
            {
                std::cout << "[*] pop_d => push_r" << std::endl;
                _returnStack.push(_dataStack.pop());
                break;
            }
            case 0x8010:
            {
                std::cout << "[*] startdone" << std::endl;
                _initialized = true;
                return;
            }
            case 0x8012:
            {
                std::cout << "[*] SVAR[number];" << std::endl;
                auto number = _popDataInteger();
                _dataStack.push(_dataStack.values()->at(_SVAR_base + number));
                break;
            }
            case 0x8013:
            {
                std::cout << "[*] SVAR[num] = value" << std::endl;
                auto number = _popDataInteger();
                auto value = _dataStack.pop();
                _dataStack.values()->at(_SVAR_base + number) = value;
                break;
            }
            case 0x8014:
            {
                std::cout << "[*] getExported(name)" << std::endl;
                auto game = &Game::getInstance();
                auto EVARS = game->location()->EVARS();
                switch (_dataStack.top()->type())
                {
                    case VMStackValue::TYPE_INTEGER:
                        _dataStack.push(EVARS->at(_script->identificators()->at(_popDataInteger())));
                        break;
                    case VMStackValue::TYPE_POINTER:
                        _dataStack.push(EVARS->at(*(std::string*)_popDataPointer()));
                        break;
                    default:
                        throw Exception("VM::opcode8014 error");
                }
                break;
            }
            case 0x8015:
            {
                std::cout << "[*] export(value, name)" << std::endl;
                auto name = (std::string*)_popDataPointer();
                auto value = _dataStack.pop();
                auto game = &Game::getInstance();
                auto EVARS = game->location()->EVARS();
                EVARS->at(*name) = value;
                break;
            }
            case 0x8016:
            {
                std::cout << "[*] export(name)" << std::endl;
                auto name = (std::string*)_popDataPointer();
                auto game = &Game::getInstance();
                auto EVARS = game->location()->EVARS();
                if (EVARS->find(*name) == EVARS->end())
                {
                    EVARS->insert(std::make_pair(*name, (VMStackValue*)0));
                }
                break;
            }
            case 0x8018:
            {
                std::cout << "[*] dswap" << std::endl;
                _dataStack.swap();
                break;
            }
            case 0x8019:
            {
                std::cout << "[*] rswap" << std::endl;
                _returnStack.swap();
                break;
            }
            case 0x801a:
            {
                std::cout << "[*] pop_d" << std::endl;
                _dataStack.pop();
                break;
            }
            case 0x801b:
            {
                std::cout << "[?] dup_r" << std::endl;
                _returnStack.push(_returnStack.top());
                break;
            }
            case 0x801c:
            {
                std::cout << "[*] ret = 0x";
                _programCounter = _popReturnInteger();
                std::cout << std::hex << _programCounter << std::endl;
                break;
            }
            case 0x8027:
            {
                std::cout << "[?] unknown pop_d pop_d" << std::endl;
                delete _dataStack.pop();
                delete _dataStack.pop();
                break;
            }
            case 0x8028:
            {
                std::cout << "[?] ? lookup_string_proc(? p1)" << std::endl;
                _popDataInteger();
                _pushDataPointer(0);
                break;
            }
            case 0x8029:
            {
                std::cout << "[*] DVAR restore = ";
                _DVAR_base = _popReturnInteger();
                 std::cout << _DVAR_base << std::endl;
                break;
            }
            case 0x802a:
            {
                std::cout << "[*] DVAR clear" << std::endl;
                while (_dataStack.size() > _DVAR_base)
                {
                    delete _dataStack.pop();
                }
                break;
            }
            case 0x802b:
            {
                std::cout << "[*] set DVAR base = ";
                auto argumentsCounter = _popDataInteger();
                _pushReturnInteger(_DVAR_base);
                _DVAR_base = _dataStack.size() - argumentsCounter;
                std::cout << _DVAR_base << std::endl;
                break;
            }
            case 0x802c:
            {
                std::cout << "[*] set SVAR_base = ";
                _SVAR_base = _dataStack.size();
                std::cout << _SVAR_base << std::endl;
                break;
            }
            case 0x802f:
            {
                std::cout << "[*] ifthen(address, condition)" << std::endl;
                auto condition = _popDataLogical();
                auto address = _popDataInteger();
                if (condition)
                {
                    _programCounter = address;
                }
                break;
            }
            case 0x8030:
            {
                std::cout << "[*] while(address, condition)" << std::endl;
                auto condition = _popDataLogical();
                if (condition)
                {
                    _programCounter = _popDataInteger();
                }
                break;
            }
            case 0x8031:
            {
                std::cout << "[*] DVAR[num] = value ";
                auto num = _popDataInteger();
                auto value = _dataStack.pop();
                std::cout << "num = " << std::hex << num << " type = " << value->type() << std::endl;
                _dataStack.values()->at(_DVAR_base + num) = value;
                break;
            }
            case 0x8032:
            {
                std::cout << "[*] DVAR[num] ";
                auto num = _popDataInteger();
                auto value = _dataStack.values()->at(_DVAR_base + num);
                _dataStack.push(value);
                std::cout << "num = " << std::hex << num << " type = " << value->type() << std::endl;
                break;
            }
            case 0x8033:
            {
                std::cout << "[*] eq ==" << std::endl;
                switch (_dataStack.top()->type())
                {
                    case VMStackValue::TYPE_INTEGER:
                    {
                        auto p2 = _popDataInteger();
                        switch (_dataStack.top()->type())
                        {
                            case VMStackValue::TYPE_INTEGER:
                            {
                                auto p1 = _popDataInteger();
                                _pushDataInteger(p1 == p2 ? 0 : 1);
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT:
                            {
                                auto p1 = _popDataFloat();
                                _pushDataInteger(p1 == p2 ? 0 : 1);
                                break;
                            }
                            case VMStackValue::TYPE_POINTER:
                            {
                                auto p1 = (int)(bool)_popDataPointer();
                                _pushDataInteger(p1 == p2 ? 0 : 1);
                                break;
                            }
                        }
                        break;
                    }
                    case VMStackValue::TYPE_POINTER:
                    {
                        auto p2 = _popDataPointer();
                        auto p1 = _popDataPointer();
                        _pushDataInteger(p1 == p2 ? 0 : 1);
                        break;
                    }
                    case VMStackValue::TYPE_FLOAT:
                    {
                        auto p2 = _popDataFloat();
                        auto p1 = _popDataFloat();
                        _pushDataInteger(p1 == p2 ? 0 : 1);
                        break;
                    }
                }
                break;
            }
            case 0x8034:
            {
                std::cout << "[*] neq !=" << std::endl;
                switch (_dataStack.top()->type())
                {
                    case VMStackValue::TYPE_INTEGER:
                    {
                        auto p2 = _popDataInteger();
                        if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER) // to check if the pointer is null
                        {
                            auto p1 = (int)(bool)_popDataPointer();
                            _pushDataInteger(p1 != p2 ? 0 : 1);
                        }
                        else
                        {
                            auto p1 = _popDataInteger();
                            _pushDataInteger(p1 != p2 ? 0 : 1);
                        }
                        break;
                    }
                    case VMStackValue::TYPE_POINTER:
                    {
                        auto p2 = (int)(bool)_popDataPointer();
                        if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER) // to check if the pointer is null
                        {
                            auto p1 = (int)(bool)_popDataPointer();
                            _pushDataInteger(p1 != p2 ? 0 : 1);
                        }
                        else
                        {
                            auto p1 = _popDataInteger();
                            _pushDataInteger(p1 != p2 ? 0 : 1);
                        }
                        break;
                    }
                    case VMStackValue::TYPE_FLOAT:
                    {
                        auto p2 = _popDataFloat();
                        auto p1 = _popDataFloat();
                        _pushDataInteger(p1 != p2 ? 0 : 1);
                        break;
                    }
                }
                break;
            }
            case 0x8035:
            {
                std::cout << "[*] leq <=" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a <= b ? 0 : 1);
                break;
            }
            case 0x8036:
            {
                std::cout << "[*] geq >=" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a >= b ? 0 : 1);
                break;
            }
            case 0x8037:
            {
                std::cout << "[*] lt <" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a < b ? 0 : 1);
                break;
            }
            case 0x8038:
            {
                std::cout << "[*] gt >" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a > b ? 0 : 1);
                break;
            }
            case 0x8039:
            {
                std::cout << "[*] plus +" << std::endl;
                auto b = _dataStack.top();
                switch (b->type())
                {                    
                    case VMStackValue::TYPE_POINTER: // STRING
                    {
                        auto p2 = (std::string*)_popDataPointer();
                        auto a = _dataStack.top();
                        switch(a->type())
                        {
                            case VMStackValue::TYPE_POINTER: // STRING + STRING
                            {
                                auto p1 = (std::string*)_popDataPointer();
                                _pushDataPointer(new std::string((p1 == 0 ? "" : *p1) + (p2 == 0 ? "" : *p2)));
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
                        auto p2 = _popDataInteger();
                        auto a = _dataStack.top();
                        switch(a->type())
                        {
                            case VMStackValue::TYPE_INTEGER: // INTEGER + INTEGER
                            {
                                auto p1 = _popDataInteger();
                                _pushDataInteger(p1 + p2);
                                break;
                            }
                            case VMStackValue::TYPE_FLOAT: // FLOAT + INTEGER
                            {
                                auto p1 = _popDataFloat();
                                _pushDataFloat(p1 + p2);
                                break;
                            }
                            case VMStackValue::TYPE_POINTER: // STRING + INTEGER
                            {
                                auto p1 = (std::string*)_popDataPointer();
                                _pushDataPointer(new std::string((p1 == 0 ? "" : *p1) + std::to_string(p2)));
                                break;
                            }
                        }
                        break;
                    }
                    case VMStackValue::TYPE_FLOAT: // FLOAT
                    {
                        auto p2 = _popDataFloat();
                        auto a = _dataStack.top();
                        switch(a->type())
                        {
                            case VMStackValue::TYPE_INTEGER: // INTEGER + FLOAT
                            {
                                auto p1 = _popDataInteger();
                                _pushDataFloat(p1 + p2);

                                break;
                            }
                            case VMStackValue::TYPE_FLOAT: // FLOAT + FLOAT
                            {
                                auto p1 = _popDataFloat();
                                _pushDataFloat(p1 + p2);
                                break;
                            }
                            case VMStackValue::TYPE_POINTER: // STRING + FLOAT
                            {
                                auto p1 = (std::string*)_popDataPointer();
                                _pushDataPointer(new std::string((p1 == 0 ? "" : *p1) + std::to_string(p2)));
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
                std::cout << "[*] minus -" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a-b);
                break;
            }
            case 0x803b:
            {
                std::cout << "[*] mult *" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a*b);
                break;
            }
            case 0x803c:
            {
                std::cout << "[*] div /" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a/b);
                break;
            }
            case 0x803d:
            {
                std::cout << "[*] mod %" << std::endl;
                auto b = _dataStack.pop();
                auto a = _dataStack.pop();
                auto p1 = dynamic_cast<VMStackIntValue*>(a);
                auto p2 = dynamic_cast<VMStackIntValue*>(b);
                _pushDataInteger(p1->value()%p2->value());
                break;
            }
            case 0x803e:
            {
                std::cout << "[*] &&" << std::endl;
                auto b = _popDataLogical();
                auto a = _popDataLogical();
                _pushDataInteger(a && b);
                break;
            }
            case 0x803f:
            {
                std::cout << "[+] ||" << std::endl;
                auto b = _popDataLogical();
                auto a = _popDataLogical();
                _pushDataInteger(a || b);
                break;
            }
            case 0x8040:
            {
                std::cout << "[*] &" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a & b);
                break;
            }
            case 0x8041:
            {
                std::cout << "[*] |" << std::endl;
                auto b = _popDataInteger();
                auto a = _popDataInteger();
                _pushDataInteger(a | b);
                break;
            }
            case 0x8045:
            {
                std::cout << "[*] !" << std::endl;
                auto a = _popDataLogical();
                _pushDataInteger(!a);
                break;
            }
            case 0x8046:
            {
                std::cout << "[*] - value (change sign)" << std::endl;
                auto value = _popDataInteger();
                _pushDataInteger(-value);
                break;
            }
            case 0x80a1:
            {
                std::cout << "[+] void giveExpPoints(int points)" << std::endl;
                auto points = _popDataInteger();
                auto game = &Game::getInstance();
                game->location()->player()->setExperience(game->location()->player()->experience() + points);
                break;
            }
            case 0x80a3:
            {
                std::cout << "[=] void play_sfx(string* p1)" << std::endl;
                _popDataPointer();
                break;
            }
            case 0x80a4:
            {
                std::cout << "[=] char* obj_name(void* what)" << std::endl;
                _popDataPointer();
                _pushDataPointer((void*)new std::string("object name"));
                break;
            }
            case 0x80a6:
            {
                std::cout << "[=] int SkillPoints(int PCStatNum)" << std::endl;
                _popDataInteger();
                _pushDataInteger(0);
                break;
            }
            case 0x80a7:
            {
                std::cout << "[+] GameObject* tile_contains_pid_obj(int position, int elevation, int PID)" << std::endl;
                auto PID = _popDataInteger();
                auto elevation = _popDataInteger();
                auto position = _popDataInteger();
                auto game = &Game::getInstance();
                GameObject* found = 0;
                for (auto object : *game->location()->objects())
                {
                    if (object->PID() == PID && object->elevation() == elevation && object->position() == position)
                    {
                        found = object;
                    }
                }
                _pushDataPointer(found);
                break;
            }
            case 0x80a8:
            {
                std::cout << "[=] void set_map_start(int x, int y, int elev, int rot)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                break;
            }
            case 0x80a9:
            {
                std::cout << "[+] void override_map_start(int x, int y, int elevation, int orientation)" << std::endl;
                auto orientation = _popDataInteger();
                auto elevation = _popDataInteger();
                auto y = _popDataInteger();
                auto x = _popDataInteger();                
                auto position = y*200 + x;
                auto game = &Game::getInstance();
                auto player = game->location()->player();
                player->setPosition(position);
                player->setOrientation(orientation);
                player->setElevation(elevation);
                break;
            }
            case 0x80aa:
            {
                std::cout << "[+] int get_skill(GameCritterObject* who, int number) " << std::endl;
                int number = _popDataInteger();
                if (number > 17) throw Exception("VM::opcode80AA - number out of range: " + std::to_string(number));
                auto object = dynamic_cast<GameCritterObject*>((GameObject*)_popDataPointer());
                if (!object) throw Exception("VM::opcode80AA pointer error");
                _pushDataInteger(object->skill(number));
                break;
            }
            case 0x80ab:
            {
                std::cout << "[=] int using_skill(GameCritterObject* who, int skill)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x80ac:
            {
                std::cout << "[=] int roll_vs_skill(ObjectPtr who, int skill, int modifier)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                _pushDataInteger(2);
                break;
            }
            case 0x80ae:
            {
                std::cout << "[=] int do_check(ObjectPtr who, int check, int modifier)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                _pushDataInteger(2);
                break;
            }
            case 0x80af:
            {
                std::cout << "[*] int is_success(int val)" << std::endl;
                auto value = _popDataInteger();
                if (value == 2 || value == 3)
                {
                    _pushDataInteger(1); // true;
                }
                else
                {
                    _pushDataInteger(0);
                }
                break;
            }
            case 0x80b0:
            {
                std::cout << "[*] int is_critical(int val)" << std::endl;
                auto value = _popDataInteger();
                if (value == 0 || value == 3)
                {
                    _pushDataInteger(1);
                }
                else
                {
                    _pushDataInteger(0);
                }
                break;
            }
            case 0x80b2:
            {
                std::cout << "[=] void mark_area_known(int AREA_MARK_TYPE, int AreaNum, int MARK_STATE);" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                break;
            }
            case 0x80b4:
            {
                std::cout << "[+] int rand(int min, int max)" << std::endl;
                auto max = _popDataInteger();
                auto min = _popDataInteger();
                srand(time(0));
                _pushDataInteger(rand()%(max - min + 1) + min);
                break;
            }
            case 0x80b6:
            {
                std::cout << "[+] int move_to(GameObject* object, int position, int elevation)" << std::endl;
                auto elevation = _popDataInteger();
                auto position = _popDataInteger();
                auto object = (GameObject*)_popDataPointer();
                object->setPosition(position);
                object->setElevation(elevation);
                _pushDataInteger(1);
                break;
            }
            case 0x80b7:
            {
                std::cout << "[+] GameObject* create_object_sid(int PID, int position, int elevation, int SID)" << std::endl;
                auto SID = _popDataInteger();
                auto elevation = _popDataInteger();
                auto position = _popDataInteger();
                auto PID = _popDataInteger();
                auto object = Location::createObject(PID);
                object->setPosition(position);
                object->setElevation(elevation);
                if (SID > 0)
                {
                    auto intFile = ResourceManager::intFileType(SID);
                    if (intFile) object->scripts()->push_back(new VM(intFile, object));
                }
                _pushDataPointer(object);
                break;
            }
            case 0x80b8:
            {
                std::cout << "[*] void display_msg(string*)" << std::endl;
                _displayString((std::string*)_popDataPointer());
                break;
            }
            case 0x80b9:
                std::cout << "script_overrides" << std::endl;
                break;
            case 0x80ba:
            {
                std::cout << "[+] int obj_is_carrying_obj_pid(GameObject* object, int PID)" << std::endl;
                auto PID = _popDataInteger();
                auto pointer = _popDataPointer();
                int amount = 0;
                if (auto critter = dynamic_cast<GameCritterObject*>((GameObject*)pointer))
                {
                    for (auto object : *critter->inventory()) if (object->PID() == PID) amount += object->amount();
                }
                else if (auto container = dynamic_cast<GameContainerItemObject*>((GameObject*)pointer))
                {
                    for (auto object : *container->inventory()) if (object->PID() == PID) amount += object->amount();
                }
                else
                {
                    throw Exception("VM::opcode80ba - unknown object type");
                }
                _pushDataInteger(amount);
                break;
            }
            case 0x80bb:
            {
                std::cout << "[+] int tile_contains_obj_pid(int position, int elevation, int PID)" << std::endl;
                auto PID = _popDataInteger();
                auto elevation = _popDataInteger();
                auto position = _popDataInteger();
                auto game = &Game::getInstance();
                int found = 0;
                for (auto object : *game->location()->objects())
                {
                    if (object->PID() == PID && object->elevation() == elevation && object->position() == position)
                    {
                        found = 1;
                    }
                }
                _pushDataInteger(found);
                break;
            }
            case 0x80bc:
            {
                std::cout << "[+] GameObject* self_obj()" << std::endl;
                _pushDataPointer(_owner);
                break;
            }
            case 0x80bd:
            {
                std::cout << "[=] void* source_obj()" << std::endl;
                _pushDataPointer(0);
                break;
            }
            case 0x80bf:
            {
                std::cout << "[+] GameDudeObject* dude_obj()" << std::endl;
                auto game = &Game::getInstance();
                _pushDataPointer(game->location()->player());
                break;
            }
            case 0x80c1:
            {
                std::cout << "[*] LVAR[num]" << std::endl;
                auto num = _popDataInteger();
                auto game = &Game::getInstance();
                _pushDataInteger(game->location()->LVAR(num));
                break;
            }
            case 0x80c2:
            {
                std::cout << "[*] LVAR[num] = value" << std::endl;
                auto value = _popDataInteger();
                auto num = _popDataInteger();
                auto game = &Game::getInstance();
                game->location()->setLVAR(num, value);
                break;
            }
            case 0x80c3:
            {
                std::cout << "[?] MVAR[num]" << std::endl;
                auto num = _popDataInteger();
                if (num < 0)
                {
                    _pushDataInteger(0);
                    break;
                }
                auto game = &Game::getInstance();
                _pushDataInteger(game->location()->MVAR(num));
                break;
            }
            case 0x80c4:
            {
                std::cout << "[+] MVAR[num] = value" << std::endl;
                auto value = _popDataInteger();
                auto num = _popDataInteger();                
                auto game = &Game::getInstance();
                game->location()->setMVAR(num, value);
                break;
            }
            case 0x80c5:
            {
                std::cout << "[?] GVAR[num]" << std::endl;
                auto num = _popDataInteger();
                if (num < 0)
                {
                    _pushDataInteger(0);
                    break;
                }
                auto game = &Game::getInstance();
                _pushDataInteger(game->GVAR(num));
                break;
            }
            case 0x80c6:
            {
                std::cout << "[+] GVAR[num] = value" << std::endl;
                auto value = _popDataInteger();
                auto num = _popDataInteger();
                auto game = &Game::getInstance();
                game->setGVAR(num, value);
                break;
            }
            case 0x80c7:
            {
                std::cout << "[*] int script_action()" << std::endl;
                _pushDataInteger(21);
                break;
            }
            case 0x80c8:
            {
                std::cout << "[=] int obj_type(void* obj)" << std::endl;
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x80c9:
            {
                std::cout << "[+] int obj_item_subtype(GameItemObject* object)" << std::endl;
                auto pointer = _popDataPointer();
                     if (dynamic_cast<GameArmorItemObject*>((GameObject*)pointer))     _pushDataInteger(0);
                else if (dynamic_cast<GameContainerItemObject*>((GameObject*)pointer)) _pushDataInteger(1);
                else if (dynamic_cast<GameDrugItemObject*>((GameObject*)pointer))      _pushDataInteger(2);
                else if (dynamic_cast<GameWeaponItemObject*>((GameObject*)pointer))    _pushDataInteger(3);
                else if (dynamic_cast<GameAmmoItemObject*>((GameObject*)pointer))      _pushDataInteger(4);
                else if (dynamic_cast<GameMiscItemObject*>((GameObject*)pointer))      _pushDataInteger(5);
                else if (dynamic_cast<GameKeyItemObject*>((GameObject*)pointer))       _pushDataInteger(6);
                else _pushDataInteger(-1);
                break;
            }
            case 0x80ca:
            {
                std::cout << "[+] int get_critter_stat(GameCritterObject* who, int number)" << std::endl;
                int number = _popDataInteger();
                if (number > 6) throw Exception("VM::opcode80CA - number out of range:" + std::to_string(number));
                auto object = dynamic_cast<GameCritterObject*>((GameObject*)_popDataPointer());
                if (!object) throw Exception("VM::opcode80CA pointer error");
                _pushDataInteger(object->stat(number) + object->statBonus(number));
                break;
            }
            case 0x80cb:
            {
                std::cout << "[+] int set_critter_stat(GameCritterObject* who, int number, int value)" << std::endl;
                int value = _popDataInteger();
                int number = _popDataInteger();
                if (number > 6) throw Exception("VM::opcode80CB - number out of range:" + std::to_string(number));
                auto object = dynamic_cast<GameCritterObject*>((GameObject*)_popDataPointer());
                if (!object) throw Exception("VM::opcode80CB pointer error");
                object->setStat(number, value);
                if (dynamic_cast<GameDudeObject*>(object))
                {
                    _pushDataInteger(3); // for dude
                }
                else
                {
                    _pushDataInteger(-1); // for critter
                }
                break;
            }
            case 0x80cc:
            {
                std::cout << "[=] void animate_stand_obj(void* obj)" << std::endl;
                _popDataPointer();
                break;
            }
            case 0x80ce:
            {
                std::cout << "[=] void animate_move_obj_to_tile(void* who, int tile, int speed)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x80cf:
            {
                std::cout << "[=] int tile_in_tile_rect(int tile1, int tile2, int tile3, int tile4, int tile)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _pushDataInteger(0);
                break;
            }
            case 0x80d0:
            {
                std::cout << "[=] void attack_complex(ObjectPtr who, int called_shot, int num_attacks, int bonus, int min_damage, int max_damage, int attacker_results, int target_results)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x80d2:
            {
                std::cout << "[=] int tile_distance(int tile1, int tile2)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _pushDataInteger(4);
                break;
            }
            case 0x80d3:
            {
                std::cout << "int tile_distance_objs(void* p2, void* p1)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                _pushDataInteger(10);
                break;
            }
            case 0x80d4:
            {
                std::cout << "[+] int objectPosition(GameObject* object)" << std::endl;
                auto object = (GameObject*)_popDataPointer();
                _pushDataInteger(object->position());
                break;
            }
            case 0x80d5:
            {
                std::cout << "[*] int tile_num_in_direction(int start_tile, int dir, int distance)" << std::endl;
                auto distance = _popDataInteger();
                auto dir = _popDataInteger();
                auto start_tile = _popDataInteger();
                _pushDataInteger(_tile_num_in_direction(start_tile, dir, distance));
                break;
            }
            case 0x80d8:
            {
                std::cout << "[=] void add_obj_to_inven(void* who, void* item)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                break;
            }
            case 0x80d9:
            {
                std::cout << "[=] void rm_obj_from_inven(void* who, void* obj)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                break;
            }
            case 0x80da:
            {
                std::cout << "[=] void wield_obj_critter(void* who, void* obj)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                break;
            }
            case 0x80dc:
            {
                std::cout << "[=] int obj_can_see_obj(GameObject* src_obj, GameObject* dst_obj)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                _pushDataInteger(1);
                break;
            }
            case 0x80de:
            {
                std::cout << "[*] void start_gdialog(int msgFileNum, ObjectPtr who, int mood, int headNum, int backgroundIdx)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                _popDataInteger();
                break;
            }
            case 0x80df:
            {
                std::cout << "[?] end_dialogue" << std::endl;
                break;
            }
            case 0x80e1:
            {
                std::cout << "[*] int metarule3(int meta, int p1, int p2, int p3)" << std::endl;
                auto p3 = _popDataInteger();
                auto p2 = _popDataInteger();
                auto p1 = _dataStack.pop();
                auto meta = _popDataInteger();
                _pushDataInteger(_metarule3(meta, p1, p2, p3));
                break;
            }
            case 0x80e3:
            {
                std::cout << "[=] void set_obj_visibility(void* obj, int visibility)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x80e4:
            {
                std::cout << "[=] void load_map(string* map, int param)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x80e5:
            {
                std::cout << "[=] void wm_area_set_pos(int areaIdx, int xPos, int yPos)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataInteger();
                break;
            }
            case 0x80e7:
            {
                std::cout << "[=] int anim_busy(void* obj)" << std::endl;
                auto object = (GameObject*)_popDataPointer();
                _pushDataInteger(object->animationQueue()->enabled());
                break;
            }
            case 0x80e9:
            {
                std::cout << "[*] void set_light_level(int level)" << std::endl;
                auto level = _popDataInteger();
                _setLightLevel(level);
                break;
            }
            case 0x80ea:
            {
                std::cout << "[*] int gameTime()" << std::endl;
                _pushDataInteger(SDL_GetTicks() / 10);
                break;
            }
            case 0x80ec:
            {
                std::cout << "[=] int elevation(void* obj)" << std::endl;
                auto object = (GameObject*)_popDataPointer();
                _pushDataInteger(object->elevation());
                break;
            }
            case 0x80ef:
                std::cout << "void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)" << std::endl;

                break;
            case 0x80f0:
            {
                std::cout << "[=] void add_timer_event(void* obj, int time, int info)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x80f1:
            {
                std::cout << "[=] void rm_timer_event (void* obj)" << std::endl;
                _popDataPointer();
                break;
            }
            case 0x80f2:
            {
                std::cout << "[=] int game_ticks(int seconds)" << std::endl;
                auto seconds = _popDataInteger();
                _pushDataInteger(seconds*1000);
                break;
            }
            case 0x80f3:
            {
                std::cout << "[=] int has_trait(int type,void* who, int trait)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                _popDataInteger();
                _pushDataInteger(1);
                break;
            }
            case 0x80f4:
            {
                std::cout << "[=] int destroy_object(void* obj)" << std::endl;
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x80f6:
            {
                std::cout << "[*] int game_time_hour" << std::endl;
                _pushDataInteger(_getTime());
                break;
            }
            case 0x80f7:
            {
                std::cout << "[=] int fixed_param()" << std::endl;
                _pushDataInteger(1);
                break;
            }
            case 0x80f9:
            {
                std::cout << "[=] void dialogue_system_enter()" << std::endl;
                break;
            }
            case 0x80fa:
            {
                std::cout << "[=] int action_being_used()" << std::endl;
                _pushDataInteger(1);
                break;
            }
            case 0x80fb:
            {
                std::cout << "[=] int critter_state(void* who)" << std::endl;
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x80fc:
            {
                std::cout << "[=] void game_time_advance(int amount)" << std::endl;
                _popDataInteger();
                break;
            }
            case 0x80ff:
            {
                std::cout << "[*] int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)" << std::endl;
                auto elevation = _popDataInteger();
                auto position = _popDataInteger();
                auto critter = (GameCritterObject*)_popDataPointer();
                critter->setElevation(elevation);
                critter->setPosition(position);
                _pushDataInteger(1);
                break;
            }
            case 0x8100:
            {
                std::cout << "[+] int obj_pid(void* obj)" << std::endl;
                auto object = (GameObject*)_popDataPointer();
                _pushDataInteger(object->PID());
                break;
            }
            case 0x8101:
            {
                std::cout << "[=] int cur_map_index()" << std::endl;
                _pushDataInteger(3);
                break;
            }
            case 0x8102:
            {
                std::cout << "[*] int critter_add_trait(void* who, int trait_type, int trait, int amount) " << std::endl;
                auto amount = _popDataInteger();
                auto trait = _popDataInteger();
                auto trait_type = _popDataInteger();
                auto who = _popDataPointer();
                _pushDataInteger(_critter_add_trait(who, trait_type, trait, amount));
                break;
            }
            case 0x8105:
            {
                std::cout << "[+] string* msgMessage(int msg_list, int msg_num);" << std::endl;
                auto msgNum = _popDataInteger();
                auto msgList = _popDataInteger();
                auto lst = ResourceManager::lstFileType("data/dialogs.lst");
                auto msg = ResourceManager::msgFileType("text/english/dialog/" + lst->strings()->at(msgList + 1));
                _pushDataPointer(msg->message(msgNum)->textPointer());
                break;
            }
            case 0x8106:
            {
                std::cout << "[=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)" << std::endl;
                auto where = _popDataInteger();
                auto critter = dynamic_cast<GameCritterObject*>((GameObject*)_popDataPointer());
                switch (where)
                {
                    case 0: // ARMOR SLOT
                        _pushDataPointer(critter->armorSlot());
                        break;
                    case 1: // RIGHT HAND SLOT
                        _pushDataPointer(critter->rightHandSlot());
                        break;
                    case 2: // LEFT HAND SLOT
                        _pushDataPointer(critter->leftHandSlot());
                        break;
                    case -2: // INVENTORY COUNT
                        _pushDataInteger(critter->inventory()->size());
                        break;
                    default:
                        throw Exception("VM::opcode8106 error");
                }
                break;
            }
            case 0x810a:
            {
                std::cout << "[=] void float_msg(void* who, string* msg, int type) " << std::endl;
                _popDataInteger();
                delete _dataStack.pop(); // pointer or 0(integer)
                _popDataPointer();
                break;
            }
            case 0x810c:
            {
                std::cout << "[*] void anim(void* who, int anim, int direction)" << std::endl;
                auto direction = _popDataInteger();
                auto anim = _popDataInteger();
                auto who = _popDataPointer();
                _anim(who, anim, direction);
                break;
            }
            case 0x810b:
            {
                std::cout << "[*] int metarule(p2, p1)" << std::endl;
                auto p1 = _dataStack.pop();
                auto p2 = _popDataInteger();
                _pushDataInteger(_metarule(p2, p1));
                break;
            }
            case 0x810d:
            {
                std::cout << "[=] void* obj_carrying_pid_obj(void* who, int pid)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                _pushDataPointer(0);
                break;
            }
            case 0x810e:
            {
                std::cout << "[=] void reg_anim_func(int p1, int p2)" << std::endl;
                auto p2 = _dataStack.pop(); // pointer or integer
                auto p1 = _popDataInteger();
                _dataStack.push(p2);
                switch (p1)
                {
                    case 0x1: // ANIM_BEGIN
                    {
                        auto p2 = _popDataInteger();
                        // RB_UNRESERVED (1) - незарезервированная последовательность, может не воспроизвестись, если отсутствуют свободные слоты
                        // RB_RESERVED (2) - зарезервированная последовательность, должна воспроизвестись в любом случае
                        break;
                    }
                    case 0x2: // ANIM_CLEAR
                    {
                        auto object = (GameObject*)_popDataPointer();
                        object->animationQueue()->start();
                        break;
                    }
                    case 0x3: // ANIMATION_END
                    {
                        _popDataInteger(); // always 0
                        break;
                    }
                }
                break;
            }
            case 0x810f:
            {
                std::cout << "[=] void reg_anim_animate(void* what, int anim, int delay) " << std::endl;
                _popDataInteger();
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x8113:
            {
                std::cout << "[=] void reg_anim_obj_move_to_tile(void* who, int dest_tile, int delay)" << std::endl;
                _popDataInteger(); // -1
                _popDataInteger();
                _popDataPointer();
                break;
            }
            case 0x8115:
            {
                std::cout << "[*] void playMovie(movieNum)" << std::endl;
                _playMovie(_popDataInteger());
                break;
            }
            case 0x8116:
            {
                std::cout << "[+] void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)" << std::endl;
                auto amount = _popDataInteger();
                auto item =(GameItemObject*)_popDataPointer();
                if (!item) throw Exception("VM::opcode8116 - item not instanceof GameItemObject");
                item->setAmount(amount);

                // who can be critter or container
                auto pointer = _popDataPointer();
                if (auto critter = dynamic_cast<GameCritterObject*>((GameObject*)pointer))
                {
                    critter->inventory()->push_back(item);
                }
                else if (auto container = dynamic_cast<GameContainerItemObject*>((GameObject*)pointer))
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
                std::cout << "[=] int rm_mult_objs_from_inven(void* who, void* obj, int count)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x8118:
                std::cout << "[*] int get_month" << std::endl;
                _pushDataInteger(_getMonth());
                break;
            case 0x811c:
            {
                std::cout << "[?] gsay_start" << std::endl;
                break;
            }
            case 0x811d:
            {
                std::cout << "[?] gsay_end" << std::endl;
                break;
            }
            case 0x811e:
            {
                std::cout << "[=] void gSay_Reply(int msg_list, int msg_num)" << std::endl;
                _dataStack.pop(); // integer or string
                _popDataInteger();
                break;
            }
            case 0x8120:
            {
                std::cout << "[=] void gSay_Message(int msg_list, int msg_num, int reaction)" << std::endl;
                _popDataInteger();
                _dataStack.pop(); // string or integer
                _popDataInteger();
                break;
            }
            case 0x8121:
            {
                std::cout << "[=] void giQ_Option(int iq_test, int msg_list, int msg_num, procedure target, int reaction)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _dataStack.pop(); // string or integer
                _popDataInteger();
                _popDataInteger();
                break;
            }
            case 0x8123:
            {
                std::cout << "[=] int GetPoison(void* obj)" << std::endl;
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x8125:
            {
                std::cout << "[=] void party_remove(void* who)" << std::endl;
                _popDataPointer();
                break;
            }
            case 0x8126:
            {
                std::cout << "[+] void reg_anim_animate_forever(GameObject* obj , int delay)" << std::endl;
                _popDataInteger(); // delay - must be -1
                auto object = (GameObject*)_popDataPointer();
                if (object->animationQueue()->animation())
                {
                    object->animationQueue()->stop();
                    object->animationQueue()->setRepeat(-1); // forever
                    object->animationQueue()->start();
                }
                break;
            }
            case 0x8128:
            {
                std::cout << "[=] int combat_is_initialized()" << std::endl;
                _pushDataInteger(0);
                break;
            }
            case 0x8129:
            {
                std::cout << "[=] void gdialog_mod_barter(int modifier)" << std::endl;
                _popDataInteger();
                break;
            }
            case 0x812d:
            {
                std::cout << "[+] int is_locked(GameDoorSceneryObject* object)" << std::endl;
                auto object = (GameDoorSceneryObject*)_popDataPointer();
                _pushDataInteger(object->locked());
                break;
            }
            case 0x812e:
            {
                std::cout << "[+] void lock(GameDoorSceneryObject* object)" << std::endl;
                auto object = (GameDoorSceneryObject*)_popDataPointer();
                object->setLocked(true);
                break;
            }
            case 0x812f:
            {
                std::cout << "[+] void unlock(GameDoorSceneryObject* object)" << std::endl;
                auto object = (GameDoorSceneryObject*)_popDataPointer();
                object->setLocked(false);
                break;
            }
            case 0x8130:
            {
                std::cout << "[+] int is_opened(GameDoorSceneryObject* object) " << std::endl;
                auto object = (GameDoorSceneryObject*)_popDataPointer();
                _pushDataInteger(object->opened());
                break;
            }
            case 0x8131:
            {
                std::cout << "[+] void open(GameDoorSceneryObject* object) " << std::endl;
                auto object = (GameDoorSceneryObject*)_popDataPointer();
                object->setOpened(true);
                break;
            }
            case 0x8132:
            {
                std::cout << "[+] void close(GameDoorSceneryObject* object) " << std::endl;
                auto object = (GameDoorSceneryObject*)_popDataPointer();
                object->setOpened(false);
                break;
            }
            case 0x8134:
            {
                std::cout << "[=] void game_ui_enable()" << std::endl;
                break;
            }
            case 0x8136:
            {
                std::cout << "[=] void gfade_out(int time)" << std::endl;
                _popDataInteger();
                break;
            }
            case 0x8137:
            {
                std::cout << "[=] void gfade_in(int time)" << std::endl;
                _popDataInteger();
                break;
            }
            case 0x8138:
            {
                std::cout << "[=] int item_caps_total(void* obj)" << std::endl;
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x8139:
            {
                std::cout << "[=] int item_caps_adjust(void* obj, int amount)" << std::endl;
                _popDataInteger();
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x8143:
            {
                std::cout << "[=] void attack_setup(ObjectPtr who, ObjectPtr victim)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                break;
            }
            case 0x8147:
            {
                std::cout << "[=] void move_obj_inven_to_obj(void* srcObj, void* destObj)" << std::endl;
                _popDataPointer();
                _popDataPointer();
                break;
            }
            case 0x8149:
            {
                std::cout << "[+] int obj_art_fid(void* obj)" << std::endl;
                auto object = (GameObject*)_popDataPointer();
                if (!object) throw Exception("VM::opcode8149() - can't convert pointer to object");
                _pushDataInteger(object->FID());
                break;
            }
            case 0x814b:
           {
                std::cout << "[*] void* party_member_obj(int pid)" << std::endl;
                _popDataInteger();
                _pushDataPointer(0);
                break;
            }
            case 0x814c:
            {
                std::cout << "[=] int rotation_to_tile(int srcTile, int destTile)" << std::endl;
                _popDataInteger();
                _popDataInteger();
                _pushDataInteger(0);
                break;
            }
            case 0x814e:
            {
                std::cout << "[=] void gdialog_set_barter_mod(int mod)" << std::endl;
                _popDataInteger();
                break;
            }
            case 0x8150:
            {
                std::cout << "[=] int obj_on_screen(void* obj)" << std::endl;
                _popDataPointer();
                _pushDataInteger(1);
                break;
            }
            case 0x8151:
            {
                std::cout << "[=] int critter_is_fleeing(void* who)" << std::endl;
                _popDataPointer();
                _pushDataInteger(0);
                break;
            }
            case 0x8153:
            {
                std::cout << "[=] void terminate_combat()" << std::endl;
                break;
            }
            case 0x8154:
            {
                std::cout << "[*] void debug(string*)" << std::endl;
                _debugMessage((std::string*)_popDataPointer());
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
                        void* pointer = &_script->identificators()->at(value);
                        _pushDataPointer(pointer);
                        std::cout << "[*] push_d *" << pointer << std::endl;
                        break;
                    }
                    default:
                    {
                        void* pointer = &_script->strings()->at(value);
                        _pushDataPointer(pointer);
                        std::cout << "[*] push_d *" << pointer << std::endl;
                        break;
                     }
                }
                break;
            }
            case 0xC001:
            {
                unsigned int value;
                *_script >> value;
                _dataStack.push(new VMStackIntValue(value));
                std::cout << "[*] push_d 0x" << std::hex << value << std::endl;
                break;
            }
            default:
                std::cout << "0x" << std::hex << opcode << std::endl;
                throw 0;
                break;
        }

    }
}

int VM::_popDataInteger()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        auto value = stackIntValue->value();
        delete stackIntValue;
        return value;
    }
    throw Exception("VM::_popDataInteger() - stack value is not integer");
}

void VM::_pushDataInteger(int value)
{
    _dataStack.push(new VMStackIntValue(value));
}

float VM::_popDataFloat()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_FLOAT)
    {
        auto stackFloatValue = dynamic_cast<VMStackFloatValue*>(stackValue);
        auto value = stackFloatValue->value();
        delete stackFloatValue;
        return value;
    }
    throw Exception("VM::_popDataFloat() - stack value is not float");
}

void VM::_pushDataFloat(float value)
{
    _dataStack.push(new VMStackFloatValue(value));
}

void* VM::_popDataPointer()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_POINTER)
    {
        auto stackPointerValue = dynamic_cast<VMStackPointerValue*>(stackValue);
        auto value = stackPointerValue->value();
        delete stackPointerValue;
        return value;
    }
    throw Exception("VM::_popDataPointer() - stack value is not a pointer");
}

void VM::_pushDataPointer(void* value)
{
    _dataStack.push(new VMStackPointerValue(value));
}

int VM::_popReturnInteger()
{
    auto stackValue = _returnStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        auto value = stackIntValue->value();
        delete stackIntValue;
        return value;
    }
    throw Exception("VM::_popReturnInteger() - stack value is not integer");
}

void VM::_pushReturnInteger(int value)
{
    _returnStack.push(new VMStackIntValue(value));
}

bool VM::_popDataLogical()
{
    switch (_dataStack.top()->type())
    {
        case VMStackValue::TYPE_FLOAT:
            return (bool) _popDataFloat();
        case VMStackValue::TYPE_INTEGER:
            return (bool) _popDataInteger();
        case VMStackValue::TYPE_POINTER:
            return (bool) _popDataPointer();
    }
    throw Exception("VM::_popDataLogical() - something strange happened");
}

int VM::_metarule(int type, VMStackValue* value)
{
    switch(type)
    {
        case 14: // METARULE_TEST_FIRSTRUN
            // Если карта открывается в первый раз, то возвращает TRUE;
            return 0;
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
    std::cout << "     Setting light level to: " << level << std::endl;
}

void VM::_playMovie(int movieNum)
{

}


void VM::_displayString(std::string* str)
{
    std::cout << *str << std::endl;
}

void VM::_debugMessage(std::string* str)
{
    std::cout << *str << std::endl;
}

int VM::_tile_num_in_direction(int start_tile, int dir, int distance)
{
    return start_tile + 20;
}

int VM::_critter_add_trait(void* who, int trait_type, int trait, int amount)
{
    return 0;
}

void VM::_anim(void* who, int anim, int direction)
{
}

int VM::_metarule3(int meta, VMStackValue* p1, int p2, int p3)
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

}





