#include "Fruit.h"

Fruit::Fruit(sf::Vector2f position):Current_Status(ACTIVE), _FruitPosition(position),_ID(FRUIT)
{   }

Fruit::~Fruit(){}

sf::Vector2f Fruit::getPosition() const //2D vector representing the position of the object
{
    return _FruitPosition;
}

Entity_ID Fruit::getEntityID() const
{
    return _ID;
}

STATUS Fruit::getStatus() const //returns the status of the object
{
    return Current_Status;
}
void Fruit::Delete() //sets the object status to inactive
{
    Current_Status = INACTIVE;
    //_ID = PATH; //double check
}

sf::Vector2u Fruit::gridPosition() const
{
    sf::Vector2u grid;
    // since the position of static maze objects is always initialised as the center of a tile,
    // the addition of 0.5 and using the floor function isnt necessary because the result will
    // always be a whole integer. It is kept here for safety sake
    int column = floor((_FruitPosition.x-6)/12+0.5);
    int row = floor((_FruitPosition.y-6)/12+0.5);
    grid.x = row;
    grid.y = column;
    return grid;
}
