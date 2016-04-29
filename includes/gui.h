#ifndef GUI_H
#define GUI_H

#include <OGRE/Ogre.h>
#include <OGRE/OgreRectangle2D.h>
#include <OGRE/OgreSceneManager.h>
#include "ogretext.h"

class Gui {
 public:
  Gui();
  void Create_Window();
  void Render();
  void Init_Scene();
  void SetBackground();
  void SetText();

 private:
  Ogre::Root *_Root;
  Ogre::RenderWindow *_Win;
  Ogre::SceneManager *_Scene;
  Ogre::Viewport *_Viewport;
  std::vector<Ogre::OgreText *> _vText;
};

#endif  // GUI_H
