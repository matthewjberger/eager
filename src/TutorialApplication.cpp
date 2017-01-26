#include "TutorialApplication.h"

TutorialApplication::TutorialApplication(void)
{
}

TutorialApplication::~TutorialApplication(void)
{
}

void TutorialApplication::createScene(void)
{
  mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));

  mCamera->setPosition(0, 47, 222);

  Ogre::Light* light = mSceneMgr->createLight("MainLight");
  light->setPosition(20.0, 80.0, 50.0);

  Ogre::Entity* ogreEntity = mSceneMgr->createEntity("ogrehead.mesh");

  Ogre::SceneNode* ogreNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
  ogreNode->attachObject(ogreEntity);

  Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");

  Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(
    Ogre::Vector3(84, 48, 0));
  ogreNode2->attachObject(ogreEntity2);

  Ogre::Entity* ogreEntity3 = mSceneMgr->createEntity("ogrehead.mesh");

  Ogre::SceneNode* ogreNode3 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
  ogreNode3->setPosition(Ogre::Vector3(0, 104, 0));
  ogreNode3->setScale(2, 1.2, 1);
  ogreNode3->attachObject(ogreEntity3);

  Ogre::Entity* ogreEntity4 = mSceneMgr->createEntity("ogrehead.mesh");

  Ogre::SceneNode* ogreNode4 = mSceneMgr->getRootSceneNode()->createChildSceneNode();
  ogreNode4->setPosition(-84, 48, 0);
  ogreNode4->roll(Ogre::Degree(-90));
  ogreNode4->attachObject(ogreEntity4);

}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
    int main(int argc, char *argv[])
#endif
    {
  // Create application object
  TutorialApplication app;

  try {
      app.go();
  } catch(Ogre::Exception& e)  {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
      MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::cerr << "An exception has occurred: " <<
    e.getFullDescription().c_str() << std::endl;
#endif
  }

  return 0;
    }

#ifdef __cplusplus
}
#endif
