/*
 * inputManager.h
 *
 *  Created on: Mar 11, 2017
 *      Author: sushil
 */

#pragma once

#include <OgreWindowEventUtilities.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>
#include <SdkTrays.h>
#include "Manager.h"

class InputManager : 
public Manager,
public OIS::KeyListener,
public OIS::MouseListener,
public Ogre::WindowEventListener,
public OgreBites::SdkTrayListener,
public Ogre::FrameListener
{
protected:
    void windowResized(Ogre::RenderWindow *rw) override;
    void windowClosed(Ogre::RenderWindow *rw) override;

    bool keyPressed(const OIS::KeyEvent &arg) override;
    bool keyReleased(const OIS::KeyEvent &arg) override;
    bool mouseMoved(const OIS::MouseEvent &arg) override;
    bool mousePressed(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;
    bool mouseReleased(const OIS::MouseEvent &arg, OIS::MouseButtonID id) override;

    bool frameRenderingQueued(const Ogre::FrameEvent& evt) override;

public:
    explicit InputManager(Engine *engine);
	~InputManager(){}
	void init() override;
	void tick(float dt) override;
	void loadLevel() override;
	void stop() override;

	//OIS Input devices
	OIS::InputManager* oisInputManager;
    OIS::Mouse*        mouse;
    OIS::Keyboard*     keyboard;

    // Ogre bites
    OgreBites::SdkTrayManager* trayManager;
    OgreBites::InputContext inputContext;
};
