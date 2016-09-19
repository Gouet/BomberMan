//
// Created by veyrie_f on 6/4/16.
//

#ifndef CPP_INDIE_STUDIO_MAPSELECTIONBOX_HPP
# define CPP_INDIE_STUDIO_MAPSELECTIONBOX_HPP

#include <list>
#include "ISelectionBox.hpp"
#include "UIManager.hpp"
#include "UIElements.hpp"

class UIEventReceiver;

class MapSelectionBox : ISelectionBox
{
public:
    MapSelectionBox(UIManager *uiManager, UIEventReceiver *eventReceiver,
                    irr::core::rect<irr::s32> pos, UIElement::Menu elemName);
    virtual ~MapSelectionBox();

public:
    virtual void Update();
    virtual void SelectNext();
    virtual void SelectPrev();
    virtual void OnSelect();

    wchar_t const* GetSelected() const;
    void AddItem(std::string const& name);

private:
    UIManager *m_manager;
    UIEventReceiver *m_receiver;
    irr::gui::IGUIListBox *m_list;
    std::list<std::string> m_names;
};

#include "UIEventReceiver.hpp"

#endif //CPP_INDIE_STUDIO_MAPSELECTIONBOX_HPP
