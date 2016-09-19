//
// Created by wery_a on 11/05/16.
//

#ifndef CPP_INDIE_STUDIO_EXPLOSION_HPP
# define CPP_INDIE_STUDIO_EXPLOSION_HPP

# include "IrrlichtController.hpp"
# include "AGameObject.hpp"

class Explosion : public AGameObject {
private:
    irr::scene::IParticleSystemSceneNode    *_ps;
  irr::scene::ILightSceneNode    *_light;
  float_t _x;
public:
    Explosion(irr::core::vector2df const &pos, std::string const &texture, double timeout = 0.5);
    virtual ~Explosion();

public:
    virtual void                        dead();
    virtual bool				isDestructible() const;
  virtual void		updateTimeOut();
  virtual void	        serialize(irr::io::IXMLWriter *) const;

private:
  std::string		particuleTexture;
};

#endif //CPP_INDIE_STUDIO_EXPLOSION_HPP
