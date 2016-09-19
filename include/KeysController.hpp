/*
** KeysController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 09:58:12 2016 Adrien WERY
** Last update	Fri Apr 29 10:30:02 2016 Adrien WERY
*/

#ifndef KEYSCONTROLLER_HPP
# define KEYSCONTROLLER_HPP

# include <map>
# include "AController.hpp"
# include "ACharacter.hpp"
# include "MotionController.hpp"
#include "KeyInfo.hpp"

/*
 * \brief This class will holds all the informations about the key bindings used by the players
 */
class KeysController : public AController {
private:
    std::map<ACharacter::ACTION, irr::EKEY_CODE> _keycodes;

public:
    KeysController (std::map<ACharacter::ACTION, irr::EKEY_CODE> const &keycodes);
    virtual ~KeysController ();
    std::map<ACharacter::ACTION, irr::EKEY_CODE> const  &getKeycodes() const;
    std::vector<KeyInfo<irr::EKEY_CODE> > const& ToString() const;

public:
    void BindAction(ACharacter::ACTION action, irr::EKEY_CODE key);

private:
    mutable std::vector<KeyInfo<irr::EKEY_CODE>> m_toString;
};

#endif /* !KEYSCONTROLLER_HPP */
