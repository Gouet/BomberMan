//
// Created by consta_n on 19/05/16.
//

#ifndef CPP_INDIE_STUDIO_PROPS_HPP
#define CPP_INDIE_STUDIO_PROPS_HPP


#include "AGameObject.hpp"

class Props : public AGameObject {

public:
  Props(const std::string &mesh,
        const std::string &texture, irr::core::vector2df const &, int transparent);
  virtual ~Props();

public:
  virtual void                        dead();
  virtual bool				isDestructible() const;
  virtual void				serialize(irr::io::IXMLWriter *) const;
};


#endif //CPP_INDIE_STUDIO_PROPSMAP_HPP
