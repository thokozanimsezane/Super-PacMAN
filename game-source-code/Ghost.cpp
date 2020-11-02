#include "Ghost.h"

Ghost::Ghost(sf::Vector2f position)
:Current_Status(ACTIVE),
_GhostPosition(position),
_effectStatus(NORMAL),
_ID(GHOST),
spawnPoint(position),
_gID(RED) // set default ghost type to red
{   }

Ghost::~Ghost() {}

Orientation Ghost::getOrientation() const
{
    //do nothing
}

sf::Vector2f Ghost::getPosition() const
{
    return _GhostPosition;
}
Entity_ID Ghost::getEntityID() const
{
    return _ID;
}
void Ghost::setGhostID(Ghost_ID gID)
{
    _gID = gID;
}

Ghost_ID Ghost::getGhostID() const
{
    return _gID;
}

void Ghost::setPosition(sf::Vector2f _position) //will be used to populate the maze in game logic
{
    _GhostPosition = _position;
}

STATUS Ghost::getStatus() const
{
    return Current_Status;
}

void Ghost::Delete()
{
    Current_Status = TRANSITION;
}

void  Ghost::Reset()
{
    Current_Status = ACTIVE;
}

void Ghost::reSpawn()
{
    setPosition(spawnPoint);
    //Current_Status = ACTIVE;
    _effectStatus = NORMAL;
}

EffectStatus Ghost::getEffectStatus() const
{
    return _effectStatus;
}

void Ghost::setEffectStatus(EffectStatus _EStatus)
{
    _effectStatus = _EStatus;
}

void Ghost::setDesiredDirection(Direction dir)
{
    _dir = dir;
}

Direction Ghost::getDesiredDirection() const
{
    return _dir;
}


//MOVE GHOSTS
void Ghost::moveUp(double delta)
{
    _GhostPosition.y -= _speed*delta;
    if (_GhostPosition.y <= 6.f)
    {
        setPosition(sf::Vector2f(_GhostPosition.x, gameHeight-6));
    }
}
void Ghost::moveDown(double delta)
{
    _GhostPosition.y += _speed*delta;
    if (_GhostPosition.y >= (gameHeight-6))
    {
        setPosition(sf::Vector2f(_GhostPosition.x, 6.f));
    }
}
void Ghost::moveLeft(double delta)
{
    _GhostPosition.x -= _speed*delta;
    if(_GhostPosition.x <= 6.f)
    {
        setPosition(sf::Vector2f(gameWidth-6,_GhostPosition.y));
    }
}
void Ghost::moveRight(double delta)
{
    _GhostPosition.x += _speed*delta;
    if (_GhostPosition.x >= gameWidth-6)
    {
        setPosition(sf::Vector2f(6.f,_GhostPosition.y));
    }
}
sf::Vector2u Ghost::gridPosition() const
{
    sf::Vector2u grid;
    int column = floor((_GhostPosition.x-6)/12+0.5);
    int row = floor((_GhostPosition.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}
