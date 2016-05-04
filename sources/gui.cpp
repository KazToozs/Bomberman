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
  if (_Device) return (true);
  _Device = irr::createDevice(irr::video::EDT_OPENGL,
                              irr::core::dimension2d<irr::u32>(_Width, _Height),
                              _Ddp, _isFullscreen, false, _VSync);
  if (_Device) {
    _Device->setResizable(false);
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
  irr::scene::ICameraSceneNode *CamNode = _Smgr->addCameraSceneNode();
  irr::scene::ILightSceneNode *LightNode =  _Smgr->addLightSceneNode();
  LightNode->setPosition(irr::core::vector3df(0,0,-10));
  _Back = _Driver->getTexture("Ressources/bg.tga");
  _MainFont = _Guienv->getFont("Ressources/mainfont.png");

  irr::scene::IMesh *cube = _Smgr->getMesh("Ressources/block.obj");
  if (!cube)
      exit(0);
  irr::scene::ISceneNode *node = _Smgr->addMeshSceneNode(cube);
  CamNode->setPosition(irr::core::vector3df(0,0,-5));
  node->setPosition(irr::core::vector3df(0,0,0));
  node->setName("CubeNode");

  return (true);
}

bool Gui::LaunchMap() {
    static float x, y, z = 0;
    _Driver->beginScene(true, true, irr::video::SColor(255, 0, 0, 0));
    /*Start Scene*/

    irr::scene::ISceneNode *node =_Smgr->getSceneNodeFromName("CubeNode");
    node->setRotation(irr::core::vector3df(x++, y++, z++));

    /*End Scene*/
    _Smgr->drawAll();
    _Guienv->drawAll();
    _Driver->endScene();
    return (true);
}

bool Gui::SetBackground() {
  _Driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
  if (_Back)
    _Driver->draw2DImage(_Back, irr::core::position2di(0, 0),
                         irr::core::rect<irr::s32>(0, 0, 1280, 720));
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
