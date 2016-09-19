//
// IrrlichtController.hpp for IRRLICHT in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:04:35 2016 Victor Gouet
// Last update Sun Jun  5 12:56:18 2016 Matthieu Tavernier
//

#ifndef IRRLICHTCONTROLLER_HPP_
# define IRRLICHTCONTROLLER_HPP_

# include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"
# include <map>

class AGameObject;

class	IrrlichtController
{
public:
    static size_t    width;
    static size_t    height;
  static irr::IrrlichtDevice                *getDevice(bool fullScreen = true);
  static irr::video::IVideoDriver           *getDriver();
  static irr::scene::ISceneManager          *getSceneManager();
  static irr::gui::IGUIEnvironment          *getGUIEnvironment();

private:
    static irr::IrrlichtDevice      *device;

public:
    static const size_t         bombSize = 15;
};

#endif
