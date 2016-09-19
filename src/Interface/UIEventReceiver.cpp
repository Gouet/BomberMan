//
// Created by veyrie_f on 4/27/16.
//

#include <dirent.h>
#include <algorithm>
#include <sys/stat.h>
#include "UIEventReceiver.hpp"
#include "Texture.hpp"
#include "GameManager.hpp"
#include "SoundManager.hpp"

UIEventReceiver::UIEventReceiver(UIManager const &manager) :
        m_manager(manager), m_device(manager.GetDevice())
{
    irr::core::array<irr::SJoystickInfo>    joystickInfo;
    int idx = 1;

    this->defaultFont = IrrlichtController::getDevice()->getGUIEnvironment()->getSkin()->getFont();

    if (IrrlichtController::getDevice()->activateJoysticks(joystickInfo))
    {
        // We start at index 1 to ignore accelerometer
        for (size_t i = 0; i < joystickInfo.size(); i++)
        {
            if (joystickInfo[i].Axes > 0 && joystickInfo[i].Buttons > 0)
            {
		        m_joysticks[idx] = new MotionController(joystickInfo[i]);
		        m_joysticksId[i] = idx;
                ++idx;
            }
        }
    }
    for (std::vector<std::map<ACharacter::ACTION, irr::EKEY_CODE>>::const_iterator it = EventGame::_keycodes.begin();
         it != EventGame::_keycodes.end(); ++it)
    {
        m_keymaps.push_back(new KeysController(*it));
    }

    for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i)
    {
        KeyIsDown[i] = false;
    }

    // Sets callbacks for GUI
    m_guiEvents[irr::gui::EGET_LISTBOX_CHANGED] = &UIEventReceiver::OnListBox;
    m_guiEvents[irr::gui::EGET_LISTBOX_SELECTED_AGAIN] = &UIEventReceiver::OnListBox;
    m_guiEvents[irr::gui::EGET_BUTTON_CLICKED] = &UIEventReceiver::OnButtonClicked;
    m_guiEvents[irr::gui::EGET_ELEMENT_FOCUSED] = &UIEventReceiver::OnElementFocused;
    SoundManager::getManager()->play("welcome.wav");
    SoundManager::getManager()->play("battleMenu.wav", 0, true, 0.5);
    DisplaySplashScreen();
}

UIEventReceiver::~UIEventReceiver()
{
    if (m_boxContainer != nullptr)
    {
        delete m_boxContainer;
    }

    for (std::map<int, MotionController *>::iterator it = m_joysticks.begin(); it != m_joysticks.end(); ++it)
    {
        delete (*it).second;
    }

    for (std::vector<KeysController *>::iterator it = m_keymaps.begin(); it != m_keymaps.end(); ++it)
    {
        delete (*it);
    }
}

/*
 * \brief Should return continue if event is completely handled
 */
bool UIEventReceiver::OnEvent(const irr::SEvent &event_copy)
{
    // Update joysticks inputs
    HandleJoysticks(event_copy);

    // Key inputs
    EVENT_STATE eventState = OnKeyInput(event_copy);
    if (eventState == HANDELD) return true;
    if (eventState == NOT_HANDLED) return false;

    // GUI events
    if (event_copy.EventType == irr::EET_GUI_EVENT)
    {
        eventState = OnGUIEvent(event_copy);
        if (eventState == HANDELD) return true;
        if (eventState == NOT_HANDLED) return false;
    }

    // Updates menu visibility according to the current game state
    if (fptr != nullptr)
    {
        if (m_boxContainer != nullptr)
        {
            delete m_boxContainer;
            m_boxContainer = nullptr;
        }
        m_manager.ClearEnv();
        m_buttons.clear();
        (this->*fptr)();
        GameManager::SharedInstance()->setPrevGameState(GameManager::SharedInstance()->getGameState());
    }
    fptr = nullptr;

    RefreshButtons();

    return false;
}

void UIEventReceiver::DisplayGameHUD()
{
}

// Show the game main menu
void UIEventReceiver::DisplayMainMenu()
{
  IrrlichtController::getDevice()->getGUIEnvironment()->getSkin()->setFont(defaultFont);
  
    SoundManager::getManager()->play("SelectYourPlayer.wav");
    irr::gui::IGUIImage *img = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND,  L"", true);
    GameManager::SharedInstance()->ClearPlayers();
    img->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("playerSelection").texture.c_str()));
    img->setScaleImage(true);
    m_boxContainer = new PlayerSelectionBoxContainer(&m_manager, this);
}

// Splash screen waiting for player to press some button
void UIEventReceiver::DisplaySplashScreen()
{
    irr::gui::IGUIImage *image = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("menuScene").texture.c_str()));

    image->setScaleImage(true);

    image = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BUTTON_START, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("menuSceneStart").texture.c_str()));

    image->setScaleImage(true);
}

/**
 * \brief Map selection
 */
void UIEventReceiver::DisplayMapMenu()
{
    SoundManager::getManager()->play("SelectMap.wav");
    m_maps = new MapSelectionBox(&m_manager, this, irr::core::rect<irr::s32>(IrrlichtController::width * 0.7, IrrlichtController::height * 0.1,
                                                                       IrrlichtController::width * 0.95, IrrlichtController::height * 0.9),
                                               UIElement::MAP_SELECTION);

    // Looks for saved games
    DIR *dir = opendir("tmpSaveMap");
    if (dir != nullptr)
    {
        for (dirent *files = readdir(dir); files != NULL; files = readdir(dir))
        {
            #ifdef __linux__
             if (files->d_type == 8)
            #elif _WIN32
             struct stat    fileStats;

             stat(files->d_name, &fileStats);
             if (S_ISREG(fileStats.st_mode))
            #endif
            {
                m_maps->AddItem(std::string(files->d_name));
            }
        }
    }
    closedir(dir);

    // Creates default map
    if (!m_spawned)
    {
        m_spawned = true;
        BomberMap::deleteMap();
        BomberMap::newMap(BINDIR"media/smallMap/map1.xml");
        BomberMap::getMap()->genMap();
    }
}

// Pause menu from pause button
void UIEventReceiver::DisplayPauseMenu()
{
    m_buttons.push_back(m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 300,
                                                  IrrlichtController::height / 2.5 - 50,
                                                  IrrlichtController::width / 2.0 + 300,
                                                  IrrlichtController::height / 2.5 + 50),
                        nullptr, UIElement::CONTINUE, L"Continue", L""));

    m_buttons.push_back(m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 300,
                                                  IrrlichtController::height / 2.0 - 50,
                                                  IrrlichtController::width / 2.0 + 300,
                                                  IrrlichtController::height / 2.0 + 50),
                        nullptr, UIElement::SPLASH_BUTTON_START, L"Quitter", L""));

    m_buttons.push_back(m_manager.GetEnv()->addButton(irr::core::rect<irr::s32>(IrrlichtController::width / 2.0 - 300,
                                                  IrrlichtController::height / 1.66 - 50,
                                                  IrrlichtController::width / 2.0 + 300,
                                                  IrrlichtController::height / 1.66 + 50),
                        nullptr, UIElement::SAVE, L"Save", L""));
}

// Screen displayed between level loading
void UIEventReceiver::DisplayLoadingScreen()
{
    irr::gui::IGUIImage *image = m_manager.GetEnv()->addImage(
            irr::core::rect<irr::s32>(0, 0, IrrlichtController::width, IrrlichtController::height),
            nullptr, UIElement::SPLASH_BACKGROUND, L"", true);
    image->setImage(IrrlichtController::getDevice()->getVideoDriver()->getTexture(
            BomberManTexture::getModel("menuScene").texture.c_str()));
}

void UIEventReceiver::RefreshButtons()
{
    int i = 0;

    for (std::list<irr::gui::IGUIButton *>::iterator it = m_buttons.begin(); it != m_buttons.end(); ++it, ++i)
    {
        if (i == 0)
        {
            m_manager.GetEnv()->setFocus(*it);
            (*it)->setPressed(true);
        }
    }
}

void UIEventReceiver::SelectNextButton()
{
    if (m_buttons.size() == 0)
        return;
    irr::gui::IGUIButton *b = m_buttons.front();
    m_buttons.pop_front();
    m_buttons.push_back(b);
}

void UIEventReceiver::SelectPrevButton()
{
    if (m_buttons.size() == 0)
        return;
    irr::gui::IGUIButton *b = m_buttons.back();
    m_buttons.pop_back();
    m_buttons.push_front(b);
}

/*
 * \brief Handles key Input events
 */
UIEventReceiver::EVENT_STATE UIEventReceiver::OnKeyInput(const irr::SEvent &event_copy)
{
    if (event_copy.EventType == irr::EET_KEY_INPUT_EVENT)
    {
        // Updates the containers
        if (event_copy.KeyInput.PressedDown && m_boxContainer != nullptr)
        {
            m_boxContainer->OnKeyPressed(event_copy.KeyInput.Key);
        }

        switch (event_copy.KeyInput.Key)
        {
            case irr::KEY_ESCAPE:
                // Unpause the game if in pause state
                if (GameManager::SharedInstance()->getGameState() == GameManager::PAUSE)
                {
                    GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                    IrrlichtController::getDevice()->setEventReceiver(GameManager::SharedInstance()->getEventGame());
                    fptr = &UIEventReceiver::DisplayGameHUD;
                }
                // Quits the game otherwise
                else
                {
                    IrrlichtController::getDevice()->closeDevice();
                }
                break;

            case irr::KEY_RETURN:
                // Enters the main menu
                if (GameManager::SharedInstance()->getGameState() == GameManager::SPLASH_SCREEN &&
                    event_copy.KeyInput.PressedDown)
                {
                    GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                    fptr = &UIEventReceiver::DisplayMainMenu;
                    return HANDELD;
                }
                else if (GameManager::SharedInstance()->getGameOver() &&
                        GameManager::SharedInstance()->getGameState() == GameManager::RANKING_SCREEN &&
                         event_copy.KeyInput.PressedDown)
                {
                    SkipEndScreen();
                    return HANDELD;
                }
                else if (GameManager::SharedInstance()->getGameState() == GameManager::MENU_MAP
                        && event_copy.KeyInput.PressedDown)
                {
                    StartGame();
                }
                break;

                //////////////////
                /// Player 1
                //////////////////
            case irr::KEY_RSHIFT:
                // Player 1 joined
                if (m_boxContainer != nullptr)
                {
                    m_boxContainer->PlayerJoin(1);
                    return HANDELD;
                }
                break;

            case irr::KEY_KEY_N:
                if (m_boxContainer != nullptr && event_copy.KeyInput.PressedDown)
                {
                    m_boxContainer->KeyBind(1);
                }
                break;

            case irr::KEY_RCONTROL:
                if (m_boxContainer != nullptr && event_copy.KeyInput.PressedDown)
                {
                    m_boxContainer->KeySelect(1);
                }
                break;

            case irr::KEY_DOWN:
                if (event_copy.KeyInput.PressedDown)
                {
                    SelectNextButton();
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectDown(1);
                    }
                    else if (m_maps != nullptr)
                    {
                        m_maps->SelectPrev();
                    }
                }
                break;

            case irr::KEY_UP:
                if (event_copy.KeyInput.PressedDown)
                {
                    SelectPrevButton();
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectUp(1);
                    }
                    else if (m_maps != nullptr)
                    {
                        m_maps->SelectNext();
                    }
                }
                break;

            case irr::KEY_LEFT:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectLeft(1);
                    }
                }
                break;

            case irr::KEY_RIGHT:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectRight(1);
                    }
                }
                break;

                ////////////////
                // Player 2
                ////////////////
            case irr::KEY_SPACE:
                // Player 2 joined
                if (m_boxContainer != nullptr)
                {
                    m_boxContainer->PlayerJoin(2);
                    return HANDELD;
                }
                break;

            case irr::KEY_KEY_E:
                if (m_boxContainer != nullptr && event_copy.KeyInput.PressedDown)
                {
                    m_boxContainer->KeySelect(2);
                }
                break;

            case irr::KEY_KEY_C:
                if (m_boxContainer != nullptr && event_copy.KeyInput.PressedDown)
                {
                    m_boxContainer->KeyBind(2);
                }
                break;

            case irr::KEY_KEY_S:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectDown(2);
                    }
                }
                break;

            case irr::KEY_KEY_W:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectUp(2);
                    }
                }
                break;

            case irr::KEY_KEY_A:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectLeft(2);
                    }
                }
                break;

            case irr::KEY_KEY_D:
                if (event_copy.KeyInput.PressedDown)
                {
                    if (m_boxContainer != nullptr)
                    {
                        m_boxContainer->SelectRight(2);
                    }
                }
                break;

            default:
                break;
        }
    }
    return IGNORED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnGUIEvent(const irr::SEvent &event_copy)
{
    if (m_guiEvents.find(event_copy.GUIEvent.EventType) != m_guiEvents.end())
    {
        return (this->*m_guiEvents[event_copy.GUIEvent.EventType])(event_copy);
    }
    return NOT_HANDLED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnListBox(const irr::SEvent &event_copy)
{
    switch (event_copy.GUIEvent.EventType)
    {
        case irr::gui::EGET_LISTBOX_CHANGED:
        {
            UpdateMap();
            break;
        }
        case irr::gui::EGET_LISTBOX_SELECTED_AGAIN:
        {
            StartGame();
        }

        default:
            break;
    }
    return IGNORED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnButtonClicked(const irr::SEvent &event_copy)
{
    irr::s32 id = event_copy.GUIEvent.Caller->getID();

    switch (id)
    {
        case UIElement::SPLASH_BUTTON_START:
            BomberMap::deleteMap();
            GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
            SoundManager::getManager()->stopAll();
            SoundManager::getManager()->play("battleMenu.wav", 0, true, 0.5);
            fptr = &UIEventReceiver::DisplayMainMenu;
            break;

        case UIElement::MAIN_MENU_BUTTON_1P:
            GameManager::SharedInstance()->setGameState(GameManager::MENU_MAP);
            fptr = &UIEventReceiver::DisplayMapMenu;
            break;

        case UIElement::MAP_SELECTION1:
            fptr = &UIEventReceiver::DisplayGameHUD;
            GameManager::SharedInstance()->setFptr(&GameManager::willStartGame);
            GameManager::SharedInstance()->setGameState(GameManager::PLAY);
            break;

        case UIElement::SAVE:
            BomberMap::getMap()->save();
                break;

            case UIElement::CONTINUE:
                fptr = &UIEventReceiver::DisplayGameHUD;
                IrrlichtController::getDevice()->setEventReceiver(
                        GameManager::SharedInstance()->getEventGame());
                GameManager::SharedInstance()->setGameState(GameManager::PLAY);
                break;

            default:
                break;
    }
    return IGNORED;
}

UIEventReceiver::EVENT_STATE UIEventReceiver::OnElementFocused(const irr::SEvent &event_copy)
{
    irr::s32 id = event_copy.GUIEvent.Caller->getID();

    switch (id)
    {
        // For the player selection menu
        case UIElement::MAIN_MENU_BUTTON_1P:
        case UIElement::MAIN_MENU_BUTTON_2P:
        case UIElement::MAIN_MENU_BUTTON_3P:
        case UIElement::MAIN_MENU_BUTTON_4P:
            if (m_boxContainer != nullptr)
            {
                m_boxContainer->UpdateBoxes(id);
            }
            break;

        default:
            return NOT_HANDLED;
            break;
    }

    return NOT_HANDLED;
}

void UIEventReceiver::HandleJoysticks(irr::SEvent const& event_copy)
{
      if (m_joysticksId.find(event_copy.JoystickEvent.Joystick) == m_joysticksId.end())
          return;

    irr::u8 idxJoystick = m_joysticksId[event_copy.JoystickEvent.Joystick];

    if (event_copy.EventType == irr::EET_JOYSTICK_INPUT_EVENT && m_joysticks[idxJoystick])
    {
        m_joysticks[idxJoystick]->setData(event_copy.JoystickEvent);
        long playerID = idxJoystick;


        // Validates on splash screen
        if (m_joysticks[idxJoystick]->IsButtonPressedOneTime(MotionController::ControllerKey::CROSS))
        {
            if (GameManager::SharedInstance()->getGameState() == GameManager::SPLASH_SCREEN)
            {
                GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
                fptr = &UIEventReceiver::DisplayMainMenu;
            }
        }

        // Notifies key pressed
        if (m_joysticks[idxJoystick])
        {
            if (m_boxContainer != nullptr)
            {
                m_boxContainer->OnKeyPressed(m_joysticks[idxJoystick]->getData().ButtonStates);
            }
        }

        // P1 validates character selection
        if (m_joysticks[idxJoystick]->IsButtonPressedOneTime(MotionController::ControllerKey::R2))
        {
            if (playerID == 1 && GameManager::SharedInstance()->getGameState() == GameManager::MAIN_MENU)
            {
                GameManager::SharedInstance()->setGameState(GameManager::MENU_MAP);
                fptr = &UIEventReceiver::DisplayMapMenu;
            }
            else if (playerID == 1 && GameManager::SharedInstance()->getGameState() == GameManager::MENU_MAP)
            {
                StartGame();
            }
            else if (playerID == 1 && GameManager::SharedInstance()->getGameState() == GameManager::RANKING_SCREEN
                    && GameManager::SharedInstance()->getGameOver())
            {
                SkipEndScreen();
            }
        }

        // Joins the party
        if (m_joysticks[idxJoystick]->IsButtonPressedOneTime(MotionController::ControllerKey::CIRCLE))
        {
            if (m_boxContainer != nullptr)
            {
                m_boxContainer->PlayerJoin(playerID);
            }
        }

        // Binds a key
        if (m_joysticks[idxJoystick]->IsButtonPressedOneTime(MotionController::ControllerKey::L2))
        {
            if (m_boxContainer != nullptr)
            {
                m_boxContainer->KeySelect(playerID);
            }
        }

        // Opens the key bind menu
        if (m_joysticks[idxJoystick]->IsButtonPressedOneTime(MotionController::ControllerKey::SQUARE))
        {
            if (m_boxContainer != nullptr)
            {
                m_boxContainer->KeyBind(playerID);
            }
        }

        // Navigates in menus
        ACharacter::ACTION act = m_joysticks[idxJoystick]->getDirAxisOneTime(MotionController::LEFT_JOYSTICK);
        if (act != ACharacter::IDLE)
        {
            if (m_boxContainer != nullptr)
            {
                switch (act)
                {
                    case ACharacter::LEFT:
                        m_boxContainer->SelectLeft(playerID);
                        break;

                    case ACharacter::RIGHT:
                        m_boxContainer->SelectRight(playerID);
                        break;

                    case ACharacter::UP:
                        m_boxContainer->SelectUp(playerID);
                        break;

                    case ACharacter::DOWN:
                        m_boxContainer->SelectDown(playerID);
                        break;

                    default:
                        break;
                }
            }
            else if (m_maps != nullptr && playerID == 1)
            {
                switch (act)
                {
                    case ACharacter::UP:
                        m_maps->SelectNext();
                        break;

                    case ACharacter::DOWN:
                        m_maps->SelectPrev();
                        break;

                    default:
                        break;
                }
            }
        }
    }
}

MotionController const *UIEventReceiver::GetJoystick(int id) const
{
    if (m_joysticks.find(id) == m_joysticks.end())
    {
        return nullptr;
    }
    return m_joysticks[id];
}

KeysController const *UIEventReceiver::GetKeyboard(unsigned int id) const
{
    if (id == 0 || id > m_keymaps.size())
    {
        return nullptr;
    }
    return m_keymaps[id - 1];
}

void UIEventReceiver::UpdateMapMenu(bool isSelection)
{
    if (m_maps == nullptr)
        return;

    if (!isSelection && !m_spawned)
    {
        UpdateMap();
    }
    else if (isSelection)
    {
        StartGame();
    }
}

void UIEventReceiver::SetSpawned(bool spawned)
{
    m_spawned = spawned;
}

void UIEventReceiver::StartGame()
{
    // Empties the list of players if the map is a saved one
    if (GameManager::ToString(m_maps->GetSelected()) == "Map 1"
        || GameManager::ToString(m_maps->GetSelected()) == "Map 2"
        || GameManager::ToString(m_maps->GetSelected()) == "Map 3")
    {
        GameManager::SharedInstance()->SwapCharacterList();
        delete m_maps;
    }
    m_maps = nullptr;
    fptr = &UIEventReceiver::DisplayGameHUD;
    GameManager::SharedInstance()->setFptr(&GameManager::willStartGame);
    GameManager::SharedInstance()->setGameState(GameManager::PLAY);
    m_spawned = false;
}

void UIEventReceiver::UpdateMap()
{
    m_spawned = true;
    BomberMap::deleteMap();
    if (GameManager::ToString(m_maps->GetSelected()) == "Map 1")
    {
        BomberMap::newMap(BINDIR"media/smallMap/map1.xml");
        BomberMap::getMap()->genMap();
    }
    else if (GameManager::ToString(m_maps->GetSelected()) == "Map 2")
    {
        BomberMap::newMap(BINDIR"media/mediumMap/map1.xml");
        BomberMap::getMap()->genMap();
    }
    else if (GameManager::ToString(m_maps->GetSelected()) == "Map 3")
    {
        BomberMap::newMap(BINDIR"media/largeMap/map1.xml");
        BomberMap::getMap()->genMap();
    }
    else
    {
        GameManager::SharedInstance()->ClearPlayers();
        BomberMap::createMapFromSave("./tmpSaveMap/" + GameManager::ToString(m_maps->GetSelected()));
    }
}

std::map<int, MotionController *> const &UIEventReceiver::GetJoysticks() const
{
    return m_joysticks;
}

std::vector<KeysController *> const &UIEventReceiver::GetKeyboards() const
{
    return m_keymaps;
}

void UIEventReceiver::SkipEndScreen()
{
    if (!GameManager::SharedInstance()->getGameOver()->getStatus())
    {
        if (BomberMap::getMap()->getSize() == SMALL_SIZE)
            BomberMap::newMap(BINDIR"media/smallMap/map1.xml");
        else if (BomberMap::getMap()->getSize() == MEDIUM_SIZE)
            BomberMap::newMap(BINDIR"media/mediumMap/map1.xml");
        else
            BomberMap::newMap(BINDIR"media/largeMap/map1.xml");
        BomberMap::getMap()->genMap();
        fptr = &UIEventReceiver::DisplayGameHUD;
        GameManager::SharedInstance()->setFptr(&GameManager::willStartGame);
        GameManager::SharedInstance()->setGameState(GameManager::PLAY);
    }
    else
    {
        GameManager::SharedInstance()->destroyGameOver();
        GameManager::SharedInstance()->setGameState(GameManager::MAIN_MENU);
        fptr = &UIEventReceiver::DisplayMainMenu;
    }
}
