//
// TrackerBomb.cpp for TRACKER BOMB in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Fri May 13 11:04:11 2016 Victor Gouet
// Last update Sun Jun  5 16:46:24 2016 Matthieu Tavernier
//

#include "TrackerBomb.hpp"
#include "BomberMap.hpp"
#include "Texture.hpp"
#include "Explosion.hpp"

TrackerBomb::TrackerBomb(int id)
  : ABomb(BomberManTexture::getModel("trackerBomb").mesh,
	  BomberManTexture::getModel("trackerBomb").texture, 5, id)
{
    _last_dir = irr::core::vector2df(0, 0);
}

TrackerBomb::~TrackerBomb()
{
  dead();
}

TrackerBomb	&TrackerBomb::operator=(ABomb const *other)
{
  use = false;
  (*this)->setVisible(false);
  this->_power = other->getPower();
  return (*this);
}

TrackerBomb::TrackerBomb(ABomb const *other) : ABomb(other)
{
  *this = other;
}

void	TrackerBomb::updateTimeOut()
{
    int                     distance = 0;
    irr::core::vector2df	pos;

  std::vector<AGameObject *>	const &charact = BomberMap::getMap()->getCharacters();

    pos = this->getMapPos();
  for (std::vector<AGameObject *>::const_iterator it = charact.begin(), end = charact.end() ; it != end ; ++it)
    {
        if ((*it)->getID() == characterId)
            continue;
        irr::core::vector2df    charPos = (*it)->getMapPos();
        if (pos.X == charPos.X && (distance == 0 || distance > pos.Y - charPos.Y)) {
            distance = pos.Y - charPos.Y;
            _last_dir =irr::core::vector2df(0, (distance > 0) ? -1 : 1);
            distance = abs(distance);
        } else if (pos.Y == charPos.Y && (distance == 0 || distance > pos.X - charPos.X)) {
            distance = pos.X - charPos.X;
            _last_dir =irr::core::vector2df((distance > 0) ? -1 : 1, 0);
            distance = abs(distance);
        }
    }
    this->setVelocity(_last_dir);
    move(50);
}

void		TrackerBomb::willExplose()
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
    _last_dir = irr::core::vector2df(0, 0);
}

bool    TrackerBomb::killObjects(irr::core::vector2df const &pos)
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
        new Explosion(pos, BomberManTexture::getModel("fireTracker").texture, 1);
    }
    return (stop);
}
