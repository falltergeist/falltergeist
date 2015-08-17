/*
 * Copyright 2012-2015 Falltergeist Developers.
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

#ifndef FALLTERGEIST_GAME_OBJECT_H
#define FALLTERGEIST_GAME_OBJECT_H

// C++ standard includes
#include <cmath>
#include <memory>
#include <string>
#include <vector>

// Falltergeist includes
#include "../Event/Emitter.h"

// Third party includes

namespace Falltergeist
{
class ActiveUI;
class AnimationQueue;
namespace Event
{
    class Event;
}
class Hexagon;
class Image;
class Location;
class TextArea;
class VM;
class Texture;

namespace Game
{
class CritterObject;

class Object : public Event::Emitter
{
public:
    enum { TYPE_ITEM = 0, TYPE_CRITTER, TYPE_SCENERY, TYPE_WALL, TYPE_TILE, TYPE_MISC, TYPE_DUDE };
    enum { TYPE_ITEM_ARMOR = 0, TYPE_ITEM_CONTAINER, TYPE_ITEM_DRUG, TYPE_ITEM_WEAPON, TYPE_ITEM_AMMO, TYPE_ITEM_MISC, TYPE_ITEM_KEY };
    enum { TYPE_SCENERY_DOOR = 0, TYPE_SCENERY_STAIRS, TYPE_SCENERY_ELEVATOR, TYPE_SCENERY_LADDER, TYPE_SCENERY_GENERIC };
    enum { TRANS_DEFAULT = 0, TRANS_NONE, TRANS_WALL, TRANS_GLASS, TRANS_STEAM, TRANS_ENERGY, TRANS_RED };
    enum { ORIENTATION_NS = 0, ORIENTATION_EW, ORIENTATION_NC, ORIENTATION_SC, ORIENTATION_EC, ORIENTATION_WC };

    Object();
    ~Object() override;

    // whether this object is transparent in terms of walking through it by a critter
    virtual bool canWalkThru() const;
    virtual void setCanWalkThru(bool value);
    
    // whether this object is transparent to the light
    virtual bool canLightThru() const;
    virtual void setCanLightThru(bool value);

    // whether this object is transparent to projectiles
    virtual bool canShootThru() const;
    virtual void setCanShootThru(bool value);
    
    virtual bool wallTransEnd() const;
    virtual void setWallTransEnd(bool value);

    // object type (TYPE_ITEM, TYPE_CRITTER, etc.)
    int type() const;
    // object subtype (for items and scenery))
    int subtype() const;

    // object prototype ID - refers to numeric ID as used in original game
    int PID() const;
    void setPID(int value);

    // object base frame ID
    int FID() const;
    virtual void setFID(int value);

    // object current elevation index on the map (0-based)
    int elevation() const;
    void setElevation(int value);

    // returns facing direction (0 - 5)
    int orientation() const;
    // changes object facing direction (0 - 5)
    virtual void setOrientation(int value);

    // object name, as defined in proto msg file
    std::string name() const;
    void setName(const std::string& value);

    // object description, as defined in proto msg file
    std::string description() const;
    void setDescription(const std::string& value);

    // script entity associated with the object
    VM* script() const;
    void setScript(VM* script);

    virtual void render();
    virtual void renderText();
    virtual void think();
    virtual void handle(Event::Event* event);

    // ActiveUI used to display object on screen and capture mouse events
    ActiveUI* ui() const;
    void setUI(ActiveUI* ui);

    // Hexagon of object current position
    Hexagon* hexagon() const;
    void setHexagon(Hexagon* hexagon);

    // TextArea, currently floating above the object
    TextArea* floatMessage() const;
    void setFloatMessage(TextArea* floatMessage);

    // is object currently being rendered
    bool inRender() const;
    void setInRender(bool value);

    // object translucency mode
    unsigned int trans() const;
    void setTrans(unsigned int value);

    // request description of the object to console, may call "description_p_proc" procedure of underlying script entity
    virtual void description_p_proc();
    // call "destroy_p_proc" procedure of underlying script entity (use this just before killing critter or destroying the object)
    virtual void destroy_p_proc();
    // request brief description of the object to console, may call "look_at_p_proc" of the script
    virtual void look_at_p_proc();
    // call "map_enter_p_proc" of the script entity (use this when dude travels to another map via exit grid or worldmap)
    virtual void map_enter_p_proc();
    // call "map_exit_p_proc" of the script entity (use this when dude travels out of current map via exit grid or worldmap)
    virtual void map_exit_p_proc();
    // call "map_update_p_proc" when map is updating (once every N frames, after times skip in pipboy)
    virtual void map_update_p_proc();
    // call "pickup_p_proc" of the script entity (when picking up item object)
    virtual void pickup_p_proc(CritterObject* pickedUpBy);
    virtual void spatial_p_proc();
    // perform "use" action, may call "use_p_proc" of the underlying script
    virtual void use_p_proc(CritterObject* usedBy);
    // perform "use object on" action, may call "use_obj_on_p_proc" procedure
    virtual void use_obj_on_p_proc(Object* objectUsed, CritterObject* usedBy);

    virtual void onUseAnimationActionFrame(Event::Event* event, CritterObject* critter);
    virtual void onUseAnimationEnd(Event::Event* event, CritterObject* critter);

    unsigned short lightOrientation() const;
    virtual void setLightOrientation(unsigned short orientation);

    unsigned int lightIntensity() const;
    virtual void setLightIntensity(unsigned int intensity);

    unsigned int lightRadius() const;
    virtual void setLightRadius(unsigned int radius);

    virtual void setFlags(unsigned int flags);

    bool flat() const;
    virtual void setFlat(bool value);

protected:
    bool _canWalkThru = true;
    bool _canLightThru = true;
    bool _canShootThru = true;
    bool _wallTransEnd = false;
    bool _flat = false;
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
    void addUIEventHandlers();
    TextArea* _floatMessage = 0;
    bool _inRender = false;
    unsigned int _trans = 0;
    unsigned short _lightOrientation;
    bool _transparent = false;
    Texture* _tmptex = NULL;
    unsigned int _lightIntensity = 0;
    unsigned int _lightRadius = 0;
};

}
}
#endif // FALLTERGEIST_GAME_OBJECT_H
