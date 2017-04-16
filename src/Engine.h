/*
 * engine.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#pragma once

#include "GraphicsManager.h"
#include "InputManager.h"
#include "EntityManager.h"
#include "GameManager.h"

class Engine
{
public:
	Engine();
	~Engine();


	EntityManager*      entityManager;
	GraphicsManager*    graphicsManager;
	InputManager*       inputManager;
	GameManager*        gameManager;

	void initialize();
	void run() const;
	void tick_all(float dt) const;
	void stop();
	void shutdown() const;

	bool keepRunning;
};
