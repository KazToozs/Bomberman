#ifndef GUI_H
#define GUI_H

#include <OGRE/Ogre.h>

class Gui {
 public:
  Gui();

 private:
  Ogre::Root *_Root;
  Ogre::RenderWindow *_Win;
};

#endif  // GUI_H
