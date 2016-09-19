//
// Texture.hpp for TEXTURE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 14:24:03 2016 Victor Gouet
// Last update Fri May 20 15:30:47 2016 Victor Gouet
//

#ifndef TEXTURE_HPP_
# define TEXTURE_HPP_

# include <string>
# include "IrrlichtController.hpp"

#ifndef BINDIR
# define BINDIR "./"
#endif

struct model {
    std::string   mesh;
    std::string   texture;
};

class	BomberManTexture
{
public:
    static const std::string path;
  
    static const std::string smallMap;
    static const std::string mediumMap;
    static const std::string largeMap;
    static const std::string bombs;
    static const std::string bonus;
    static const std::string characters;
    static const std::string gui;
    static const std::string font;

    static const std::map<std::string, struct model> _models;

public:
  static void loadTexture();
   static const struct model   &getModel(const std::string &model);

};

#endif
