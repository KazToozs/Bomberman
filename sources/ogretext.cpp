#include "ogretext.h"

Ogre::OgreText::OgreText() {
  olm = OverlayManager::getSingletonPtr();
  if (init == 0) {
    panel = static_cast<OverlayContainer *>(
        olm->createOverlayElement("Panel", "GUI"));
    panel->setMetricsMode(Ogre::GMM_PIXELS);
    panel->setPosition(0, 0);
    panel->setDimensions(1.0f, 1.0f);
    overlay = olm->create("GUI_OVERLAY");
    overlay->add2D(panel);
  }
  ++(this->init);
  szElement = "element_" + StringConverter::toString(init);
  overlay = olm->getByName("GUI_OVERLAY");
  panel = static_cast<OverlayContainer *>(olm->getOverlayElement("GUI"));
  textArea = static_cast<TextAreaOverlayElement *>(
      olm->createOverlayElement("TextArea", szElement));
  panel->addChild(textArea);
  overlay->show();
}

Ogre::OgreText::~OgreText() {
  szElement = "element_" + StringConverter::toString(init);
  olm->destroyOverlayElement(szElement);
  --(this->init);
  if (init == 0) {
    olm->destroyOverlayElement("GUI");
    olm->destroy("GUI_OVERLAY");
  }
}

void Ogre::OgreText::setText(char *szString) {
  textArea->setCaption(szString);
  textArea->setDimensions(1.0f, 1.0f);
  textArea->setMetricsMode(Ogre::GMM_RELATIVE);
  textArea->setFontName("BlueHighway");
  textArea->setCharHeight(0.03f);
}

void Ogre::OgreText::setText(String szString) {
  textArea->setCaption(szString);
  textArea->setDimensions(1.0f, 1.0f);
  textArea->setMetricsMode(Ogre::GMM_RELATIVE);
  textArea->setFontName("BlueHighway");
  textArea->setCharHeight(0.03f);
}

void Ogre::OgreText::setPos(float x, float y) { textArea->setPosition(x, y); }

void Ogre::OgreText::setCol(float R, float G, float B, float I) {
  textArea->setColour(Ogre::ColourValue(R, G, B, I));
}

void Ogre::OgreText::setSize(float charSize) {
    textArea->setCharHeight(charSize);
}
