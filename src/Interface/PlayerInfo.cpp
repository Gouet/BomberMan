//
// Created by veyrie_f on 5/22/16.
//

#include "Texture.hpp"
#include "PlayerInfo.hpp"

PlayerInfo::PlayerInfo(std::string const &name,
                       std::string const &skin,
                       bool bIsIa,
                       PlayerInfo::IAStrength strength, AController *controller) :
        m_name(name),
        _mesh(BomberManTexture::getModel(skin).mesh),
        _texture(BomberManTexture::getModel(skin).texture),
        m_isIa(bIsIa),
        m_strength(strength),
        m_controller(controller)
{
    this->pos = NULL;
}


PlayerInfo::PlayerInfo(std::string const &name,
                       std::string const &mesh,
                       std::string const &texture,
                       bool bIsIa,
                       IAStrength strength, AController *controller) :
          m_name(name),
          _mesh(mesh),
          _texture(texture),
          m_isIa(bIsIa),
          m_strength(strength),
          m_controller(controller)
{
    this->pos = NULL;
}

PlayerInfo::~PlayerInfo()
{
    if (this->pos)
        delete this->pos;
}

void    PlayerInfo::setPos(irr::core::vector2df const &pos)
{
    this->pos = new irr::core::vector2df(pos);
}

irr::core::vector2df const *PlayerInfo::GetPos() const
{
    return (this->pos);
}

std::string const &PlayerInfo::GetMesh() const
{
    return (_mesh);
}

std::string const &PlayerInfo::GetTexture() const
{
    return (_texture);
}

std::string const &PlayerInfo::GetName() const
{
    return m_name;
}

bool PlayerInfo::GetIsIA() const
{
    return m_isIa;
}

PlayerInfo::IAStrength PlayerInfo::GetIAStrength() const
{
    return m_strength;
}

AController const *PlayerInfo::GetController() const
{
    return m_controller;
}
