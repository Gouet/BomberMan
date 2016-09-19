//
// Created by gaspar_q on 5/9/16.
//

#ifndef CPP_INDIE_STUDIO_IAPLAYER_HPP
#define CPP_INDIE_STUDIO_IAPLAYER_HPP

#include "ACharacter.hpp"
#include "PlayerInfo.hpp"
#include "LuaHandler.hpp"

class IAPlayer : public ACharacter
{
public:
    static const std::string easyLvl;
    static const std::string mediumLvl;
    static const std::string hardLvl;
    static Lua::LuaHandler   *handler;

private:
    static const double easyRate;
    static const double mediumRate;
    static const double hardRate;

public:
    explicit IAPlayer(std::string const &,
                      irr::core::vector2df const &,
                      const std::string &,
                      const std::string &,
                      int,
                      const std::string &diff = IAPlayer::easyLvl);

    ~IAPlayer();

public:
    virtual void      compute();

    virtual void      serialize(irr::io::IXMLWriter *xmlr) const;

    void              setDifficulty(const std::string &difficulty);

    const std::string &getDifficulty(void) const;

    irr::core::vector2df    bombDropSimulation() const;

    bool canDropBomb() const;

public:
    static void              initIA(int width, int height);

    static void              shutDownIA();

    static const std::string &getDifficultyFromCode(PlayerInfo::IAStrength);

private:
    static int canIADropBomb(lua_State *state);

    static int getIAPos(lua_State *state);

    static int simulateBombDrop(lua_State *state);

    static int getIAFocusPos(lua_State *state);

    static int setIAFocusPos(lua_State *state);

private:
    std::string          behaviour;
    irr::core::vector2df focus;
    double bombRate;
    double nextBomb;
};

#endif //CPP_INDIE_STUDIO_IAPLAYER_HPP
