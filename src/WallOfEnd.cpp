//
// WallOfEnd.cpp for WALL OF END in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Wed Jun  1 23:02:35 2016 Victor Gouet
// Last update Sun Jun  5 17:04:47 2016 Matthieu Tavernier
//

#include "BomberMap.hpp"
#include "Texture.hpp"
#include "WallOfEnd.hpp"

WallOfEnd::WallOfEnd(irr::core::vector2df const &pos)
  : AGameObject(pos, BomberManTexture::getModel("edge").mesh,
		BomberManTexture::getModel("edge").texture, OTHER, 100), _pos(pos)
{
  (*this)->setPosition(irr::core::vector3df((*this)->getPosition().X,
					    (*this)->getPosition().Y + 300,
					    (*this)->getPosition().Z));
  (*this)->setScale(irr::core::vector3df(0.8f, 0.8f, 0.8f));
  _arrived = 0;
}

WallOfEnd::~WallOfEnd()
{

}

void		WallOfEnd::updateTimeOut()
{
  irr::core::vector3df	pos = (*this)->getPosition();

  if (pos.Y > 0)
    (*this)->setPosition(irr::core::vector3df(pos.X,
					      pos.Y - 30,
					      pos.Z));
  else
    {
      if (_arrived == 0)
      	{
	  (*this)->setPosition(irr::core::vector3df(pos.X,
						    0,
						    pos.Z));	  
	}
	  std::vector<AGameObject *> vec = BomberMap::getMap()->getObjsFromVector2(_pos);
	  for (std::vector<AGameObject *>::iterator it = vec.begin(), end = vec.end() ; it != end ; ++it)
	    {
	      (*it)->dead();
	      if ((*it)->isDestructible())
		delete *it;
	    }
	  ++_arrived;
    }
}

void          WallOfEnd::dead()
{
}

bool		WallOfEnd::isDestructible() const
{
  return (false);
}

void		WallOfEnd::serialize(irr::io::IXMLWriter *) const
{
}
