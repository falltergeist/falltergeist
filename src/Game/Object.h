/*
 * Copyright 2012-2016 Falltergeist Developers.
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
#include <memory>
#include <string>

// Falltergeist includes
#include "../Event/EventTarget.h"
#include "../Graphics/TransFlags.h"
#include "../UI/Base.h"

// Third party includes

namespace Falltergeist
{
namespace Event
{
    class Event;
}
namespace Graphics
{
    class Texture;
}
namespace UI
{
    class AnimationQueue;
    class Base;
    class Image;
    class TextArea;
}
namespace VM
{
    class Script;
}

class Hexagon;
class Location;

namespace Game
{
class CritterObject;

// represents orientation in hexagonal space
// @todo move this class to separate file!
class Orientation
{
private:
    unsigned char _dir;

public:
    enum
    {
        NS = 0, EW, NC, SC, EC, WC
    };

    Orientation(unsigned char value = NS)
    {
        *this = value;
    }

    Orientation& operator =(unsigned char value)
    {
        _dir = (unsigned char)(value % 6);
        return *this;
    }

    operator unsigned char() const { return _dir; }
};


class Object : public Event::EventTarget
{
public:
    // Object type as defined in prototype
    enum class Type
    {
        ITEM = 0,
        CRITTER,
        SCENERY,
        WALL,
        TILE,
        MISC,
        DUDE
    };


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

    // object type
    Type type() const;

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
    Orientation orientation() const;
    // changes object facing direction (0 - 5)
    virtual void setOrientation(Orientation value);

    // object name, as defined in proto msg file
    std::string name() const;
    void setName(const std::string& value);

    // object description, as defined in proto msg file
    std::string description() const;
    void setDescription(const std::string& value);

    // script entity associated with the object
    VM::Script* script() const;
    void setScript(VM::Script* script);

    /**
     * @brief Handles OS events coming from the State::handle().
     * Used in Event Capturing process.
     * This method is called first in the main loop (before think() and render()).
     */
    virtual void handle(Event::Event* event);
    /**
     * @brief Process any real-time actions of the game object (like calling critter_p_proc).
     * This method is called after handle() but before render() in the main loop.
     */
    virtual void think();
    /**
     * @brief Render this object, if it has visible UI elements.
     * This method is called last in the main loop (after handle() and think()).
     */
    virtual void render();

    /**
    * @brief Render object outline, if it has visible UI elements.
    */
    virtual void renderOutline(int type);

    /**
     * @brief Render floater text above object, if any.
     */
    virtual void renderText();

    // ActiveUI used to display object on screen and capture mouse events
    UI::Base* ui() const;
    void setUI(UI::Base* ui);

    // Hexagon of object current position
    Hexagon* hexagon() const;
    void setHexagon(Hexagon* hexagon);

    // TextArea, currently floating above the object
    UI::TextArea* floatMessage() const;
    void setFloatMessage(std::unique_ptr<UI::TextArea> floatMessage);

    // is object currently being rendered
    bool inRender() const;
    void setInRender(bool value);

    // object translucency mode
    Graphics::TransFlags::Trans trans() const;
    // sets object translucency mode
    void setTrans(Graphics::TransFlags::Trans value);

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
    // perform "use" action, may call "use_p_proc" of the underlying script
    virtual void use_p_proc(CritterObject* usedBy);
    // perform "use object on" action, may call "use_obj_on_p_proc" procedure
    virtual void use_obj_on_p_proc(Object* objectUsed, CritterObject* usedBy);

    virtual void onUseAnimationActionFrame(Event::Event* event, CritterObject* critter);
    virtual void onUseAnimationEnd(Event::Event* event, CritterObject* critter);

    unsigned short lightOrientation() const;
    virtual void setLightOrientation(Orientation orientation);

    unsigned int lightIntensity() const;
    virtual void setLightIntensity(unsigned int intensity);

    unsigned int lightRadius() const;
    virtual void setLightRadius(unsigned int radius);

    virtual void setFlags(unsigned int flags);

    bool flat() const;
    virtual void setFlat(bool value);

    unsigned int defaultFrame();
    virtual void setDefaultFrame(unsigned int frame);

protected:
    bool _canWalkThru = true;
    bool _canLightThru = false;
    bool _canShootThru = true;
    bool _wallTransEnd = false;
    bool _flat = false;
    Type _type;
    int _PID = -1;
    int _FID = -1;
    int _elevation = 0;
    Orientation _orientation;
    std::string _name;
    std::string _description;
    std::unique_ptr<VM::Script> _script;
    std::unique_ptr<UI::Base> _ui;
    Hexagon* _hexagon = nullptr;
    virtual void _generateUi();
    void addUIEventHandlers();
    std::unique_ptr<UI::TextArea> _floatMessage;
    bool _inRender = false;
    Graphics::TransFlags::Trans _trans = Graphics::TransFlags::Trans::DEFAULT;
    Orientation _lightOrientation;
    unsigned int _lightIntensity = 0;
    unsigned int _lightRadius = 0;
    virtual bool _useEggTransparency();

    unsigned int _defaultFrame;

private:
    bool _isIntersectsWithEgg();

};

}
}
#endif // FALLTERGEIST_GAME_OBJECT_H
