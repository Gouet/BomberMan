//
// main.cpp for MAIN in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio/src
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Tue Apr 26 21:31:44 2016 Victor Gouet
// Last update Sun Jun  5 17:04:56 2016 Matthieu Tavernier
//

#include "GameManager.hpp"

int	main()
{
  try
  {
    GameManager::SharedInstance()->run();
    delete(GameManager::SharedInstance());
    IrrlichtController::getDevice()->drop();
  }
  catch (std::exception &exp)
  {
    std::cerr << exp.what() << std::endl;
    return (1);
  }
  return (0);
}
