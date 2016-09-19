//
// MineBomb.cpp for MINE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat May 21 21:18:14 2016 Victor Gouet
// Last update Sun Jun  5 16:45:59 2016 Matthieu Tavernier
//

#include "MineBomb.hpp"
#include "BomberMap.hpp"
#include "Texture.hpp"
#include "Explosion.hpp"
#include "GameObjectTimeContainer.hpp"

MineBomb::MineBomb(int id)
  : ABomb(BomberManTexture::getModel("mineBomb").mesh,
	  BomberManTexture::getModel("mineBomb").texture, 100, id)
{
  this->_power = 1;
  use = false;
  timeout = 100;
  (*this)->setVisible(false);
  (*this)->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  this->setType(AGameObject::NONE);

  time_t	timer;
  struct tm	y2k;

  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  secRef = difftime(timer, mktime(&y2k));
}

MineBomb::~MineBomb()
{

}

MineBomb	&MineBomb::operator=(ABomb const *other)
{
  use = false;
  timeout = 100;
  (*this)->setVisible(false);
  this->_power = 1;
  (*this)->setScale(irr::core::vector3df(0, 0, 0));
  this->setType(AGameObject::NONE);
  time_t	timer;
  struct tm	y2k;

  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  secRef = difftime(timer, mktime(&y2k));
  return (*this);
}

MineBomb::MineBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

void		MineBomb::disable()
{
}

bool		MineBomb::isDestructible() const
{
  return (true);
}

void		MineBomb::updateTimeOut()
{
  if (getTimeOutObj() == 1.5)
    {
      (*this)->setScale((*this)->getScale() + 0.004);
      return ;
    }

  time_t	timer;
  struct tm	y2k;
  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  double time = difftime(timer, mktime(&y2k));
  
  if (time < secRef + 3)
    {
      (*this)->setVisible(false);
      return ;
    }

  std::vector<AGameObject *> const &caracter = BomberMap::getMap()->getCharacters();
  std::vector<AGameObject *>::const_iterator	it = caracter.begin();

  while (it != caracter.end())
    {
      if ((*it)->getMapPos() == this->getMapPos())
	{
	  (*this)->setVisible(true);
	  (*this)->setScale(irr::core::vector3df(0.2, 0.2, 0.2));
	  setTimeOutWithoutInContainer(1.5);
	}
      ++it;
    }
}

void		MineBomb::willExplose()
{
    irr::core::vector2df        pos = this->getMapPos();

    this->killObjects(pos);
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(-power, 0))) {
            break;
        }
    }
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(power, 0))) {
            break;
        }
    }
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(0, -power))) {
            break;
        }
    }
    for (int power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(0, power))) {
            break;
        }
    }
}

bool    MineBomb::killObjects(irr::core::vector2df const &pos)
{
    std::vector<AGameObject *>   objs;
    AGameObject::Type           type;
    bool                        stop = false;

    type = AGameObject::NONE;
    objs = BomberMap::getMap()->getObjsFromVector2(pos);
    for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
        if (this == (*it)) {
            continue;
        }
        type = (*it)->getType();
        if (type != AGameObject::BLOCK && type != AGameObject::NONE && type != AGameObject::BOOM) {
            AGameObject *obj = (*it);
            obj->dead();
            if (type != AGameObject::BOOM
		&& !obj->isObjectTimeOut()
		&& obj->isDestructible()) {
                delete obj;
            }
        }
        if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
            stop = true;
        }
    }
    if (type != AGameObject::BLOCK) {
        new Explosion(pos, BomberManTexture::getModel("fire").texture, 1);
    }
    return (stop);
}
