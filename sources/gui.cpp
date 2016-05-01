#include "gui.h"
#include "iostream"

Gui::Gui(int Height, int Width, int Ddp, bool Fullscreen, bool Vsync)
    : _Height(Height),
      _Width(Width),
      _Ddp(Ddp),
      _isFullscreen(Fullscreen),
      _VSync(Vsync) {
  _Device = NULL;
  _Driver = NULL;
  _Back = NULL;
  _MainFont = NULL;
}

bool Gui::CreateWindow() {
  _Device = irr::createDevice(irr::video::EDT_OPENGL,
                              irr::core::dimension2d<irr::u32>(_Width, _Height),
                              _Ddp, _isFullscreen, false, _VSync);
  if (_Device) {
    _Device->setWindowCaption(L"Indie Studio : Bomberman");
    _Driver = _Device->getVideoDriver();
    _Smgr = _Device->getSceneManager();
    _Guienv = _Device->getGUIEnvironment();
    return (true);
  }
  return (false);
}

bool Gui::WindowIsOpen() { return (_Device->run()); }

bool Gui::Load() {
  _Smgr->addCameraSceneNode();
  _Back = _Driver->getTexture("Ressources/bg.tga");
  _MainFont = _Guienv->getFont("Ressources/mainfont.png");
}

bool Gui::SetBackground() {
  _Driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
  if (_Back)
    _Driver->draw2DImage(_Back, irr::core::position2di(0, 0),
                         irr::core::rect<irr::s32>(0, 0, 1280, 720));
  std::cout << _MainFont << std::endl;
  if (_MainFont)
  _MainFont->draw(L"Solo", irr::core::rect<irr::s32>(0, 311, 517, 408),
                  irr::video::SColor(255, 0, 0, 0));
  _Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
}

Gui::~Gui() {
  if (_Device) {
    _Device->drop();
  }
}
