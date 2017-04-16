/*
 * Entity381.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "Entity381.h"
#include "Aspect.h"

Entity381::Entity381(EntityType entType, Ogre::Vector3 pos, float heading)
{
	this->aspects_.clear();
}

void Entity381::tick(float dt)
{
    for(const auto& aspect : aspects_)
    {
        aspect->tick(dt);
    }
}
