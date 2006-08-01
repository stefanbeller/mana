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

#include "animation.h"

#include <cassert>

#include "log.h"

#include "resources/image.h"
#include "resources/resourcemanager.h"
#include "resources/spriteset.h"

Animation::Animation():
    mTime(0)
{
    iCurrentPhase = mAnimationPhases.begin();
}

void
Animation::update(unsigned int time)
{
    mTime += time;
    if (!mAnimationPhases.empty())
    {
        unsigned int delay = iCurrentPhase->delay;
        while (mTime > delay && delay > 0)
        {
            mTime -= delay;
            iCurrentPhase++;
            if (iCurrentPhase == mAnimationPhases.end())
            {
                iCurrentPhase = mAnimationPhases.begin();
            }
        }
    }
}

int
Animation::getCurrentPhase() const
{
    return mAnimationPhases.empty() ? -1 : iCurrentPhase->image;
}

void
Animation::addPhase(int image, unsigned int delay, int offsetX, int offsetY)
{
    //add new phase to animation list
    AnimationPhase newPhase = { image, delay, offsetX, offsetY };

    mAnimationPhases.push_back(newPhase);
    //reset animation circle
    iCurrentPhase = mAnimationPhases.begin();
}

int
Animation::getLength()
{
    if (mAnimationPhases.empty())
        return 0;


    std::list<AnimationPhase>::iterator i;
    int length = 0;
    for (i = mAnimationPhases.begin(); i != mAnimationPhases.end(); i++)
    {
        length += i->delay;
    }
    return length;
}

Action::Action():
    mSpriteset(NULL)
{
}

Action::~Action()
{
    for (AnimationIterator i = mAnimations.begin(); i != mAnimations.end(); i++)
    {
        delete i->second;
    }
    mAnimations.clear();
}

Animation*
Action::getAnimation(int direction) const
{
    Animations::const_iterator i = mAnimations.find(direction);

    // When the direction isn't defined, try the default
    if (i == mAnimations.end())
    {
        i = mAnimations.find(0);
    }

    return (i == mAnimations.end()) ? NULL : i->second;
}

void
Action::setAnimation(int direction, Animation *animation)
{
    // Set first direction as default direction
    if (mAnimations.empty())
    {
        mAnimations[0] = animation;
    }

    mAnimations[direction] = animation;
}