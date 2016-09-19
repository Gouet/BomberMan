//
// Wall.cpp for WALL in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:19:48 2016 Victor Gouet
// Last update Sun Jun  5 17:33:34 2016 Victor Gouet
//

#include <fstream>
#include <iostream>
#include "Wall.hpp"
#include "Texture.hpp"

Wall::Wall(irr::core::vector2df const &pos, State state,
	   std::string const &mesh, std::string const &texture)
  : AGameObject(pos, mesh, texture, (state == Destructible) ? OTHER : BLOCK), _state(state)
{
    (*this)->setScale(irr::core::vector3df(0.8f, 0.8f, 0.8f));
    dataFile = new DataFile(pos, state, mesh, texture);
}

Wall::~Wall()
{
  delete dataFile;
}

void		Wall::serialize(irr::io::IXMLWriter *xmlr) const
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
  std::wstring		state = L"" + std::to_wstring(getState());

  xmlr->writeElement(L"Wall", true,
		     L"x", xValue.c_str(),
		     L"y", yValue.c_str(),
		     L"state", state.c_str(),
		     L"mesh", mesh.c_str(),
		     L"texture", texture.c_str()
		     );
  xmlr->writeLineBreak();
}

void                        Wall::dead()
{
  int			i;
  int			r;
  int			nbBonus;

  if (_state == Invicible || _state == Edge)
    return ;
  if (BomberMap::getMap()->getSize() == SMALL_SIZE)
    nbBonus = 11;
  else
    nbBonus = 12;
  i = rand() % nbBonus;
  switch (i)
    {
    case 0:
      new BonusSpeed(this->getMapPos());
      break;
    case 1:
      new BonusPower(this->getMapPos());
      break;
    case 2:
      new BonusFireBomb(this->getMapPos());
      break;
    case 3:
      new ItemThrow(this->getMapPos());
      break;
    case 4:
      new BonusBombPass(this->getMapPos());
      break;
    case 5:
      new BonusBiggestMan(this->getMapPos());
      break;
    case 6:
      new BonusSmallestMan(this->getMapPos());
      break;
    case 7:
      new BonusInvincible(this->getMapPos());
      break;
    case 8:
      new BonusTrackerBomb(this->getMapPos());
      break;
    case 9:
      new BonusFragBomb(this->getMapPos());
      break;
    case 10:
      new ItemMineBomb(this->getMapPos());
      break;
    case 11:
      new BonusAtomicBomb(this->getMapPos());
      break;
    default:
      break;
    }
  this->setPos(irr::core::vector2df(-2000, -2000));
}

bool				Wall::isDestructible() const
{
  return (false);
}

Wall::State			Wall::getState() const
{
  return (_state);
}

void		        Wall::save(std::string const &fileName)
{
  std::ofstream	ofs(fileName, std::ios::binary | std::ios::out | std::ios::trunc);

  ofs.write((char *)dataFile, sizeof(*dataFile));
  ofs.close();
}

Wall::DataFile::DataFile(irr::core::vector2df const &pos, State state, std::string const &mesh, std::string const &texture)
  : pos(pos), state(state)
{
  memset(this->mesh, 0, sizeof(this->mesh));
	memset(this->texture, 0, sizeof(this->texture));

  memcpy(this->mesh, mesh.c_str(), mesh.size());
  memcpy(this->texture, texture.c_str(), texture.size());
}

Wall::DataFile::~DataFile()
{
}

void		Wall::DataFile::convertToWall() const
{
  new Wall(this->pos, state, mesh, texture);
}
