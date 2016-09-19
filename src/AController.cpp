/*
** AController.hpp for cpp_indie_studio
**
** Made by	Adrien WERY
** Login	wery_a
**
** Started on	Fri Apr 29 10:01:24 2016 Adrien WERY
** Last update	Fri Apr 29 10:04:15 2016 Adrien WERY
*/

#include "AController.hpp"

AController::AController() : _used(false)
{

}

AController::~AController()
{

}

void	AController::stopUseIt() const
{
  this->_used = false;
}

bool    AController::isUsed() const
{
    return (this->_used);
}

void    AController::useIt()
{
    this->_used = true;
}
