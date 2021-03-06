#include "Gui.hh"
#include <iostream>
#include <sstream>
#include <cstdlib>
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

const Game* Gui::getGame() const { return (this->_Game); }

void Gui::LoadGame(Game* game) {
	std::cout << "I'm here : " << game << std::endl;
	_Mtx->lock();
	_Game = game;
	_Game->init(new Keybind(this));
	_Map = game->get_map();
	_MapsModels.resize(_Map->getMap().size());
	for (int y = 0; y < _Map->getMap().size(); y++) {
		_MapsModels[y].resize((*_Map)[0].size());
		for (int x = 0; x < (*_Map)[0].size(); x++) {
			_MapsModels[y][x] = NULL;
		}
	}
	_Mtx->unlock();
	this->_Menu->StartGame();
	_Game->start();
}

void Gui::StopGame() {
	if (this->_Game) {
		delete this->_Game;
	}
	this->_Game = NULL;
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

Gui::~Gui() { }

/*Private !*/

void Gui::InitJoystick() {
	irr::core::array<irr::SJoystickInfo> joystickInfo;
	if (_Device->activateJoysticks(joystickInfo)) {
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

void Gui::LoadPlayersModels() {
	int size = 4;
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

void Gui::LoadShaders() {
	_Back = _Driver->getTexture("Ressources/Pictures/back_game720.png");
	_BackInGame = _Driver->getTexture("Ressources/Pictures/backingame.png");
	_Splash = _Driver->getTexture("Ressources/Pictures/splash.png");
	_MainFont = _Guienv->getFont("Ressources/Fonts/mainfont.png");
	_MusicMenu.openFromFile("Ressources/Sounds/MenuTheme.ogg");
	_MusicGame.openFromFile("Ressources/Sounds/GameTheme.ogg");
	_BufferTuturu.loadFromFile("Ressources/Sounds/Tutturuu.ogg");
}

void Gui::MovePlayer(int id) {
	static unsigned int current_pos[4] = { 0, 0, 0, 0 };
	IPlayer* player = _Game->get_players()[id];
	float posx = player->get_pos().x * 2;
	float posy = player->get_pos().y * 2 - 1;
	irr::core::vector3df oldpos = _PlayerModels[id][0]->getPosition();
	for (int i = 0; i < 3; i++) {
		bool b = (i == current_pos[id] % 3) ? true : false;
		_PlayerModels[id][i]->setPosition(irr::core::vector3df(posx, posy, 0));
		if (oldpos.X < posx)
			_PlayerModels[id][i]->setRotation(irr::core::vector3df(-90, 0, -90));
		if (oldpos.X > posx)
			_PlayerModels[id][i]->setRotation(irr::core::vector3df(-90, 0, 90));
		if (oldpos.Y < posy)
			_PlayerModels[id][i]->setRotation(irr::core::vector3df(-90, 0, 0));
		if (oldpos.Y > posy)
			_PlayerModels[id][i]->setRotation(irr::core::vector3df(-90, 0, 180));
		_PlayerModels[id][i]->setVisible(player->is_alive() && b);
	}
	current_pos[id]++;
}

void Gui::LoadMaps() {
	_BlockModels.resize(11);
	_SizeBlock.resize(11);
	_BlockModels[Case::FREE] = NULL;
	_BlockModels[Case::UNBREAKABLE] =
		_Smgr->getMesh("Ressources/Models/Block/unbreak/Unbreak.obj");
	_BlockModels[Case::BREAKABLE] =
		_Smgr->getMesh("Ressources/Models/Block/breakable/Breakable.obj");
	_BlockModels[Case::BOMB] =
		_Smgr->getMesh("Ressources/Models/Original_bomb/voltorb.obj");
	_BlockModels[Case::B_BOMB] =
		_Smgr->getMesh("Ressources/Models/Bomb_plus/bomb_plus.obj");
	_BlockModels[Case::EXPLODING] =
		_Smgr->getMesh("Ressources/Models/Block/Exploding/exploding.obj");
	_BlockModels[Case::NOPE] = NULL;
	_BlockModels[Case::POWERUP_BOMB] =
		_Smgr->getMesh("Ressources/Models/Powerup_Bomb/powerup_bomb.obj");
	_BlockModels[Case::POWERUP_RANGE] =
		_Smgr->getMesh("Ressources/Models/Powerup_Range/powerup_range.obj");
	_BlockModels[Case::POWERUP_SPEED] =
		_Smgr->getMesh("Ressources/Models/Powerup_Speed/powerup_speed.obj");

	_SizeBlock[Case::FREE] = irr::core::vector3df(0.25f, 0.25f, 0.25f);
	_SizeBlock[Case::UNBREAKABLE] = irr::core::vector3df(0.003f, 0.003f, 0.003f);
	_SizeBlock[Case::BREAKABLE] = irr::core::vector3df(0.003f, 0.003f, 0.003f);
	_SizeBlock[Case::BOMB] = irr::core::vector3df(0.18f, 0.18f, 0.18f);
	_SizeBlock[Case::B_BOMB] = irr::core::vector3df(0.07f, 0.07f, 0.07f);
	_SizeBlock[Case::EXPLODING] = irr::core::vector3df(0.05f, 0.05f, 0.05f);
	_SizeBlock[Case::NOPE] = irr::core::vector3df(0.25f, 0.25f, 0.25f);
	_SizeBlock[Case::POWERUP_BOMB] = irr::core::vector3df(0.25f, 0.25f, 0.25f);
	_SizeBlock[Case::POWERUP_RANGE] = irr::core::vector3df(0.25f, 0.25f, 0.25f);
	_SizeBlock[Case::POWERUP_SPEED] = irr::core::vector3df(0.25f, 0.25f, 0.25f);

	PutWall();
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
			mesh = _BlockModels[type._powerup->get_type()];
		}
	} else
		mesh = _BlockModels[type._state];
	if (!mesh) return;
	irr::scene::ISceneNode* new_block = _Smgr->addMeshSceneNode(mesh);
	new_block->setID(type._state);
	old = new_block;
	old->setPosition(irr::core::vector3df(x * 2 + 1, y * 2, 0));
	if (type._state != Case::BOMB)
		old->setRotation(irr::core::vector3df(-90, 0, 0));
	else
		old->setRotation(irr::core::vector3df(180, 0, 180));
	old->setScale(_SizeBlock[type._state]);
}

void Gui::PutWall() {
	Case c;
	irr::scene::ISceneNode* elem = NULL;

	c._state = Case::UNBREAKABLE;
	c._powerup = NULL;
	for (int i = 0; i < 18; i++) {
		UpdateBlock(-1 + i, -1, c, elem);
		elem = NULL;
	}
	for (int i = 0; i < 18; i++) {
		UpdateBlock(-1 + i, 16, c, elem);
		elem = NULL;
	}
	for (int i = 0; i < 16; i++) {
		UpdateBlock(-1, i, c, elem);
		elem = NULL;
	}
	for (int i = 0; i < 16; i++) {
		UpdateBlock(16, i, c, elem);
		elem = NULL;
	}
}

void Gui::ClearBlock() {
	Case c;

	c._state = Case::FREE;
	c._powerup = NULL;
	for (int x = 0; x < 16; x++) {
		for (int y = 0; y < 16; y++) {
			UpdateBlock(x, y, c, _MapsModels[y][x]);
		}
	}
	_Smgr->clear();
}

void Gui::DrawBackground() {
	if (_Back)
		_Driver->draw2DImage(_Back, irr::core::position2di(0, 0),
							 irr::core::rect<irr::s32>(0, 0, 1280, 720));
}
void Gui::DrawButton(const char *name) {
	if (_MainFont)
		_MainFont->draw(name, irr::core::rect<irr::s32>(0, 311, 517, 408),
						irr::video::SColor(255, 0, 0, 0), false, true);
}
void Gui::DrawBackMaps() {
	if (_BackInGame)
		_Driver->draw2DImage(_BackInGame, irr::core::position2di(0, 0),
							 irr::core::rect<irr::s32>(0, 0, 1280, 720));
}

void Gui::DrawFPS() {
	std::stringstream ss;
	ss << _Driver->getFPS();
	_MainFont->draw(ss.str().c_str(), irr::core::rect<irr::s32>(0, 311, 517, 408),
					irr::video::SColor(255, 0, 0, 0), false, true);
}

void Gui::DrawWinner() {
	std::stringstream sswin;
	const IPlayer *pl = _Game->who_alive();
	if (pl) {
		sswin << "Player " << pl->get_team() << " Win !";
	} else {
		sswin << "No player Win !";
	}
	DrawButton(sswin.str().c_str());
}

bool Gui::DrawScene() {
	bool aff = false;

	_Mtx->lock();
	if (_Game) {
	_Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));
		if (_Game->check_finish()) {
			ClearBlock();
			DrawBackground();
			DrawWinner();
			aff = true;
		} else {
			DrawBackMaps();
#ifdef _DEBUG_
			DrawFPS();
#endif
			if (this->_Game->get_actualisation()) ActualiseMaps();
			for (int i = 0; i < _Game->get_players().size(); i++) {
				MovePlayer(i);
			}
		}
		_Smgr->drawAll();
		_Driver->endScene();
		if (aff) {
			std::this_thread::sleep_for(std::chrono::microseconds(1000000));
			StopGame();
		}
	}
	_Mtx->unlock();
	return (true);
}

void Gui::DrawMenu() {
	const std::string button = _Menu->getButtonName();

	_Mtx->lock();
	_Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));

	DrawBackground();
	DrawButton(button.c_str());

	_Guienv->drawAll();
	_Driver->endScene();
	_Mtx->unlock();
}

void Gui::DrawSplash() {
	_Driver->beginScene(true, true, irr::video::SColor(255, 128, 128, 128));

	if (_Splash)
		_Driver->draw2DImage(_Splash, irr::core::position2di(0, 0),
							 irr::core::rect<irr::s32>(0, 0, 1280, 720));

	_Guienv->drawAll();
	_Driver->endScene();
}

void Gui::CloseWindows() {
	this->_Device->closeDevice();
}

void Gui::InitCam() {
	irr::scene::ICameraSceneNode* CamNode = _Smgr->addCameraSceneNode();
	irr::scene::ILightSceneNode* LightNode =
		_Smgr->addLightSceneNode(0, irr::core::vector3df(0, 0, -200),
								 irr::video::SColor(255, 128, 128, 128), 50.0f);
	CamNode->setPosition(irr::core::vector3df(16, 2, -20));
	CamNode->setTarget(irr::core::vector3df(16, 10, 0));
}

void Gui::StartLoop() {
	bool is_game_sound = false;

	if (!CreateWindow()) return;

	this->LoadShaders();
	std::this_thread::sleep_for(std::chrono::microseconds(5000));
	_Sound.setBuffer(_BufferTuturu);
	_Sound.play();
	while (WindowIsOpen()) {
		if (_Sound.getStatus() == sf::Sound::Playing && !is_game_sound)
			DrawSplash();
		else {
			if (_Menu->getId() == Menu::GAME) {
				_MusicMenu.stop();
				if (is_game_sound) {
					_Smgr->clear();
					InitCam();
					LoadPlayersModels();
					LoadMaps();
					is_game_sound = false;
					_MusicGame.setLoop(true);
					_MusicGame.play();
				}
				DrawScene();
			} else {
				if (!is_game_sound) {
					is_game_sound = true;
					_MusicGame.stop();
					_MusicMenu.setLoop(true);
					_MusicMenu.play();
				}
				DrawMenu();
			}
		}
	}
	_Mtx->lock();
	if (_Smgr) {
		_Smgr->drop();
		_Smgr = NULL;
	}
	_Mtx->unlock();
}
