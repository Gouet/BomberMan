/*
** KeysController.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 10:00:02 2016 Adrien WERY
** Last update	Fri Apr 29 10:52:18 2016 Adrien WERY
*/

#include <iostream>
#include "KeysController.hpp"

KeysController::KeysController(std::map<ACharacter::ACTION, irr::EKEY_CODE> const &keycodes) : _keycodes(keycodes)
{
/*
 * Default keys
 */
    m_keysToString = {
            "-",
            "Left Button",
            "Right Button",
            "Cancel",
            "Middle Button",
            "X Button 1",
            "X Button 2",
            "-",
            "Back",
            "Tab",
            "-",
            "-",
            "Clear",
            "Return",
            "-",
            "-",
            "Shift",
            "Control",
            "Menu",
            "Pause",
            "Capital",
            "Kana",
            "-",
            "Junja",
            "Final",
            "Kanji",
            "-",
            "Escape",
            "Convert",
            "Nonconvert",
            "Accept",
            "Mode Change",
            "Space",
            "Priot",
            "Next",
            "End",
            "Home",
            "Left",
            "Up",
            "Right",
            "Down",
            "Select",
            "Print",
            "Execute",
            "Snapshot",
            "Insert",
            "Delete",
            "Help",
            "0",
            "1",
            "2",
            "3",
            "4",
            "5",
            "6",
            "7",
            "8",
            "9",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "A",
            "B",
            "C",
            "D",
            "E",
            "F",
            "G",
            "H",
            "I",
            "J",
            "K",
            "L",
            "M",
            "N",
            "O",
            "P",
            "Q",
            "R",
            "S",
            "T",
            "U",
            "V",
            "W",
            "X",
            "Y",
            "Z",
            "Left Windows",
            "Right Windows",
            "Apps",
            "-",
            "Sleep",
            "Numpad 0",
            "Numpad 1",
            "Numpad 2",
            "Numpad 3",
            "Numpad 4",
            "Numpad 5",
            "Numpad 6",
            "Numpad 7",
            "Numpad 8",
            "Numpad 9",
            "Numpad *",
            "Numpad +",
            "Numpad /",
            "Numpad -",
            "Numpad .",
            "Numpad /",
            "F1",
            "F2",
            "F3",
            "F4",
            "F5",
            "F6",
            "F7",
            "F8",
            "F9",
            "F10",
            "F11",
            "F12",
            "F13",
            "F14",
            "F15",
            "F16",
            "F17",
            "F18",
            "F19",
            "F20",
            "F21",
            "F22",
            "F23",
            "F24",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "Num Lock",
            "Scroll Lock",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "Left Shift",
            "Right Shight",
            "Left Control",
            "Right Control",
            "Left Menu",
            "Right Menu",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "Plus",
            "Comma",
            "Minus",
            "Period",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "-",
            "Attn",
            "CrSel",
            "ExSel",
            "Erase OEF",
            "Play",
            "Zoom",
            "PA1",
            "OEM Clear",
            "-"
    };
}

KeysController::~KeysController()
{
}

std::map<ACharacter::ACTION, irr::EKEY_CODE> const  &KeysController::getKeycodes() const
{
    return (this->_keycodes);
}

void KeysController::BindAction(ACharacter::ACTION action, irr::EKEY_CODE key)
{
    std::map<ACharacter::ACTION, irr::EKEY_CODE>::iterator it;

    // if key is already bind, assign old bind to it
    for (it = _keycodes.begin(); it != _keycodes.end(); ++it)
    {
        if ((*it).second == key)
        {
            (*it).second = _keycodes[action];
            break;
        }
    }

    // Assigns new key
    _keycodes[action] = key;
}

const std::vector<KeyInfo<irr::EKEY_CODE >> &KeysController::ToString() const
{
    std::map<ACharacter::ACTION, irr::EKEY_CODE>::const_iterator it;
    std::string toAdd;

    m_toString.clear();
    int i = 0;
    for (it = _keycodes.begin(); it != _keycodes.end(); ++it)
    {
        toAdd = ACharacter::textAction[i++];
        for (unsigned long j = toAdd.size(); j < 60; j++)
        {
            toAdd += ".";
        }
        toAdd += m_keysToString[(*it).second];
        m_toString.push_back(KeyInfo<irr::EKEY_CODE >((*it).first, (*it).second, toAdd));
    }
    return m_toString;
}
