/*
** MotionController.cpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 10:00:02 2016 Adrien WERY
** Last update	Fri Apr 29 10:07:53 2016 Adrien WERY
*/

#include <iostream>
#include "MotionController.hpp"

MotionController::MotionController(irr::SJoystickInfo info) : _info(info)
{
    m_keysToString = {
            "Square",
            "Cross",
            "Circle",
            "Triangle",
            "L1",
            "R1",
            "L2",
            "R2",
            "L2",
            "First Option",
            "Second Option",
            "L3",
            "R3",
            "Home",
            "Other"
    };

    _keycodes = {
            { ACharacter::ACTION::LEFT, ControllerKey::CROSS },
            { ACharacter::ACTION::RIGHT, ControllerKey::CROSS },
            { ACharacter::ACTION::UP, ControllerKey::CROSS },
            { ACharacter::ACTION::DOWN, ControllerKey::CROSS },
            { ACharacter::ACTION::BOMB, ControllerKey::SQUARE },
            { ACharacter::ACTION::ACT, ControllerKey::CIRCLE },
    };
    _timerDelay = getTimeSeconds();
}

MotionController::~MotionController()
{

}

const irr::SJoystickInfo            &MotionController::getInfo() const
{
    return (this->_info);
}

const irr::SEvent::SJoystickEvent   &MotionController::getData() const
{
    return (this->_data);
}

void                                MotionController::setData(const irr::SEvent::SJoystickEvent data)
{
    this->_data = data;
}

long long  MotionController::getTimeSeconds() const
{
  struct timeval tp;
  gettimeofday(&tp, NULL);
  long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000; //get current timestamp in milliseconds
  return (mslong);
}

ACharacter::ACTION      MotionController::getDirAxisOneTime(const Axis axis) const
{
    irr::f32 moveHorizontal;
    irr::f32 moveVertical;

    if (getTimeSeconds() < _timerDelay + 200)
      return (ACharacter::ACTION::IDLE);
    switch (axis) {
    case LEFT_JOYSTICK:
      moveHorizontal = (irr::f32)this->_data.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
      if (moveHorizontal > 0.5f) {
	_timerDelay = getTimeSeconds();
	return (ACharacter::ACTION::RIGHT);
      } else if (moveHorizontal < -0.5f) {	
	_timerDelay = getTimeSeconds();
	return (ACharacter::ACTION::LEFT);
      } else {
	moveVertical = (irr::f32)this->_data.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
	if (moveVertical > 0.5f) {
	  _timerDelay = getTimeSeconds();
	  return (ACharacter::ACTION::UP);
	} else if (moveVertical < -0.5f) {
	  _timerDelay = getTimeSeconds();
	  return (ACharacter::ACTION::DOWN);
	}
      }
      break;
    case RIGHT_JOYSTICK:
      break;
    default:
      break;
    }
    return (ACharacter::ACTION::IDLE);
}

bool    MotionController::IsButtonPressedOneTime(ControllerKey button) const
{
  if (button == this->_data.ButtonStates)
    {
      if (getTimeSeconds() < _timerDelay + 200)
    	{
    	  return (false);
    	}
      _timerDelay = getTimeSeconds();
      return (true);
    }
  return (false);
}

ACharacter::ACTION      MotionController::getDirAxis(const Axis axis) const
{
    irr::f32 moveHorizontal;
    irr::f32 moveVertical;

    switch (axis) {
    case LEFT_JOYSTICK:
      moveHorizontal = (irr::f32)this->_data.Axis[irr::SEvent::SJoystickEvent::AXIS_X] / 32767.f;
      if (moveHorizontal > 0.5f) {
	return (ACharacter::ACTION::RIGHT);
      } else if (moveHorizontal < -0.5f) {	
	return (ACharacter::ACTION::LEFT);
      } else {
	moveVertical = (irr::f32)this->_data.Axis[irr::SEvent::SJoystickEvent::AXIS_Y] / -32767.f;
	if (moveVertical > 0.5f) {
	  return (ACharacter::ACTION::UP);
	} else if (moveVertical < -0.5f) {
	  return (ACharacter::ACTION::DOWN);
	}
      }
      break;
    case RIGHT_JOYSTICK:
      break;
    default:
      break;
    }
    return (ACharacter::ACTION::IDLE);
}

bool    MotionController::IsButtonPressed(ControllerKey button) const
{
  return (button == this->_data.ButtonStates);
}

bool MotionController::IsButtonPressed(ACharacter::ACTION act) const
{
    if (_keycodes.find(act) == _keycodes.end())
        return false;
    return IsButtonPressed(_keycodes[act]);
}

void MotionController::BindAction(ACharacter::ACTION action, MotionController::ControllerKey key)
{
    std::map<ACharacter::ACTION, MotionController::ControllerKey>::iterator it;

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

const std::vector<KeyInfo<MotionController::ControllerKey> > &MotionController::ToString()
{
    std::map<ACharacter::ACTION, ControllerKey>::const_iterator it;
    std::string toAdd;
    int keyIdx = 0;

    m_toString.clear();
    int i = 0;
    for (it = _keycodes.begin(); it != _keycodes.end(); ++it)
    {
        // The 4 first keys are for directions, thus cannot be mapped
        if (i > 3)
        {
            toAdd = ACharacter::textAction[i];
            for (unsigned long j = toAdd.size(); j < 60; j++)
            {
                toAdd += ".";
            }
            while (keyIdx <= 12 && ((1 << keyIdx) & (*it).second) == 0)
            {
                ++keyIdx;
            }
            if (keyIdx <= 12)
            {
                toAdd += m_keysToString[keyIdx];
                m_toString.push_back(KeyInfo<MotionController::ControllerKey >((*it).first, (*it).second, toAdd));
            }
        }
        keyIdx = 0;
        ++i;
    }
    return m_toString;
}
