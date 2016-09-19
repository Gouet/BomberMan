//
// AItem.cpp for ITEM in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May  9 17:27:09 2016 Victor Gouet
// Last update Sun Jun  5 16:47:14 2016 Matthieu Tavernier
//

#include "AItem.hpp"
#include "BomberMap.hpp"
#include "SoundManager.hpp"

AItem::AItem(irr::core::vector2df const &pos, std::string const &mesh,
             std::string const &texture, std::string const &nameType, AGameObject::Type type)
        : AGameObject(pos, mesh, texture, type), nameType(nameType)
{
    (*this)->setPosition((*this)->getPosition() + irr::core::vector3df(0, BomberMap::scale / 2, 0));
    (*this)->setRotation(irr::core::vector3df(40, 0, 0));
    irr::scene::ISceneNodeAnimator *anim =IrrlichtController::getSceneManager()->createRotationAnimator(irr::core::vector3df(0,1,0));
    (*this)->addAnimator(anim);
    anim->drop();
}

AItem::~AItem()
{

}

void		AItem::dead()
{
  (*this)->setVisible(false);
  this->setPos(irr::core::vector2df(1000, 1000));
  SoundManager::getManager()->play("takeBonus.wav", (*this)->getID());
}

void		AItem::serialize(irr::io::IXMLWriter *xmlr) const
{
    irr::core::vector2df	pos = getMapPos();

    std::string		meshStr = getMesh();
    std::string		textureStr = getTexture();

    std::wstring		xValue = L"" + std::to_wstring(pos.X);
    std::wstring		yValue = L"" + std::to_wstring(pos.Y);
    std::wstring		mesh = L"" ;
    mesh.assign(meshStr.begin(), meshStr.end());

    std::wstring		texture = L"";
    texture.assign(textureStr.begin(), textureStr.end());
    std::wstring		nameTypeWstr = L"";
    nameTypeWstr.assign(nameType.begin(), nameType.end());

    xmlr->writeElement(nameTypeWstr.c_str(), true,
                       L"x", xValue.c_str(),
                       L"y", yValue.c_str(),
                       L"mesh", mesh.c_str(),
                       L"texture", texture.c_str()
    );
    xmlr->writeLineBreak();
}

bool	        AItem::isDestructible() const
{
  return (false);
}
