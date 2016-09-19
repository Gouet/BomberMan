//
// Created by wery_a on 26/05/16.
//

#include <stdexcept>
#include <vector>
#include <iostream>
#include "Texture.hpp"
#include "SoundManager.hpp"

//# define DEBUG

SoundManager            *SoundManager::manager = NULL;

SoundManager            *SoundManager::getManager()
{
    if (!manager)
        manager = new SoundManager();
    return (manager);
}

SoundManager::SoundManager() : soundPath(BINDIR"media/sound/")
{
#ifndef DEBUG
    FMOD::System_Create(&engine);
    engine->init(32, FMOD_INIT_NORMAL, NULL);
#endif
}

SoundManager::~SoundManager()
{
#ifndef DEBUG
    for (std::map<std::string, FMOD::Sound *>::iterator it = this->_sounds.begin(); it != this->_sounds.end(); ++it)
    {
        it->second->release();
    }
    engine->close();
    engine->release();
#endif
}

void    SoundManager::play(std::string const &sound, unsigned int id, bool loop, float volume)
{
#ifndef DEBUG
    FMOD::Channel   *channel;

    if (this->_sounds[sound] == 0)
    {
        engine->createSound((soundPath + sound).c_str(), (loop) ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &this->_sounds[sound]);
    }
    engine->playSound(this->_sounds[sound], 0, false, &channel);
    channel->setVolume(volume);
    if (this->_channels[id] && id) {
        this->_channels[id]->stop();
    }
    if (id == 0)
        this->_channelsCOM.push_back(channel);
    else
        this->_channels[id] = channel;
#endif
}

void    SoundManager::stop(int id)
{
#ifndef DEBUG
    if (id == -1)
        stopAll();
    if (this->_channels[id])
    {
        this->_channels[id]->stop();
        this->_channels.erase(id);
    }
#endif
}

void    SoundManager::stopAll()
{
#ifndef DEBUG
    for (std::map<unsigned int, FMOD::Channel *>::iterator it = this->_channels.begin(); it != this->_channels.end(); ++it) {
        it->second->stop();
    }
    this->_channels.clear();
    this->stopAllBack();
#endif
}

void    SoundManager::stopAllBack()
{
#ifndef DEBUG
    for (std::vector<FMOD::Channel *>::iterator it = this->_channelsCOM.begin(); it != this->_channelsCOM.end(); ++it) {
        (*it)->stop();
    }
    this->_channelsCOM.clear();
#endif
}
