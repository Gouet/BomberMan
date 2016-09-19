//
// AGameObject.cpp for GAME OBJECT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:00:41 2016 Victor Gouet
// Last update Sun Jun  5 16:38:42 2016 Matthieu Tavernier
//

#include <iostream>
#include "AGameObject.hpp"
#include "BomberMap.hpp"
#include "GameObjectTimeContainer.hpp"

AGameObject::AGameObject(irr::core::vector2df const &pos, std::string const &mesh, std::string const &texture, Type type, double timeout) : _type(type)
{
  static int		id = 1;

  BomberMap::getMap()->add(this, pos);
  irr::scene::IAnimatedMesh *meshNode;

  anime = NULL;
  time_t	timer;
  struct tm	y2k;

  this->_timeout = timeout;
  _rltimeout = timeout;

  timer = time(NULL);

  if (timeout != -1)
  {
    memset(&y2k, 0, sizeof(y2k));
    y2k.tm_year = 100;
    y2k.tm_mday = 1;
    _timer = difftime(timer, mktime(&y2k));

    GameObjectTimeContainer::SharedInstance()->add(this);
  }
  else
  {
    _timer = 0;
  }
  _mesh = mesh;
  if (!(meshNode = IrrlichtController::getSceneManager()->getMesh(mesh.c_str())))
  {
    IrrlichtController::getDevice()->drop();
    std::cout << type << std::endl;
    throw std::runtime_error("Failed to create IAnimatedMesh in AGameObject");
  }
  else if ((_node = IrrlichtController::getSceneManager()->addAnimatedMeshSceneNode(meshNode, 0, 0)))
  {
    if (texture != "")
    {
      _node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(texture.c_str()));
      _texture = texture;
      _node->setMaterialFlag(irr::video::EMF_LIGHTING ,true);
    }
    _node->setMD2Animation(irr::scene::EMAT_STAND);
    _node->setID(id++);
  }
  this->setPos(pos);
}

AGameObject::~AGameObject()
{
  BomberMap::getMap()->remove(this);
  GameObjectTimeContainer::SharedInstance()->remove(this);
  (*this)->remove();
}


std::string			const	&AGameObject::getTexture() const
{
  return (_texture);
}

std::string			const	&AGameObject::getMesh() const
{
  return (_mesh);
}

int				AGameObject::getID() const
{
  return (_node->getID());
}

void				AGameObject::addAnimation()
{
  irr::core::array<irr::video::ITexture *>	array;

  array.push_back(IrrlichtController::getDriver()->getTexture(_texture.c_str()));
  array.push_back(IrrlichtController::getDriver()->getTexture(""));
  anime =  IrrlichtController::getSceneManager()->createTextureAnimator(array, 100, true);
  _node->addAnimator(anime);
}

void				AGameObject::removeAnnimation()
{
  if (anime) {
    _node->removeAnimator(anime);
    anime->drop();
  }
  _node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(_texture.c_str()));
  anime = NULL;
}

irr::scene::ISceneNodeAnimator	*AGameObject::getAnimator() const
{
  return (anime);
}

bool					AGameObject::isObjectTimeOut() const
{
  return (!(_timeout == -1));
}

void					AGameObject::wait()
{
  struct tm	y2k;
  time_t	timer;
  double	timeSec;

  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  timeSec = difftime(timer, mktime(&y2k));
  _timeout = timeSec - _timer + _rltimeout;
}

void				AGameObject::setType(Type type)
{
  this->_type = type;
}

bool				AGameObject::isTimeOut() const
{
  time_t	timer;
  struct tm	y2k;
  double	seconds;

  if (_timeout == -1)
    return (true);

  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;

  timer = time(NULL);
  seconds = difftime(timer, mktime(&y2k));
  return (seconds >= (_timer + _timeout));
}

void			AGameObject::setTimeOutWithoutInContainer(double timeout)
{
  time_t	timer;
  struct tm	y2k;

  this->_timeout = timeout;
  _rltimeout = timeout;
  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  _timer = difftime(timer, mktime(&y2k));
}

void			AGameObject::setTimeOut(double timeout)
{
  time_t	timer;
  struct tm	y2k;

  this->_timeout = timeout;
  _rltimeout = timeout;
  timer = time(NULL);
  memset(&y2k, 0, sizeof(y2k));
  y2k.tm_year = 100;
  y2k.tm_mday = 1;
  _timer = difftime(timer, mktime(&y2k));
  GameObjectTimeContainer::SharedInstance()->add(this);
}

double			AGameObject::getTimeOutObj() const
{
  return (_timeout);
}

void			      AGameObject::updateTimeOut()
{
}

irr::scene::IAnimatedMeshSceneNode *AGameObject::operator->() const
{
  return (_node);
}

irr::scene::IAnimatedMeshSceneNode *AGameObject::getSceneNode() const
{
  return (_node);
}

AGameObject::Type   AGameObject::getType() const
{
  return (this->_type);
}

void                AGameObject::setPos(irr::core::vector2df const &pos)
{
  BomberMap::getMap()->move(this, pos);
  _node->setPosition(irr::core::vector3df(pos.X - BomberMap::getMap()->getSize() / 2, 0, pos.Y - BomberMap::getMap()->getSize() / 2) * BomberMap::scale);
}

irr::core::vector2df    AGameObject::getMapPos() const
{
  return (BomberMap::getMap()->get(const_cast<AGameObject*>(this)));
}

irr::core::vector2df    AGameObject::getRealPos() const
{
  irr::core::vector3df    pos3df = _node->getPosition() / BomberMap::scale;

  return (irr::core::vector2df(pos3df.X + BomberMap::getMap()->getSize() / 2, pos3df.Z + BomberMap::getMap()->getSize() / 2));
}
