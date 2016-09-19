//
// AGameObjectFactory.hpp for FACTORY in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May 23 21:44:28 2016 Victor Gouet
// Last update Mon May 23 22:59:50 2016 Victor Gouet
//

#ifndef AGAMEOBJECTFACTORY_HPP_
# define AGAMEOBJECTFACTORY_HPP_

# include "BomberMap.hpp"
# include "AGameObject.hpp"

class		AGameObjectFactory;

namespace AGameObjectData
{  
  class		Data
  {
  public:
    Data(irr::io::IrrXMLReader *reader)
    {
      x = reader->getAttributeValueAsFloat("x");
      y = reader->getAttributeValueAsFloat("y");
      mesh = reader->getAttributeValueSafe("mesh");
      texture = reader->getAttributeValueSafe("texture");
    }
    ~Data() {}

  public:
    irr::core::vector2df	getPos() const
    {
      return (irr::core::vector2df(x, y));
    }

  public:
    float	x;
    float	y;
    std::string	mesh;
    std::string	texture;
  };
}

typedef void	(AGameObjectFactory::*funcFactoryPointer)(irr::io::IrrXMLReader *,
							  AGameObjectData::Data *);

class	AGameObjectFactory
{
public:
  AGameObjectFactory();
  ~AGameObjectFactory() {}

private:
  void		createWall(irr::io::IrrXMLReader *, AGameObjectData::Data *);
  void		createPlayer(irr::io::IrrXMLReader *, AGameObjectData::Data *);
  void		createIA(irr::io::IrrXMLReader *, AGameObjectData::Data *);
  void		createExplosion(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusAtomicBomb(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusBiggestMan(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusBombPass(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusFireBomb(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusFragBomb(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusInvincible(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusPower(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusSmallestMan(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusSpeed(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createBonusTrackerBomb(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createItemMineBomb(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);
  void		createItemThrow(irr::io::IrrXMLReader *reader, AGameObjectData::Data *data);

public:
  void	instantiateGameObjectFromXMLFile(irr::io::IrrXMLReader *reader,
						 std::string const &nodeName);
private:
  std::map<std::string, funcFactoryPointer>		fptr;
};

#endif
