/*
 *  The Mana World
 *  Copyright 2004 The Mana World Development Team
 *
 *  This file is part of The Mana World.
 *
 *  The Mana World is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  any later version.
 *
 *  The Mana World is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with The Mana World; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 *  $Id$
 */

#ifndef _TMW_SPRITESET_H
#define _TMW_SPRITESET_H

#include <vector>

#include "resource.h"

class Image;


/**
 * Stores a complete set of sprites.
 */
class Spriteset : public Resource
{
    public:
        /*
         * Cuts the passed image in a grid of sub images.
         */
        Spriteset(const std::string& idPath, Image *img, int w, int h);

        /**
         * Destructor.
         */
        ~Spriteset();

        int getWidth() { return mWidth; };

        int getHeight() { return mHeight; };

        typedef std::vector<Image*>::size_type size_type;
        Image* get(size_type i);

        size_type size() { return mSpriteset.size(); }

    private:
        // Vector storing the whole spriteset.
        std::vector<Image*> mSpriteset;
        // Height and width of the images in the spriteset
        int mHeight;
        int mWidth;
};

#endif