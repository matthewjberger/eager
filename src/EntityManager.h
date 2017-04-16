/*
 * EntityManager.h
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#pragma once

#include <list>
#include "Entity381.h"
#include "Manager.h"

class Engine;

class EntityManager: public Manager
{
public:

    explicit EntityManager(Engine *eng);
	~EntityManager();

    void init() override;
    void tick(float dt) override;
    void loadLevel() override;
    void stop() override;

private:
	std::list<Entity381 *> entities_;

};
