/*
 * Manager.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#pragma once

class Engine;

class Manager
{
public:
	Engine *engine;

    explicit Manager(Engine *eng) :
        engine(eng) {}
    virtual ~Manager() {}

	virtual void tick(float dt) = 0;
	virtual void init() = 0;
	virtual void loadLevel() = 0;
	virtual void stop() = 0;
};
