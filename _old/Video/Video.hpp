//
// Video.hpp for indie studio in /home/tavern_d/rendu/semestre4/cpp_indie_studio/include
// 
// Made by Matthieu Tavernier
// Login   <tavern_d@epitech.net>
// 
// Started on  Thu Apr 28 11:35:00 2016 Matthieu Tavernier
// Last update Mon May 16 15:20:51 2016 Matthieu Tavernier
//

#ifndef VIDEO_HPP_
# define VIDEO_HPP_

# include <stdio.h>
# include <dirent.h>
# include <vector>
# include <iostream>
# include <unistd.h>
# include <algorithm>
# include "../Irrlicht/irrlicht-1.8.3/include/irrlicht.h"
# include "../IrrKlang/include/irrKlang.h"

class Video
{
private:
    static const std::string default_path_video;
    static const std::string default_path_sound;
public:
    Video(const std::string path = default_path_video);
    ~Video();

public:
    void Run();

private:
    std::vector<std::string> files;
};

#endif /* !VIDEO_HPP_ */
