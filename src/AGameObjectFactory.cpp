//
// AGameObjectFactory.cpp for FACTORY in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May 23 21:46:02 2016 Victor Gouet
// Last update Sun Jun  5 16:38:59 2016 Matthieu Tavernier
//

#include "GameManager.hpp"
#include "AGameObjectFactory.hpp"
#include "Explosion.hpp"


AGameObjectFactory::AGameObjectFactory()
{
  fptr["Wall"] = &AGameObjectFactory::createWall;
  fptr["Player"] = &AGameObjectFactory::createPlayer;
  fptr["IAPlayer"] = &AGameObjectFactory::createIA;
  fptr["BonusAtomicBomb"] = &AGameObjectFactory::createBonusAtomicBomb;
  fptr["BonusBiggestMan"] = &AGameObjectFactory::createBonusBiggestMan;
  fptr["BonusBombPass"] = &AGameObjectFactory::createBonusBombPass;
  fptr["BonusFireBomb"] = &AGameObjectFactory::createBonusFireBomb;
  fptr["BonusFragBomb"] = &AGameObjectFactory::createBonusFragBomb;
  fptr["BonusInvincible"] = &AGameObjectFactory::createBonusInvincible;
  fptr["BonusPower"] = &AGameObjectFactory::createBonusPower;
  fptr["BonusSmallestMan"] = &AGameObjectFactory::createBonusSmallestMan;
  fptr["BonusSpeed"] = &AGameObjectFactory::createBonusSpeed;
  fptr["BonusTrackerBomb"] = &AGameObjectFactory::createBonusTrackerBomb;
  fptr["ItemMineBomb"] = &AGameObjectFactory::createItemMineBomb;
  fptr["ItemThrow"] = &AGameObjectFactory::createItemThrow;
}

void		AGameObjectFactory::createWall(irr::io::IrrXMLReader *reader,
					       AGameObjectData::Data *data) 
{
  new Wall(data->getPos(),
	   (Wall::State)reader->getAttributeValueAsInt("state"),
	   data->mesh,
	   data->texture);
}
void		AGameObjectFactory::createPlayer(irr::io::IrrXMLReader *reader,
						 AGameObjectData::Data *data) 
{
  PlayerInfo *player = new PlayerInfo(std::string(reader->getAttributeValueSafe("name")),
				      data->mesh,
				      data->texture);
  player->setPos(data->getPos());
  GameManager::SharedInstance()->AddPlayer(player);
}

void		AGameObjectFactory::createIA(irr::io::IrrXMLReader *reader,
					     AGameObjectData::Data *data) 
{
  PlayerInfo *iaPlayer = new PlayerInfo(std::string(reader->getAttributeValueSafe("name")),
				        data->mesh,
				        data->texture,
					true);
  iaPlayer->setPos(data->getPos());
  GameManager::SharedInstance()->AddPlayer(iaPlayer);
}


void		AGameObjectFactory::createExplosion(irr::io::IrrXMLReader *, 
						    AGameObjectData::Data *data)
{
  new Explosion(data->getPos(), data->texture, 1);
}

void		AGameObjectFactory::createBonusAtomicBomb(irr::io::IrrXMLReader *,
							  AGameObjectData::Data *data)
{
  new BonusAtomicBomb(data->getPos());
}

void		AGameObjectFactory::createBonusBiggestMan(irr::io::IrrXMLReader *,
							  AGameObjectData::Data *data)
{
  new BonusBiggestMan(data->getPos());
}

void		AGameObjectFactory::createBonusBombPass(irr::io::IrrXMLReader *,
							AGameObjectData::Data *data)
{
  new BonusBombPass(data->getPos());
}

void		AGameObjectFactory::createBonusFireBomb(irr::io::IrrXMLReader *,
							AGameObjectData::Data *data)
{
  new BonusFireBomb(data->getPos());
}

void		AGameObjectFactory::createBonusFragBomb(irr::io::IrrXMLReader *,
							AGameObjectData::Data *data)
{
  new BonusFragBomb(data->getPos());
}

void		AGameObjectFactory::createBonusInvincible(irr::io::IrrXMLReader *,
							  AGameObjectData::Data *data)
{
  new BonusInvincible(data->getPos());
}

void		AGameObjectFactory::createBonusPower(irr::io::IrrXMLReader *,
						     AGameObjectData::Data *data)
{
  new BonusPower(data->getPos());
}

void		AGameObjectFactory::createBonusSmallestMan(irr::io::IrrXMLReader *,
							   AGameObjectData::Data *data)
{
  new BonusSmallestMan(data->getPos());
}

void		AGameObjectFactory::createBonusSpeed(irr::io::IrrXMLReader *,
						     AGameObjectData::Data *data)
{
  new BonusSpeed(data->getPos());
}

void		AGameObjectFactory::createBonusTrackerBomb(irr::io::IrrXMLReader *,
							   AGameObjectData::Data *data)
{
  new BonusTrackerBomb(data->getPos());
}

void		AGameObjectFactory::createItemMineBomb(irr::io::IrrXMLReader *,
						       AGameObjectData::Data *data)
{
  new ItemMineBomb(data->getPos());
}

void		AGameObjectFactory::createItemThrow(irr::io::IrrXMLReader *,
						    AGameObjectData::Data *data)
{
  new ItemThrow(data->getPos());
}

void	AGameObjectFactory::instantiateGameObjectFromXMLFile(irr::io::IrrXMLReader *reader,
							     std::string  const &nodeName) 
{
  if (nodeName == "Info")
    {
      BomberMap::newMap(reader->getAttributeValueSafe("decor"));
    }
  std::map<std::string, funcFactoryPointer>::iterator	it;
  
  if ((it = this->fptr.find(nodeName)) == fptr.end())
    return ;
  AGameObjectData::Data *data = new AGameObjectData::Data(reader);
  (this->*it->second)(reader, data);
  delete data;
}
