#include "gui.h"
#include <iostream>
#include <unistd.h>

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
  Text = "Loool";
  _run = true;
  _mtx = new std::mutex();
}

bool Gui::Start() {
  _th = new std::thread([&] { StartLoop(); });
  if (_th->joinable()) return (true);
}

bool Gui::Alive() {
  _mtx->lock();
  if (this->_run) {
    _mtx->unlock();
    return (true);
  }
  _mtx->unlock();
  return (false);
}

bool Gui::CreateWindow() {
  _mtx->lock();
  if (_Device) return (true);
  _Device = irr::createDevice(irr::video::EDT_OPENGL,
                              irr::core::dimension2d<irr::u32>(_Width, _Height),
                              _Ddp, _isFullscreen, false, _VSync, &_event);
  if (_Device) {
    _Device->setResizable(false);
    _Device->setWindowCaption(L"Indie Studio : Bomberman");

    _Driver = _Device->getVideoDriver();
    _Smgr = _Device->getSceneManager();
    _Guienv = _Device->getGUIEnvironment();

    irr::core::array<irr::SJoystickInfo> joystickInfo;
    if (_Device->activateJoysticks(joystickInfo)) {
      std::cout << "Joystick support is enabled and " << joystickInfo.size()
                << " joystick(s) are present." << std::endl;

      for (irr::u32 joystick = 0; joystick < joystickInfo.size(); ++joystick) {
        std::cout << "Joystick " << joystick << ":" << std::endl;
        std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'"
                  << std::endl;
        std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
        std::cout << "\tButtons: " << joystickInfo[joystick].Buttons
                  << std::endl;

        std::cout << "\tHat is: ";

        switch (joystickInfo[joystick].PovHat) {
          case irr::SJoystickInfo::POV_HAT_PRESENT:
            std::cout << "present" << std::endl;
            break;

          case irr::SJoystickInfo::POV_HAT_ABSENT:
            std::cout << "absent" << std::endl;
            break;

          case irr::SJoystickInfo::POV_HAT_UNKNOWN:
          default:
            std::cout << "unknown" << std::endl;
            break;
        }
      }
    } else {
      std::cout << "Joystick support is not enabled." << std::endl;
    }

    _mtx->unlock();
    return (true);
  }
  _mtx->unlock();
  return (false);
}

bool Gui::WindowIsOpen() {
  _mtx->lock();
  if (!_Device) {
    _mtx->unlock();
    return (true);
  }
  this->_run = _Device->run();
  _mtx->unlock();
  return (_run);
}

bool Gui::Load() {
  _mtx->lock();
  irr::scene::ICameraSceneNode *CamNode = _Smgr->addCameraSceneNode();
  irr::scene::ILightSceneNode *LightNode =
      _Smgr->addLightSceneNode(0, irr::core::vector3df(0, 0, 200),
                               irr::video::SColor(255, 128, 128, 128), 50.0f);
  _Back = _Driver->getTexture("Ressources/bg.tga");
  _Back_game = _Driver->getTexture("Ressources/backgame.jpg");
  _MainFont = _Guienv->getFont("Ressources/mainfont.png");

  irr::scene::IMesh *cube = _Smgr->getMesh("Ressources/Models/Latios/state1.obj");
  irr::scene::IMesh *cube1 = _Smgr->getMesh("Ressources/Models/Latios/state2.obj");
  irr::scene::IMesh *cube2 = _Smgr->getMesh("Ressources/Models/Latios/state3.obj");
  if (!cube) exit(0);
  for (int i = 0; i < 1; i++) {
    for (int y = 0; y < 1; y++) {
        irr::scene::ISceneNode *bb8Node = _Smgr->addMeshSceneNode(cube);
        bb8Node->setPosition(irr::core::vector3df(2 * y, 2 * i, 0));
        bb8Node->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
        bb8Node->setRotation(irr::core::vector3df(90, 0, 0));
        bb8Node->setName("state1");
        bb8Node = _Smgr->addMeshSceneNode(cube1);
        bb8Node->setPosition(irr::core::vector3df(2 * y, 2 * i, 0));
        bb8Node->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
        bb8Node->setRotation(irr::core::vector3df(90, 0, 0));
        bb8Node->setName("state2");
        bb8Node = _Smgr->addMeshSceneNode(cube2);
        bb8Node->setPosition(irr::core::vector3df(2 * y, 2 * i, 0));
        bb8Node->setScale(irr::core::vector3df(0.1, 0.1, 0.1));
        bb8Node->setRotation(irr::core::vector3df(90, 0, 0));
        bb8Node->setName("state3");
    }
  }

  CamNode->setPosition(irr::core::vector3df(0, -10, 30));
  CamNode->setTarget(irr::core::vector3df(0, 0, 0));
  _mtx->unlock();
  return (true);
}

bool Gui::LaunchMap() {
  _mtx->lock();
  static float x, y, z = 0;
  _Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));
  /*Start Scene*/

  irr::scene::ISceneNode *node = _Smgr->getSceneNodeFromName("CubeNode");
  irr::scene::ICameraSceneNode *cam = _Smgr->getActiveCamera();
  if (node) node->setRotation(irr::core::vector3df(x++, y++, z++));

  /*End Scene*/
  _Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
  _mtx->unlock();
  return (true);
}

bool Gui::SetBackground() {
    static int state = 0;

  _mtx->lock();
  _Driver->beginScene(true, true, irr::video::SColor(255, 255, 255, 255));
  if (_Back)
    _Driver->draw2DImage(_Back, irr::core::position2di(0, 0),
                         irr::core::rect<irr::s32>(0, 0, 1280, 720));
  if (_MainFont)
    _MainFont->draw(Text.c_str(), irr::core::rect<irr::s32>(0, 311, 517, 408),
                    irr::video::SColor(255, 0, 0, 0));
  if (state < 20) {
      irr::scene::ISceneNode *node = _Smgr->getSceneNodeFromName("state1");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(true);
      node = _Smgr->getSceneNodeFromName("state2");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(false);
      node = _Smgr->getSceneNodeFromName("state3");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(false);
  }
  else if (state < 40) {
      irr::scene::ISceneNode *node = _Smgr->getSceneNodeFromName("state1");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(false);
      node = _Smgr->getSceneNodeFromName("state2");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(true);
      node = _Smgr->getSceneNodeFromName("state3");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(false);
  }
  else if (state < 60) {
      irr::scene::ISceneNode *node = _Smgr->getSceneNodeFromName("state1");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(false);
      node = _Smgr->getSceneNodeFromName("state2");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(false);
      node = _Smgr->getSceneNodeFromName("state3");
      node->setRotation(irr::core::vector3df(this->get_joy_event().Axis[0],
                                             this->get_joy_event().Axis[1], 0));
      node->setVisible(true);
  }
  if (state == 60)
      state = 0;
  state++;
  _Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
  _mtx->unlock();
}

void Gui::StartLoop() {
  if (!CreateWindow()) return;
  this->Load();
  while (WindowIsOpen()) {
    SetBackground();
    usleep(1000);
  }
  _mtx->lock();
  if (_Device) {
    _Device->drop();
  }
  _Device = NULL;
  _mtx->unlock();
}

Gui::~Gui() { _th->join(); }
