#ifndef GUI_H
#define GUI_H

#include <irrlicht.h>
#include <irrKlang.h>
#include <vector>
#include <thread>
#include <mutex>
#include "Map.hh"
#include "ControlEventReceiver.hh"
#include "Case.h"
#include "Game.hh"
#include "IPlayer.hh"
#include "Menu.hh"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrKlang.lib") // link with irrKlang.dll
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

#if defined(WIN32)
#include <conio.h>
#else
#include "conio.h"
#endif

class Menu;

class Gui {
 public:
  Gui(int Height = 720, int Width = 1280, int Ddp = 32, bool Fullscreen = false,
      bool Vsync = true);

  bool Start(Menu *menu);
  void LoadGame(Game *game);
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
  void LoadMaps();
  int check_keys();

  void ActualiseMaps();
  void UpdateBlock(int x, int y, Case type, irr::scene::ISceneNode*& old);
  void MovePlayer(int);
  void PutWall();
  bool DrawScene();
  void DrawMenu();
  void DrawSplash();
  void StartLoop();

  irr::IrrlichtDevice* _Device;
  irr::video::IVideoDriver* _Driver;
  irr::scene::ISceneManager* _Smgr;
  irr::gui::IGUIEnvironment* _Guienv;
  irr::gui::IGUIFont* _MainFont;
  irr::video::ITexture* _Back;
  irr::video::ITexture* _Splash;
  std::vector<std::vector<irr::scene::ISceneNode*>> _PlayerModels;
  std::vector<std::vector<irr::scene::ISceneNode*>> _MapsModels;
  irr::scene::ISceneNode* _BaseModels;
  std::vector<irr::scene::IMesh*> _BlockModels;

  ControlEventReceiver _Event;
  irrklang::ISoundEngine* _Sound;
  irrklang::ISound* _SoundTutu;
  irrklang::ISound* _SoundMain;
  std::thread* _Th;
  std::mutex* _Mtx;
  int _Height;
  int _Width;
  int _Ddp;
  bool _isFullscreen;
  bool _VSync;
  bool _Run;
  Game* _Game;
  Map* _Map;
  Menu* _Menu;
};

#endif  // GUI_H
