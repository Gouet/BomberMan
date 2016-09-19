//
// Created by veyrie_f on 5/11/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERSELECTIONBOX_HPP
#define CPP_INDIE_STUDIO_PLAYERSELECTIONBOX_HPP


#include <list>
#include "UIManager.hpp"
#include "UIElements.hpp"
#include "ISelectionBox.hpp"
#include "PlayerSelectionBoxContainer.hpp"
#include "PlayerInfo.hpp"
#include "KeySelectionBox.hpp"

/*
 * \brief Represents a box to select the player character.
 * If it is an ia, the ia level is displayed. Otherwise, the character is displayed
 */
class PlayerSelectionBox : public ISelectionBox
{
public:
    PlayerSelectionBox(UIManager *uiManager, PlayerSelectionBoxContainer *container, irr::io::path const& sprite,
                       irr::core::rect<irr::s32> pos, UIElement::Menu elemName, bool bIsIaPlayer, UIElement::Menu id, int playerID);
    virtual ~PlayerSelectionBox();

public:
    void Update();
    void SelectNext();
    void SelectNextIA();
    void SelectPrev();
    void OnSelect();
    void OnKeyPressed(irr::EKEY_CODE key);
    void OnKeyPressed(irr::u32 key);
    UIElement::Menu GetId() const;
    irr::gui::IGUIButton const& GetButton() const;
    void SetFocus(bool bIsFocused) const;

    bool GetIaStatus() const;
    void SetIaStatus(bool isIA);
    std::wstring GetPlayerName() const;
    std::string const& GetSkin() const;
    PlayerInfo::IAStrength GetIAStrength() const;

    void KeyBind() const;

private:
    UIManager *m_manager;
    PlayerSelectionBoxContainer *m_container;
    irr::video::IVideoDriver *m_driver;
    mutable std::list<std::string> m_images;
    bool m_bIsIaPlayer;
    irr::core::rect<irr::s32> m_pos;
    irr::scene::ISceneManager *m_sceneManager;
    irr::gui::IGUIImage *m_image;
    irr::scene::IAnimatedMeshSceneNode *m_modelNode = nullptr;
    std::list<std::string> m_models;
    int m_playerID;
    irr::gui::IGUIButton *m_button;
    UIElement::Menu m_id;
    irr::gui::IGUIEditBox *m_playerName;
    KeySelectionBox *m_keySelection;
};


#endif //CPP_INDIE_STUDIO_PLAYERSELECTIONBOX_HPP
