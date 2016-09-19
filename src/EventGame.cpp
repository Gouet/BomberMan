/*
** EventGame.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Wed Apr 27 15:16:31 2016 Adrien WERY
** Last update	Sat Apr 30 01:04:43 2016 Adrien WERY
*/

#include <iostream>
#include "EventGame.hpp"

const std::vector<std::map<ACharacter::ACTION, irr::EKEY_CODE>> EventGame::_keycodes({
    {
      {ACharacter::LEFT, irr::KEY_LEFT},
	{ACharacter::RIGHT, irr::KEY_RIGHT},
	  {ACharacter::UP, irr::KEY_UP},
	    {ACharacter::DOWN, irr::KEY_DOWN},
	      {ACharacter::BOMB, irr::KEY_SPACE},
		{ACharacter::ACT, irr::KEY_KEY_I}
    },
      {
	{ACharacter::LEFT, irr::KEY_KEY_Q},
	  {ACharacter::RIGHT, irr::KEY_KEY_D},
	    {ACharacter::UP, irr::KEY_KEY_Z},
	      {ACharacter::DOWN, irr::KEY_KEY_S},
		{ACharacter::BOMB, irr::KEY_KEY_L},
		  {ACharacter::ACT, irr::KEY_KEY_K}
      }
  });

EventGame::EventGame()
{

}

EventGame::~EventGame()
{

}

bool 	EventGame::OnEvent(const irr::SEvent &event)
{
    if (event.EventType == irr::EET_KEY_INPUT_EVENT) {
        KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
    }
    if (event.EventType == irr::EET_JOYSTICK_INPUT_EVENT && this->_joysticks[event.JoystickEvent.Joystick]) {
        this->_joysticks[event.JoystickEvent.Joystick]->setData(event.JoystickEvent);
    }
    return (false);
}

bool 	EventGame::IsKeyDownOneTime(irr::EKEY_CODE keyCode) const
{
    bool	key = KeyIsDown[keyCode];

    KeyIsDown[keyCode] = false;
    return (key);
}

bool 	EventGame::IsKeyDown(irr::EKEY_CODE keyCode) const
{
    return (KeyIsDown[keyCode]);
}

void EventGame::reset()
{
    for (irr::u32 i=0; i < irr::KEY_KEY_CODES_COUNT; ++i) {
        KeyIsDown[i] = false;
    }
}

void    EventGame::pushController(MotionController *controller)
{
    this->_joysticks[controller->getInfo().Joystick] = controller;
}
