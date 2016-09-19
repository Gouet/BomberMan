//
// HighScore.hpp for HighScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HighScore
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 17:40:43 2016 Victor Gouet
// Last update Sat Jun  4 14:18:54 2016 Victor Gouet
//

#ifndef HIGHSCORE_HPP_
# define HIGHSCORE_HPP_

# define MAGICNBR	1996

# include <cstring>
# include <iostream>

typedef struct	s_header
{
  int		magicNbr;
  int		headerSize;
  int		fileSize;
  int		nbrHighScore;

  s_header(int headerSize, int fileSize, int nbrHighScore);
  s_header();
}		t_header;

typedef struct	s_highScore
{
private:
  char		name[20];
  int		score;

public:
  s_highScore(int newScore, std::string const &newName);
  s_highScore();

public:
  void	        setName(std::string const &newName);
  void		setScore(int newScore);

public:
  int		getScore() const;
  std::string const getName() const;

}		t_highScore;

#endif
