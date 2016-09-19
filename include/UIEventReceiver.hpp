//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
#define CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP

#include <iostream>
#include <vector>
#include <list>
#include "irrlicht.h"
#include "UIElements.hpp"
#include "UIManager.hpp"
#include "PlayerSelectionBox.hpp"
#include "PlayerSelectionBoxContainer.hpp"
#include "MotionController.hpp"
#include "KeysController.hpp"
#include "MapSelectionBox.hpp"

class PlayerSelectionBoxContainer;

// Event receiver for ui
class UIEventReceiver : public irr::IEventReceiver
{
private:
    enum EVENT_STATE
    { HANDELD, NOT_HANDLED, IGNORED };

public:
    UIEventReceiver(UIManager const& manager);
    virtual ~UIEventReceiver();

public:
    virtual bool OnEvent(const irr::SEvent &event);
    MotionController const*GetJoystick(int id) const;
    KeysController const*GetKeyboard(unsigned int id) const;

public:
    void DisplayPauseMenu();
    void UpdateMapMenu(bool isSelection = false);
    void SetSpawned(bool spawned);
    std::map<int, MotionController *> const&GetJoysticks() const;
    std::vector<KeysController *> const& GetKeyboards() const;

private:
    void DisplayMainMenu();
    void DisplaySplashScreen();
    void DisplayMapMenu();
    void DisplayLoadingScreen();
    void DisplayGameHUD();
    void UpdateMap();
    void StartGame();
    void SkipEndScreen();

    /*
     * \brief Event handlers
     */
private:
    void HandleJoysticks(irr::SEvent const&event);

    EVENT_STATE OnKeyInput(const irr::SEvent &event);
    EVENT_STATE OnGUIEvent(const irr::SEvent &event);
    EVENT_STATE OnListBox(const irr::SEvent &event);
    EVENT_STATE OnButtonClicked(const irr::SEvent &event);
    EVENT_STATE OnElementFocused(const irr::SEvent &event);

    /*
     * \brief Button handling
     */
    void RefreshButtons();
    void SelectNextButton();
    void SelectPrevButton();

private:
    UIManager m_manager;
    irr::IrrlichtDevice *m_device;

    void (UIEventReceiver::*fptr)() = nullptr;
    std::list<irr::gui::IGUIButton*> m_buttons;
    PlayerSelectionBoxContainer *m_boxContainer = nullptr;
    MapSelectionBox *m_maps = nullptr;

  // default font
  irr::gui::IGUIFont		*defaultFont;

    // Avoid multiple spawn of the map
    bool m_spawned = false;

    // Joysticks
    mutable std::map<int, MotionController *> m_joysticks;
    std::vector<KeysController *> m_keymaps;
    mutable bool    KeyIsDown[irr::KEY_KEY_CODES_COUNT];
    typedef EVENT_STATE (UIEventReceiver::*event)(const irr::SEvent &);
    std::map<irr::gui::EGUI_EVENT_TYPE, event> m_guiEvents;
    std::map<irr::u8, irr::u8>	m_joysticksId;
};


#endif //CPP_INDIE_STUDIO_UIEVENTRECEIVER_HPP
