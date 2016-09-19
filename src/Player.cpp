//
// Player.cpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Sun Jun  5 17:02:53 2016 Matthieu Tavernier
//

#include <iostream>
#include "ACharacter.hpp"
#include "Player.hpp"

Player::Player(std::string const &name, irr::core::vector2df const &pos,
               std::string const &mesh, std::string const &texture, int player,
               EventGame &eventGame, AController const *controller)
        : ACharacter(name, pos, mesh, texture, player), _eventGame(eventGame)
{
    (*this)->setName(name.c_str());
    this->_joystick = NULL;
    this->keyController = NULL;
    if ((_joystick = dynamic_cast<MotionController*>(const_cast<AController*>(controller)))) {
        eventGame.pushController(_joystick);
    } else if ((keyController = dynamic_cast<KeysController*>(const_cast<AController*>(controller)))) {
        _keycodes = keyController->getKeycodes();
    }
}

Player::~Player()
{

}

void		Player::serialize(irr::io::IXMLWriter *xmlr) const
{
    irr::core::vector2df	pos = getMapPos();

    std::string		meshStr = getMesh();
    std::string		textureStr = getTexture();

    std::wstring		xValue = L"" + std::to_wstring(pos.X);
    std::wstring		yValue = L"" + std::to_wstring(pos.Y);
    std::wstring		mesh = L"" ;
    mesh.assign(meshStr.begin(), meshStr.end());

    std::wstring		texture = L"";
    texture.assign(textureStr.begin(), textureStr.end());

    std::wstring		playerName = L"";
    playerName.assign(getName().begin(), getName().end());

    xmlr->writeElement(L"Player", true,
                       L"x", xValue.c_str(),
                       L"y", yValue.c_str(),
                       L"mesh", mesh.c_str(),
                       L"texture", texture.c_str(),
                       L"name", playerName.c_str()
    );
    xmlr->writeLineBreak();
}

void		Player::compute()
{
    ACharacter::ACTION  act = ACharacter::IDLE;
    // Joystick
    if (this->_joystick) {
        act = this->_joystick->getDirAxis(MotionController::LEFT_JOYSTICK);
        if (this->_joystick->IsButtonPressed(ACharacter::ACTION::BOMB)) {
            act = ACharacter::ACTION::BOMB;
        }
        if (this->_joystick->IsButtonPressed(ACharacter::ACTION::ACT)) {
            act = ACharacter::ACTION::ACT;
        }
    } else {
        // KeysCode
        if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::DOWN)->second)) {
            act = ACharacter::ACTION::DOWN;
        } else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::UP)->second)) {
            act = ACharacter::ACTION::UP;
        } else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::LEFT)->second)) {
            act = ACharacter::ACTION::LEFT;
        } else if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::RIGHT)->second)) {
            act = ACharacter::ACTION::RIGHT;
        }
        if (_eventGame.IsKeyDown(this->_keycodes.find(ACharacter::ACTION::BOMB)->second)) {
            act = ACharacter::ACTION::BOMB;
        }
        if (_eventGame.IsKeyDownOneTime(this->_keycodes.find(ACharacter::ACTION::ACT)->second)) {
            act = ACharacter::ACTION::ACT;
        }
    }
    this->action(act);
}
