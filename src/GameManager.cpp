//
// GameManager.cpp for MANAGER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Mon May  9 10:38:55 2016 Victor Gouet
// Last update Mon Jun  6 04:06:16 2016 veyrie_f
//

#include <sstream>
#include "Intro.hpp"
#include "Intro.hpp"
#include "SoundManager.hpp"
#include "GameManager.hpp"
#include "Texture.hpp"
#include "GameObjectTimeContainer.hpp"
#include "IAPlayer.hpp"

const int	GameManager::endOfGame = 60;

GameManager::GameManager()
{
    try {
        IrrlichtController::getDevice(true);
    } catch (std::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(0);
    }
    m_st_text = NULL;
    BomberManTexture::loadTexture();
    m_gameState = PLAY;
    defaultFont = NULL;
    setGameState(SPLASH_SCREEN);
    _state = PREV_MENU;
    uiManager = NULL;
    uiEventReceiver = NULL;
    wallOfDead = NULL;
    eventGame = new EventGame();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);
    m_cameras[MENU_CAM_1] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                      irr::core::vector3df(100, 12, -30),
                                                                                      irr::core::vector3df(100, 12, 0));
    m_cameras[MENU_CAM_2] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                      irr::core::vector3df(200, 12, -30),
                                                                                      irr::core::vector3df(200, 12, 0));
    m_cameras[MENU_CAM_3] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                      irr::core::vector3df(300, 12, -30),
                                                                                      irr::core::vector3df(300, 12, 0));
    m_cameras[MENU_CAM_4] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                      irr::core::vector3df(400, 12, -30),
                                                                                      irr::core::vector3df(400, 12, 0));
    m_cameras[GAME_CAMERA] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                       irr::core::vector3df(0, 0, 0),
                                                                                       irr::core::vector3df(0, 0, 0));
    m_cameras[MAIN_MENU_CAM] = IrrlichtController::getSceneManager()->addCameraSceneNode(nullptr,
                                                                                         irr::core::vector3df(0, 0, 0),
                                                                                         irr::core::vector3df(0, 0, 0));
    is_gameOver = false;
}

GameManager::~GameManager()
{
    delete uiEventReceiver;
    delete uiManager;
    delete eventGame;
    if (wallOfDead)
        delete wallOfDead;
    delete SoundManager::getManager();
    ClearPlayers();
    for (std::list<PlayerInfo *>::iterator it = m_playerInfoUI.begin(), end = m_playerInfoUI.end(); it != end; ++it)
    {
        delete(*it);
    }
}

GameManager *GameManager::SharedInstance()
{
    static GameManager	*GM = NULL;

    if (GM == NULL)
    {
        GM = new GameManager();
    }
    return (GM);
}

void        GameManager::setGameState(GameState state)
{
    m_gameSatePrev = m_gameState;
    m_gameState = state;
}

GameManager::GameState    GameManager::getGameState() const
{
    return (m_gameState);
}

void        GameManager::setPrevGameState(GameState state)
{
    m_gameSatePrev = state;
}

GameManager::GameState    GameManager::getPrevGameState() const
{
    return (m_gameSatePrev);
}

void    GameManager::run()
{
    Intro *intro = new Intro(eventGame);
    intro->run();
    delete intro;
    uiManager = new UIManager(IrrlichtController::getDevice(false));
    uiEventReceiver = new UIEventReceiver(*uiManager);

    setFptr(&GameManager::willStartMenu);
    while (IrrlichtController::getDevice()->run() && IrrlichtController::getDriver())
    {
        if (!IrrlichtController::getDevice()->isWindowActive())
            continue;
        IrrlichtController::getDriver()->beginScene(true, true, irr::video::SColor(0, 0, 0, 0));
        if (fptr)
            (this->*fptr)();
        fptr = NULL;
        if (m_gameState == PAUSE)
            GameObjectTimeContainer::SharedInstance()->timerStop();
        if (m_gameState == PLAY)
        {
            _state = GAME;
            onGame();
        }
        else
        {
            _state = MENU;
            onMenu();
        }

        IrrlichtController::getSceneManager()->drawAll();
        IrrlichtController::getGUIEnvironment()->drawAll();
        IrrlichtController::getDriver()->endScene();
    }
}

void    GameManager::onMenu()
{
    if (GameManager::SharedInstance()->getGameState() == GameManager::PAUSE)
        return;

    irr::core::rect<irr::s32> viewPort = IrrlichtController::getDriver()->getViewPort();
    irr::scene::ICameraSceneNode *camera = m_cameras[MAIN_MENU_CAM];

    if (GameManager::SharedInstance()->getGameState() == GameManager::MAIN_MENU)
    {
        playerRanking.reset();
        // Camera 1
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
                irr::core::rect<irr::s32>(IrrlichtController::width * 0.014, IrrlichtController::height * 0.445,
                                          IrrlichtController::width * 0.24, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_1]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 2
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
                irr::core::rect<irr::s32>(IrrlichtController::width * 0.262, IrrlichtController::height * 0.445,
                                          IrrlichtController::width * 0.49, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_2]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

        // Camera 3
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
                irr::core::rect<irr::s32>(IrrlichtController::width * 0.515, IrrlichtController::height * 0.445,
                                          IrrlichtController::width * 0.743, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_3]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();

//        // Camera 4
        IrrlichtController::getDevice()->getVideoDriver()->setViewPort(
                irr::core::rect<irr::s32>(IrrlichtController::width * 0.762, IrrlichtController::height * 0.445,
                                          IrrlichtController::width * 0.99, IrrlichtController::height * 0.85));
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[MENU_CAM_4]);
        IrrlichtController::getDevice()->getSceneManager()->drawAll();
    }
    else if (GameManager::SharedInstance()->getGameState() == GameManager::MENU_MAP)
    {
        activeCam(MAIN_MENU_CAM);
        if (anim == nullptr || m_cameras[MAIN_MENU_CAM]->getAnimators().empty())
        {
            anim = IrrlichtController::getDevice()->getSceneManager()->createFlyCircleAnimator(
                    irr::core::vector3df(0, 300, 0), 360.0f, 0.0004f);
            m_cameras[MAIN_MENU_CAM]->setPosition(irr::core::vector3df(300, 250, 300));
            m_cameras[MAIN_MENU_CAM]->addAnimator(anim);
            anim->drop();
        }
        IrrlichtController::getDevice()->getSceneManager()->drawAll();
    }
    else if (GameManager::SharedInstance()->getGameState() == GameManager::RANKING_SCREEN)
    {
        displayRankingScreen();
        is_gameOver = false;
    }
    // Resets the viewport
    IrrlichtController::getDriver()->setViewPort(viewPort);
    if (camera)
        IrrlichtController::getSceneManager()->setActiveCamera(camera);
}

void    GameManager::displayRankingScreen()
{
    if (!is_gameOver)
        return;
    m_st_text->remove();
    if (this->defaultFont)
        IrrlichtController::getDevice()->getGUIEnvironment()->getSkin()->setFont(this->defaultFont);
    m_st_text = NULL;
    playerRanking.displayRankingScreen();
}

void	GameManager::setCountDownText(std::wstringstream const &ss)
{
    if (!m_st_text)
    {
        IrrlichtController::getDevice()->getGUIEnvironment()->getSkin()->setFont(IrrlichtController::getDevice()->getGUIEnvironment()->getFont(BINDIR"media/font/arcade_font.xml"));
        m_st_text = IrrlichtController::getDevice()->getGUIEnvironment()->addStaticText(ss.str().c_str(), irr::core::rect<irr::s32>(0, 100, (irr::s32) IrrlichtController::width, 200), false, true);
        m_st_text->setOverrideColor(irr::video::SColor(255, 255, 255, 255));
        m_st_text->setTextAlignment(irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER, irr::gui::EGUI_ALIGNMENT::EGUIA_CENTER);
    }
    else
        m_st_text->setText(ss.str().c_str());
}

void    GameManager::onGame()
{
    if (eventGame->IsKeyDownOneTime(irr::EKEY_CODE::KEY_KEY_P))
    {
        m_st_text = NULL;
        setGameState(PAUSE);
        IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);
        uiEventReceiver->DisplayPauseMenu();
        return ;
    }

    if (wallOfDead)
    {
        // TIMER FOR WALLOFDEAD
        double actualTime = getTimeSeconds();
        double time = actualTime - beginTimer;
        if (time >= 1)
        {
            std::wstringstream ss;

            if (countdown > 0)
            {
                countdown -= 1;
                if (countdown == 0)
                {
                    SoundManager::getManager()->stopAllBack();
                    SoundManager::getManager()->play("wallOfDeath.wav");
                }
                ss << countdown;
                setCountDownText(ss);
            }
            else
            {
                ss << "Wall Of Death !";
                setCountDownText(ss);
                m_st_text->setOverrideColor(irr::video::SColor(255, 229, 57, 53));
            }
            beginTimer = actualTime;
        }
        if (wallOfDead->canDropWall())
        {
            wallOfDead->createWallOfDead();
        }
    }

    GameObjectTimeContainer::SharedInstance()->callTimeOutObjects();

    std::vector<ACharacter *>::iterator it = characters.begin();
    ACharacter *winner = NULL;

    while (it != characters.end())
    {
        if (!(*it)->isDead())
        {
            (*it)->compute();
            winner = (*it);
        }
        ++it;
    }

    if ((is_gameOver = playerRanking.isTheEndOfTheGame(winner)))
    {
        if (gameOverTimer == 0 && winner)
        {
            gameOverTimer = getTimeSeconds();
            return ;
        }
        if (gameOverTimer + 1.5 > getTimeSeconds() && winner)
        {
            return ;
        }
        IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[0]);
        BomberMap::getMap()->removeBlocks();
        setGameState(RANKING_SCREEN);
        IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);
    }
}

double	GameManager::getTimeSeconds() const
{
    time_t	timer;
    struct tm	y2k;

    timer = time(NULL);
    memset(&y2k, 0, sizeof(y2k));
    y2k.tm_year = 100;
    y2k.tm_mday = 1;
    return (difftime(timer, mktime(&y2k)));

}

void    GameManager::addDeadPlayer(ACharacter *player)
{
    playerRanking.addPlayerToRank(player);
}

void    GameManager::willStartGame()
{
    GameObjectTimeContainer::SharedInstance()->removeAll();

    if (wallOfDead)
        delete wallOfDead;

    this->defaultFont = IrrlichtController::getDevice()->getGUIEnvironment()->getSkin()->getFont();

    if (m_st_text)
        m_st_text->remove();

    // TIMER COUNTDOWN
    countdown = GameManager::endOfGame;
    gameOverTimer = 0;
    beginTimer = getTimeSeconds();
    wallOfDead = new WallOfDead(GameManager::endOfGame);

    SoundManager::getManager()->stopAll();
    SoundManager::getManager()->play("battleIntro.wav");
    SoundManager::getManager()->play("battleTheme1.wav", 0, true, 0.5);
    std::vector<irr::core::vector2df> const &spawn = BomberMap::getMap()->getSpawn();

    characters.clear();
    IrrlichtController::getDevice()->setEventReceiver(eventGame);

    int		i = 0;

    eventGame->reset();
    for (std::list<PlayerInfo *>::iterator	it = m_playerInfo.begin() ;  it != m_playerInfo.end() ; ++it)
    {
        if ((*it)->GetIsIA())
        {
            characters.push_back(new IAPlayer((*it)->GetName(),
                                              (*it)->GetPos() == NULL ? spawn[i] : *((*it)->GetPos()),
                                              (*it)->GetMesh(),
                                              (*it)->GetTexture(),
                                              i + 1,
                                              IAPlayer::getDifficultyFromCode((*it)->GetIAStrength())
            ));
        }
        else
        {
            characters.push_back(new Player((*it)->GetName(),
                                            (*it)->GetPos() == NULL ? spawn[i] : *((*it)->GetPos()),
                                            (*it)->GetMesh(),
                                            (*it)->GetTexture(),
                                            i+1, *eventGame,
                                            (*it)->GetController()));
        }
        ++i;
    }
    playerRanking.clear();
    playerRanking.setPlayers(characters);
    activeCam(GameManager::GameCamera::GAME_CAMERA);
    BomberMap::getMap()->refreshCamera();
    BomberMap::getMap()->giveDangerMap().setSize(static_cast<size_t >(BomberMap::getMap()->getSize()));
    BomberMap::getMap()->giveDangerMap().refresh(BomberMap::getMap());

    std::wstringstream ss;

    ss << countdown;
    setCountDownText(ss);
}

void    GameManager::willStartMenu()
{
    IrrlichtController::getDevice()->setEventReceiver(uiEventReceiver);

}

UIManager *GameManager::getUIManager() const
{
    return (this->uiManager);
}

EventGame *GameManager::getEventGame() const
{
    return (this->eventGame);
}

void        GameManager::setFptr(initInstance _fptr)
{
    this->fptr = _fptr;
}

void GameManager::AddPlayer(PlayerInfo *player)
{
    if (player != nullptr)
    {
        m_playerInfo.push_back(player);
    }
}

void GameManager::ClearPlayers()
{
    for (std::list<PlayerInfo *>::iterator it = m_playerInfo.begin(), end = m_playerInfo.end(); it != end; ++it)
    {
        delete(*it);
    }
    m_playerInfo.clear();
}

void GameManager::AddPlayerFromUI(PlayerInfo *player)
{
    if (player != nullptr)
    {
        m_playerInfoUI.push_back(player);
    }
}

std::list<PlayerInfo *>::const_iterator GameManager::GetPlayers() const
{
    return m_playerInfo.begin();
}

std::string GameManager::ToString(std::wstring const &str)
{
    return std::string(str.begin(), str.end());
}

std::wstring GameManager::ToWstring(std::string const &str)
{
    return std::wstring(str.begin(), str.end());
}

void GameManager::SwapCharacterList()
{
    m_playerInfo.clear();
    m_playerInfo.merge(m_playerInfoUI);
}

GameOver *GameManager::getGameOver() const {
    return playerRanking.getGameOver();
}

void GameManager::destroyGameOver()
{
    playerRanking.destroyGameOver();
}

irr::scene::ICameraSceneNode *GameManager::getCam(GameCamera cam) const {
    return m_cameras[cam];
}

void GameManager::activeCam(GameCamera cam) {
    IrrlichtController::getSceneManager()->setActiveCamera(m_cameras[cam]);
}
