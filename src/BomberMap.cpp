//
// BomberMap.cpp for MAP in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 18:14:09 2016 Victor Gouet
// Last update Sun Jun  5 16:41:16 2016 Matthieu Tavernier
//

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <queue>
#include "irrXML.h"
#include "BomberMap.hpp"
#include "Texture.hpp"
#include "Color.hpp"
#include "Player.hpp"
#include "IAPlayer.hpp"
#include "GameObjectTimeContainer.hpp"
#include "GameManager.hpp"
#include "AGameObjectFactory.hpp"

BomberMap *BomberMap::bomberMap = NULL;

const int		BomberMap::size_side[3] = {SMALL_SIZE, MEDIUM_SIZE, LARGE_SIZE};

BomberMap::BomberMap(std::string const &filename) :
        _mapSize(SMALL),
        _filename(filename),
        _dangerMap(static_cast<size_t >(size_side[_mapSize]))
{
  _dangerMap.refresh(this);
  IAPlayer::initIA(size_side[_mapSize], size_side[_mapSize]);
}

BomberMap::BomberMap(Size mapSize) :
        _mapSize(mapSize),
        _filename(""),
        _dangerMap(static_cast<size_t >(size_side[_mapSize]))
{
  terrain_model = NULL;
  _camera = NULL;
  // initSpawn();
  _dangerMap.refresh(this);
  IAPlayer::initIA(size_side[_mapSize], size_side[_mapSize]);
}

BomberMap::~BomberMap()
{
    std::map<AGameObject*, irr::core::vector2df>::iterator it_o = _objects.begin();

    while (it_o != _objects.end())
    {
        AGameObject	*obj = (*it_o).first;

        GameObjectTimeContainer::SharedInstance()->remove(obj);
        delete (obj);
        it_o = _objects.begin();
    }
    for (std::vector<irr::scene::ILightSceneNode*>::iterator it = lightVector.begin(), end = lightVector.end() ; end != it ; ++it)
    {
        (*it)->remove();
    }
    IAPlayer::shutDownIA();
}

std::map<AGameObject *, irr::core::vector2df>	const &BomberMap::getObjects() const
{
  return (_objects);
}

void            BomberMap::genMap()
{
  this->generateMap();
}

void			BomberMap::generateGround()
{
  terrain_model = IrrlichtController::getSceneManager()->addHillPlaneMesh("ground",
                                                                          irr::core::dimension2d<irr::f32>(25, 25), // Tile size
                                                                          irr::core::dimension2d<irr::u32>(size_side[_mapSize], size_side[_mapSize]), // Tile count
                                                                          0, // Material
                                                                          0.0f, // Hill height
                                                                          irr::core::dimension2d<irr::f32>(0.0f, 0.0f), // countHills
                                                                          irr::core::dimension2d<irr::f32>(size_side[_mapSize], size_side[_mapSize])); // textureRepeatCount

  _ground = IrrlichtController::getSceneManager()->addMeshSceneNode(terrain_model->getMesh(0));
  _ground->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(BomberManTexture::getModel("ground").texture.c_str()));
  _ground->setMaterialFlag(irr::video::EMF_LIGHTING, true);

  irr::scene::ILightSceneNode* light;
  irr::video::SLight  light_data;
  light_data.Radius = 1000.0f;
  light_data.OuterCone = 50.0f;
  light_data.Type = irr::video::ELT_SPOT;
  light_data.AmbientColor = irr::video::SColorf(0.5f, 0.5f, 0.5f);
  light_data.SpecularColor = irr::video::SColorf(0.1f,0.1f,0.1f,1);
  light_data.DiffuseColor = irr::video::SColorf(1.0f, 1.0f, 1.0f);
  light_data.CastShadows = true;

  light = IrrlichtController::getSceneManager()->addLightSceneNode();
  light->setPosition(irr::core::vector3df(0, 300, 0));
  light->setLightType(irr::video::ELT_POINT);
  light->setLightData(light_data);
  lightVector.push_back(light);
  light = IrrlichtController::getSceneManager()->addLightSceneNode();
  light->setLightData(light_data);
  light->setPosition(irr::core::vector3df(125, 0, -125));
  light->setRotation(irr::core::vector3df(-45, -45, 0));
  lightVector.push_back(light);
  light = IrrlichtController::getSceneManager()->addLightSceneNode();
  light->setLightData(light_data);
  light->setPosition(irr::core::vector3df(125, 0, 125));
  light->setRotation(irr::core::vector3df(-45, 225, 0));
  lightVector.push_back(light);
  light = IrrlichtController::getSceneManager()->addLightSceneNode();
  light->setLightData(light_data);
  light->setPosition(irr::core::vector3df(-125, 0, -125));
  light->setRotation(irr::core::vector3df(-45, 45, 0));
  lightVector.push_back(light);
  light = IrrlichtController::getSceneManager()->addLightSceneNode();
  light->setLightData(light_data);
  light->setPosition(irr::core::vector3df(-125, 0, 125));
  light->setRotation(irr::core::vector3df(-45, 135, 0));
  lightVector.push_back(light);
}

int	BomberMap::getSize() const
{
  return (size_side[_mapSize]);
}

std::vector<irr::core::vector2df> const	&BomberMap::getSpawn() const
{
  return (_spawner);
}

void			BomberMap::initSpawn()
{
  _spawner.push_back(irr::core::vector2df(1, 1));
  _spawner.push_back(irr::core::vector2df(BomberMap::size_side[_mapSize] - 2, BomberMap::size_side[_mapSize] - 2));
  _spawner.push_back(irr::core::vector2df(BomberMap::size_side[_mapSize] - 2, 1));
  _spawner.push_back(irr::core::vector2df(1, BomberMap::size_side[_mapSize] - 2));
}

bool			BomberMap::canPutDestructibleWall(int x, int y) const
{
  int			proba;

  if ((x == 1 && y == 1) || (x == 2 && y == 1) || (x == 1 && y == 2))
    return (false);
  if ((x == BomberMap::size_side[_mapSize] - 2 && y == BomberMap::size_side[_mapSize] - 2)
      || (x == BomberMap::size_side[_mapSize] - 3 && y == BomberMap::size_side[_mapSize] - 2)
      || (x == BomberMap::size_side[_mapSize] - 2 && y == BomberMap::size_side[_mapSize] - 3))
    return (false);
  if ((x == BomberMap::size_side[_mapSize] - 2 && y == 1)
      || (x == BomberMap::size_side[_mapSize] - 3 && y == 1)
      || (x == BomberMap::size_side[_mapSize] - 2 && y == 2))
    return (false);
  if ((x == 1 && y == BomberMap::size_side[_mapSize] - 2)
      || (x == 1 && y == BomberMap::size_side[_mapSize] - 3)
      || (x == 2 && y == BomberMap::size_side[_mapSize] - 2))
    return (false);
  proba = rand() % 10;
  return (proba >= 1);
}

void			BomberMap::generateMap()
{
  srand(time(NULL));
  for (int y = 0; y < BomberMap::size_side[_mapSize]; ++y) {
    for (int x = 0; x < BomberMap::size_side[_mapSize]; ++x) {
      if (x == 0 || y == 0 || x == BomberMap::size_side[_mapSize] - 1
          || y == BomberMap::size_side[_mapSize] - 1)
      {
        new Wall(irr::core::vector2df(x, y), Wall::Edge, BomberManTexture::getModel("edge").mesh, BomberManTexture::getModel("edge").texture);
      }
      else if (x % 2 == 0 && y % 2 == 0 && x != 0 && y != 0)
      {
        int dice = rand() % 3;
        new Wall(irr::core::vector2df(x, y), Wall::Invicible, _walls[dice].first, _walls[dice].second);
      }
      else if (canPutDestructibleWall(x, y))
      {
	  new Wall(irr::core::vector2df(x, y), Wall::Destructible, BomberManTexture::getModel("cubeDestructible").mesh, BomberManTexture::getModel("cubeDestructible").texture);
      }
    }
  }
  _dangerMap.refresh(this);
}

std::string		BomberMap::getCurrentDate() const
{
  time_t     now = time(0);
  struct tm  tstruct;
  char       buf[80];
  tstruct = *localtime(&now);

  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

void	BomberMap::save() const
{
  #ifdef __linux__
    mkdir("tmpSaveMap", 0777);
  #elif _WIN32
    mkdir("tmpSaveMap");
  #endif
  if (chdir("tmpSaveMap") == -1)
    return ;
  irr::IrrlichtDevice  *device = irr::createDevice(irr::video::EDT_NULL);
  std::string		fileNameMap = "MapSave" + getCurrentDate() + ".xml";
  irr::io::IXMLWriter* xmlr = device->getFileSystem()->createXMLWriter(fileNameMap.c_str());

  xmlr->writeXMLHeader();

  std::wstring	fileName = L"";

  fileName.assign(_filename.begin(), _filename.end());

  xmlr->writeElement(L"Info", true, L"decor", fileName.c_str());
  xmlr->writeLineBreak();

  for (std::map<AGameObject *, irr::core::vector2df>::const_iterator it = _objects.begin(),
           end = _objects.end() ; it != end ; ++it)
  {
    it->first->serialize(xmlr);
  }

  xmlr->writeClosingTag(L"mapSave");
  xmlr->drop();
  if (chdir("..") == -1)
    std::cout << "Can't back to directory" << std::endl;
}

void		BomberMap::createMapFromSave(std::string const &filename)
{
  irr::io::IrrXMLReader	*reader;
  std::string nodeName;
  AGameObjectFactory	factory;

  reader = irr::io::createIrrXMLReader(filename.c_str());
  while (reader && reader->read())
  {
    if (reader->getNodeType() == irr::io::EXN_ELEMENT)
    {
      nodeName = (char *) reader->getNodeName();
      factory.instantiateGameObjectFromXMLFile(reader, nodeName);
    }
  }
}

irr::scene::ICameraSceneNode *BomberMap::get_camera() const {
  return _camera;
}

void BomberMap::deserialize()
{
  irr::io::IrrXMLReader *reader;
  int initAsset;
  bool initCam;
  bool initTarget;
  reader = irr::io::createIrrXMLReader(_filename.c_str());
  initAsset = 0;
  initCam = false;
  initTarget = false;
  std::string nodeName;
  std::string meshesDir;
  std::string texturesDir;
  while (reader && reader->read())
  {
    if (reader->getNodeType() == irr::io::EXN_ELEMENT)
    {
      nodeName = (char *) reader->getNodeName();
      if (!initTarget && nodeName == "target")
      {
        _target.X = reader->getAttributeValueAsFloat("px");
        _target.Y = reader->getAttributeValueAsFloat("py");
        _target.Z = reader->getAttributeValueAsFloat("pz");
        initTarget = true;
      }
      if (initTarget && !initCam && nodeName == "camera")
      {
        _camera_pos.X = reader->getAttributeValueAsFloat("px");
        _camera_pos.Y = reader->getAttributeValueAsFloat("py");
        _camera_pos.Z = reader->getAttributeValueAsFloat("pz");
	      _camera = GameManager::SharedInstance()->getCam(GameManager::GameCamera::GAME_CAMERA);
	      _camera->setPosition(_camera_pos);
        _camera->setAspectRatio(19/9);
        _camera->setFOV(reader->getAttributeValueAsFloat("fov"));
        _camera->setTarget(_target);
        _camera->setAutomaticCulling(irr::scene::EAC_OFF);
        _camera->setFarValue(1000);
        _camera->setNearValue(10);
        initCam = true;
      }
      else if (nodeName == "size")
      {
        _mapSize = (Size) reader->getAttributeValueAsInt("size");
	initSpawn();
      }
      else if (nodeName == "ambient_light")
      {
        IrrlichtController::getSceneManager()->setAmbientLight(irr::video::SColorf(reader->getAttributeValueAsFloat("r"),
                                                                                   reader->getAttributeValueAsFloat("g"),
                                                                                   reader->getAttributeValueAsFloat("b"),
                                                                                   reader->getAttributeValueAsFloat("a")));
      }
      else if (nodeName == "light")
      {
        irr::scene::ILightSceneNode*   light;
        irr::video::SLight             light_data;

        nodeName = reader->getAttributeValueSafe("type");
        if (nodeName == "spot")
          light_data.Type = irr::video::ELT_SPOT;
        else if (nodeName == "point")
          light_data.Type = irr::video::ELT_POINT;
        else if (nodeName == "directional")
          light_data.Type = irr::video::ELT_DIRECTIONAL;
        light_data.Radius = reader->getAttributeValueAsFloat("radius");
        light_data.OuterCone = reader->getAttributeValueAsFloat("outer_cone");
        Color col(reader->getAttributeValueSafe("ambient_color"));
        light_data.AmbientColor = irr::video::SColorf(col.r, col.g, col.b);
        col.set(reader->getAttributeValueSafe("specular_color"));
        light_data.SpecularColor = irr::video::SColorf(col.r, col.g, col.b, col.a);
        col.set(reader->getAttributeValueSafe("diffuse_color"));
        light_data.DiffuseColor = irr::video::SColorf(col.r, col.g, col.b, col.a);

        light = IrrlichtController::getSceneManager()->addLightSceneNode();
        light->setLightData(light_data);
        light->setRadius(reader->getAttributeValueAsFloat("radius"));
        light->enableCastShadow(false);
        light->setPosition(irr::core::vector3df(reader->getAttributeValueAsFloat("px"),
                                                reader->getAttributeValueAsFloat("py"),
                                                reader->getAttributeValueAsFloat("pz")));
        light->setRotation(irr::core::vector3df(reader->getAttributeValueAsFloat("rx"),
                                                reader->getAttributeValueAsFloat("ry"),
                                                reader->getAttributeValueAsFloat("rz")));

      }
      else if (nodeName == "meshes_dir")
      {
        meshesDir = reader->getAttributeValueSafe("file");
        initAsset += 1;
      }
      else if (nodeName == "textures_dir")
      {
        texturesDir = reader->getAttributeValueSafe("file");
        initAsset += 1;
      }
      else if (initAsset == 2 && nodeName == "props")
      {
        float repeat = reader->getAttributeValueAsFloat("repeat");
        Props *prop = new Props(meshesDir + std::string(reader->getAttributeValueSafe("mesh")),
                                   texturesDir + std::string(reader->getAttributeValueSafe("texture")),
                                   irr::core::vector2df(repeat, repeat),
                                   reader->getAttributeValueAsInt("transparent"));
        float sx = reader->getAttributeValueAsFloat("sx");
        float sy = reader->getAttributeValueAsFloat("sy");
        float sz = reader->getAttributeValueAsFloat("sz");
        prop->getSceneNode()->setScale(irr::core::vector3df((sx)?sx:1, (sy)?sy:1, (sz)?sz:1));
        _props.push_back(prop);
      }
      else if (nodeName == "walls")
      {
        _walls[0].first = meshesDir + reader->getAttributeValueSafe("mesh1");
        _walls[0].second = texturesDir + reader->getAttributeValueSafe("texture1");
        _walls[1].first = meshesDir + reader->getAttributeValueSafe("mesh2");
        _walls[1].second = texturesDir + reader->getAttributeValueSafe("texture2");
        _walls[2].first = meshesDir + reader->getAttributeValueSafe("mesh3");
        _walls[2].second = texturesDir + reader->getAttributeValueSafe("texture3");
      }
    }
  }
  delete reader;
}

void		BomberMap::refreshCamera()
{
  _camera->setPosition(_camera_pos);
  _camera->setTarget(_target);
}

void		BomberMap::newMap(Size mapSize)
{
  if (bomberMap)
  {
    delete bomberMap;
  }
  bomberMap = new BomberMap(mapSize);
}

void		BomberMap::newMap(std::string const& filename)
{
  if (bomberMap)
  {
    delete bomberMap;
  }
  bomberMap = new BomberMap(filename);
  bomberMap->deserialize();
}

void		BomberMap::deleteMap()
{
  if (bomberMap)
  {
    delete bomberMap;
  }
  bomberMap = NULL;
}

bool		BomberMap::isInstantiate()
{
  if (bomberMap)
    return (true);
  return (false);
}

BomberMap       * BomberMap::getMap()
{
  if (!bomberMap) {
    bomberMap = new BomberMap();
  }
  return (bomberMap);
}

std::vector<AGameObject *> const &BomberMap::getCharacters() const
{
  return (_characters);
}

void  BomberMap::add(AGameObject* obj, const irr::core::vector2df &pos)
{
  this->_objects[obj] = pos;
  if (obj->getType() == AGameObject::CHARACTER)
    _characters.push_back(obj);
  _dangerMap.refresh(this);
}

void  BomberMap::remove(AGameObject *obj)
{
  this->_objects.erase(obj);
  if (obj->getType() == AGameObject::CHARACTER)
  {
    std::vector<AGameObject *>::iterator	it = _characters.begin();
    while (it != _characters.end())
    {
      if (*it == obj)
        it = _characters.erase(it);
      else
        ++it;
    }
  }
  _dangerMap.refresh(this);
}

void  BomberMap::move(AGameObject *obj, const irr::core::vector2df &pos)
{
  this->_objects[obj] = pos;
  _dangerMap.refresh(this);
}

std::vector<AGameObject *>  BomberMap::getObjsFromVector2(const irr::core::vector2df &pos) const
{
  std::vector<AGameObject *>  objs;

  for (std::map<AGameObject*, irr::core::vector2df>::const_iterator it = this->_objects.begin(); it != this->_objects.end(); ++it) {
    if (it->second == pos) {
      objs.push_back(it->first);
    }
  }
  return (objs);
}

const irr::core::vector2df  &BomberMap::get(AGameObject *obj) const
{
  return (this->_objects.find(obj)->second);
}

void    BomberMap::loadModel(struct model mod)
{
  irr::scene::IAnimatedMesh           *meshNode;
  irr::scene::IAnimatedMeshSceneNode  *node;

  if (!(meshNode = IrrlichtController::getSceneManager()->getMesh(mod.mesh.c_str())))
  {
    IrrlichtController::getDevice()->drop();
    throw std::runtime_error("Failed to create IAnimatedMesh in AGameObject");
  }
  else if ((node = IrrlichtController::getSceneManager()->addAnimatedMeshSceneNode(meshNode, 0, 0)))
  {
    node->setMaterialTexture(0, IrrlichtController::getDriver()->getTexture(mod.texture.c_str()));
    node->setMD2Animation(irr::scene::EMAT_STAND);
    node->setMaterialFlag(irr::video::EMF_LIGHTING ,true);
  }
}

void BomberMap::removeBlocks()
{
  std::map<AGameObject*, irr::core::vector2df>::iterator it_o = _objects.begin();
  while (it_o != _objects.end())
  {
    AGameObject	*obj = (*it_o).first;
    if (!dynamic_cast<ACharacter *>(obj))
    {
      GameObjectTimeContainer::SharedInstance()->remove(obj);
      delete (obj);
      it_o = _objects.begin();
    }
    else
      ++it_o;
  }
}

DangerMap &BomberMap::giveDangerMap(void)
{
  return _dangerMap;
}
