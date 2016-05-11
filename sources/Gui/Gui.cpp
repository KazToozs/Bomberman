#include "Gui.hh"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Case.h"

Gui::Gui(int Height, int Width, int Ddp, bool Fullscreen, bool Vsync)
    : _Height(Height),
      _Width(Width),
      _Ddp(Ddp),
      _isFullscreen(Fullscreen),
      _VSync(Vsync) {
  _Device = NULL;
  _Driver = NULL;
  _MainFont = NULL;
  _Run = true;
  _Mtx = new std::mutex();
  _Map = new Map(10, 10);
}

/*Public !!!*/

bool Gui::Start() {
  _Th = new std::thread([&] { StartLoop(); });
  if (_Th->joinable()) return (true);
}

bool Gui::Alive() const {
  _Mtx->lock();
  if (this->_Run) {
    _Mtx->unlock();
    return (true);
  }
  _Mtx->unlock();
  return (false);
}

const irr::SEvent::SJoystickEvent& Gui::get_joy_event() const {
  return (_Event.get_joy_event());
}

const std::vector<irr::SEvent::SKeyInput>& Gui::get_key_event() const {
  return (_Event.get_key_event());
}

Gui::~Gui() { _Th->join(); }

/*Private !*/

void Gui::InitJoystick() {
  irr::core::array<irr::SJoystickInfo> joystickInfo;
  if (_Device->activateJoysticks(joystickInfo)) {
    std::cout << "Joystick support is enabled and " << joystickInfo.size()
              << " joystick(s) are present." << std::endl;

    for (irr::u32 joystick = 0; joystick < joystickInfo.size(); ++joystick) {
      std::cout << "Joystick " << joystick << ":" << std::endl;
      std::cout << "\tName: '" << joystickInfo[joystick].Name.c_str() << "'"
                << std::endl;
      std::cout << "\tAxes: " << joystickInfo[joystick].Axes << std::endl;
      std::cout << "\tButtons: " << joystickInfo[joystick].Buttons << std::endl;

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
}

bool Gui::CreateWindow() {
  _Mtx->lock();
  if (_Device) return (true);
  _Device = irr::createDevice(irr::video::EDT_OPENGL,
                              irr::core::dimension2d<irr::u32>(_Width, _Height),
                              _Ddp, _isFullscreen, false, _VSync, &_Event);
  if (_Device) {
    _Device->setResizable(false);
    _Device->setWindowCaption(L"Indie Studio : Bomberman");

    _Driver = _Device->getVideoDriver();
    _Smgr = _Device->getSceneManager();
    _Guienv = _Device->getGUIEnvironment();
    this->InitJoystick();

    _Mtx->unlock();
    return (true);
  }
  _Mtx->unlock();
  return (false);
}

bool Gui::WindowIsOpen() {
  _Mtx->lock();
  if (!_Device) {
    _Mtx->unlock();
    return (true);
  }
  this->_Run = _Device->run();
  _Mtx->unlock();
  return (_Run);
}

void Gui::LoadModels() {
  _PlayerModels.resize(4);
  for (int i = 0; i < 4; i++) {
    std::stringstream ss;
    ss << "Ressources/Models/Latios";
    if (i) ss << i;
    _PlayerModels[i].resize(3);
    irr::scene::IMesh* state =
        _Smgr->getMesh((ss.str() + "/state1.obj").c_str());
    _PlayerModels[i][0] = _Smgr->addMeshSceneNode(state);
    _PlayerModels[i][0]->setVisible(false);
    _PlayerModels[i][0]->setScale(irr::core::vector3df(0.02f, 0.02f, 0.02f));

    state = _Smgr->getMesh((ss.str() + "/state1.obj").c_str());
    _PlayerModels[i][1] = _Smgr->addMeshSceneNode(state);
    _PlayerModels[i][1]->setVisible(false);
    _PlayerModels[i][1]->setScale(irr::core::vector3df(0.02f, 0.02f, 0.02f));
    state = _Smgr->getMesh((ss.str() + "/state1.obj").c_str());
    _PlayerModels[i][2] = _Smgr->addMeshSceneNode(state);
    _PlayerModels[i][2]->setVisible(false);
    _PlayerModels[i][2]->setScale(irr::core::vector3df(0.02f, 0.02f, 0.02f));
  }
}

void Gui::Load() {
  _Mtx->lock();
  irr::scene::ICameraSceneNode* CamNode = _Smgr->addCameraSceneNode();
  irr::scene::ILightSceneNode* LightNode =
      _Smgr->addLightSceneNode(0, irr::core::vector3df(0, 0, 200),
                               irr::video::SColor(255, 128, 128, 128), 50.0f);
  CamNode->setPosition(irr::core::vector3df(0, -10, 30));
  CamNode->setTarget(irr::core::vector3df(0, 0, 0));
  LoadModels();
  LoadMaps();
  _Mtx->unlock();
}

void Gui::MovePlayer(int id) {
  static float x, y, z = 0.0f;
  if (id == 0) {
    x += 0.1f;
    y += 0.1f;
    z += 0.01f;
  }
  for (int i = 0; i < 3; i++) {
    _PlayerModels[id][i]->setPosition(irr::core::vector3df(id * 2, id * 2, 0));
    _PlayerModels[id][i]->setRotation(irr::core::vector3df(x, y, z));
    _PlayerModels[id][i]->setVisible(true);
  }
}

void Gui::LoadMaps() {
  _BlockModels.resize(6);
  _BlockModels[Case::FREE] = NULL;
  _BlockModels[Case::UNBREAKABLE] =
      _Smgr->getMesh("Ressources/Models/Unbreak.obj");
  _BlockModels[Case::BREAKABLE] =
      _Smgr->getMesh("Ressources/Models/Breakable.obj");
  _BlockModels[Case::TAKEN] = _Smgr->getMesh("Ressources/Models/Taken.obj");
  _BlockModels[Case::BOMB] = _Smgr->getMesh("Ressources/Models/Bomb.obj");
  _BlockModels[Case::EXPLODING] =
      _Smgr->getMesh("Ressources/Models/Exploding.obj");

  _MapsModels.resize(_Map->getMap().size());
  for (int y = 0; y < _Map->getMap().size(); y++) {
      _MapsModels[y].resize((*_Map)[0].size());
    for (int x = 0; x < (*_Map)[0].size(); x++) {
        _MapsModels[y][x] = NULL;
    }
  }
}

void Gui::ActualiseMaps() {
    for (int y = 0; y < _Map->getMap().size(); y++) {

    }
}

bool Gui::DrawScene() {
  _Mtx->lock();
  _Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));
  /*Start Scene*/

  for (int i = 0; i < 4; i++) {
    MovePlayer(i);
  }

  /*End Scene*/
  _Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
  _Mtx->unlock();
  return (true);
}

void Gui::StartLoop() {
  if (!CreateWindow()) return;
  this->Load();
  while (WindowIsOpen()) {
    DrawScene();
  }
  _Mtx->lock();
  if (_Device) {
    _Device->drop();
  }
  _Device = NULL;
  _Mtx->unlock();
}
