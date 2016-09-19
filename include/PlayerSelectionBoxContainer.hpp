//
// Created by veyrie_f on 5/15/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP
#define CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP

#include <list>
#include "UIManager.hpp"
#include "MotionController.hpp"

class PlayerSelectionBox;
class UIEventReceiver;

/*
 * \brief Container managing all the player boxes in the GUI
 */
class PlayerSelectionBoxContainer
{
public:
    PlayerSelectionBoxContainer(UIManager *uiManager, UIEventReceiver *m_receiver);
    ~PlayerSelectionBoxContainer();

public:
    void SelectUp(int playerID);
    void SelectDown(int playerID);
    void SelectLeft(int playerID);
    void SelectRight(int playerID);
    void UpdateBoxes(irr::s32 id);
    void PlayerJoin(int playerID);

    void SelectSkin(std::string const& skin);
    void UnselectSkin(std::string const& skin);
    bool IsSkinAvailable(std::string const& skin) const;

    void SaveSelection();
    void KeyBind(int playerID) const;
    void KeySelect(int playerID) const;
    void OnKeyPressed(irr::EKEY_CODE key);
    void OnKeyPressed(irr::u32 key);

    UIEventReceiver const* GetEventReceiver() const;
private:

private:
    // Knows which box is selected by P1
    std::list<PlayerSelectionBox*> m_boxes;
    UIManager *m_manager;
    UIEventReceiver *m_receiver;
    std::list<std::string> m_availableSkins;
    // Used to save the relative rotation of the P1
    bool m_joined[4] = {false, false, false, false};
    PlayerSelectionBox *m_boxList[4];
};

#include "UIEventReceiver.hpp"

#endif //CPP_INDIE_STUDIO_PLAYERSELECTIONBOXCONTAINER_HPP
