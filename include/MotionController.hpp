/*
** MotionController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 09:58:12 2016 Adrien WERY
** Last update	Fri Apr 29 10:07:47 2016 Adrien WERY
*/

#ifndef MOTIONCONTROLLER_HPP
# define MOTIONCONTROLLER_HPP

#include <sys/time.h>
# include "AController.hpp"
# include "ACharacter.hpp"
#include "KeyInfo.hpp"

class MotionController : public AController {

public:
    enum Axis {
        LEFT_JOYSTICK,
        RIGHT_JOYSTICK
    };

    enum ControllerKey {
        SQUARE = 1 << 0,
        CROSS = 1 << 1,
        CIRCLE = 1 << 2,
        TRIANGLE = 1 << 3,
        L1 = 1 << 4,
        R1 = 1 << 5,
        L2 = 1 << 6,
        R2 = 1 << 7,
        FIRST_OPTION = 1 << 7,
        SECOND_OPTION = 1 << 8,
        L3 = 1 << 9,
        R3 = 1 << 10,
        HOME = 1 << 11,
        OTHER = 1 << 12
    };

private:
    mutable std::map<ACharacter::ACTION, ControllerKey> _keycodes;

public:
    void BindAction(ACharacter::ACTION action, ControllerKey key);
    std::vector<KeyInfo<ControllerKey> > const& ToString();
  long long		getTimeSeconds() const;

private:
    irr::SJoystickInfo          _info;
    irr::SEvent::SJoystickEvent _data;
    mutable std::vector<KeyInfo<ControllerKey> > m_toString;

private:
  mutable long long	_timerDelay;

public:
    MotionController (irr::SJoystickInfo info);
    virtual ~MotionController ();
    const irr::SJoystickInfo            &getInfo() const;
    const irr::SEvent::SJoystickEvent   &getData() const;
    void                                setData(irr::SEvent::SJoystickEvent data);
    ACharacter::ACTION                  getDirAxis(const Axis axis) const;
    bool                                IsButtonPressed(ControllerKey button) const;
    bool                                IsButtonPressed(ACharacter::ACTION act) const;
  ACharacter::ACTION                  getDirAxisOneTime(const Axis axis) const;
  bool                                IsButtonPressedOneTime(ControllerKey button) const;

};

#endif /* !MOTIONCONTROLLER_HPP */
