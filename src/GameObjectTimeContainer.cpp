//
// GameObjectTimeContainer.cpp for TIME in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
// 
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
// 
// Started on  Tue May 10 18:55:37 2016 Victor Gouet
// Last update Sun Jun  5 16:53:22 2016 Matthieu Tavernier
//

#include <iostream>
#include "MineBomb.hpp"
#include "Explosion.hpp"
#include "TrackerBomb.hpp"
#include "GameObjectTimeContainer.hpp"

GameObjectTimeContainer *GameObjectTimeContainer::instance = NULL;

GameObjectTimeContainer::GameObjectTimeContainer()
{

}

GameObjectTimeContainer::~GameObjectTimeContainer()
{

}

GameObjectTimeContainer *GameObjectTimeContainer::SharedInstance()
{
    if (instance == NULL)
    {
        instance = new GameObjectTimeContainer();
    }
    return (instance);
}

void                GameObjectTimeContainer::add(AGameObject *obj)
{
    container.push_back(obj);
}

void                GameObjectTimeContainer::timerStop()
{
    std::list<AGameObject *>::iterator it = container.begin();

    while (it != container.end())
    {
        (*it)->wait();
        ++it;
    }
}

void                GameObjectTimeContainer::remove(AGameObject *obj)
{
    std::list<AGameObject *>::iterator it = container.begin();

    while (it != container.end())
    {
        if (*it == obj)
        {
            it = container.erase(it);
        }
        else
            ++it;
    }
}

void				GameObjectTimeContainer::removeAll()
{
    container.clear();
}

void				GameObjectTimeContainer::callTimeOutObjects()
{
    std::list<AGameObject *>::iterator it = container.begin();

    while (it != container.end())
    {
        if (*it) {
            (*it)->updateTimeOut();
        }

        if (*it && (*it)->isTimeOut())
        {
            (*it)->dead();
            if ((*it)->isDestructible())
            {
                delete (*it);
                it = container.begin();
            }
            else
            {
                it = container.erase(it);
            }
        }
        else
        {
            ++it;
        }
    }
}
