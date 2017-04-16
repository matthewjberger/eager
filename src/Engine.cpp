/*
 * engine.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#include "engine.h"
#include <OgreTimer.h>

Engine::Engine()
{
	graphicsManager = nullptr;
	inputManager = nullptr;
	entityManager = nullptr;
	gameManager = nullptr;
	keepRunning = true;
}

Engine::~Engine()
{
}

void Engine::stop()
{
	keepRunning = false;
}

void Engine::initialize()
{
    // construct
    graphicsManager = new GraphicsManager(this);
    inputManager = new InputManager(this);
    entityManager = new EntityManager(this);
    gameManager = new GameManager(this);

    // initialize
    graphicsManager->init();
    inputManager->init();
    entityManager->init();
    gameManager->init();

    // load level to play
    graphicsManager->loadLevel();
    inputManager->loadLevel();
    entityManager->loadLevel();
    gameManager->loadLevel();
}

void Engine::tick_all(float dt) const
{
    if (!keepRunning) return;
    graphicsManager->tick(dt); if (!keepRunning) return;
	inputManager->tick(dt); if (!keepRunning) return;
	entityManager->tick(dt); if (!keepRunning) return;
	gameManager->tick(dt); 
}

void Engine::shutdown() const
{
	inputManager->stop();
	graphicsManager->stop();
	entityManager->stop();
	gameManager->stop();
}

void Engine::run() const
{
	auto timer = std::unique_ptr<Ogre::Timer>(new Ogre::Timer());
	float oldTime = timer->getMilliseconds()/1000.0f;
	float newTime;
	float dt = 0.001f;
	while(keepRunning)
    {
		newTime = timer->getMilliseconds()/1000.0f;
		dt = newTime - oldTime;
		oldTime = newTime;
		tick_all(dt);
	}
	shutdown();
}
