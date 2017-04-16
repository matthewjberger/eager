/*
 * EntityManager.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: sushil
 */

#include "EntityManager.h"
#include "Engine.h"

EntityManager::EntityManager(Engine *eng): Manager(eng)
{
	entities_.clear();
}

EntityManager::~EntityManager()
{
}

void EntityManager::tick(float dt)
{
    for(const auto& entity : entities_)
    {
        entity->tick(dt);
    }
}

void EntityManager::init()
{
}

void EntityManager::loadLevel()
{
}

void EntityManager::stop()
{
}