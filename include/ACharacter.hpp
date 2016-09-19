//
// ACharacter.hpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:36:14 2016 Victor Gouet
// Last update Fri Jun  3 11:35:56 2016 Victor Gouet
//

#ifndef ACHARACTER_HPP_
# define ACHARACTER_HPP_

# include <thread>
# include <mutex>
# include <thread>
# include <vector>
# include "AGameObject.hpp"
# include "BombContainer.hpp"
# include "AItem.hpp"

class	ACharacter	: public AGameObject
{
public:
	static const std::vector<std::string> textAction;
	enum ACTION { IDLE = 0, LEFT, RIGHT, UP, DOWN, BOMB, ACT };
    enum MD3_ANIMATION { STAY, RUN, ATTACK };

public:
    static constexpr double BASICSPEED = 100.0;

public:
  ACharacter(std::string const &name, irr::core::vector2df const &pos,
             std::string const &mesh, std::string const &texture, int player,
	     int score = 0, bool invincible = false);
  virtual ~ACharacter();

protected:
	void			action(ACTION act);
  void			moveTo(irr::core::vector2df const &dir);

private:
  void			onInvinciblePeriode(double time);

public:
  void		  invincibleEnabledDuringPeriod(double time);
	void			setMD3Animation(MD3_ANIMATION anim);

public:
  virtual void          dead();
  virtual bool		isDestructible() const;

public:
  void			setMoveSpeed(double);
  std::string const     &getName() const;
  double                getMoveSpeed() const;
  void		        putBomb();
  void                  setName(const std::string &);
  void		        increasePowerBomb();
  bool			isDead() const;
  virtual void		compute() = 0;
  void			setBombPass(bool pass);
  void			setLifeUp();
  int			getScore() const;
  int			get_player() const;
  void 			reset();
  void			setBasicLife();
	bool 	isArrived(void) const;

public:
  BombContainer		*getBombContainer() const;

private:
  std::string	        _name;

private:
	int                   _player;
  BombContainer		*_bombContainer;
  double		moveSpeed;
  int			anime;
  irr::core::vector2df  _last_act;
  bool                  _arrived;
  AItem			*item;
  bool			_dead;

private:
  bool			bombPass;
  int			life;
  int			_score;
  bool			_invincible;
  std::mutex		mutex;
  std::thread		*t;
  bool			onRun;

protected:
  irr::u32		then;
  irr::f32		frameDeltaTime;
};

#endif
