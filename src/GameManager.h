/*
 * gameManager.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#pragma once

#include "Manager.h"


class GameManager : public Manager
{
public:
    explicit GameManager(Engine *engine);
	~GameManager();

    void init() override;
    void tick(float dt) override;
    void loadLevel() override;
    void stop() override;
};
