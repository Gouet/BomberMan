//
// HighScore.cpp for HIGHTSCORE in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Sat Jun  4 14:14:04 2016 Victor Gouet
// Last update Sun Jun  5 16:53:48 2016 Matthieu Tavernier
//

#include "HighScore.hpp"

s_header::s_header(int headerSize, int fileSize, int nbrHighScore)
  : magicNbr(MAGICNBR), headerSize(headerSize), fileSize(fileSize), nbrHighScore(nbrHighScore)
{
}

s_header::s_header()
{
}


s_highScore::s_highScore(int newScore, std::string const &newName)
{
  score = 0;
  std::memset(name, 0, sizeof(name));
  setName(newName);
  setScore(newScore);
}

s_highScore::s_highScore()
{
  score = 0;
  std::memset(name, 0, sizeof(name));
}

void	        s_highScore::setName(std::string const &newName)
{
  unsigned int	i = 0;

  while (i < newName.size() && i < sizeof(name) - 1)
    {
      name[i] = newName[i];
      ++i;
    }
  name[i] = '\0';
}

void		s_highScore::setScore(int newScore)
{
  score = newScore;
}

int		s_highScore::getScore() const
{
  return (this->score);
}

std::string const s_highScore::getName() const
{
  return (std::string(name));
}
