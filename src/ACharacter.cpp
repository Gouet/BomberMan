//
// ACharacter.cpp for ACHARACTER in /home/gouet_v/Rendu/semester4/CPP/cpp_indie_studio
//
// Made by Victor Gouet
// Login   <gouet_v@epitech.net>
//
// Started on  Wed Apr 27 09:43:11 2016 Victor Gouet
// Last update Sun Jun  5 16:38:06 2016 Matthieu Tavernier
//

#include <unistd.h>
#include <iostream>
#include "GameManager.hpp"
#include "SoundManager.hpp"
#include "ACharacter.hpp"
#include "BombFactory.hpp"
#include "ABonus.hpp"
#include "AtomicBomb.hpp"
#include "BomberMap.hpp"
#include "TrackerBomb.hpp"
#include "FragBomb.hpp"

const std::vector<std::string> ACharacter::textAction {"Move Left", "Move Right", "Move Up", "Move Down", "Drop Bomb", "Perform Action"};

struct SMD3AnimationType
{
    irr::s32 begin;
    irr::s32 end;
    irr::s32 fps;
};

static const SMD3AnimationType MD3AnimationTypeList[3] =
        {
                {  0,  96,  25}, // IDLE
                { 97,  216, 20}, // RUN
                { 217,  247,  25}, // ATTACK
        };

ACharacter::ACharacter(std::string const &name, irr::core::vector2df const &pos,
                       std::string const &mesh, std::string const &texture, int player,
                       int score, bool invincible)
        : AGameObject(pos, mesh, texture, AGameObject::CHARACTER),
          _name(name), _player(player), _score(score), _invincible(invincible)
{
    onRun = false;
    t = NULL;
    life = 1;
    bombPass = false;
    _dead = false;
    this->item = NULL;
    _arrived = true;
    _last_act = irr::core::vector2df(0, 0);
    anime = irr::scene::EMAT_STAND;
    moveSpeed = BASICSPEED;
    then = IrrlichtController::getDevice()->getTimer()->getTime();
    _bombContainer = BombFactory::CreateBombContainer<FireBomb>((*this)->getID());
    setMD3Animation(MD3_ANIMATION::STAY);
}

void ACharacter::reset()
{
    t = NULL;
    life = 1;
    bombPass = false;
    _dead = false;
    if (this->item)
        delete(item);
    this->item = NULL;
    _arrived = true;
    _last_act = irr::core::vector2df(0, 0);
    anime = irr::scene::EMAT_STAND;
    moveSpeed = BASICSPEED;
    then = IrrlichtController::getDevice()->getTimer()->getTime();
    (*this)->setScale(irr::core::vector3df(1, 1, 1));
    if (_bombContainer)
        delete _bombContainer;
    _bombContainer = BombFactory::CreateBombContainer<FireBomb>((*this)->getID());
}

ACharacter::~ACharacter()
{
    if (t)
    {
        mutex.lock();
        onRun = false;
        mutex.unlock();
        t->join();
        delete (t);
    }
    delete(_bombContainer);
}

void			ACharacter::onInvinciblePeriode(double time)
{
    double		i = 0;

    mutex.lock();
    _invincible = true;
    mutex.unlock();
    while (i < time)
    {
        if (mutex.try_lock())
        {
            if (!onRun)
            {
                mutex.unlock();
                break;
            }
            mutex.unlock();
        }
        usleep(100);
        i = i + 100;
    }
    mutex.lock();
    _invincible = false;
    mutex.unlock();
}

void			ACharacter::invincibleEnabledDuringPeriod(double time)
{
    mutex.lock();
    if (_invincible)
    {
        mutex.unlock();
        return ;
    }
    mutex.unlock();
    if (t)
    {
        mutex.lock();
        onRun = false;
        mutex.unlock();
        t->join();
        delete (t);
    }
    addAnimation();
    mutex.lock();
    onRun = true;
    mutex.unlock();
    t = new std::thread([time, this] { this->onInvinciblePeriode(time);
    });
}

void                    ACharacter::dead()
{
    mutex.lock();
    if (_invincible)
    {
        mutex.unlock();
        return ;
    }
    mutex.unlock();

    --life;
    if (life == 1)
    {
        invincibleEnabledDuringPeriod(1000000);
        (*this)->setScale(irr::core::vector3df(1, 1, 1));
        setMoveSpeed(BASICSPEED);
    }
    if (life <= 0)
    {
        _dead = true;
        SoundManager::getManager()->play("dead.wav");
        setPos(irr::core::vector2df(-2000, -2000));
        GameManager::SharedInstance()->addDeadPlayer(this);
        this->removeAnnimation();
    }
}

BombContainer		*ACharacter::getBombContainer() const
{
    return (_bombContainer);
}

bool			ACharacter::isDestructible() const
{
    return (false);
}

void			ACharacter::setMoveSpeed(double speed)
{
    this->moveSpeed = speed;
}

void ACharacter::setMD3Animation(MD3_ANIMATION anim)
{
    (*this)->setFrameLoop(MD3AnimationTypeList[anim].begin, MD3AnimationTypeList[anim].end);
    (*this)->setAnimationSpeed(MD3AnimationTypeList[anim].fps);
}

void			ACharacter::setLifeUp()
{
    life = 2;
}

void			ACharacter::setBasicLife()
{
    life = 1;
}

std::string const &	ACharacter::getName() const
{
    return (_name);
}

double		ACharacter::getMoveSpeed() const
{
    return (moveSpeed);
}

void			ACharacter::setName(const std::string &string)
{
    _name = string;
    (*this)->setName(string.c_str());
}

void		        ACharacter::increasePowerBomb()
{
    _bombContainer->upgradePowerBombs();
}

void            ACharacter::action(ACTION act)
{
    bool			stand = true;
    const irr::u32 now = IrrlichtController::getDevice()->getTimer()->getTime();
    this->frameDeltaTime = (irr::f32)(now - this->then) / 1000.f;

    if (!_invincible && getAnimator())
        removeAnnimation();
    if (_arrived || act == BOMB)
    {
        switch (act) {
            case DOWN:
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, 0, 0));
                _last_act = irr::core::vector2df(0, -1);
                break;
            case UP:
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, 180, 0));
                _last_act = irr::core::vector2df(0, 1);
                break;
            case LEFT:
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, 90, 0));
                _last_act = irr::core::vector2df(-1, 0);
                break;
            case RIGHT:
                stand = false;
                _arrived = false;
                (*this)->setRotation(irr::core::vector3df(0, -90, 0));
                _last_act = irr::core::vector2df(1, 0);
                break;
            case BOMB:
                this->putBomb();
                break;
            case ACT:
                if (this->item)
                {
                    this->item->use(this->getMapPos(), _last_act);
                }
                break;
            default:
                _arrived = true;
                break;
        }
    }
    if (!_arrived)
    {
        stand = false;
        this->moveTo(_last_act);
    }
    if (stand && anime != irr::scene::EMAT_STAND)  {
        setMD3Animation(ACharacter::MD3_ANIMATION::STAY);
        anime = irr::scene::EMAT_STAND;
    } else if (!stand && anime != irr::scene::EMAT_RUN) {
        setMD3Animation(ACharacter::MD3_ANIMATION::RUN);
        anime = irr::scene::EMAT_RUN;
    }
    then = now;
}

bool		ACharacter::isDead() const
{
    return (_dead);
}

int		ACharacter::getScore() const
{
    return (_score);
}

void            ACharacter::moveTo(irr::core::vector2df const &dir)
{
    std::vector<AGameObject*>   objs = BomberMap::getMap()->getObjsFromVector2(this->getMapPos() + dir);
    AGameObject::Type           type;

    for (std::vector<AGameObject*>::iterator it = objs.begin(); it != objs.end(); ++it) {
        type = (*it)->getType();
        if (type == AGameObject::BONUS)
        {
            ABonus	*bonus;

            if (((bonus = dynamic_cast<ABonus *>(*it))) != NULL)
            {
                bonus->take(*this);
                _score += 5;
                delete bonus;
            }
        }
        else if (type == AGameObject::ITEM)
        {
            AItem	*item;

            if (((item = dynamic_cast<AItem *>(*it))) != NULL)
            {
                if (this->item)
                    delete (this->item);
                _score += 5;
                this->item = item;
                this->item->dead();
            }
        }
        else if (type == AGameObject::BOMB)
        {
            if (!bombPass)
            {
                _arrived = true;
                return;
            }
        }
        else if (type != AGameObject::CHARACTER
                 && type != AGameObject::BOOM
                 && type != AGameObject::NONE) {
            _arrived = true;
            return;
        }
    }
    float   distance = this->getRealPos().getDistanceFrom(this->getMapPos() + dir);

    if (distance < 0.2 || distance > 1) {
        _arrived = true;
        this->setPos(this->getMapPos() + dir);
        return;
    }
    (*this)->setPosition(irr::core::vector3df((*this)->getPosition().X + dir.X * frameDeltaTime * moveSpeed, 0, (*this)->getPosition().Z + dir.Y * frameDeltaTime * moveSpeed));
}

void			ACharacter::setBombPass(bool pass)
{
    bombPass = pass;
}

void			ACharacter::putBomb()
{
    ABomb			        *bomb;
    std::vector<ABomb *>    bombs = this->_bombContainer->getBombs();
    for (std::vector<ABomb *>::const_iterator it = bombs.begin(); it != bombs.end(); ++it) {
        if ((*it)->getMapPos() == this->getMapPos()) {
            return;
        }
    }
    if ((bomb = _bombContainer->getBomb()))
    {
        *bomb << this->getMapPos();
    }
}

int ACharacter::get_player() const {
    return _player;
}

bool ACharacter::isArrived(void) const
{
    return _arrived;
}
