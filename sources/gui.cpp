#include "gui.h"

Gui::Gui() {
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

  Ogre::ConfigOptionMap config_map = _Root->getRenderSystem()->getConfigOptions();
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
  params["monitorIndex"] = "0";  // TEMPFIX!!!!!!!!!!
  _Root->initialise(false, "Indie Game : Bomberman");
  _Win =
      _Root->createRenderWindow("Indie Game : Bomberman", width, height, fullscreen, &params);

  _Root->startRendering();
}
