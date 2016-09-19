//
// Created by wery_a on 11/05/16.
//

#include <iostream>
#include "BomberMap.hpp"
#include "Texture.hpp"
#include "Explosion.hpp"

Explosion::Explosion(irr::core::vector2df const &pos, std::string const &texture, double timeout)
        : AGameObject(pos, BomberManTexture::getModel("fireExplosion").mesh,
        BomberManTexture::getModel("fireExplosion").texture, Type::BOOM, timeout)
{
    (*this)->setVisible(false);
    _ps = IrrlichtController::getSceneManager()->addParticleSystemSceneNode(false);
    irr::scene::IParticleEmitter* em = _ps->createBoxEmitter(
    irr::core::aabbox3d<irr::f32>(-10,0,-10,10,1,10),
    irr::core::vector3df(0.0f,0.05f,0.0f), 80,100,
    irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
    800,2000,0,
    irr::core::dimension2df(10.f,10.f),
    irr::core::dimension2df(20.f,20.f));
    _ps->setEmitter(em);

    _x = -1;
    _light = IrrlichtController::getSceneManager()->addLightSceneNode(0, (*this)->getPosition(), irr::video::SColor(255, 255, 204, 0), 0);
    _light->setLightType(irr::video::ELT_POINT);
    _light->enableCastShadow(false);

    em->drop();
    irr::scene::IParticleAffector* paf = _ps->createFadeOutParticleAffector();
    _ps->addAffector(paf);
    paf->drop();
    _ps->setPosition((*this)->getPosition());
    _ps->setScale(irr::core::vector3df(1,1,1));
    _ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
    _ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
    particuleTexture = texture;
    _ps->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(texture.c_str()));
    _ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
}

void			Explosion::updateTimeOut()
{
    float res;

    std::vector<AGameObject *> vec = BomberMap::getMap()->getObjsFromVector2(this->getMapPos());
    for (std::vector<AGameObject *>::iterator it = vec.begin(), end = vec.end() ; it != end ; ++it)
      {
	if ((*it)->getType() == AGameObject::CHARACTER)
	  {
	    (*it)->dead();
	  }
      }
    if (_x < 1)
    {
        res = (float) (-1 * (pow(_x, 2)) + 1);
        _x += 0.01;
        if (res > 0)
            _light->setRadius(res * 1000);
    }
    else if (_x == 1)
        _light->setRadius(0);
}


Explosion::~Explosion()
{
    _light->remove();
  _ps->setEmitter(0);
}

void		Explosion::serialize(irr::io::IXMLWriter *xmlr) const
{
  irr::core::vector2df	pos = getMapPos();

  std::string		meshStr = getMesh();
  std::string		textureStr = particuleTexture;

  std::wstring		xValue = L"" + std::to_wstring(pos.X);
  std::wstring		yValue = L"" + std::to_wstring(pos.Y);
  std::wstring		mesh = L"" ;
  mesh.assign(meshStr.begin(), meshStr.end());

  std::wstring		texture = L"";
  texture.assign(textureStr.begin(), textureStr.end());


  xmlr->writeElement(L"Explosion", true,
		     L"x", xValue.c_str(),
		     L"y", yValue.c_str(),
		     L"mesh", mesh.c_str(),
		     L"texture", texture.c_str()
		     );
  xmlr->writeLineBreak();
}

void        Explosion::dead()
{
  _ps->setEmitter(0);
}

bool        Explosion::isDestructible() const
{
    return (true);
}
