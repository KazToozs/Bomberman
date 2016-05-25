#include "Gui.hh"
#include <iostream>
#include <sstream>
#include <unistd.h>
#include "Keybind.hh"

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
  _Game = NULL;
  _Map = NULL;
}

/*Public !!!*/

bool Gui::Start(Menu* menu) {
  _Menu = menu;
  _Th = new std::thread([&] { StartLoop(); });
  if (_Th->joinable()) return (true);
}

const Game *Gui::getGame() const {
    return (this->_Game);
}

void Gui::LoadGame(Game* game) {
  std::cout << "I'm here : " << game << std::endl;
  _Mtx->lock();
  _Game = game;
  _Game->init(new Keybind(this));
  _Map = game->get_map();
  LoadModels();
  _MapsModels.resize(_Map->getMap().size());
  for (int y = 0; y < _Map->getMap().size(); y++) {
    _MapsModels[y].resize((*_Map)[0].size());
    for (int x = 0; x < (*_Map)[0].size(); x++) {
      _MapsModels[y][x] = NULL;
    }
  }
  this->_Menu->StartGame();
  _Mtx->unlock();
  _Game->start();
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
  int size = _Game->get_players().size();
  _PlayerModels.resize(size);
  std::cout << size << std::endl;
  for (int i = 0; i < size; i++) {
    std::stringstream ss;
    ss << "Ressources/Models/Latios";
    if (i) ss << i;
    _PlayerModels[i].resize(3);
    irr::scene::IMesh* state =
        _Smgr->getMesh((ss.str() + "/state1.obj").c_str());
    _PlayerModels[i][0] = _Smgr->addMeshSceneNode(state);
    _PlayerModels[i][0]->setVisible(false);
    _PlayerModels[i][0]->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
    _PlayerModels[i][0]->setRotation(irr::core::vector3df(90, 0, 0));

    state = _Smgr->getMesh((ss.str() + "/state2.obj").c_str());
    _PlayerModels[i][1] = _Smgr->addMeshSceneNode(state);
    _PlayerModels[i][1]->setVisible(false);
    _PlayerModels[i][1]->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
    _PlayerModels[i][1]->setRotation(irr::core::vector3df(90, 0, 0));
    state = _Smgr->getMesh((ss.str() + "/state3.obj").c_str());
    _PlayerModels[i][2] = _Smgr->addMeshSceneNode(state);
    _PlayerModels[i][2]->setVisible(false);
    _PlayerModels[i][2]->setScale(irr::core::vector3df(0.01f, 0.01f, 0.01f));
    _PlayerModels[i][2]->setRotation(irr::core::vector3df(90, 0, 0));
  }
}

void Gui::Load() {
  _Mtx->lock();
  irr::scene::ICameraSceneNode* CamNode = _Smgr->addCameraSceneNode();
  irr::scene::ILightSceneNode* LightNode =
      _Smgr->addLightSceneNode(0, irr::core::vector3df(0, 0, -200),
                               irr::video::SColor(255, 128, 128, 128), 50.0f);
  CamNode->setPosition(irr::core::vector3df(20, 4, -26));
  CamNode->setTarget(irr::core::vector3df(20, 14, 0));
  _Back = _Driver->getTexture("Ressources/Pictures/back_game720.png");
  _Splash = _Driver->getTexture("Ressources/Pictures/splash.png");
  _MainFont = _Guienv->getFont("Ressources/Fonts/mainfont.png");
  _BufferTuturu.loadFromFile("Ressources/Sounds/Tutturuu.wav");
  _BufferMainSound.loadFromFile("Ressources/Sounds/MenuTheme.wav");
  LoadMaps();
  _Mtx->unlock();
}

void Gui::MovePlayer(int id) {
  static int current_pos = 0;
  std::vector<IPlayer*> players = _Game->get_players();
  float posx = players[id]->get_pos().x;
  float posy = players[id]->get_pos().y;

  for (int i = 0; i < 3; i++) {
      bool b = (i == current_pos) ? true : false;
    _PlayerModels[id][i]->setPosition(
        irr::core::vector3df(posx * 2 + ((!b) ? 5000: 0) , posy * 2, 0));
    _PlayerModels[id][i]->setRotation(irr::core::vector3df(180, 0, 0));
    _PlayerModels[id][i]->setVisible(b);
  }
  current_pos = (current_pos + 1) % 3;
}

void Gui::LoadMaps() {
  _BaseModels = NULL;
  _BlockModels.resize(11);
  _BlockModels[Case::FREE] = NULL;
  _BlockModels[Case::UNBREAKABLE] =
      _Smgr->getMesh("Ressources/Models/Block/unbreak/Unbreak.obj");
  _BlockModels[Case::BREAKABLE] =
      _Smgr->getMesh("Ressources/Models/Block/breakable/Breakable.obj");
  _BlockModels[Case::BOMB] =
      _Smgr->getMesh("Ressources/Models/Original_bomb/original_bomb.obj");
  _BlockModels[Case::B_BOMB] =
      _Smgr->getMesh("Ressources/Models/Bomb_plus/bomb_plus.obj");
  _BlockModels[Case::EXPLODING] =
      _Smgr->getMesh("Ressources/Models/Block/Exploding.obj");
  _BlockModels[Case::NOPE] =
      _Smgr->getMesh("Ressources/Models/Block/cube/cube.obj");
  _BlockModels[Case::POWERUP_BOMB] =
      _Smgr->getMesh("Ressources/Models/Powerup_Bomb/powerup_bomb.obj");
  _BlockModels[Case::POWERUP_RANGE] =
      _Smgr->getMesh("Ressources/Models/Powerup_Range/powerup_range.obj");
  _BlockModels[Case::POWERUP_SPEED] =
      _Smgr->getMesh("Ressources/Models/Powerup_Speed/powerup_speed.obj");
}

void Gui::ActualiseMaps() {
  for (int y = 0; y < _Map->getMap().size(); y++) {
    for (int x = 0; x < _Map->getMap().size(); x++) {
      UpdateBlock(x, y, (*_Map)[y][x], _MapsModels[y][x]);
    }
  }
}

void Gui::UpdateBlock(int x, int y, Case type, irr::scene::ISceneNode*& old) {
  irr::scene::IMesh* mesh = NULL;
  if (old) {
    if (old->getID() == type._state) return;
    _Smgr->addToDeletionQueue(old);
    old = NULL;
  }
  if (type._state == Case::FREE) {
    if (!type._powerup) {
      old = NULL;
      return;
    } else {
      switch (type._powerup->get_type()) {
        case SPEEDUP:
          mesh = _BlockModels[Case::POWERUP_SPEED];
          break;
        case RANGEUP:
          mesh = _BlockModels[Case::POWERUP_RANGE];
          break;
        case BOMBUP:
          mesh = _BlockModels[Case::POWERUP_BOMB];
          break;
      }
    }
  } else
    mesh = _BlockModels[type._state];
  if (!mesh) return;
  irr::scene::ISceneNode* new_block = _Smgr->addMeshSceneNode(mesh);
  new_block->setID(type._state);
  old = new_block;
  old->setPosition(irr::core::vector3df(x * 2, y * 2, 0));
  old->setRotation(irr::core::vector3df(50, 0, 0));
  if (type._state != Case::BOMB)
    old->setScale(irr::core::vector3df(0.003f, 0.003f, 0.003f));
  else
    old->setScale(irr::core::vector3df(0.10f, 0.10f, 0.10f));
}

void Gui::PutWall() {
  Case c;
  irr::scene::ISceneNode* elem = NULL;

  c._state = Case::BOMB;
  c._powerup = NULL;
  for (int i = 0; i < 22; i++) {
    UpdateBlock(-1 + i, -1, c, elem);
    elem = NULL;
  }
  for (int i = 0; i < 22; i++) {
    UpdateBlock(-1 + i, 20, c, elem);
    elem = NULL;
  }
  for (int i = 0; i < 20; i++) {
    UpdateBlock(-1, i, c, elem);
    elem = NULL;
  }
  for (int i = 0; i < 20; i++) {
    UpdateBlock(20, i, c, elem);
    elem = NULL;
  }
}

bool Gui::DrawScene() {
  Case c;

  c._state = Case::NOPE;
  c._powerup = NULL;
  _Mtx->lock();
  _Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));
  /*Start Scene*/
  if (!_BaseModels) UpdateBlock(0, 0, c, _BaseModels);
  ActualiseMaps();
  for (int i = 0; i < _Game->get_players().size(); i++) {
    MovePlayer(i);
  }

  /*End Scene*/
  _Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
  _Mtx->unlock();
  return (true);
}

void Gui::DrawMenu() {
  const std::string button = _Menu->getButtonName();

  _Mtx->lock();
  _Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));
  /*Start Menu*/

  if (_Back)
    _Driver->draw2DImage(_Back, irr::core::position2di(0, 0),
                         irr::core::rect<irr::s32>(0, 0, 1280, 720));
  if (_MainFont)
    _MainFont->draw(button.c_str(), irr::core::rect<irr::s32>(0, 311, 517, 408),
                    irr::video::SColor(255, 0, 0, 0), false, true);

  /*End Menu*/
  //_Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
  _Mtx->unlock();
}

void Gui::DrawSplash() {
  _Mtx->lock();
  _Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));
  /*Start Menu*/

  if (_Back)
    _Driver->draw2DImage(_Splash, irr::core::position2di(0, 0),
                         irr::core::rect<irr::s32>(0, 0, 1280, 720));
  /*End Menu*/
  //_Smgr->drawAll();
  _Guienv->drawAll();
  _Driver->endScene();
  _Mtx->unlock();
}

void Gui::StartLoop() {
  bool is_game_sound = false;

  if (!CreateWindow()) return;
  this->Load();
  usleep(5000);
  PutWall();
  _Sound.setBuffer(_BufferTuturu);
  _Sound.play();
  while (WindowIsOpen()) {
    if (_Sound.getStatus() == sf::Sound::Playing && !is_game_sound)
      DrawSplash();
    else {
      if (!is_game_sound) {
        is_game_sound = true;
        _Sound.setBuffer(_BufferMainSound);
        _Sound.setLoop(true);
        _Sound.play();
      }
      if (_Menu->getId() == Menu::GAME)
        DrawScene();
      else
        DrawMenu();
    }
  }
  _Mtx->lock();
  if (_Smgr) _Smgr->drop();
  if (_Guienv) _Guienv->drop();
  if (_MainFont) _MainFont->drop();
  if (_Device) _Device->drop();
  _Device = NULL;
  _Mtx->unlock();
}
