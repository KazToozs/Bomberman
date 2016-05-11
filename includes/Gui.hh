#ifndef GUI_H
#define GUI_H

#include <irrlicht.h>
#include <vector>
#include <thread>
#include <mutex>
#include "ControlEventReceiver.hh"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class Gui {
 public:
  Gui(int Height = 720, int Width = 1280, int Ddp = 32, bool Fullscreen = false,
      bool Vsync = true);

  bool Start();
  bool Alive() const;
  const irr::SEvent::SJoystickEvent& get_joy_event() const;
  const std::vector<irr::SEvent::SKeyInput>& get_key_event() const;

  ~Gui();

 private:
  void InitJoystick();
  bool CreateWindow();
  bool WindowIsOpen();
  void Load();
  void LoadModels();

  void MovePlayer(int);
  bool DrawScene();
  void StartLoop();

  irr::IrrlichtDevice* _Device;
  irr::video::IVideoDriver* _Driver;
  irr::scene::ISceneManager* _Smgr;
  irr::gui::IGUIEnvironment* _Guienv;
  irr::gui::IGUIFont* _MainFont;
  std::vector<std::vector<irr::scene::ISceneNode *>> _PlayerModels;
  std::vector<std::vector<int>> _Maps;

  ControlEventReceiver _Event;
  std::thread* _Th;
  std::mutex* _Mtx;
  int _Height;
  int _Width;
  int _Ddp;
  bool _isFullscreen;
  bool _VSync;
  bool _Run;
};

#endif  // GUI_H
