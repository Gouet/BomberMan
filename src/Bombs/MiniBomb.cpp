//
// MiniBomb.cpp for MINI in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 20 16:31:36 2016 Victor Gouet
// Last update Sun Jun  5 16:46:10 2016 Matthieu Tavernier
//

#include <iostream>
#include "MiniBomb.hpp"
#include "BomberMap.hpp"
#include "Texture.hpp"
#include "Explosion.hpp"
#include "GameObjectTimeContainer.hpp"

MiniBomb::MiniBomb(int id)
  : ABomb(BomberManTexture::getModel("miniBomb").mesh,
	  BomberManTexture::getModel("miniBomb").texture, 0.5, id)
{
  this->_power = 1;
  use = false;
  timeout = 0.5;
  (*this)->setVisible(false);
  (*this)->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
}

MiniBomb::~MiniBomb()
{

}

MiniBomb	&MiniBomb::operator=(ABomb const *other)
{
  use = false;
  timeout = 0.5;
  (*this)->setVisible(false);
  this->_power = 1;
  (*this)->setScale(irr::core::vector3df(0.5, 0.5, 0.5));
  return (*this);
}

MiniBomb::MiniBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

bool		MiniBomb::isDestructible() const
{
  return (false);
}

void		MiniBomb::willExplose()
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

bool    MiniBomb::killObjects(irr::core::vector2df const &pos)
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
