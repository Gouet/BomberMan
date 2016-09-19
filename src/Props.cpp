//
// Created by consta_n on 19/05/16.
//

#include <iostream>
#include "Props.hpp"
#include "BomberMap.hpp"

Props::Props(const std::string &mesh,
      const std::string &texture, irr::core::vector2df const &scale, int transparent)
    : AGameObject(irr::core::vector2df(0, 0), mesh, texture, OTHER) {
   (*this)->setPosition(irr::core::vector3df(0, 0, 0));
   if (scale.X && scale.Y)
      (*this)->getMaterial(0).getTextureMatrix(0).setTextureScale(scale.X,scale.Y);
   if (transparent)
      (*this)->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
   irr::core::vector3df	pos = (*this)->getPosition();
   if (BomberMap::getMap()->getSize() == MEDIUM_SIZE)
     {
       pos.Z += 30;
     }
   else if (BomberMap::getMap()->getSize() == LARGE_SIZE)
     {
       pos.Z += 50;
     }
   (*this)->setPosition(pos);
}

void Props::dead() {

}

void				Props::serialize(irr::io::IXMLWriter *) const
{

}

bool Props::isDestructible() const {
   return false;
}


Props::~Props()
{

}
