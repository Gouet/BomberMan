//
// Created by veyrie_f on 5/27/16.
//

#ifndef CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP
#define CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP

#include "ISelectionBox.hpp"
#include "UIManager.hpp"
#include "UIElements.hpp"
#include "AController.hpp"
#include "ACharacter.hpp"
#include "KeysController.hpp"

class KeySelectionBox : public ISelectionBox
{
public:
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID);
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID, AController const*controller);
    explicit KeySelectionBox(UIManager *uiManager, irr::core::rect<irr::s32> pos, UIElement::Menu elemID, int playerID, irr::SJoystickInfo info);
    virtual ~KeySelectionBox();

public:
    void SelectNext();
    void SelectPrev();
    void Update();
    void OnSelect();
    void OnKeyPress(irr::EKEY_CODE key);
    void OnKeyPress(irr::u32 key);
    bool IsSelecting() const;

public:
    void SetActive(bool bActive) const;
    bool IsActive() const;

private:
    void CreateListBox(irr::core::rect<irr::s32> pos, UIElement::Menu elemID);
    void UpdateElements();

private:
    UIManager *m_manager;
    int m_playerID;
    irr::gui::IGUIListBox *m_listBox;
    irr::gui::IGUIImage *m_background;
    AController *m_controller;
    std::vector<KeyInfo<irr::EKEY_CODE> > m_keys;
    std::vector<KeyInfo<MotionController::ControllerKey > > m_motions;
    bool m_isSelecting = false;
};


#endif //CPP_INDIE_STUDIO_KEYSELECTIONBOX_HPP
