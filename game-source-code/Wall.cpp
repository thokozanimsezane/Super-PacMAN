#include "Wall.h"

Wall::Wall(sf::Vector2f position):_ID(WALL), _wallPosition(position),Current_Status(ACTIVE)
{   }

Wall::~Wall(){}

sf::Vector2f Wall::getPosition() const
{
    return _wallPosition;
}
Entity_ID Wall::getEntityID() const
{
    return _ID;
}

STATUS Wall::getStatus() const //returns the status of the object
{
    return Current_Status;
}

void Wall::Delete()
{
    //do nothing
}
