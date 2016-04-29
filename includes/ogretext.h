#ifndef OGRETEXT_H
#define OGRETEXT_H

#include <OGRE/OgrePrerequisites.h>
#include <OGRE/Overlay/OgreTextAreaOverlayElement.h>
#include <OGRE/OgreStringConverter.h>

namespace Ogre {

class OgreText {
 public:
  OgreText() ;
  ~OgreText() ;
  void setText(char *szString);
  void setText(String szString);
  void setPos(float x, float y);
  void setCol(float R, float G, float B, float I);
  void setSize(float charSize);

 private:
  OverlayManager *olm;
  OverlayContainer *panel;
  Overlay *overlay;
  TextAreaOverlayElement *textArea;
  static int init;
  String szElement;
};

int OgreText::init = 0;
}

#endif  // OGRETEXT_H
