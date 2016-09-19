//
// ISerialize.hpp for SERIALIZE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon May 23 17:48:22 2016 Victor Gouet
// Last update Mon May 23 18:16:37 2016 Victor Gouet
//

#ifndef ISERIALIZE_HPP_
# define ISERIALIZE_HPP_

# include "IrrlichtController.hpp"

class		ISerialize
{
public:
  virtual void		serialize(irr::io::IXMLWriter *) const = 0;
  virtual ~ISerialize() {}
};

#endif
