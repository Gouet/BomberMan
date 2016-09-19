//
// Wall.hpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Apr 27 18:18:28 2016 Victor Gouet
// Last update Sun Jun  5 21:12:57 2016 Victor Gouet
//

#ifndef WALL_HPP_
# define WALL_HPP_

# include <map>
# include <string>
# include "AGameObject.hpp"
# include "BomberMap.hpp"
# include "BonusSpeed.hpp"
# include "BonusPower.hpp"
# include "BonusFireBomb.hpp"
# include "ItemThrow.hpp"
# include "BonusBombPass.hpp"
# include "BonusBiggestMan.hpp"
# include "BonusSmallestMan.hpp"
# include "BonusInvincible.hpp"
# include "BonusTrackerBomb.hpp"
# include "BonusFragBomb.hpp"
# include "BonusAtomicBomb.hpp"
# include "ItemMineBomb.hpp"

class	Wall : public AGameObject
{
public:
  enum 	State
    {
      Invicible,
      Destructible,
      Edge
    };

private:
  static const std::map<Wall::State, std::string> _types;

public:
  Wall(irr::core::vector2df const &pos, State state = Destructible);
  Wall(irr::core::vector2df const &pos, State state,
       std::string const &mesh, std::string const &texture);
  virtual ~Wall();

public:
  class		DataFile
  {
  public:
    DataFile() {}
    DataFile(irr::core::vector2df const &pos, State state, std::string const &mesh, std::string const &texture);
    ~DataFile();

  public:
    void		convertToWall() const;

  private:
    irr::core::vector2df	pos;
    State			state;
    char			mesh[100];
    char			texture[100];
  };

public:
  virtual void                        dead();
  virtual bool				isDestructible() const;
  virtual void		serialize(irr::io::IXMLWriter *) const;

public:
  void		        save(std::string const &);

public:
  State			getState() const;

private:
  State			_state;
  DataFile		*dataFile;
};

#endif
