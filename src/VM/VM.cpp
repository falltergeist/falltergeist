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
#include "../VM/Handlers/Opcode80BBHandler.h"
#include "../VM/Handlers/Opcode80BCHandler.h"
#include "../VM/Handlers/Opcode80BDHandler.h"
#include "../VM/Handlers/Opcode80BFHandler.h"
#include "../VM/Handlers/Opcode80C1Handler.h"
#include "../VM/Handlers/Opcode80C2Handler.h"
#include "../VM/Handlers/Opcode80C3Handler.h"
#include "../VM/Handlers/Opcode80C4Handler.h"
#include "../VM/Handlers/Opcode80C5Handler.h"
#include "../VM/Handlers/Opcode80C6Handler.h"
#include "../VM/Handlers/Opcode80C7Handler.h"
#include "../VM/Handlers/Opcode80C8Handler.h"
#include "../VM/Handlers/Opcode80C9Handler.h"
#include "../VM/Handlers/Opcode80CAHandler.h"
#include "../VM/Handlers/Opcode80CBHandler.h"
#include "../VM/Handlers/Opcode80CCHandler.h"
#include "../VM/Handlers/Opcode80CEHandler.h"
#include "../VM/Handlers/Opcode80CFHandler.h"
#include "../VM/Handlers/Opcode80D0Handler.h"
#include "../VM/Handlers/Opcode80D2Handler.h"
#include "../VM/Handlers/Opcode80D3Handler.h"
#include "../VM/Handlers/Opcode80D4Handler.h"
#include "../VM/Handlers/Opcode80D5Handler.h"
#include "../VM/Handlers/Opcode80D8Handler.h"
#include "../VM/Handlers/Opcode80D9Handler.h"
#include "../VM/Handlers/Opcode80DAHandler.h"
#include "../VM/Handlers/Opcode80DCHandler.h"
#include "../VM/Handlers/Opcode80DEHandler.h"
#include "../VM/Handlers/Opcode80DFHandler.h"
#include "../VM/Handlers/Opcode80E1Handler.h"
#include "../VM/Handlers/Opcode80E3Handler.h"
#include "../VM/Handlers/Opcode80E4Handler.h"
#include "../VM/Handlers/Opcode80E5Handler.h"
#include "../VM/Handlers/Opcode80E7Handler.h"
#include "../VM/Handlers/Opcode80E8Handler.h"
#include "../VM/Handlers/Opcode80E9Handler.h"
#include "../VM/Handlers/Opcode80EAHandler.h"
#include "../VM/Handlers/Opcode80ECHandler.h"
#include "../VM/Handlers/Opcode80EFHandler.h"
#include "../VM/Handlers/Opcode80F0Handler.h"
#include "../VM/Handlers/Opcode80F1Handler.h"
#include "../VM/Handlers/Opcode80F2Handler.h"
#include "../VM/Handlers/Opcode80F3Handler.h"
#include "../VM/Handlers/Opcode80F4Handler.h"
#include "../VM/Handlers/Opcode80F6Handler.h"
#include "../VM/Handlers/Opcode80F7Handler.h"
#include "../VM/Handlers/Opcode80F9Handler.h"
#include "../VM/Handlers/Opcode80FAHandler.h"
#include "../VM/Handlers/Opcode80FBHandler.h"
#include "../VM/Handlers/Opcode80FCHandler.h"
#include "../VM/Handlers/Opcode80FFHandler.h"
#include "../VM/Handlers/Opcode8100Handler.h"
#include "../VM/Handlers/Opcode8101Handler.h"
#include "../VM/Handlers/Opcode8102Handler.h"
#include "../VM/Handlers/Opcode8105Handler.h"
#include "../VM/Handlers/Opcode8106Handler.h"
#include "../VM/Handlers/Opcode810AHandler.h"
#include "../VM/Handlers/Opcode810BHandler.h"
#include "../VM/Handlers/Opcode810CHandler.h"
#include "../VM/Handlers/Opcode810DHandler.h"
#include "../VM/Handlers/Opcode810EHandler.h"
#include "../VM/Handlers/Opcode810FHandler.h"
#include "../VM/Handlers/Opcode8113Handler.h"
#include "../VM/Handlers/Opcode8115Handler.h"
#include "../VM/Handlers/Opcode8116Handler.h"
#include "../VM/Handlers/Opcode8117Handler.h"
#include "../VM/Handlers/Opcode8118Handler.h"
#include "../VM/Handlers/Opcode8119Handler.h"
#include "../VM/Handlers/Opcode811CHandler.h"
#include "../VM/Handlers/Opcode811DHandler.h"
#include "../VM/Handlers/Opcode811EHandler.h"
#include "../VM/Handlers/Opcode8120Handler.h"
#include "../VM/Handlers/Opcode8121Handler.h"
#include "../VM/Handlers/Opcode8123Handler.h"
#include "../VM/Handlers/Opcode8126Handler.h"
#include "../VM/Handlers/Opcode8127Handler.h"
#include "../VM/Handlers/Opcode8128Handler.h"
#include "../VM/Handlers/Opcode8129Handler.h"
#include "../VM/Handlers/Opcode812DHandler.h"
#include "../VM/Handlers/Opcode812EHandler.h"
#include "../VM/Handlers/Opcode812FHandler.h"
#include "../VM/Handlers/Opcode8136Handler.h"
#include "../VM/Handlers/Opcode8137Handler.h"
#include "../VM/Handlers/Opcode813CHandler.h"
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
            case 0x80BB:
                opcodeHandler = new Opcode80BBHandler(this);
                break;
            case 0x80BC:
                opcodeHandler = new Opcode80BCHandler(this);
                break;
            case 0x80BD:
                opcodeHandler = new Opcode80BDHandler(this);
                break;
            case 0x80BF:
                opcodeHandler = new Opcode80BFHandler(this);
                break;
            case 0x80C1:
                opcodeHandler = new Opcode80C1Handler(this);
                break;
            case 0x80C2:
                opcodeHandler = new Opcode80C2Handler(this);
                break;
            case 0x80C3:
                opcodeHandler = new Opcode80C3Handler(this);
                break;
            case 0x80C4:
                opcodeHandler = new Opcode80C4Handler(this);
                break;
            case 0x80C5:
                opcodeHandler = new Opcode80C5Handler(this);
                break;
            case 0x80C6:
                opcodeHandler = new Opcode80C6Handler(this);
                break;
            case 0x80C7:
                opcodeHandler = new Opcode80C7Handler(this);
                break;
            case 0x80C8:
                opcodeHandler = new Opcode80C8Handler(this);
                break;
            case 0x80C9:
                opcodeHandler = new Opcode80C9Handler(this);
                break;
            case 0x80CA:
                opcodeHandler = new Opcode80CAHandler(this);
                break;
            case 0x80CB:
                opcodeHandler = new Opcode80CBHandler(this);
                break;
            case 0x80CC:
                opcodeHandler = new Opcode80CCHandler(this);
                break;
            case 0x80CE:
                opcodeHandler = new Opcode80CEHandler(this);
                break;
            case 0x80CF:
                opcodeHandler = new Opcode80CFHandler(this);
                break;
            case 0x80D0:
                opcodeHandler = new Opcode80D0Handler(this);
                break;
            case 0x80D2:
                opcodeHandler = new Opcode80D2Handler(this);
                break;
            case 0x80D3:
                opcodeHandler = new Opcode80D3Handler(this);
                break;
            case 0x80D4:
                opcodeHandler = new Opcode80D4Handler(this);
                break;
            case 0x80D5:
                opcodeHandler = new Opcode80D5Handler(this);
                break;
            case 0x80D8:
                opcodeHandler = new Opcode80D8Handler(this);
                break;
            case 0x80D9:
                opcodeHandler = new Opcode80D9Handler(this);
                break;
            case 0x80DA:
                opcodeHandler = new Opcode80DAHandler(this);
                break;
            case 0x80DC:
                opcodeHandler = new Opcode80DCHandler(this);
                break;
            case 0x80DE:
                opcodeHandler = new Opcode80DEHandler(this);
                break;
            case 0x80DF:
                opcodeHandler = new Opcode80DFHandler(this);
                break;
            case 0x80E1:
                opcodeHandler = new Opcode80E1Handler(this);
                break;
            case 0x80E3:
                opcodeHandler = new Opcode80E3Handler(this);
                break;
            case 0x80E4:
                opcodeHandler = new Opcode80E4Handler(this);
                break;
            case 0x80E5:
                opcodeHandler = new Opcode80E5Handler(this);
                break;
            case 0x80E7:
                opcodeHandler = new Opcode80E7Handler(this);
                break;
            case 0x80E8:
                opcodeHandler = new Opcode80E8Handler(this);
                break;
            case 0x80E9:
                opcodeHandler = new Opcode80E9Handler(this);
                break;
            case 0x80EA:
                opcodeHandler = new Opcode80EAHandler(this);
                break;
            case 0x80EC:
                opcodeHandler = new Opcode80ECHandler(this);
                break;
            case 0x80EF:
                opcodeHandler = new Opcode80EFHandler(this);
                break;
            case 0x80F0:
                opcodeHandler = new Opcode80F0Handler(this);
                break;
            case 0x80F1:
                opcodeHandler = new Opcode80F1Handler(this);
                break;
            case 0x80F2:
                opcodeHandler = new Opcode80F2Handler(this);
                break;
            case 0x80F3:
                opcodeHandler = new Opcode80F3Handler(this);
                break;
            case 0x80F4:
                opcodeHandler = new Opcode80F4Handler(this);
                break;
            case 0x80F6:
                opcodeHandler = new Opcode80F6Handler(this);
                break;
            case 0x80F7:
                opcodeHandler = new Opcode80F7Handler(this);
                break;
            case 0x80F9:
                opcodeHandler = new Opcode80F9Handler(this);
                break;
            case 0x80FA:
                opcodeHandler = new Opcode80FAHandler(this);
                break;
            case 0x80FB:
                opcodeHandler = new Opcode80FBHandler(this);
                break;
            case 0x80FC:
                opcodeHandler = new Opcode80FCHandler(this);
                break;
            case 0x80FF:
                opcodeHandler = new Opcode80FFHandler(this);
                break;
            case 0x8100:
                opcodeHandler = new Opcode8100Handler(this);
                break;
            case 0x8101:
                opcodeHandler = new Opcode8101Handler(this);
                break;
            case 0x8102:
                opcodeHandler = new Opcode8102Handler(this);
                break;
            case 0x8105:
                opcodeHandler = new Opcode8105Handler(this);
                break;
            case 0x8106:
                opcodeHandler = new Opcode8106Handler(this);
                break;
            case 0x810A:
                opcodeHandler = new Opcode810AHandler(this);
                break;
            case 0x810B:
                opcodeHandler = new Opcode810BHandler(this);
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
            case 0x810F:
                opcodeHandler = new Opcode810FHandler(this);
                break;
            case 0x8113:
                opcodeHandler = new Opcode8113Handler(this);
                break;
            case 0x8115:
                opcodeHandler = new Opcode8115Handler(this);
                break;
            case 0x8116:
                opcodeHandler = new Opcode8115Handler(this);
                break;
            case 0x8117:
                opcodeHandler = new Opcode8117Handler(this);
                break;
            case 0x8118:
                opcodeHandler = new Opcode8118Handler(this);
                break;
            case 0x8119:
                opcodeHandler = new Opcode8119Handler(this);
                break;
            case 0x811C:
                opcodeHandler = new Opcode811CHandler(this);
                break;
            case 0x811D:
                opcodeHandler = new Opcode811DHandler(this);
                break;
            case 0x811E:
                opcodeHandler = new Opcode811EHandler(this);
                break;
            case 0x8120:
                opcodeHandler = new Opcode8120Handler(this);
                break;
            case 0x8121:
                opcodeHandler = new Opcode8121Handler(this);
                break;
            case 0x8123:
                opcodeHandler = new Opcode8123Handler(this);
                break;
            case 0x8126:
                opcodeHandler = new Opcode8126Handler(this);
                break;
            case 0x8127:
                opcodeHandler = new Opcode8127Handler(this);
                break;
            case 0x8128:
                opcodeHandler = new Opcode8128Handler(this);
                break;
            case 0x8129:
                opcodeHandler = new Opcode8129Handler(this);
                break;
            case 0x812D:
                opcodeHandler = new Opcode812DHandler(this);
                break;
            case 0x812E:
                opcodeHandler = new Opcode812EHandler(this);
                break;
            case 0x812F:
                opcodeHandler = new Opcode812FHandler(this);
                break;
            case 0x8136:
                opcodeHandler = new Opcode8136Handler(this);
                break;
            case 0x8137:
                opcodeHandler = new Opcode8137Handler(this);
                break;
            case 0x813C:
                opcodeHandler = new Opcode813CHandler(this);
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
            case 0x80bb: break;
            case 0x80bc: break;
            case 0x80bd: break;
            case 0x80bf: break;
            case 0x80c1: break;
            case 0x80c2: break;
            case 0x80c3: break;
            case 0x80c4: break;
            case 0x80c5: break;
            case 0x80c6: break;
            case 0x80c7: break;
            case 0x80c8: break;
            case 0x80c9: break;
            case 0x80ca: break;
            case 0x80cb: break;
            case 0x80cc: break;
            case 0x80ce: break;
            case 0x80cf: break;
            case 0x80d0: break;
            case 0x80d2: break;
            case 0x80d3: break;
            case 0x80d4: break;
            case 0x80d5: break;
            case 0x80d8: break;
            case 0x80d9: break;
            case 0x80da: break;
            case 0x80dc: break;
            case 0x80de: break;
            case 0x80df: break;
            case 0x80e1: break;
            case 0x80e3: break;
            case 0x80e4: break;
            case 0x80e5: break;
            case 0x80e7: break;
            case 0x80e8: break;
            case 0x80e9: break;
            case 0x80ea: break;
            case 0x80ec: break;
            case 0x80ef: break;
            case 0x80f0: break;
            case 0x80f1: break;
            case 0x80f2: break;
            case 0x80f3: break;
            case 0x80f4: break;
            case 0x80f6: break;
            case 0x80f7: break;
            case 0x80f9: break;
            case 0x80fa: break;
            case 0x80fb: break;
            case 0x80fc: break;
            case 0x80ff: break;
            case 0x8100: break;
            case 0x8101: break;
            case 0x8102: break;
            case 0x8105: break;
            case 0x8106: break;
            case 0x810a: break;
            case 0x810c: break;
            case 0x810b: break;
            case 0x810d: break;
            case 0x810e: break;
            case 0x810f: break;
            case 0x8113: break;
            case 0x8115: break;
            case 0x8116: break;
            case 0x8117: break;
            case 0x8118: break;
            case 0x8119: break;
            case 0x811c: break;
            case 0x811d: break;
            case 0x811e: break;
            case 0x8120: break;
            case 0x8121: break;
            case 0x8123: break;
            case 0x8125: break;
            case 0x8126: break;
            case 0x8127: break;
            case 0x8128: break;
            case 0x8129: break;
            case 0x812d: break;
            case 0x812e: break;
            case 0x812f: break;
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
            case 0x8136: break;
            case 0x8137: break;
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
            case 0x813c: break;
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

int VM::metarule(int type, VMStackValue* value)
{
  return _metarule(type,value);
}

void VM::setLightLevel(int level)
{
    Logger::debug("SCRIPT") << "     Setting light level to: " + std::to_string(level) << std::endl;
}

void VM::_playMovie(int movieNum)
{

}

void VM::playMovie(int movieNum)
{
  _playMovie(movieNum);
}

int VM::tile_num_in_direction(int start_tile, int dir, int distance)
{
    return _tile_num_in_direction(start_tile,dir,distance);
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

int VM::critter_add_trait(void* who, int trait_type, int trait, int amount)
{
    return _critter_add_trait(who,trait_type,trait,amount);
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

int VM::metarule3(int meta, VMStackValue* p1, int p2, int p3)
{
    return _metarule3(meta,p1,p2,p3);
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

std::vector<VMStackValue*>* VM::LVARS()
{
    return &_LVARS;
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





