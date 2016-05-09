#ifndef GUI_H
#define GUI_H

#include <irrlicht.h>
#include <vector>
#include <thread>
#include <mutex>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

class MyEventReceiver : public irr::IEventReceiver {
 public:
  // This is the one method that we have to implement
  virtual bool OnEvent(const irr::SEvent& event) {
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
      _KeyIsDown[event.KeyInput.Key] = event.KeyInput;
    }
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT) {
      _JoystickEvent = event.JoystickEvent;
    }

    return false;
  }

  const irr::SEvent::SJoystickEvent& get_joy_event() const {
      return (_JoystickEvent);
  }

  const std::vector<irr::SEvent::SKeyInput>& get_key_event() const {
      return (_KeyIsDown);
  }

  // This is used to check whether a key is being held down
  virtual bool IsKeyDown(irr::EKEY_CODE keyCode) const {
    return _KeyIsDown[keyCode].PressedDown;
  }

  MyEventReceiver() { _KeyIsDown.resize(irr::KEY_KEY_CODES_COUNT); }

 private:
  std::vector<irr::SEvent::SKeyInput> _KeyIsDown;
  irr::SEvent::SJoystickEvent _JoystickEvent;
};

class Gui {
 public:
  Gui(int Height = 720, int Width = 1280, int Ddp = 32, bool Fullscreen = false,
      bool Vsync = true);

  bool Start();
  bool Alive();


  const irr::SEvent::SJoystickEvent& get_joy_event() const {
      return (_event.get_joy_event());
  }

  const std::vector<irr::SEvent::SKeyInput>& get_key_event() const {
      return (_event.get_key_event());
  }

  void SetText(std::string text) {
      this->Text = text;
  }


  ~Gui();

 private:
  void StartLoop();
  bool CreateWindow();
  bool SetBackground();
  bool LaunchMap();
  bool Load();
  bool WindowIsOpen();

  irr::IrrlichtDevice* _Device;
  irr::video::IVideoDriver* _Driver;
  irr::video::ITexture* _Back;
  irr::video::ITexture* _Back_game;
  irr::scene::ISceneManager* _Smgr;
  irr::gui::IGUIEnvironment* _Guienv;
  irr::gui::IGUIFont* _MainFont;

  std::string Text;
  MyEventReceiver _event;
  std::thread* _th;
  std::mutex* _mtx;
  int _Height;
  int _Width;
  int _Ddp;
  bool _isFullscreen;
  bool _VSync;
  bool _run;
};

#endif  // GUI_H
