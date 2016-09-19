//
// Created by wery_a on 26/05/16.
//

#ifndef CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
# define CPP_INDIE_STUDIO_SOUNDMANAGER_HPP

# include <string>
# include <map>
# include <vector>
# include <fmod.hpp>

class SoundManager {
private:
    std::map<std::string, FMOD::Sound *>    _sounds;
    std::map<unsigned int, FMOD::Channel *> _channels;
    std::vector<FMOD::Channel *>            _channelsCOM;
    FMOD::System         *engine;
    const std::string    soundPath;

public:
    static SoundManager             *manager;

public:
    static SoundManager             *getManager();

public:
    SoundManager();
    virtual ~SoundManager();
    void    play(std::string const &sound, unsigned  int id = 0, bool loop = false, float volume = 1.0);
    void    stop(int id);
    void    stopAll();
    void    stopAllBack();
};

#endif //CPP_INDIE_STUDIO_SOUNDMANAGER_HPP
