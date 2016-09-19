//
// LoadHightScore.cpp for LoadHightScore in /home/gouet_v/Rendu/semester4/CPP/cpp_arcade/HightScore
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Mon Mar 14 18:04:40 2016 Victor Gouet
// Last update Sun Jun  5 17:02:02 2016 Matthieu Tavernier
//

#include "LoadHighScore.hpp"

LoadHighScore::LoadHighScore(std::string const &fileName) : fileName(fileName)
{
  std::ifstream		fd;
  std::stringstream	buffer;
  t_header		header;
  int			lenght;
  int			i;

  fd.open(fileName.c_str(), std::ios::in | std::fstream::binary);
  if (fd.is_open())
    {
      fd.seekg(0, fd.end);
      lenght = fd.tellg();
      fd.seekg(0, fd.beg);
      std::memset(&header, 0, sizeof(t_header));
      fd.read(reinterpret_cast<char *>(&header), sizeof(t_header));
      if (header.magicNbr != MAGICNBR)
	throw std::out_of_range("LoadHighScore: Bad Magic Number");
      if (header.headerSize != sizeof(t_header))
	throw std::out_of_range("LoadHighScore: Bad header size");
      if (header.fileSize != lenght)
      	throw std::out_of_range("LoadHighScore: Bad file size");
      i = 0;
      while (i < header.nbrHighScore
	     && (int)(sizeof(t_header) + (sizeof(t_highScore) * i)) < header.fileSize)
	{
	  t_highScore	*highScore = new s_highScore();
	  fd.read(reinterpret_cast<char *>(highScore), sizeof(t_highScore));
	  highScoreList.push_back(highScore);
	  ++i;
	}
      fd.close();
    }
}

LoadHighScore::~LoadHighScore()
{
  std::vector<t_highScore *>::const_iterator	it = highScoreList.begin();

  while (it != highScoreList.end())
    {
      delete *it;
      ++it;
    }
}

bool		     LoadHighScore::isUpper(const t_highScore *first,
					     const t_highScore *last)
{
  return (first->getScore() > last->getScore());
}

void					LoadHighScore::setHighScore(t_highScore *newScore)
{
  bool					check = true;

  std::vector<t_highScore *>::iterator	it = highScoreList.begin();
  while (it != highScoreList.end())
    {
      if ((*it)->getName() == newScore->getName())
	{
	  (*it)->setScore(newScore->getScore() + (*it)->getScore());
	  check = false;
	}
      ++it;
    }
  if (check)
    highScoreList.push_back(newScore);
  std::sort(highScoreList.begin(), highScoreList.end(), LoadHighScore::isUpper);
}

const std::vector<t_highScore *>	LoadHighScore::getAllHighScore() const
{
  return (highScoreList);
}

std::string const			&LoadHighScore::getFileName() const
{
  return (this->fileName);
}

void					LoadHighScore::flush() const
{
  std::ofstream						fd;
  std::vector<t_highScore *>::const_iterator	it;
  t_header		        *header = new s_header(sizeof(t_header),
						       sizeof(t_header) +
						       (sizeof(t_highScore) * highScoreList.size()), highScoreList.size());

  fd.open(fileName.c_str(), std::ios::binary | std::ios::out | std::ios::trunc);
  if (fd.is_open())
    {
      fd.write(reinterpret_cast<const char *>(header), sizeof(t_header));
      it = highScoreList.begin();
      while (it != highScoreList.end())
      	{
      	  fd.write(reinterpret_cast<const char *>(*it), sizeof(t_highScore));
      	  ++it;
      	}
      fd.close();
      delete header;
    }
}

std::ostream &operator<<(std::ostream &ostream, LoadHighScore const &highScore)
{
  std::vector<t_highScore *>::const_iterator	it;
  const std::vector<t_highScore *>		vectorHighScore =
    highScore.getAllHighScore();

  it = vectorHighScore.begin();
  while (it != vectorHighScore.end())
    {
      ostream << "{" << std::endl << "\t" << "name: \"" << (*it)->getName() << "\"," << std::endl;
      ostream <<  "\t" << "highScore: " << (*it)->getScore() << std::endl;
      ostream << "}" << std::endl;
      ++it;
    }
  return (ostream);
}
