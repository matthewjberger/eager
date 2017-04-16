/*
 * GxfManager.h
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#pragma once

#include "Manager.h"

#include <OgreRoot.h>
#include <OgreConfigFile.h>
#include <OgreRenderWindow.h>
#include <OgreSceneManager.h>
#include <OgreCamera.h>
#include <OgreSceneNode.h>
#include <OgreViewport.h>
#include <SdkTrays.h>

class GraphicsManager : public Manager
{

public:
    explicit GraphicsManager(Engine *eng);
	~GraphicsManager();

    void tick(float dt) override;
    void init() override;
    void loadLevel() override;
    void stop() override;

	Ogre::Root *ogreRoot;
	Ogre::RenderWindow* ogreRenderWindow;
	Ogre::SceneManager* ogreSceneManager;
	Ogre::SceneNode *cameraNode, *pitchNode;
    Ogre::OverlaySystem* overlaySystem;

	void testScene() const;

private:
	//Ogre variables
	Ogre::Camera* ogreCamera;
	Ogre::String resources;
	Ogre::String plugins;
	Ogre::ConfigFile cf;
	void loadConfig(Ogre::ConfigFile cf) const;
	void configureRenderSystem() const;
    static void initResources();

	void createSceneManager();
	void createCamera();
	Ogre::Viewport *ogreViewport;
	void createViewport();

    // Ray Casting
    Ogre::RaySceneQuery* raySceneQuery;
};
