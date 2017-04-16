/*
 * graphicsManager.cpp
 *
 *  Created on: Mar 9, 2017
 *      Author: sushil
 */

#include "GraphicsManager.h"
#include "Engine.h"
GraphicsManager::GraphicsManager(Engine *eng): Manager(eng) {

#ifdef _DEBUG
	resources = "resources_d.cfg";
	plugins   = "plugins_d.cfg";
#else
	resources = "resources.cfg";
	plugins   = "plugins.cfg";
#endif

	ogreRoot = new Ogre::Root(plugins);

	cf.load(resources);
	loadConfig(cf);
	configureRenderSystem();
	ogreRenderWindow = ogreRoot->initialise(true, "Matthew Berger - CS381 Game Engine");
	createSceneManager();
	initResources();
	createCamera();
	createViewport();

    raySceneQuery = ogreSceneManager->createRayQuery(Ogre::Ray());

}

void GraphicsManager::loadConfig(Ogre::ConfigFile cf) const
{
	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();
	while(secIt.hasMoreElements()){
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;
		for(it = settings->begin(); it != settings->end(); ++it){
			locType = it->first;
			name = it->second;
			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
}

void GraphicsManager::configureRenderSystem() const
{
	if(!(ogreRoot->restoreConfig() || ogreRoot->showConfigDialog()))
		engine->stop();
}

void GraphicsManager::initResources(){
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void GraphicsManager::createSceneManager(){
	ogreSceneManager = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
    overlaySystem = new Ogre::OverlaySystem();
    ogreSceneManager->addRenderQueueListener(overlaySystem);
}

void GraphicsManager::createCamera(){
	ogreCamera = ogreSceneManager->createCamera("MainCam");
	ogreCamera->setPosition(0, 0, 0);
	ogreCamera->setNearClipDistance(5);
	cameraNode = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
	pitchNode = cameraNode->createChildSceneNode();
	pitchNode->attachObject(ogreCamera);
	cameraNode->setPosition(0, 100, 500);
	ogreCamera->lookAt(0, 0, 0);

}

void GraphicsManager::createViewport(){
	ogreViewport = ogreRenderWindow->addViewport(ogreCamera);
	ogreViewport->setBackgroundColour(Ogre::ColourValue(0, 0, 0));
	ogreCamera->setAspectRatio(Ogre::Real(ogreViewport->getActualWidth()) /
											Ogre::Real(ogreViewport->getActualHeight()));
}

void GraphicsManager::testScene() const
{
	Ogre::Entity *ent = ogreSceneManager->createEntity("ogrehead.mesh");
	Ogre::SceneNode* node = ogreSceneManager->getRootSceneNode()->createChildSceneNode();
	node->attachObject(ent);
	ogreSceneManager->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
	Ogre::Light* light = ogreSceneManager->createLight("MainLight");
	light->setPosition(20, 80, 50);
	std::cout << "Test scene done" << std::endl;
}




GraphicsManager::~GraphicsManager() {
	delete ogreRoot; //after inputManager destructor
}

void GraphicsManager::init(){
	testScene();
}

void GraphicsManager::loadLevel(){

}


void GraphicsManager::tick(float dt){
	Ogre::WindowEventUtilities::messagePump();
	if(!ogreRoot->renderOneFrame()) engine->stop();
}

void GraphicsManager::stop(){
	ogreRoot->shutdown();
}