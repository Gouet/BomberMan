//
// Created by veyrie_f on 5/22/16.
//

#ifndef CPP_INDIE_STUDIO_PLAYERINFO_HPP
#define CPP_INDIE_STUDIO_PLAYERINFO_HPP

#include <iostream>
#include "IrrlichtController.hpp"
#include "AController.hpp"

/*
 * \brief This class hold the info concerning a player
 */
class PlayerInfo
{
public:
    enum IAStrength
    {
        EASY, MEDIUM, HARD
    };

public:

    PlayerInfo(std::string const &name, std::string const &skin, bool bIsIa = false,
               IAStrength strength = EASY, AController *controller = nullptr);

    PlayerInfo(std::string const &name,
               std::string const &mesh,
               std::string const &texture,
               bool bIsIa = false,
               IAStrength strength = EASY,
               AController *controller = nullptr);

    ~PlayerInfo();

public:
    void setPos(irr::core::vector2df const &pos);

public:
    std::string const &GetName() const;
    std::string const &GetMesh() const;
    std::string const &GetTexture() const;
    bool GetIsIA() const;
    IAStrength GetIAStrength() const;
    irr::core::vector2df const *GetPos() const;
    AController const* GetController() const;

private:
    std::string m_name;
    std::string _mesh;
    std::string _texture;
    bool m_isIa;
    IAStrength m_strength;
    irr::core::vector2df *pos;
	AController *m_controller;
};


#endif //CPP_INDIE_STUDIO_PLAYERINFO_HPP
