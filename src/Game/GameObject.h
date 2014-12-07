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

#ifndef FALLTERGEIST_GAMEOBJECT_H
#define FALLTERGEIST_GAMEOBJECT_H

// C++ standard includes
#include <vector>
#include <string>
#include <memory>

// Falltergeist includes
#include "../Engine/Event/Event.h"

// Third party includes

namespace Falltergeist
{
class ActiveUI;
class AnimationQueue;
class Event;
class GameCritterObject;
class Hexagon;
class Image;
class Location;
class TextArea;
class VM;

class GameObject : public EventEmitter
{
protected:
    bool _canWalkThru = true;
    int _type = -1;
    int _subtype = -1;
    int _PID = -1;
    int _FID = -1;
    int _elevation = 0;
    int _orientation = 0;
    std::string _name;
    std::string _description;
    VM* _script = 0;
    ActiveUI* _ui = 0;
    Hexagon* _hexagon = 0;
    virtual void _generateUi();
    TextArea* _floatMessage = 0;
    bool _inRender = false;
    unsigned int _trans = 0;
public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_MISC, TYPE_DUDE };
    enum { TYPE_ITEM_ARMOR = 0, TYPE_ITEM_CONTAINER, TYPE_ITEM_DRUG, TYPE_ITEM_WEAPON, TYPE_ITEM_AMMO, TYPE_ITEM_MISC, TYPE_ITEM_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIRS, TYPE_SCENERY_ELEVATOR, TYPE_SCENERY_LADDER, TYPE_SCENERY_GENERIC };
    enum { TRANS_NONE = 0, TRANS_WALL, TRANS_GLASS, TRANS_STEAM, TRANS_ENERGY, TRANS_RED };

    GameObject();
    virtual ~GameObject();

    bool canWalkThru();
    virtual void setCanWalkThru(bool value);

    int type();
    int subtype();

    int PID();
    void setPID(int value);

    int FID();
    virtual void setFID(int value);

    int elevation();
    void setElevation(int value);

    int orientation();
    virtual void setOrientation(int value);

    std::string name();
    void setName(std::string value);

    std::string description();
    void setDescription(std::string value);

    VM* script();
    void setScript(VM* script);

    virtual void render();
    virtual void think();
    virtual void handle(Event* event);

    ActiveUI* ui();
    void setUI(ActiveUI* ui);

    Hexagon* hexagon();
    void setHexagon(Hexagon* hexagon);

    TextArea* floatMessage();
    void setFloatMessage(TextArea* floatMessage);

    void setInRender(bool value);
    bool inRender();

    void setTrans(unsigned int value);
    unsigned int trans();

    virtual void description_p_proc();
    virtual void destroy_p_proc();
    virtual void look_at_p_proc();
    virtual void map_enter_p_proc();
    virtual void map_exit_p_proc();
    virtual void map_update_p_proc();
    virtual void pickup_p_proc();
    virtual void spatial_p_proc();
    virtual void use_p_proc();
    virtual void use_obj_on_p_proc();

    virtual void onUseAnimationActionFrame(Event* event, GameCritterObject* critter);
    virtual void onUseAnimationEnd(Event* event, GameCritterObject* critter);
};

}
#endif // FALLTERGEIST_GAMEOBJECT_H
