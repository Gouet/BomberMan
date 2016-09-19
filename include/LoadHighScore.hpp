//
// LoadHightScore.hpp for LoadHightScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HightScore/include
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 17:51:22 2016 Victor Gouet
// Last update Sat Jun  4 14:40:12 2016 Victor Gouet
//

#ifndef LOADHIGHSCORE_HPP_
# define LOADHIGHSCORE_HPP_

# include <algorithm>
# include <iostream>
# include <vector>
# include <fstream>
# include <fstream>
# include <sstream>
# include <stdexcept>
# include "HighScore.hpp"

class	LoadHighScore
{
public:
  LoadHighScore(std::string const &fileName);
  ~LoadHighScore();

public:
  void					setHighScore(t_highScore *newScore);
  const std::vector<t_highScore *>	getAllHighScore() const;
  std::string const			&getFileName() const;
  void					flush() const;

private:
  static bool					isUpper(const t_highScore *, const t_highScore *);

private:
  const std::string			fileName;
  std::vector<t_highScore *>	highScoreList;
};

std::ostream &operator<<(std::ostream &ostream, LoadHighScore const &highScore);

#endif
