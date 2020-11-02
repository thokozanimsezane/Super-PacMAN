#include "Keys.h"

Keys::Keys(sf::Vector2f position):Current_Status(ACTIVE), _KeyPosition(position),_ID(KEY)
{   }

Keys::~Keys(){}

sf::Vector2f Keys::getPosition() const //2D vector representing the position of the object
{
    return _KeyPosition;
}
Entity_ID Keys::getEntityID() const
{
    return _ID;
}

STATUS Keys::getStatus() const //returns the status of the object
{
    return Current_Status;
}
void Keys::Delete() //sets the object status to inactive
{
    Current_Status = INACTIVE;
   // _ID = PATH;
}

sf::Vector2u Keys::gridPosition() const
{
    sf::Vector2u grid;
    // since the position of static maze objects is always initialised as the center of a tile,
    // the addition of 0.5 and using the floor function isnt necessary because the result will
    // always be a whole integer. It is kept here for safety sake
    int column = floor((_KeyPosition.x-6)/12+0.5);
    int row = floor((_KeyPosition.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}
