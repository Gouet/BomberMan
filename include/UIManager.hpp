//
// Created by veyrie_f on 4/27/16.
//

#ifndef CPP_INDIE_STUDIO_UIMANAGER_HPP
#define CPP_INDIE_STUDIO_UIMANAGER_HPP

#include <stdexcept>
#include <map>
#include "IrrlichtController.hpp"

class UIManager
{
public:
    UIManager(irr::IrrlichtDevice *device);
    virtual ~UIManager();

    // Encapsulates all the ui components
public:
    irr::IrrlichtDevice *GetDevice() const;
    irr::gui::IGUIEnvironment *GetEnv() const;
    irr::gui::IGUISkin const *GetSkin() const;
    irr::gui::IGUIFont const* GetFont(const irr::io::path& fileName) const;
    void SetFont(irr::gui::IGUIFont *font, irr::gui::EGUI_DEFAULT_FONT def) const;

    void AddButton(irr::core::rect<irr::s32> transform, irr::gui::IGUIElement *parent, irr::s32 id,
                   const wchar_t *text, const wchar_t *tip) const;

    void AddStaticText(const wchar_t *text, irr::core::rect<irr::s32> transform, bool hasBorder, bool wordWrap,
                           irr::gui::IGUIElement *parent, irr::s32 id, bool fillBackground) const;

    // Changes alpha value for all the objects
    void SetSkinTransparency(irr::s32 alpha, irr::gui::IGUISkin * skin) const;

    irr::gui::IGUIElement *GetElementFromID(irr::s32 id) const;

    void ClearEnv() const;

    // Exception class
public:
    class UIException : public std::runtime_error
    {
    public:
        UIException(std::string const& msg) : runtime_error(msg)
        {}
    };

private:
    irr::IrrlichtDevice *m_device;
    irr::video::IVideoDriver *m_videoDriver;
    irr::gui::IGUIEnvironment* m_env;
};


#endif //CPP_INDIE_STUDIO_UIMANAGER_HPP
