#ifndef GUI_H
#define GUI_H

#include <irrlicht.h>
#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Gui {
 public:
  Gui(int Height = 720, int Width = 1280, int Ddp = 32, bool Fullscreen = false,
      bool Vsync = true);
  bool CreateWindow();
  bool WindowIsOpen();
  bool SetBackground();
  bool Load();
  ~Gui();

 private:
  irr::IrrlichtDevice *_Device;
  irr::video::IVideoDriver* _Driver;
  irr::video::ITexture* _Back;
  irr::scene::ISceneManager* _Smgr;
  irr::gui::IGUIEnvironment* _Guienv;
  irr::gui::IGUIFont *_MainFont;

  int _Height;
  int _Width;
  int _Ddp;
  bool _isFullscreen;
  bool _VSync;
};

#endif  // GUI_H
