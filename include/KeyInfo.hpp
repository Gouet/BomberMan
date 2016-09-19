//
// Created by veyrie_f on 6/5/16.
//

#ifndef CPP_INDIE_STUDIO_KEYINFO_HPP
#define CPP_INDIE_STUDIO_KEYINFO_HPP

#include <iostream>
#include "ACharacter.hpp"

/*
 * Storage class for key infos
 */
template <class KeycodeType>
class KeyInfo
{
public:
    KeyInfo(ACharacter::ACTION action, KeycodeType keycode, std::string const& toString) :
            m_action(action),
            m_keycode(keycode),
            m_toString(toString)
    {

    }

    ~KeyInfo()
    {

    }

    std::string const& ToString() const
    {
        return m_toString;
    }

    ACharacter::ACTION GetAction() const
    {
        return m_action;
    }

    irr::EKEY_CODE GetKeycode() const
    {
        return m_keycode;
    }

private:
    ACharacter::ACTION m_action;
    KeycodeType m_keycode;
    std::string m_toString;
};

#endif //CPP_INDIE_STUDIO_KEYINFO_HPP
