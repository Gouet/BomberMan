//
// Created by gaspar_q on 5/9/16.
//

#include <BomberMap.hpp>
#include "IAPlayer.hpp"
#include "LuaBomberMap.hpp"
#include "LuaVector2.hpp"
#include "LuaGameObjectArray.hpp"

template <>
const std::string Lua::LuaClass<IAPlayer>::className = "IA";

const std::string     IAPlayer::easyLvl = "easyBehaviour";
const std::string     IAPlayer::mediumLvl = "mediumBehaviour";
const std::string     IAPlayer::hardLvl = "hardBehaviour";
Lua::LuaHandler       *IAPlayer::handler;

const double IAPlayer::easyRate = 10;
const double IAPlayer::mediumRate = 5;
const double IAPlayer::hardRate = 2;

/**
 * @desc Will initialise the lua state for an IA usage, will initialise prototypes, classes and globals in the code
 *
 * @param width The width of the map
 * @param height The height of the map
 */
void IAPlayer::initIA(int width, int height)
{
    Lua::LuaClass<BomberMap>::LuaPrototype({
                                                   {"objsAtPos", LuaBomberMap::objsAtPos},
                                                   {"getDangerAtPos", LuaBomberMap::getDangerAtPos},
                                                   {"getNbOfType", LuaBomberMap::getNbOfType}
                                           }).Register();
    Lua::LuaClass<irr::core::vector2df>::LuaPrototype({
                                                              {"new", Lua::LuaClass<irr::core::vector2df>::defaultConstructor},
                                                              {"creat", LuaVector2::createPos},
                                                              {"getX", LuaVector2::getX},
                                                              {"getY", LuaVector2::getY},
                                                              {"setX", LuaVector2::setX},
                                                              {"setY", LuaVector2::setY},
                                                              {"mul", LuaVector2::mul},
                                                              {"add", LuaVector2::add},
                                                              {"equal", LuaVector2::equal},
                                                              {"__gc", Lua::LuaClass<irr::core::vector2df>::defaultDestructor}
                                                      }).Register();
    Lua::LuaClass<std::vector<AGameObject *> >::LuaPrototype({
                                                                     {"new", Lua::LuaClass<std::vector<AGameObject *> >::defaultConstructor},
                                                                     {"typeAtIndex", LuaGameObjectArray::typeAtIndex},
                                                                     {"posAtIndex", LuaGameObjectArray::posAtIndex},
                                                                     {"size", LuaGameObjectArray::size},
                                                                     {"hasType", LuaGameObjectArray::hasType},
                                                                     {"__gc", Lua::LuaClass<std::vector<AGameObject *> >::defaultDestructor}
                                                             }).Register();
    Lua::LuaClass<IAPlayer>::LuaPrototype({
                                                  {"getPos", getIAPos},
                                                  {"bombDropSimul", simulateBombDrop},
                                                  {"getFocus", getIAFocusPos},
                                                  {"setFocus", setIAFocusPos},
                                                  {"canDropBomb", canIADropBomb}
                                          }).Register();
    Lua::setGlobalValue(width, "MapW");
    Lua::setGlobalValue(height, "MapH");
    Lua::setGlobalValue((int)AGameObject::Type::NONE, "NONE");
    Lua::setGlobalValue((int)AGameObject::Type::CHARACTER, "CHARACTER");
    Lua::setGlobalValue((int)AGameObject::Type::BOMB, "BOMB");
    Lua::setGlobalValue((int)AGameObject::Type::ITEM, "ITEM");
    Lua::setGlobalValue((int)AGameObject::Type::BLOCK, "BLOCK");
    Lua::setGlobalValue((int)AGameObject::Type::BONUS, "BONUS");
    Lua::setGlobalValue((int)AGameObject::Type::BOOM, "BOOM");
    Lua::setGlobalValue((int)AGameObject::Type::OTHER, "OTHER");
    Lua::setGlobalValue((int)ACharacter::IDLE, "IDLE");
    Lua::setGlobalValue((int)ACharacter::LEFT, "LEFT");
    Lua::setGlobalValue((int)ACharacter::RIGHT, "RIGHT");
    Lua::setGlobalValue((int)ACharacter::UP, "UP");
    Lua::setGlobalValue((int)ACharacter::DOWN, "DOWN");
    Lua::setGlobalValue((int)ACharacter::BOMB, "DROPBOMB");
    Lua::setGlobalValue((int)ACharacter::ACT, "ACT");
    Lua::setGlobalValue((int)DangerMap::ERROR, "ERSTATE");
    Lua::setGlobalValue((int)DangerMap::DANGEROUS, "DANGEROUS");
    Lua::setGlobalValue((int)DangerMap::BLOCKED, "BLOCKED");
    Lua::setGlobalValue((int)DangerMap::SAFE, "SAFE");
    Lua::setGlobalValue(BINDIR, "BINARY");
    handler = new Lua::LuaHandler(BINDIR"ia/iaBehaviour.lua");
}


/**
 * @desc Will shutdown the lua state used by IA, will unregister classes and delete the lua_state and the handler
 */
void IAPlayer::shutDownIA()
{
    Lua::LuaClass<BomberMap>::LuaPrototype().Unregister();
    Lua::LuaClass<irr::core::vector2df>::LuaPrototype().Unregister();
    Lua::LuaClass<std::vector<AGameObject *> >::LuaPrototype().Unregister();
    Lua::LuaClass<IAPlayer>::LuaPrototype().Unregister();
    Lua::acquireState(NULL, true);
    delete(handler);
}

/**
 * @desc Will serialise an IA into an xml send in parameters
 *
 * @param xmlr The xml writer that correspond to the xml file in which serialize the IA
 */
void	        IAPlayer::serialize(irr::io::IXMLWriter *xmlr) const
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

  std::wstring		playerName = L"";
  playerName.assign(getName().begin(), getName().end());

  xmlr->writeElement(L"IAPlayer", true,
		     L"x", xValue.c_str(),
		     L"y", yValue.c_str(),
		     L"mesh", mesh.c_str(),
		     L"texture", texture.c_str(),
		     L"name", playerName.c_str()
		     );
  xmlr->writeLineBreak();
}

/**
 * @desc IAPlayer constructor that have to be called, will recurse initialize ACharacter
 *
 * @param name Player name
 * @pos The spawn position of the IA
 * @mesh The mesh(shape) of the IA
 * @texture The texture(skin) of the IA
 * @player The player id in the game
 * @diff The difficulty of the IA can be easyLvl, mediumLvl, hardLvl
 */
IAPlayer::IAPlayer(std::string const &name, irr::core::vector2df const &pos, const std::string &mesh, const std::string &texture, int player, const std::string &diff) :
    ACharacter(name, pos, mesh, texture, player),
    behaviour(diff),
    focus(pos.X, pos.Y),
    bombRate(0),
    nextBomb(0)
{
    if (behaviour == IAPlayer::mediumLvl)
        bombRate = IAPlayer::mediumRate;
    else if (behaviour == IAPlayer::hardLvl)
        bombRate = IAPlayer::hardRate;
    else
        bombRate = IAPlayer::easyRate;
    nextBomb = std::clock() / 1000000 + bombRate;
}

/**
 * @desc IAPlayer desctructor that does nothing
 */
IAPlayer::~IAPlayer()
{

}

/**
 * @desc Compute method that will be called at each frame if the IA is not dead. The method will do an action in game
 */
void IAPlayer::compute()
{
    ACharacter::ACTION todo;

    try
    {
        if (!isArrived())
            todo = static_cast<ACharacter::ACTION >(-1);
        else
        {
            Lua::setGlobalValue(BomberMap::getMap(), "bomberMap");
            Lua::setGlobalValue(BomberMap::getMap()->getSize(), "MapW");
            Lua::setGlobalValue(BomberMap::getMap()->getSize(), "MapH");
            todo = static_cast<ACharacter::ACTION>((*IAPlayer::handler)[behaviour](this));
            if (todo == ACharacter::BOMB)
                nextBomb = std::clock() / 1000000 + bombRate;
        }
    }
    catch (std::exception &exception)
    {
        std::cerr << "IA Computation: " << exception.what() << std::endl;
        todo = static_cast<ACharacter::ACTION >(rand() % (ACharacter::ACT + 1));
    }
    this->action(todo);
}

/**
 * @desc Difficulty setter
 *
 * @param difficulty The difficulty you want to set, can be easyLvl, mediumLvl, hardLvl
 */
void IAPlayer::setDifficulty(const std::string &difficulty)
{
    behaviour = difficulty;
}

/**
 * @desc Simulate a bomb drop at its position
 *
 * @return The last fallback position after droping a bomb
 */
irr::core::vector2df IAPlayer::bombDropSimulation() const
{
    ABomb   *toDrop = getBombContainer()->getBomb();

    if (!toDrop)
        return irr::core::vector2df(-1, -1);

    BomberMap::getMap()->move(toDrop, getMapPos());
    irr::core::vector2df    fallBack = BomberMap::getMap()->giveDangerMap().getFirstFallBackPosition(getMapPos());
    BomberMap::getMap()->move(toDrop, irr::core::vector2df(-1000, -1000));

    return fallBack;
}

/**
 * @desc Getter for difficulty
 *
 * @return The difficulty of the IA
 */
const std::string &IAPlayer::getDifficulty(void) const
{
    return behaviour;
}

/**
 * @desc Tells if an IA can drop a bomb
 *
 * @return true if she can, false either
 */
bool IAPlayer::canDropBomb() const
{
    if (std::clock() / 1000000 > nextBomb)
        return true;
    return false;
}

/**
 * @desc Getter for the difficulty from a PlayerInfo code
 *
 * @param strength The code from PlayerInfo
 * @return The difficulty that correspond, if no code are corresponding, return easyLvl
 */
const std::string &IAPlayer::getDifficultyFromCode(PlayerInfo::IAStrength strength)
{
    switch (strength)
    {
        case PlayerInfo::EASY:
            return IAPlayer::easyLvl;
        case PlayerInfo::MEDIUM:
            return IAPlayer::mediumLvl;
        case PlayerInfo::HARD:
            return IAPlayer::hardLvl;
        default:
            return IAPlayer::easyLvl;
    }
}

/**
 * @desc Static function for LuaClass<IAPlayer>::LuaPrototype that get the IA current position
 *
 * @return The index of the IA position in the lua stack
 */
int IAPlayer::getIAPos(lua_State *)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();
    Lua::LuaClass<irr::core::vector2df> toret(thisptr->getMapPos());

    toret.dontDelete();
    return 1;
}

/**
 * @desc Static function for LuaClass<IAPlayer>::LuaPrototype that simulate a bomb drop
 *
 * @return The index of the IA last fallback position or null in the lua stack
 */
int IAPlayer::simulateBombDrop(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();

    irr::core::vector2df    fallbackPos = thisptr->bombDropSimulation();
    if (fallbackPos == irr::core::vector2df(-1, -1))
    {
        return (0);
    }
    Lua::LuaClass<irr::core::vector2df> toret(fallbackPos);

    toret.dontDelete();
    return 1;
}

/**
 * @desc Static function for LuaClass<IAPlayer>::LuaPrototype that get the IA focus position
 *
 * @return The index of the IA focus position in the lua stack
 */
int IAPlayer::getIAFocusPos(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();
    Lua::LuaClass<irr::core::vector2df> topush(thisptr->focus);

    topush.dontDelete();
    return 1;
}

/**
 * @desc Static function for LuaClass<IAPlayer>::LuaPrototype that set the IA focus position
 *
 * @return null
 */
int IAPlayer::setIAFocusPos(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();
    irr::core::vector2df *toset = Lua::LuaClass<irr::core::vector2df>::getThis(2);

    thisptr->focus = *toset;
    return 0;
}

/**
 * @desc Static function for LuaClass<IAPlayer>::LuaPrototype that tells if an ia can drop a bomb
 *
 * @return The index of the boolean returned in the lua stack
 */
int IAPlayer::canIADropBomb(lua_State *state)
{
    IAPlayer    *thisptr = Lua::LuaClass<IAPlayer>::getThis();

    lua_pushboolean(state, thisptr->canDropBomb());
    return 1;
}
