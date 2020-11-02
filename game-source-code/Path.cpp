#include "Path.h"

Path::Path(sf::Vector2f position): _ID(PATH), _PathPosition(position), Current_Status(ACTIVE)
{   }

Path::~Path(){}

sf::Vector2f Path::getPosition() const
{
    return _PathPosition;
}
Entity_ID Path::getEntityID() const
{
    return _ID;
}
STATUS Path::getStatus() const//returns the status of the object
{
    return Current_Status;
}


void Path::Delete()
{
    //do nothing
}
