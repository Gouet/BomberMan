//
// Created by veyrie_f on 4/27/16.
//

#include "UIManager.hpp"

UIManager::UIManager(irr::IrrlichtDevice *device) :
        m_device(device)
{
    if (m_device == nullptr)
    {
        throw UIException("No device assigned");
    }

    if ((m_videoDriver = m_device->getVideoDriver()) == nullptr)
    {
        throw UIException("No video driver found");
    }

    if ((m_env = m_device->getGUIEnvironment()) == nullptr)
    {
        throw UIException("No GUI environment found");
    }
}

UIManager::~UIManager()
{

}

irr::gui::IGUIElement *UIManager::GetElementFromID(irr::s32 id) const
{
    return m_env->getRootGUIElement()->getElementFromId(id);
}

void UIManager::SetSkinTransparency(irr::s32 alpha, irr::gui::IGUISkin *skin) const
{
    for (irr::s32 i=0; i<irr::gui::EGDC_COUNT ; ++i)
    {
        irr::video::SColor col = skin->getColor((irr::gui::EGUI_DEFAULT_COLOR)i);
        col.setAlpha(alpha);
        skin->setColor((irr::gui::EGUI_DEFAULT_COLOR)i, col);
    }
}

irr::IrrlichtDevice *UIManager::GetDevice() const
{
    return m_device;
}

irr::gui::IGUISkin const *UIManager::GetSkin() const
{
    return m_env->getSkin();
}

irr::gui::IGUIFont const *UIManager::GetFont(const irr::io::path& fileName) const
{
    return m_env->getFont(fileName);
}

void UIManager::SetFont(irr::gui::IGUIFont *font, irr::gui::EGUI_DEFAULT_FONT def) const
{
    m_env->getSkin()->setFont(font, def);
}

void UIManager::AddButton(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                          const wchar_t *text, const wchar_t *tip) const
{
    m_env->addButton(transform, parent, id, text, tip);
}

void UIManager::AddStaticText(const wchar_t *text, irr::core::rect<irr::s32> transform, bool hasBorder, bool wordWrap,
                              irr::gui::IGUIElement *parent, irr::s32 id, bool fillBackground) const
{
    m_env->addStaticText(text, transform, hasBorder, wordWrap, parent, id, fillBackground);
}

void UIManager::ClearEnv() const
{
    m_env->clear();
}

irr::gui::IGUIEnvironment *UIManager::GetEnv() const
{
    return m_env;
}
