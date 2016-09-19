//
// FragBomb.cpp for FRAG in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 16:22:17 2016 Victor Gouet
// Last update Sun Jun  5 16:45:44 2016 Matthieu Tavernier
//

#include <iostream>
#include "FragBomb.hpp"
#include "BomberMap.hpp"
#include "Texture.hpp"
#include "Explosion.hpp"
#include "MiniBomb.hpp"

FragBomb::FragBomb(int id)
  : ABomb(BomberManTexture::getModel("fragBomb").mesh,
	  BomberManTexture::getModel("fragBomb").texture, 3, id)
{
  vec = NULL;
}

FragBomb::~FragBomb()
{

}

FragBomb	&FragBomb::operator=(ABomb const *other)
{
  vec = NULL;
  use = false;
  timeout = 3;
  (*this)->setVisible(false);
  this->_power = other->getPower();
  return (*this);
}

FragBomb::FragBomb(ABomb const *other) : ABomb(other)
{
  vec = NULL;
  *this = other;
}

void		FragBomb::willExplose()
{
    irr::core::vector2df        pos = this->getMapPos();
    MiniBomb			*mini;
    
    this->killObjects(pos);

    int power;

    vec = NULL;
    for (power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(-power, 0))) {
            break;
        }
    }
    if (vec)
      {
	mini = new MiniBomb();
	*mini << *vec;
	delete vec;
      }
    vec = NULL;

    for (power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(power, 0))) {
            break;
        }
    }

    if (vec)
      {
	mini = new MiniBomb();
	*mini << *vec;
	delete vec;
      }
    vec = NULL;

    for (power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(0, -power))) {
            break;
        }
    }

    if (vec)
      {
	mini = new MiniBomb();
	*mini << *vec;
	delete vec;
      }
    vec = NULL;

    for (power = 1; power <= this->_power; ++power) {
        if (this->killObjects(pos + irr::core::vector2df(0, power))) {
            break;
        }
    }

    if (vec)
      {
	mini = new MiniBomb();
	*mini << *vec;
	delete vec;
      }
    vec = NULL;
}

bool    FragBomb::killObjects(irr::core::vector2df const &pos)
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
	    if (type != AGameObject::BOOM &&
		!obj->isObjectTimeOut()
		&& obj->isDestructible()) {
                delete obj;
            }
        }
        if (type == AGameObject::BLOCK || type == AGameObject::OTHER) {
            stop = true;
        }
    }
    if (type != AGameObject::BLOCK) {
      if (vec)
	delete vec;
      vec = new irr::core::vector2df(pos);
      new Explosion(pos, BomberManTexture::getModel("fire").texture, 1);
    }
    return (stop);
}
