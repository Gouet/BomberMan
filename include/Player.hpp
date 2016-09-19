//
// Player.hpp for Player in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Sun Jun  5 12:58:20 2016 Matthieu Tavernier
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <map>
# include "EventGame.hpp"
# include "MotionController.hpp"

class	Player	: public ACharacter
{
private:
  EventGame	const &					_eventGame;
  std::map<ACharacter::ACTION, irr::EKEY_CODE>  _keycodes;
  MotionController            	*_joystick;
  KeysController				*keyController;

public:
  Player(std::string const &name, irr::core::vector2df const &pos,
	 std::string const &mesh, std::string const &texture, int player,
	 EventGame &eventGame, AController const *controller = nullptr);
  virtual ~Player();

public:
  virtual void		compute();
  virtual void		serialize(irr::io::IXMLWriter *) const;
};

#endif
