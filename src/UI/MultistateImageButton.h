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

#ifndef FALLTERGEIST_MULTISTATEIMAGEBUTTON_H
#define	FALLTERGEIST_MULTISTATEIMAGEBUTTON_H

// C++ standard includes
#include <vector>

// Falltergeist includes
#include "../Engine/ActiveUI.h"
#include "../UI/ImageList.h"
// Third party includes

namespace Falltergeist
{
class ImageList;
class Image;

class MultistateImageButton : public ActiveUI
{
protected:
    ImageList _imageList;
    unsigned int _currentState = 0;
    int _mode = MODE_CYCLIC;
    int _modeFactor = 1; // or -1
    unsigned int _maxState = 0;
    unsigned int _minState = 0;
    void _onLeftButtonClick(std::shared_ptr<MouseEvent> event);
public:
    enum {MODE_PROGRESSION = 1, MODE_CYCLIC};
    enum {TYPE_BIG_SWITCH = 1, TYPE_SMALL_SWITCH};
    MultistateImageButton(int x = 0, int y = 0);
    MultistateImageButton(unsigned int type, int x = 0, int y = 0);
    MultistateImageButton(std::shared_ptr<ImageList> imageList, int x = 0, int y = 0);
    virtual ~MultistateImageButton();
    void addImage(std::shared_ptr<Image> image);
    unsigned int state();
    void setState(unsigned int state);
    unsigned int minState();
    void setMinState(unsigned int value);
    unsigned int maxState();
    void setMaxState(unsigned int value);
    void setMode(int mode);    
    int mode();
    void setModeFactor(int factor);
    int modeFactor();
    virtual std::shared_ptr<Texture> texture();
};

}
#endif	/* FALLTERGEIST_MULTISTATEIMAGEBUTTON_H */

