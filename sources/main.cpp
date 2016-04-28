/*#include <OGRE/Ogre.h>
#include <OGRE/OgreRectangle2D.h>
#include <OGRE/OgreFrameListener.h>
#include <iostream>

#include <OGRE/OgreStringConverter.h>
*/
#include "gui.h"

Ogre::Viewport *viewport = NULL;

//

/*
class MyFrameListener : public Ogre::FrameListener {
 public:
  bool frameStarted(const Ogre::FrameEvent &evt);
  bool frameEnded(const Ogre::FrameEvent &evt);
  bool frameRenderingQueued(const Ogre::FrameEvent &evt);
};

bool MyFrameListener::frameStarted(const Ogre::FrameEvent &evt) { return true; }

bool MyFrameListener::frameEnded(const Ogre::FrameEvent &evt) { return true; }

bool MyFrameListener::frameRenderingQueued(const Ogre::FrameEvent &evt) {
  return true;
}

int main(void) {
  // Create an instance of the OGRE Root Class
  Ogre::Root *root = new Ogre::Root;

  // Configures the application
  if (!root->restoreConfig()) root->showConfigDialog();
  root->saveConfig();

  Ogre::ConfigFile cf;
  cf.load("resource.cfg");

  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();

  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements()) {
    secName = seci.peekNextKey();
    Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
    Ogre::ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i) {
      typeName = i->first;
      archName = i->second;
      Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
          archName, typeName, secName);
    }
  }

  Ogre::RenderWindow *window = NULL;
  if (root->restoreConfig() || root->showConfigDialog()) {
    window = root->initialise(true, "Indie Game : Bomberman");
  } else {
    return false;
  }
  Ogre::SceneManager *sceneManager = root->createSceneManager(Ogre::ST_GENERIC);
  sceneManager->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f));

  Ogre::Camera *camera = sceneManager->createCamera("Camera");
  camera->setPosition(Ogre::Vector3(0, 0, 90));
  camera->lookAt(Ogre::Vector3(0, 0, 0));
  camera->setNearClipDistance(5);

  Ogre::Light *light1 = sceneManager->createLight("Light1");
  light1->setType(Ogre::Light::LT_POINT);
  light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
  light1->setSpecularColour(1.0f, 0.0f, 0.0f);
  light1->setAttenuation(10, 0.5, 0.045, 0.0);

  Ogre::MaterialPtr material =
      Ogre::MaterialManager::getSingleton().create("Background", "General");
  material->getTechnique(0)->getPass(0)->createTextureUnitState("bg.tga");
  material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
  material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
  material->getTechnique(0)->getPass(0)->setLightingEnabled(false);

  Ogre::Rectangle2D *rect = new Ogre::Rectangle2D(true);
  rect->setCorners(-1.0, 1.0, 1.0, -1.0, true);
  rect->setMaterial("Background");

  rect->setRenderQueueGroup(Ogre::RENDER_QUEUE_BACKGROUND);

  Ogre::AxisAlignedBox aabInf;
  aabInf.setInfinite();
  rect->setBoundingBox(aabInf);

  Ogre::SceneNode *node =
      sceneManager->getRootSceneNode()->createChildSceneNode("Background");
  node->attachObject(rect);

  Ogre::Entity *ogreEntity = sceneManager->createEntity("ogrehead.mesh");

  Ogre::SceneNode *lightNode = sceneManager->createSceneNode("LightNode");
  lightNode->attachObject(light1);
  lightNode->setScale(0.01f, 0.01f, 0.01f);
  lightNode->setPosition(0, 0, 40);

  sceneManager->getRootSceneNode()->addChild(lightNode);
  Ogre::SceneNode *ogreNode =
      sceneManager->getRootSceneNode()->createChildSceneNode();
  // ogreNode->attachObject(ogreEntity);

  viewport = window->addViewport(camera);
  viewport->setBackgroundColour(Ogre::ColourValue(1.0, 1.0, 1.0));

  camera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) /
                         Ogre::Real(viewport->getActualHeight()));

  //  MyFrameListener *myListener = new MyFrameListener();
  //  root->addFrameListener(myListener);

  // Tell root to start rendering
  root->startRendering();

  // Cleanup
  // delete myListener;
  delete root;

  return 0;
}*/

int main() {
    Gui g;
}
