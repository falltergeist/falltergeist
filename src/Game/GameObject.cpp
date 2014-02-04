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
 *
 */

// C++ standard includes

// Falltergeist includes
#include "../Engine/InteractiveSurface.h"
#include "../Engine/Animation.h"
#include "../Game/GameObject.h"
#include "../Game/GameDefines.h"
#include "../Engine/Exception.h"

// Third party includes

namespace Falltergeist
{

GameObject::GameObject()
{
}

GameObject::~GameObject()
{
}

int GameObject::type()
{
    return _type;
}

int GameObject::subtype()
{
    return _subtype;
}

int GameObject::PID()
{
    return _PID;
}

void GameObject::setPID(int value)
{
    _PID = value;
}

int GameObject::FID()
{
    return _FID;
}

void GameObject::setFID(int value)
{
    _FID = value;
}

int GameObject::position()
{
    return _position;
}

void GameObject::setPosition(int value)
{
    _position = value;
}

int GameObject::elevation()
{
    return _elevation;
}

void GameObject::setElevation(int value)
{
    if (value < 0 || value > 3)
    {
        throw Exception("GameObject::setElevation() - value out of range: " + std::to_string(value));
    }
    _elevation = value;
}

int GameObject::orientation()
{    
    return _orientation;
}

void GameObject::setOrientation(int value)
{
    if (value < 0 || value > 5)
    {
        throw Exception("GameObject::setOrientation() - value out of range: " + std::to_string(value));
    }
    _orientation = value;
    animationQueue()->clear();
    delete _surface; _surface = 0;

    auto frm = ResourceManager::frmFileType(FID());
    if (frm)
    {
        auto id = PID() & 0x00000FFF;
        auto type = (PID() & 0x0F000000) >> 24;
        if (type == 5 && id == 12) // Map scroll blockers
        {
            return;
            //frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
        }
        if (type == 5 && id >= 16 && id <= 23) // exit tiles
        {
            frm = ResourceManager::frmFileType("art/intrface/msef001.frm");
        }

        if (frm->framesPerDirection() > 1)
        {
            auto animation = new Animation(frm);
            animation->setCurrentSurfaceSet(this->orientation());
            this->animationQueue()->add(animation);
        }
        else
        {
            auto surface = new InteractiveSurface(frm, this->orientation());
            this->setSurface(surface);
        }
    }
}

std::string GameObject::name()
{
    return _name;
}

void GameObject::setName(std::string value)
{
    _name = value;
}

std::string GameObject::description()
{
    return _description;
}

void GameObject::setDescription(std::string value)
{
    _description = value;
}

std::vector<VM*>* GameObject::scripts()
{
    return &_scripts;
}

Location* GameObject::location()
{
    return _location;
}

void GameObject::setLocation(Location* value)
{
    _location = value;
}

AnimationQueue* GameObject::animationQueue()
{
    return &_animationQueue;
}

InteractiveSurface* GameObject::surface()
{
    if (!_surface)
    {
        if (_animationQueue.queue()->size() > 0)
        {
            return (InteractiveSurface*)_animationQueue.animation();
        }
    }
    return _surface;
}

void GameObject::setSurface(InteractiveSurface* surface)
{
    _surface = surface;
}

}
