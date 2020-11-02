#include "Common.h"
#include "Pacman.h"

Pacman::Pacman(sf::Vector2f position)
: _PacPosition(position),
Current_Status(ACTIVE),
_effectStatus(NORMAL),
_ID(PACMAN),
_speed(40.f),
spawnPoint(position),
_orientation(FACING_RIGHT)
{  }

Pacman::~Pacman() {}

sf::Vector2f Pacman::getPosition() const //2D vector representing the position of the object
{
    return _PacPosition;
}

Entity_ID Pacman::getEntityID() const
{
    return _ID;
}

STATUS Pacman::getStatus() const //returns the status of the object
{
    return Current_Status;
}
void Pacman::setPosition(sf::Vector2f _position)
{
   // if (_position.x ..) boundaries - but this could be confused since we use walls and paths
    //    throw "Invalid Pacman position";
    _PacPosition = _position;
}

void Pacman::Delete() //sets the object status to inactive
{
    //set status to transition - set position back to original position
    setStatus(TRANSITION);

    //setStatus to transition - pacman flashes at iorigin - invulnerable at this point
}

void Pacman::Reset()
{
    setStatus(ACTIVE);
}

void Pacman::reSpawn()
{
    setPosition(spawnPoint);
    //setStatus(ACTIVE);
}

void Pacman::setStatus(STATUS _status)
{
    Current_Status = _status;
}

// Boundaries of tiles will be considered before calling the move functions.
void Pacman::moveUp(double delta)
{
    _PacPosition.y -= _speed*delta;
    if (_PacPosition.y <= 6.f)
    {
        setPosition(sf::Vector2f(_PacPosition.x, gameHeight-6));
    }
    _orientation = FACING_UP;

}
void Pacman::moveDown(double delta)
{
    _PacPosition.y += _speed*delta;

    if (_PacPosition.y >= (gameHeight-6))
    {
        setPosition(sf::Vector2f(_PacPosition.x,6.f));
    }
    _orientation = FACING_DOWN;

}
void Pacman::moveLeft(double delta)
{
    _PacPosition.x -= _speed*delta;
    if(_PacPosition.x <= 6.f)
    {
        setPosition(sf::Vector2f((gameWidth-6),_PacPosition.y));
    }
    _orientation = FACING_LEFT;
}
void Pacman::moveRight(double delta)
{
    _PacPosition.x += _speed*delta;
    if(_PacPosition.x >= (gameWidth-6))
    {
        setPosition(sf::Vector2f(6.f,_PacPosition.y));
    }
    _orientation = FACING_RIGHT;
}

Orientation Pacman::getOrientation() const
{
    return _orientation;
}

EffectStatus Pacman::getEffectStatus() const
{
    return _effectStatus;
}

void Pacman::setEffectStatus(EffectStatus _effect)
{
    _effectStatus = _effect;
    // this means that if a power pellet is eaten soon after a super pellet
    // the speed will continue - until the timer runs out.
    if (_effect == EffectStatus::SUPER)
    {
        setSpeed(60.f);
    }
    else if (_effect == EffectStatus::NORMAL)
    {
        setSpeed(40.f);
    }
}

void Pacman::setSpeed(float Speed) //only changed by effect manager
{
    _speed = Speed;
}

//set upon user input
// this is then used in a path handler to determine whether the direction is valid or not
void Pacman::setDesiredDirection(Direction dir)
{
    _DesiredDir = dir;
}

Direction Pacman::getDesiredDirection() const
{
    return _DesiredDir;
}

sf::Vector2u Pacman::gridPosition() const
{
    sf::Vector2u grid;
    int column = floor((_PacPosition.x-6)/12+0.5);
    int row = floor((_PacPosition.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}

Ghost_ID Pacman::getGhostID() const
{
    return Ghost_ID::RED; //if something happens, it at least returns something, should never return anything though
}
