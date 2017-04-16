/*
 * Entity.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#pragma once

#include <OgreVector3.h>
#include <OgreSceneNode.h>
#include "Types.h"
#include <list>

class Aspect;

class Entity381
{
public:
	Entity381(EntityType entityType, Ogre::Vector3 pos, float heading);
	~Entity381() {}

	void tick(float dt);

	EntityType type_;
	std::list<Aspect*> aspects_;
};
