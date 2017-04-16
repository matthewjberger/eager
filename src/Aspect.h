/*
 * Aspect.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#pragma once

#include "Entity381.h"

class Aspect 
{
public:
    explicit Aspect(Entity381* ent);
	virtual ~Aspect();

	virtual void tick(float dt) = 0;
	Entity381 *entity;
};
