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
#include <ctime>
#include <sstream>

// Falltergeist includes
#include "../Engine/Exception.h"
#include "../Engine/Game.h"
#include "../Engine/Graphics/Animation.h"
#include "../Engine/Logger.h"
#include "../Engine/PathFinding/Hexagon.h"
#include "../Engine/PathFinding/HexagonGrid.h"
#include "../Engine/ResourceManager.h"
#include "../Game/GameAmmoItemObject.h"
#include "../Game/GameArmorItemObject.h"
#include "../Game/GameContainerItemObject.h"
#include "../Game/GameDefines.h"
#include "../Game/GameDoorSceneryObject.h"
#include "../Game/GameDrugItemObject.h"
#include "../Game/GameDudeObject.h"
#include "../Game/GameKeyItemObject.h"
#include "../Game/GameMiscItemObject.h"
#include "../Game/GameObject.h"
#include "../Game/GameObjectFactory.h"
#include "../Game/GameWeaponItemObject.h"
#include "../States/CritterDialogState.h"
#include "../States/LocationState.h"
#include "../VM/VM.h"
#include "../VM/VMHaltException.h"
#include "../VM/VMStackIntValue.h"
#include "../VM/VMStackFloatValue.h"
#include "../VM/VMStackPointerValue.h"
#include "../VM/Handlers/Opcode8002Handler.h"
#include "../VM/Handlers/Opcode8003Handler.h"
#include "../VM/Handlers/Opcode8004Handler.h"
#include "../VM/Handlers/Opcode8005Handler.h"
#include "../VM/Handlers/Opcode800CHandler.h"
#include "../VM/Handlers/Opcode800DHandler.h"
#include "../VM/Handlers/Opcode8010Handler.h"
#include "../VM/Handlers/Opcode8012Handler.h"
#include "../VM/Handlers/Opcode8013Handler.h"
#include "../VM/Handlers/Opcode8014Handler.h"
#include "../VM/Handlers/Opcode8015Handler.h"
#include "../VM/Handlers/Opcode8016Handler.h"
#include "../VM/Handlers/Opcode8018Handler.h"
#include "../VM/Handlers/Opcode8019Handler.h"
#include "../VM/Handlers/Opcode801AHandler.h"
#include "../VM/Handlers/Opcode801BHandler.h"
#include "../VM/Handlers/Opcode801CHandler.h"
#include "../VM/Handlers/Opcode8027Handler.h"
#include "../VM/Handlers/Opcode8028Handler.h"
#include "../VM/Handlers/Opcode8029Handler.h"
#include "../VM/Handlers/Opcode802AHandler.h"
#include "../VM/Handlers/Opcode802BHandler.h"
#include "../VM/Handlers/Opcode802CHandler.h"
#include "../VM/Handlers/Opcode802FHandler.h"
#include "../VM/Handlers/Opcode8030Handler.h"
#include "../VM/Handlers/Opcode8031Handler.h"
#include "../VM/Handlers/Opcode8032Handler.h"
#include "../VM/Handlers/Opcode8033Handler.h"
#include "../VM/Handlers/Opcode8034Handler.h"
#include "../VM/Handlers/Opcode8035Handler.h"
#include "../VM/Handlers/Opcode8036Handler.h"
#include "../VM/Handlers/Opcode8037Handler.h"
#include "../VM/Handlers/Opcode8038Handler.h"
#include "../VM/Handlers/Opcode8039Handler.h"
#include "../VM/Handlers/Opcode803AHandler.h"
#include "../VM/Handlers/Opcode803BHandler.h"
#include "../VM/Handlers/Opcode803CHandler.h"
#include "../VM/Handlers/Opcode803DHandler.h"
#include "../VM/Handlers/Opcode803EHandler.h"
#include "../VM/Handlers/Opcode803FHandler.h"
#include "../VM/Handlers/Opcode8040Handler.h"
#include "../VM/Handlers/Opcode8041Handler.h"
#include "../VM/Handlers/Opcode8045Handler.h"
#include "../VM/Handlers/Opcode8046Handler.h"
#include "../VM/Handlers/Opcode80A1Handler.h"
#include "../VM/Handlers/Opcode80A3Handler.h"
#include "../VM/Handlers/Opcode80A4Handler.h"
#include "../VM/Handlers/Opcode80A6Handler.h"
#include "../VM/Handlers/Opcode80A7Handler.h"
#include "../VM/Handlers/Opcode80A8Handler.h"
#include "../VM/Handlers/Opcode80A9Handler.h"
#include "../VM/Handlers/Opcode80AAHandler.h"
#include "../VM/Handlers/Opcode80ABHandler.h"
#include "../VM/Handlers/Opcode80ACHandler.h"
#include "../VM/Handlers/Opcode80AEHandler.h"
#include "../VM/Handlers/Opcode80AFHandler.h"
#include "../VM/Handlers/Opcode80B0Handler.h"
#include "../VM/Handlers/Opcode80B2Handler.h"
#include "../VM/Handlers/Opcode80B4Handler.h"
#include "../VM/Handlers/Opcode80B6Handler.h"
#include "../VM/Handlers/Opcode80B7Handler.h"
#include "../VM/Handlers/Opcode80B8Handler.h"
#include "../VM/Handlers/Opcode80B9Handler.h"
#include "../VM/Handlers/Opcode80BAHandler.h"
#include "../VM/Handlers/Opcode80BCHandler.h"
#include "../VM/Handlers/Opcode80CAHandler.h"
#include "../VM/Handlers/Opcode80CBHandler.h"
#include "../VM/Handlers/Opcode80DEHandler.h"
#include "../VM/Handlers/Opcode810AHandler.h"
#include "../VM/Handlers/Opcode810CHandler.h"
#include "../VM/Handlers/Opcode810DHandler.h"
#include "../VM/Handlers/Opcode810EHandler.h"
#include "../VM/Handlers/Opcode8119Handler.h"
#include "../VM/Handlers/Opcode8126Handler.h"
#include "../VM/Handlers/Opcode8127Handler.h"
#include "../VM/Handlers/Opcode9001Handler.h"
#include "../VM/Handlers/OpcodeC001Handler.h"

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

bool VM::hasFunction(std::string name)
{
    try
    {
        _script->function(name);
    }
    catch (libfalltergeist::Exception &e)
    {
        return false;
    }
    return true;
}

void VM::call(std::string name)
{
    _overrides = false;
    try
    {
        _programCounter = _script->function(name);
        pushDataInteger(0); // arguments counter;
        pushReturnInteger(0); // return adrress
        Logger::debug("SCRIPT") << "CALLED: " << name << " [" << _script->filename() << "]" << std::endl;
        run();
        popDataInteger(); // remove function result
        Logger::debug("SCRIPT") << "Function ended" << std::endl;
    }
    catch (libfalltergeist::Exception &e)
    {
        Logger::debug("SCRIPT") << "Function not exist: " << name << std::endl;
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

        OpcodeHandler* opcodeHandler = 0;
        switch (opcode)
        {
            // В этот switch нужно перенести те опкоды, которые теперь в виде класса
            // Это нужно из-за того что эти классы сами меняют программный счетчик
            // И нужно предотвратить его смену здесь в default
            case 0x8002:
                opcodeHandler = new Opcode8002Handler(this);
                break;
            case 0x8003:
                opcodeHandler = new Opcode8003Handler(this);
                break;
            case 0x8004:
                opcodeHandler = new Opcode8004Handler(this);
                break;
            case 0x8005:
                opcodeHandler = new Opcode8005Handler(this);
                break;
            case 0x800C:
                opcodeHandler = new Opcode800CHandler(this);
                break;
            case 0x800D:
                opcodeHandler = new Opcode800DHandler(this);
                break;
            case 0x8010:
                opcodeHandler = new Opcode8010Handler(this);
                break;
            case 0x8012:
                opcodeHandler = new Opcode8012Handler(this);
                break;
            case 0x8013:
                opcodeHandler = new Opcode8013Handler(this);
                break;
            case 0x8014:
                opcodeHandler = new Opcode8014Handler(this);
                break;
            case 0x8015:
                opcodeHandler = new Opcode8015Handler(this);
                break;
            case 0x8016:
                opcodeHandler = new Opcode8016Handler(this);
                break;
            case 0x8018:
                opcodeHandler = new Opcode8018Handler(this);
                break;
            case 0x8019:
                opcodeHandler = new Opcode8019Handler(this);
                break;
            case 0x801A:
                opcodeHandler = new Opcode801AHandler(this);
                break;
            case 0x801B:
                opcodeHandler = new Opcode801BHandler(this);
                break;
            case 0x801C:
                opcodeHandler = new Opcode801CHandler(this);
                break;
            case 0x8027:
                opcodeHandler = new Opcode8027Handler(this);
                break;
            case 0x8028:
                opcodeHandler = new Opcode8028Handler(this);
                break;
            case 0x8029:
                opcodeHandler = new Opcode8029Handler(this);
                break;
            case 0x802A:
                opcodeHandler = new Opcode802AHandler(this);
                break;
            case 0x802B:
                opcodeHandler = new Opcode802BHandler(this);
                break;
            case 0x802C:
                opcodeHandler = new Opcode802CHandler(this);
                break;
            case 0x802F:
                opcodeHandler = new Opcode802FHandler(this);
                break;
            case 0x8030:
                opcodeHandler = new Opcode8030Handler(this);
                break;
            case 0x8031:
                opcodeHandler = new Opcode8031Handler(this);
                break;
            case 0x8032:
                opcodeHandler = new Opcode8032Handler(this);
                break;
            case 0x8033:
                opcodeHandler = new Opcode8033Handler(this);
                break;
            case 0x8034:
                opcodeHandler = new Opcode8034Handler(this);
                break;
            case 0x8035:
                opcodeHandler = new Opcode8035Handler(this);
                break;
            case 0x8036:
                opcodeHandler = new Opcode8036Handler(this);
                break;
            case 0x8037:
                opcodeHandler = new Opcode8037Handler(this);
                break;
            case 0x8038:
                opcodeHandler = new Opcode8038Handler(this);
                break;
            case 0x8039:
                opcodeHandler = new Opcode8039Handler(this);
                break;
            case 0x803A:
                opcodeHandler = new Opcode803AHandler(this);
                break;
            case 0x803B:
                opcodeHandler = new Opcode803BHandler(this);
                break;
            case 0x803C:
                opcodeHandler = new Opcode803CHandler(this);
                break;
            case 0x803D:
                opcodeHandler = new Opcode803DHandler(this);
                break;
            case 0x803E:
                opcodeHandler = new Opcode803EHandler(this);
                break;
            case 0x803F:
                opcodeHandler = new Opcode803FHandler(this);
                break;
            case 0x8040:
                opcodeHandler = new Opcode8040Handler(this);
                break;
            case 0x8041:
                opcodeHandler = new Opcode8041Handler(this);
                break;
            case 0x8045:
                opcodeHandler = new Opcode8045Handler(this);
                break;
            case 0x8046:
                opcodeHandler = new Opcode8046Handler(this);
                break;
            case 0x80A1:
                opcodeHandler = new Opcode80A1Handler(this);
                break;
            case 0x80A3:
                opcodeHandler = new Opcode80A3Handler(this);
                break;
            case 0x80A4:
                opcodeHandler = new Opcode80A4Handler(this);
                break;
            case 0x80A6:
                opcodeHandler = new Opcode80A6Handler(this);
                break;
            case 0x80A7:
                opcodeHandler = new Opcode80A7Handler(this);
                break;
            case 0x80A8:
                opcodeHandler = new Opcode80A8Handler(this);
                break;
            case 0x80A9:
                opcodeHandler = new Opcode80A9Handler(this);
                break;
            case 0x80AA:
                opcodeHandler = new Opcode80AAHandler(this);
                break;
            case 0x80AB:
                opcodeHandler = new Opcode80ABHandler(this);
                break;
            case 0x80AC:
                opcodeHandler = new Opcode80ACHandler(this);
                break;
            case 0x80AE:
                opcodeHandler = new Opcode80AEHandler(this);
                break;
            case 0x80AF:
                opcodeHandler = new Opcode80AFHandler(this);
                break;
            case 0x80B0:
                opcodeHandler = new Opcode80B0Handler(this);
                break;
            case 0x80B2:
                opcodeHandler = new Opcode80B2Handler(this);
                break;
            case 0x80B4:
                opcodeHandler = new Opcode80B4Handler(this);
                break;
            case 0x80B6:
                opcodeHandler = new Opcode80B6Handler(this);
                break;
            case 0x80B7:
                opcodeHandler = new Opcode80B7Handler(this);
                break;
            case 0x80B8:
                opcodeHandler = new Opcode80B8Handler(this);
                break;
            case 0x80B9:
                opcodeHandler = new Opcode80B9Handler(this);
                break;
            case 0x80BA:
                opcodeHandler = new Opcode80BAHandler(this);
                break;
            case 0x80BC:
                opcodeHandler = new Opcode80BCHandler(this);
                break;
            case 0x80CA:
                opcodeHandler = new Opcode80CAHandler(this);
                break;
            case 0x80CB:
                opcodeHandler = new Opcode80CBHandler(this);
                break;
            case 0x80DE:
                opcodeHandler = new Opcode80DEHandler(this);
                break;
            case 0x810A:
                opcodeHandler = new Opcode810AHandler(this);
                break;
            case 0x810C:
                opcodeHandler = new Opcode810CHandler(this);
                break;
            case 0x810D:
                opcodeHandler = new Opcode810DHandler(this);
                break;
            case 0x810E:
                opcodeHandler = new Opcode810EHandler(this);
                break;
            case 0x8119:
                opcodeHandler = new Opcode8119Handler(this);
                break;
            case 0x8126:
                opcodeHandler = new Opcode8126Handler(this);
                break;
            case 0x8127:
                opcodeHandler = new Opcode8127Handler(this);
                break;
            case 0x9001:
                opcodeHandler = new Opcode9001Handler(this);
                break;
            case 0xC001:
                opcodeHandler = new OpcodeC001Handler(this);
                break;
            default:
                _programCounter += 2;
                break;
        }
        switch (opcode)
        {
            case 0x8002: break;
            case 0x8003: break;
            case 0x8004: break;
            case 0x8005: break;
            case 0x800c: break;
            case 0x800d: break;
            case 0x8010: break;
            case 0x8012: break;
            case 0x8013: break;
            case 0x8014: break;
            case 0x8015: break;
            case 0x8016: break;
            case 0x8018: break;
            case 0x8019: break;
            case 0x801a: break;
            case 0x801b: break;
            case 0x801c: break;
            case 0x8027: break;
            case 0x8028: break;
            case 0x8029: break;
            case 0x802a: break;
            case 0x802b: break;
            case 0x802c: break;
            case 0x802f: break;
            case 0x8030: break;
            case 0x8031: break;
            case 0x8032: break;
            case 0x8033: break;
            case 0x8034: break;
            case 0x8035: break;
            case 0x8036: break;
            case 0x8037: break;
            case 0x8038: break;
            case 0x8039: break;
            case 0x803a: break;
            case 0x803b: break;
            case 0x803c: break;
            case 0x803d: break;
            case 0x803e: break;
            case 0x803f: break;
            case 0x8040: break;
            case 0x8041: break;
            case 0x8045: break;
            case 0x8046: break;
            case 0x80a1: break;
            case 0x80a3: break;
            case 0x80a4: break;
            case 0x80a6: break;
            case 0x80a7: break;
            case 0x80a8: break;
            case 0x80a9: break;
            case 0x80aa: break;
            case 0x80ab: break;
            case 0x80ac: break;
            case 0x80ae: break;
            case 0x80af: break;
            case 0x80b0: break;
            case 0x80b2: break;
            case 0x80b4: break;
            case 0x80b6: break;
            case 0x80b7: break;
            case 0x80b8: break;
            case 0x80b9: break;
            case 0x80ba: break;
            case 0x80bb:
            {
                Logger::debug("SCRIPT") << "[80BB] [+] int tile_contains_obj_pid(int position, int elevation, int PID)" << std::endl;
                auto PID = popDataInteger();
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto game = Game::getInstance();
                int found = 0;
                for (auto object : *game->locationState()->hexagonGrid()->at(position)->objects())
                {
                    if (object->PID() == PID && object->elevation() == elevation)
                    {
                        found = 1;
                    }
                }
                pushDataInteger(found);
                break;
            }
            case 0x80bc: break;
            case 0x80bd:
            {
                Logger::debug("SCRIPT") << "[80BD] [=] void* source_obj()" << std::endl;
                pushDataPointer(0);
                break;
            }
            case 0x80bf:
            {
                Logger::debug("SCRIPT") << "[80BF] [+] GameDudeObject* dude_obj()" << std::endl;
                auto game = Game::getInstance();
                pushDataPointer(game->player());
                break;
            }
            case 0x80c1:
            {
                Logger::debug("SCRIPT") << "[80C1] [*] LVAR[num]" << std::endl;
                unsigned int num = popDataInteger();
                while (num >= _LVARS.size()) _LVARS.push_back(new VMStackIntValue(0));
                _dataStack.push(_LVARS.at(num));
                break;
            }
            case 0x80c2:
            {
                Logger::debug("SCRIPT") << "[80C2] [*] LVAR[num] = value" << std::endl;
                auto value = _dataStack.pop();
                unsigned int num = popDataInteger();
                while (num >= _LVARS.size()) _LVARS.push_back(new VMStackIntValue(0));
                _LVARS.at(num) = value;
                break;
            }
            case 0x80c3:
            {
                Logger::debug("SCRIPT") << "[80C3] [?] MVAR[num]" << std::endl;
                auto num = popDataInteger();
                if (num < 0)
                {
                    pushDataInteger(0);
                    break;
                }
                auto game = Game::getInstance();
                pushDataInteger(game->locationState()->MVAR(num));
                break;
            }
            case 0x80c4:
            {
                Logger::debug("SCRIPT") << "[80C4] [+] MVAR[num] = value" << std::endl;
                auto value = popDataInteger();
                auto num = popDataInteger();
                auto game = Game::getInstance();
                game->locationState()->setMVAR(num, value);
                break;
            }
            case 0x80c5:
            {
                auto& debug = Logger::debug("SCRIPT");
                debug << "[80C5] [?] GVAR[num]" << std::endl;
                int num = popDataInteger();
                int value;
                if (num < 0)
                {
                    value = 0;
                }
                else
                {
                    auto game = Game::getInstance();
                    value = game->GVAR(num);
                }
                pushDataInteger(value);

                debug << "    num = 0x" << std::hex << num << std::endl;
                debug << "    value = 0x" << std::hex << value << std::endl;

                break;
            }
            case 0x80c6:
            {
                Logger::debug("SCRIPT") << "[80C6] [+] GVAR[num] = value" << std::endl;
                auto value = popDataInteger();
                auto num = popDataInteger();
                auto game = Game::getInstance();
                game->setGVAR(num, value);
                break;
            }
            case 0x80c7:
            {
                Logger::debug("SCRIPT") << "[80C7] [*] int script_action()" << std::endl;
                pushDataInteger(21);
                break;
            }
            case 0x80c8:
            {
                Logger::debug("SCRIPT") << "[80C8] [=] int obj_type(void* obj)" << std::endl;
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80c9:
            {
                Logger::debug("SCRIPT") << "[80C9] [+] int obj_item_subtype(GameItemObject* object)" << std::endl;
                auto pointer = popDataPointer();
                if      (static_cast<GameArmorItemObject*>(pointer))     pushDataInteger(0);
                else if (static_cast<GameContainerItemObject*>(pointer)) pushDataInteger(1);
                else if (static_cast<GameDrugItemObject*>(pointer))      pushDataInteger(2);
                else if (static_cast<GameWeaponItemObject*>(pointer))    pushDataInteger(3);
                else if (static_cast<GameAmmoItemObject*>(pointer))      pushDataInteger(4);
                else if (static_cast<GameMiscItemObject*>(pointer))      pushDataInteger(5);
                else if (static_cast<GameKeyItemObject*>(pointer))       pushDataInteger(6);
                else pushDataInteger(-1);
                break;
            }
            case 0x80ca: break;
            case 0x80cb: break;
            case 0x80cc:
            {
                Logger::debug("SCRIPT") << "[80CC] [=] void animate_stand_obj(void* obj)" << std::endl;
                popDataPointer();
                break;
            }
            case 0x80ce:
            {
                Logger::debug("SCRIPT") << "[80CE] [=] void animate_move_obj_to_tile(void* who, int tile, int speed)" << std::endl;
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80cf:
            {
                Logger::debug("SCRIPT") << "[80CF] [=] int tile_in_tile_rect(int tile1, int tile2, int tile3, int tile4, int tile)" << std::endl;
                popDataInteger();
                popDataInteger();
                popDataInteger();
                popDataInteger();
                pushDataInteger(0);
                break;
            }
            case 0x80d0:
            {
                Logger::debug("SCRIPT") << "[80D0] [=] void attack_complex(ObjectPtr who, int called_shot, int num_attacks, int bonus"
                        ", int min_damage, int max_damage, int attacker_results, int target_results)" << std::endl;
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
                Logger::debug("SCRIPT") << "[80D2] [=] int tile_distance(int tile1, int tile2)" << std::endl;
                popDataInteger();
                popDataInteger();
                pushDataInteger(4);
                break;
            }
            case 0x80d3:
            {
                Logger::debug("SCRIPT") << "[80D3] int tile_distance_objs(void* p2, void* p1)" << std::endl;
                popDataPointer();
                popDataPointer();
                pushDataInteger(10);
                break;
            }
            case 0x80d4:
            {
                Logger::debug("SCRIPT") << "[80D4] [+] int objectPosition(GameObject* object)" << std::endl;
                auto object = static_cast<GameObject*>(popDataPointer());
                if (!object) throw new Exception("Opcode 80d4 error");
                pushDataInteger(object->hexagon()->number());
                break;
            }
            case 0x80d5:
            {
                Logger::debug("SCRIPT") << "[80D5] [*] int tile_num_in_direction(int start_tile, int dir, int distance)" << std::endl;
                auto distance = popDataInteger();
                auto dir = popDataInteger();
                auto start_tile = popDataInteger();
                pushDataInteger(_tile_num_in_direction(start_tile, dir, distance));
                break;
            }
            case 0x80d8:
            {
                Logger::debug("SCRIPT") << "[80D8] [=] void add_obj_to_inven(void* who, void* item)" << std::endl;
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x80d9:
            {
                Logger::debug("SCRIPT") << "[80D9] [=] void rm_obj_from_inven(void* who, void* obj)" << std::endl;
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x80da:
            {
                Logger::debug("SCRIPT") << "[80DA] [=] void wield_obj_critter(void* who, void* obj)" << std::endl;
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x80dc:
            {
                Logger::debug("SCRIPT") << "[80DC] [=] int obj_can_see_obj(GameObject* src_obj, GameObject* dst_obj)" << std::endl;
                popDataPointer();
                popDataPointer();
                pushDataInteger(1);
                break;
            }
            case 0x80de: break;
            case 0x80df:
            {
                Logger::debug("SCRIPT") << "[80DF] [?] end_dialogue" << std::endl;
                auto game = Game::getInstance();
                game->popState(); // interact state
                break;
            }
            case 0x80e1:
            {
                Logger::debug("SCRIPT") << "[80E1] [*] int metarule3(int meta, int p1, int p2, int p3)" << std::endl;
                auto p3 = popDataInteger();
                auto p2 = popDataInteger();
                auto p1 = _dataStack.pop();
                auto meta = popDataInteger();
                pushDataInteger(_metarule3(meta, p1, p2, p3));
                break;
            }
            case 0x80e3:
            {
                Logger::debug("SCRIPT") << "[80E3] [=] void set_obj_visibility(void* obj, int visibility)" << std::endl;
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80e4:
            {
                Logger::debug("SCRIPT") << "[80E4] [=] void load_map(string* map, int param)" << std::endl;
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80e5:
            {
                Logger::debug("SCRIPT") << "[80E5] [=] void wm_area_set_pos(int areaIdx, int xPos, int yPos)" << std::endl;
                popDataInteger();
                popDataInteger();
                popDataInteger();
                break;
            }
            case 0x80e7:
            {
                Logger::debug("SCRIPT") << "[80E7] [=] int anim_busy(void* obj)" << std::endl;
                popDataPointer();//auto object = (GameObject*)popDataPointer();
                //pushDataInteger(object->animationQueue()->enabled());
                pushDataInteger(1);
                break;
            }
            case 0x80e9:
            {
                Logger::debug("SCRIPT") << "[80E9] [*] void set_light_level(int level)" << std::endl;
                auto level = popDataInteger();
                _setLightLevel(level);
                break;
            }
            case 0x80ea:
            {
                Logger::debug("SCRIPT") << "[80EA] [*] int gameTime()" << std::endl;
                pushDataInteger(SDL_GetTicks() / 10);
                break;
            }
            case 0x80ec:
            {
                Logger::debug("SCRIPT") << "[80EC] [=] int elevation(void* obj)" << std::endl;
                auto object = static_cast<GameObject*>(popDataPointer());
                if (!object) throw new Exception("Opcode 80ec error");
                pushDataInteger(object->elevation());
                break;
            }
            case 0x80ef:
                Logger::debug("SCRIPT") << "[80EF] void critter_dmg(ObjectPtr who, int dmg_amount, int dmg_type)" << std::endl;
                break;
            case 0x80f0:
            {
                Logger::debug("SCRIPT") << "[80F0] [=] void add_timer_event(void* obj, int time, int info)" << std::endl;
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x80f1:
            {
                Logger::debug("SCRIPT") << "[80F1] [=] void rm_timer_event (void* obj)" << std::endl;
                popDataPointer();
                break;
            }
            case 0x80f2:
            {
                Logger::debug("SCRIPT") << "[80F2] [=] int game_ticks(int seconds)" << std::endl;
                auto seconds = popDataInteger();
                pushDataInteger(seconds*1000);
                break;
            }
            case 0x80f3:
            {
                Logger::debug("SCRIPT") << "[80F3] [=] int has_trait(int type,void* who, int trait)" << std::endl;
                popDataInteger();
                popDataPointer();
                popDataInteger();
                pushDataInteger(1);
                break;
            }
            case 0x80f4:
            {
                Logger::debug("SCRIPT") << "[80F4] [=] int destroy_object(void* obj)" << std::endl;
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80f6:
            {
                Logger::debug("SCRIPT") << "[80F6] [*] int game_time_hour" << std::endl;
                pushDataInteger(_getTime());
                break;
            }
            case 0x80f7:
            {
                Logger::debug("SCRIPT") << "[80F7] [=] int fixed_param()" << std::endl;
                pushDataInteger(1);
                break;
            }
            case 0x80f9:
            {
                Logger::debug("SCRIPT") << "[80F9] [=] void dialogue_system_enter()" << std::endl;
                break;
            }
            case 0x80fa:
            {
                Logger::debug("SCRIPT") << "[80FA] [=] int action_being_used()" << std::endl;
                pushDataInteger(1);
                break;
            }
            case 0x80fb:
            {
                Logger::debug("SCRIPT") << "[80FB] [=] int critter_state(void* who)" << std::endl;
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x80fc:
            {
                Logger::debug("SCRIPT") << "[80FC] [=] void game_time_advance(int amount)" << std::endl;
                popDataInteger();
                break;
            }
            case 0x80ff:
            {
                Logger::debug("SCRIPT") << "[80FF] [*] int critter_attempt_placement(GameCritterObject* critter, int position, int elevation)" << std::endl;
                auto elevation = popDataInteger();
                auto position = popDataInteger();
                auto critter = static_cast<GameCritterObject*>(popDataPointer());
                if (!critter) throw new Exception("Opcode 80ff error");
                auto hexagon = Game::getInstance()->locationState()->hexagonGrid()->at(position);
                LocationState::moveObjectToHexagon(critter, hexagon);
                critter->setElevation(elevation);
                pushDataInteger(1);
                break;
            }
            case 0x8100:
            {
                Logger::debug("SCRIPT") << "[8100] [+] int obj_pid(void* obj)" << std::endl;
                auto object = static_cast<GameObject*>(popDataPointer());
                if (!object) throw new Exception("Opcode 8100 error");
                pushDataInteger(object->PID());
                break;
            }
            case 0x8101:
            {
                Logger::debug("SCRIPT") << "[8101] [=] int cur_map_index()" << std::endl;
                pushDataInteger(3);
                break;
            }
            case 0x8102:
            {
                Logger::debug("SCRIPT") << "[8102] [*] int critter_add_trait(void* who, int trait_type, int trait, int amount) " << std::endl;
                auto amount = popDataInteger();
                auto trait = popDataInteger();
                auto trait_type = popDataInteger();
                auto who = popDataPointer();
                pushDataInteger(_critter_add_trait(who, trait_type, trait, amount));
                break;
            }
            case 0x8105:
            {
                Logger::debug("SCRIPT") << "[8105] [+] string* msgMessage(int msg_list, int msg_num);" << std::endl;
                auto msgNum = popDataInteger();
                auto msgList = popDataInteger();
                pushDataPointer(new std::string(msgMessage(msgList, msgNum)), VMStackPointerValue::POINTER_TYPE_STRING);
                break;
            }
            case 0x8106:
            {
                Logger::debug("SCRIPT") << "[8106] [=] void* (int) critter_inven_obj(GameCritterObject* critter, int where)" << std::endl;
                auto where = popDataInteger();
                auto critter = static_cast<GameCritterObject*>(popDataPointer());
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
            case 0x810a: break;
            case 0x810c: break;
            case 0x810b:
            {
                Logger::debug("SCRIPT") << "[810B] [*] int metarule(p2, p1)" << std::endl;
                auto p1 = _dataStack.pop();
                auto p2 = popDataInteger();
                pushDataInteger(_metarule(p2, p1));
                break;
            }
            case 0x810d: break;
            case 0x810e: break;
            case 0x810f:
            {
                Logger::debug("SCRIPT") << "[810F] [=] void reg_anim_animate(void* what, int anim, int delay) " << std::endl;
                popDataInteger();
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x8113:
            {
                Logger::debug("SCRIPT") << "[8113] [=] void reg_anim_obj_move_to_tile(void* who, int dest_tile, int delay)" << std::endl;
                popDataInteger(); // -1
                popDataInteger();
                popDataPointer();
                break;
            }
            case 0x8115:
            {
                Logger::debug("SCRIPT") << "[8115] [*] void playMovie(movieNum)" << std::endl;
                _playMovie(popDataInteger());
                break;
            }
            case 0x8116:
            {
                Logger::debug("SCRIPT") << "[8116] [+] void add_mult_objs_to_inven(GameObject* who, GameItemObject* item, int amount)" << std::endl;
                auto amount = popDataInteger();
                auto item = static_cast<GameItemObject*>(popDataPointer());
                if (!item) throw Exception("VM::opcode8116 - item not instanceof GameItemObject");
                item->setAmount(amount);
                // who can be critter or container
                auto pointer = static_cast<GameObject*>(popDataPointer());
                if (auto critter = dynamic_cast<GameCritterObject*>(pointer))
                {
                    critter->inventory()->push_back(item);
                }
                else if (auto container = dynamic_cast<GameContainerItemObject*>(pointer))
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
                Logger::debug("SCRIPT") << "[8117] [=] int rm_mult_objs_from_inven(void* who, void* obj, int count)" << std::endl;
                popDataInteger();
                popDataPointer();
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8118:
                Logger::debug("SCRIPT") << "[8118] [*] int get_month" << std::endl;
                pushDataInteger(_getMonth());
                break;
            case 0x8119: break;
            case 0x811c:
            {
                Logger::debug("SCRIPT") << "[811C] [?] gsay_start" << std::endl;
                auto dialog = new CritterDialogState();
                Game::getInstance()->pushState(dialog);
                break;
            }
            case 0x811d:
            {
                Logger::debug("SCRIPT") << "[811D] [?] gsay_end" << std::endl;
                auto dialog = dynamic_cast<CritterDialogState*>(Game::getInstance()->states()->back());
                if (dialog->hasAnswers())
                {
                    pushDataInteger(0);
                    return;
                }
                Game::getInstance()->popState(); // dialog state
                break;
            }
            case 0x811e:
            {
                Logger::debug("SCRIPT") << "[811E] [=] void gSay_Reply(int msg_file_num, int msg_num)" << std::endl;
                auto dialog = dynamic_cast<CritterDialogState*>(Game::getInstance()->states()->back());
                dialog->deleteAnswers();
                if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER)
                {
                    auto question = static_cast<std::string*>(popDataPointer());
                    dialog->setQuestion(*question);
                    //delete question;
                }
                else
                {
                    auto msg_num = popDataInteger();
                    auto msg_file_num = popDataInteger();
                    dialog->setQuestion(msgMessage(msg_file_num, msg_num));
                }
                break;
            }
            case 0x8120:
            {
                Logger::debug("SCRIPT") << "[8120] [=] void gSay_Message(int msg_list, int msg_num, int reaction)" << std::endl;
                popDataInteger();
                _dataStack.pop(); // string or integer
                popDataInteger();
                break;
            }
            case 0x8121:
            {
                Logger::debug("SCRIPT") << "[8121] [+] void giQ_Option(int iq_test, int msg_list, int msg_num, procedure target, int reaction)" << std::endl;

                auto reaction = popDataInteger();
                auto function = popDataInteger();
                std::string* text = 0;
                if (_dataStack.top()->type() == VMStackValue::TYPE_POINTER)
                {
                    text = static_cast<std::string*>(popDataPointer());
                    popDataInteger(); // msg_list
                }
                else
                {
                    auto msg_num = popDataInteger();
                    auto msg_file_num = popDataInteger();
                    text = new std::string(msgMessage(msg_file_num, msg_num));
                }
                auto iq = popDataInteger();
                auto game = Game::getInstance();
                auto dialog = dynamic_cast<CritterDialogState*>(game->states()->back());
                if (iq >= 0)
                {
                    if (game->player()->stat(game->player()->STATS_INTELLIGENCE) >= iq)
                    {
                        dialog->reactions()->push_back(reaction);
                        dialog->functions()->push_back(function);
                        dialog->addAnswer(*text);
                    }
                }
                if (iq < 0)
                {
                    if (game->player()->stat(game->player()->STATS_INTELLIGENCE) <= abs(iq))
                    {
                        dialog->reactions()->push_back(reaction);
                        dialog->functions()->push_back(function);
                        dialog->addAnswer(*text);
                    }
                }
                //delete text;
                break;
            }
            case 0x8123:
            {
                Logger::debug("SCRIPT") << "[8123] [=] int GetPoison(void* obj)" << std::endl;
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8125:
            {
                Logger::debug("SCRIPT") << "[8125] [=] void party_remove(void* who)" << std::endl;
                popDataPointer();
                break;
            }
            case 0x8126: break;
            case 0x8127: break;
            case 0x8128:
            {
                Logger::debug("SCRIPT") << "[8128] [=] int combat_is_initialized()" << std::endl;
                pushDataInteger(0);
                break;
            }
            case 0x8129:
            {
                Logger::debug("SCRIPT") << "[8129] [=] void gdialog_mod_barter(int modifier)" << std::endl;
                popDataInteger();
                break;
            }
            case 0x812d:
            {
                Logger::debug("SCRIPT") << "[812D] [+] int is_locked(GameDoorSceneryObject* object)" << std::endl;
                auto object = static_cast<GameDoorSceneryObject*>(popDataPointer());
                pushDataInteger(object->locked());
                break;
            }
            case 0x812e:
            {
                Logger::debug("SCRIPT") << "[812E] [+] void lock(GameDoorSceneryObject* object)" << std::endl;
                auto object = static_cast<GameDoorSceneryObject*>(popDataPointer());
                object->setLocked(true);
                break;
            }
            case 0x812f:
            {
                Logger::debug("SCRIPT") << "[812F] [+] void unlock(GameDoorSceneryObject* object)" << std::endl;
                auto object = static_cast<GameDoorSceneryObject*>(popDataPointer());
                object->setLocked(false);
                break;
            }
            case 0x8130:
            {
                Logger::debug("SCRIPT") << "[8130] [+] int is_opened(GameDoorSceneryObject* object) " << std::endl;
                auto object = static_cast<GameDoorSceneryObject*>(popDataPointer());
                pushDataInteger(object->opened());
                break;
            }
            case 0x8131:
            {
                Logger::debug("SCRIPT") << "[8131] [+] void open(GameDoorSceneryObject* object) " << std::endl;
                auto object = static_cast<GameDoorSceneryObject*>(popDataPointer());
                object->setOpened(true);
                break;
            }
            case 0x8132:
            {
                Logger::debug("SCRIPT") << "[8132] [+] void close(GameDoorSceneryObject* object) " << std::endl;
                auto object = static_cast<GameDoorSceneryObject*>(popDataPointer());
                object->setOpened(false);
                break;
            }
            case 0x8134:
            {
                Logger::debug("SCRIPT") << "[8134] [=] void game_ui_enable()" << std::endl;
                break;
            }
            case 0x8136:
            {
                Logger::debug("SCRIPT") << "[8136] [=] void gfade_out(int time)" << std::endl;
                popDataInteger();
                break;
            }
            case 0x8137:
            {
                Logger::debug("SCRIPT") << "[8137] [=] void gfade_in(int time)" << std::endl;
                popDataInteger();
                break;
            }
            case 0x8138:
            {
                Logger::debug("SCRIPT") << "[8138] [=] int item_caps_total(void* obj)" << std::endl;
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8139:
            {
                Logger::debug("SCRIPT") << "[8139] [=] int item_caps_adjust(void* obj, int amount)" << std::endl;
                popDataInteger();
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8143:
            {
                Logger::debug("SCRIPT") << "[8143] [=] void attack_setup(ObjectPtr who, ObjectPtr victim)" << std::endl;
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x8147:
            {
                Logger::debug("SCRIPT") << "[8147] [=] void move_obj_inven_to_obj(void* srcObj, void* destObj)" << std::endl;
                popDataPointer();
                popDataPointer();
                break;
            }
            case 0x8149:
            {
                Logger::debug("SCRIPT") << "[8149] [+] int obj_art_fid(void* obj)" << std::endl;
                auto object = static_cast<GameObject*>(popDataPointer());
                if (!object) throw Exception("VM::opcode8149() - can't convert pointer to object");
                pushDataInteger(object->FID());
                break;
            }
            case 0x814b:
            {
                Logger::debug("SCRIPT") << "[814B] [*] void* party_member_obj(int pid)" << std::endl;
                popDataInteger();
                pushDataPointer(0);
                break;
            }
            case 0x814c:
            {
                Logger::debug("SCRIPT") << "[814C] [=] int rotation_to_tile(int srcTile, int destTile)" << std::endl;
                popDataInteger();
                popDataInteger();
                pushDataInteger(0);
                break;
            }
            case 0x814e:
            {
                Logger::debug("SCRIPT") << "[814E] [=] void gdialog_set_barter_mod(int mod)" << std::endl;
                popDataInteger();
                break;
            }
            case 0x8150:
            {
                Logger::debug("SCRIPT") << "[8150] [=] int obj_on_screen(void* obj)" << std::endl;
                popDataPointer();
                pushDataInteger(1);
                break;
            }
            case 0x8151:
            {
                Logger::debug("SCRIPT") << "[8151] [=] int critter_is_fleeing(void* who)" << std::endl;
                popDataPointer();
                pushDataInteger(0);
                break;
            }
            case 0x8153:
            {
                Logger::debug("SCRIPT") << "[8153] [=] void terminate_combat()" << std::endl;
                break;
            }
            case 0x8154:
            {
                Logger::debug("SCRIPT") << "[8154] [*] void debug(string*)" << std::endl;
                auto string = static_cast<std::string*>(popDataPointer());
                Logger::debug("SCRIPT") << *string << std::endl;
                //delete string;
                break;
            }
            case 0x9001: break;
            case 0xC001: break;
            default:
            {
                std::ostringstream os;
                os << "0x" << std::hex << opcode;
                throw Exception("["+os.str()+"] - unimplemented opcode");
            }
        }
        if (opcodeHandler)
        {
            try
            {
                opcodeHandler->run();
            }
            catch(VMHaltException& e)
            {
                return;
            }
        }
    }
}

int VM::popDataInteger()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        auto value = stackIntValue->value();
        return value;
    }
    throw Exception("VM::popDataInteger() - stack value is not integer");
}

void VM::pushDataInteger(int value)
{
    _dataStack.push(new VMStackIntValue(value));
}

float VM::popDataFloat()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_FLOAT)
    {
        auto stackFloatValue = dynamic_cast<VMStackFloatValue*>(stackValue);
        auto value = stackFloatValue->value();
        return value;
    }
    throw Exception("VM::popDataFloat() - stack value is not float");
}

void VM::pushDataFloat(float value)
{
    _dataStack.push(new VMStackFloatValue(value));
}

void* VM::popDataPointer()
{
    auto stackValue = _dataStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_POINTER)
    {
        auto stackPointerValue = dynamic_cast<VMStackPointerValue*>(stackValue);
        auto value = stackPointerValue->value();
        return value;
    }
    throw Exception("VM::popDataPointer() - stack value is not a pointer");
}

void VM::pushDataPointer(void* value, unsigned int type)
{
    auto pointer = new VMStackPointerValue(value);
    pointer->setPointerType(type);
    _dataStack.push(pointer);
}

int VM::popReturnInteger()
{
    auto stackValue = _returnStack.pop();
    if (stackValue->type() == VMStackValue::TYPE_INTEGER)
    {
        auto stackIntValue = dynamic_cast<VMStackIntValue*>(stackValue);
        auto value = stackIntValue->value();
        return value;
    }
    throw Exception("VM::popReturnInteger() - stack value is not integer");
}

void VM::pushReturnInteger(int value)
{
    _returnStack.push(new VMStackIntValue(value));
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

int VM::_metarule(int type, VMStackValue* value)
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
    Logger::debug("SCRIPT") << "     Setting light level to: " + std::to_string(level) << std::endl;
}

void VM::_playMovie(int movieNum)
{

}


void VM::_displayString(std::string str)
{
    Logger::debug("SCRIPT") << str << std::endl;
}

int VM::_tile_num_in_direction(int start_tile, int dir, int distance)
{
    return start_tile + 20;
}

int VM::_critter_add_trait(void* who, int trait_type, int trait, int amount)
{
    return 0;
}

void VM::anim(GameCritterObject* who, int anim, int direction)
{
    throw 1;
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

std::string VM::msgMessage(int msg_file_num, int msg_num)
{
    auto lst = ResourceManager::lstFileType("data/dialogs.lst");
    auto msg = ResourceManager::msgFileType("text/english/dialog/" + lst->strings()->at(msg_file_num - 1));
    if (!msg)
    {
        Logger::debug("SCRIPT") << "VM::msgMessage(file, num) not found. file: " + std::to_string(msg_file_num) + " num: " + std::to_string(msg_num) << std::endl;
        return "";
    }
    return msg->message(msg_num)->text();
}

libfalltergeist::IntFileType* VM::script()
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

void* VM::owner()
{
    return _owner;
}

bool VM::initialized()
{
    return _initialized;
}

void VM::setInitialized(bool value)
{
    _initialized = value;
}

int VM::SVARbase()
{
    return _SVAR_base;
}

void VM::setSVARbase(int Value)
{
    _SVAR_base = Value;
}

int VM::DVARbase()
{
    return _DVAR_base;
}

void VM::setDVARBase(int Value)
{
    _DVAR_base = Value;
}

bool VM::overrides()
{
    return _overrides;
}

void VM::setOverrides(bool Value)
{
    _overrides = Value;
}

}





