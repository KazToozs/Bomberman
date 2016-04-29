#include "gui.h"

Gui::Gui() {
    _Viewport = NULL;
  _Root = new Ogre::Root("Ressources/plugins.cfg", "Ressources/ogre.cfg");

  if (!_Root->restoreConfig()) _Root->showConfigDialog();
  _Root->saveConfig();

  Ogre::ConfigFile cf;
  cf.load("Ressources/ressource.cfg");

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
  _Root->initialise(false, "Indie Game : Bomberman");
}

void Gui::Render() { _Root->startRendering(); }

void Gui::SetBackground() {
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
      _Scene->getRootSceneNode()->createChildSceneNode("Background");
  node->attachObject(rect);
}

void Gui::Create_Window() {
    Ogre::ConfigOptionMap config_map =
        _Root->getRenderSystem()->getConfigOptions();
    Ogre::String resolution_str = config_map["Video Mode"].currentValue;
    Ogre::String colourDepth =
        resolution_str.substr(resolution_str.rfind('@') + 2, 2);
    Ogre::String::size_type widthEnd = resolution_str.find(' ');
    Ogre::String::size_type heightEnd = resolution_str.find(' ', widthEnd + 3);
    int width =
        Ogre::StringConverter::parseInt(resolution_str.substr(0, widthEnd));
    int height = Ogre::StringConverter::parseInt(
        resolution_str.substr(widthEnd + 3, heightEnd));
    bool fullscreen =
        Ogre::StringConverter::parseBool(config_map["Full Screen"].currentValue);
    bool hwgamma = config_map["sRGB Gamma Conversion"].currentValue == "Yes";
    Ogre::NameValuePairList params;
    params["border"] = "fixed";
    params["colourDepth"] = colourDepth;
    params["FSAA"] = config_map["FSAA"].currentValue;
    params["FSAAHint"] = config_map["FSAAHint"].currentValue;
    params["vsync"] = config_map["vsync"].currentValue;
    params["vsyncInterval"] = config_map["vsyncInterval"].currentValue;
    params["useNVPerfHUD"] = config_map["useNVPerfHUD"].currentValue;
    params["gamma"] = Ogre::StringConverter::toString(hwgamma);
    params["monitorIndex"] = "0";
  _Win = _Root->createRenderWindow("Indie Game : Bomberman", width, height,
                                   fullscreen, &params);
}

void Gui::Init_Scene() {
  _Scene = _Root->createSceneManager(Ogre::ST_GENERIC);
  _Scene->setAmbientLight(Ogre::ColourValue(0.0f, 0.0f, 0.0f));

  Ogre::Camera *camera = _Scene->createCamera("Camera");
  camera->setPosition(Ogre::Vector3(0, 0, 90));
  camera->lookAt(Ogre::Vector3(0, 0, 0));
  camera->setNearClipDistance(5);

  Ogre::Light *light1 = _Scene->createLight("Light1");
  light1->setType(Ogre::Light::LT_POINT);
  light1->setDiffuseColour(1.0f, 1.0f, 1.0f);
  light1->setSpecularColour(1.0f, 0.0f, 0.0f);
  light1->setAttenuation(10, 0.5, 0.045, 0.0);

  Ogre::SceneNode *lightNode = _Scene->createSceneNode("LightNode");
  lightNode->attachObject(light1);
  lightNode->setScale(0.01f, 0.01f, 0.01f);
  lightNode->setPosition(0, 0, 40);

  _Scene->getRootSceneNode()->addChild(lightNode);
  Ogre::SceneNode *ogreNode =
      _Scene->getRootSceneNode()->createChildSceneNode();

  _Viewport = _Win->addViewport(camera);
  _Viewport->setBackgroundColour(Ogre::ColourValue(1.0, 1.0, 1.0));

  camera->setAspectRatio(Ogre::Real(_Viewport->getActualWidth()) /
                         Ogre::Real(_Viewport->getActualHeight()));
}

void Gui::SetText() {
    Ogre::OgreText *ogretext = new Ogre::OgreText();
    _vText.push_back(ogretext);
    ogretext->setText("Test Text");
    ogretext->setPos(10,10);
    ogretext->setCol(1,0,0,1);
    ogretext->setSize(0.20f);
}
