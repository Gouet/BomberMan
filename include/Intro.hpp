//
// Created by wery_a on 26/05/16.
//

#ifndef CPP_INDIE_STUDIO_INTRO_HPP
#define CPP_INDIE_STUDIO_INTRO_HPP

# include <string>
# include <vector>
# include "EventGame.hpp"

class Intro {
private:
    static const std::string default_path_video;

private:
    std::vector<std::string>    files;
    EventGame                   *eventGame;

public:
    Intro(EventGame *eventGame);
    ~Intro();

public:
    void    run();
};

#endif //CPP_INDIE_STUDIO_INTRO_HPP
