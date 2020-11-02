#include "GhostMovementManager.h"
//void set reference position (so pacman doesnt have to be passed in for multiple ghosts - just passed in once
GhostMovementManager::GhostMovementManager(std::shared_ptr<MazeManager> maze):_maze(maze)
{  }

GhostMovementManager::~GhostMovementManager(){}


void GhostMovementManager::moveToValidPath(std::vector<std::shared_ptr<IDynamicMazeEntity>>& Entities)
{
    //create timer for each ghost
    // each ghost timer is a private member
    time = _delta.stop();
    for (auto& entity : Entities)
    {
        if (entity->getEntityID() == PACMAN)
        {
            pacReference = entity->getPosition();
        }
        else if (entity->getEntityID() == GHOST)
        {
            auto gID = entity->getGhostID();
            switch (gID)
            {
                case Ghost_ID::BLUE:
                    {
                        chooseMovement(entity, _blue);
                        break;
                    }
                case Ghost_ID::RED:
                    {
                        chooseMovement(entity,_red);
                        break;
                    }
                case Ghost_ID::PINK:
                    {
                        chooseMovement(entity,_pink);
                        break;
                    }
                case Ghost_ID::ORANGE:
                    {
                        chooseMovement(entity,_orange);
                        break;
                    }
            }
        }
    }
    _delta.reset();

}


//implement something to make sure the ghosts don't just go back into the spawn box
void GhostMovementManager::chooseMovement(std::shared_ptr<IDynamicMazeEntity> _ghost, StopWatch _watch)
{
    // map ghost pointer to a stopwatch.
    auto ghostPosition = _ghost->getPosition();
    if (checkSpawnPointBox(ghostPosition))
    {
        moveOut(_ghost, _watch);
    }
    else if (_watch.stop() <= 8 || _ghost->getEffectStatus() == EffectStatus::POWER)
    {
        moveDesignated(_ghost);
    }
    else
    {
        moveTowards(_ghost, pacReference);
    }
}


bool GhostMovementManager::checkSpawnPointBox(sf::Vector2f position)
{
    if (position.y > 174 && position.y < 294)
    {
        if (position.x>246 && position.x < 414)
        {
            return true;
        }
        else return false;
    }
    else
        return false;
}

void GhostMovementManager::moveOut(std::shared_ptr<IDynamicMazeEntity> _ghost, StopWatch _watch)
{
    auto position = _ghost->getPosition();
    // move ghost to center of spawn box
    if (position.x < 318)
    {
        _ghost->moveRight(time);
    }
    else if (position.x > 342)
    {
        _ghost->moveLeft(time);
    }
    // if ghost is in the center - then move up
    else if (position.x >= 318 && position.x <=342 )
    {
        _ghost->moveUp(time);
    }
    _watch.reset(); //start the ghost's respective timer
}

void GhostMovementManager::moveDesignated(std::shared_ptr<IDynamicMazeEntity> _ghost)
{
    auto gID = _ghost->getGhostID();
    switch (gID)
        {
            case Ghost_ID::BLUE:
                {
                    moveTowards(_ghost, sf::Vector2f(30,30));
                    break;
                }
            case Ghost_ID::RED:
                {
                    moveTowards(_ghost, sf::Vector2f(630,30));
                    break;
                }
            case Ghost_ID::PINK:
                {
                    moveTowards(_ghost, sf::Vector2f(690,30));
                    break;
                }
            case Ghost_ID::ORANGE:
                {
                    moveTowards(_ghost, sf::Vector2f(690,630));
                    break;
                }
        }
}


void GhostMovementManager::moveTowards(std::shared_ptr<IDynamicMazeEntity> _ghost, sf::Vector2f pacPosition)
{
    auto ghostPosition = _ghost->getPosition();
    Direction Dir = Direction::NONE; //assign default as no direction

    if ((pacPosition.y-6) > ghostPosition.y)
    {
        if ((pacPosition.x-6) > ghostPosition.x)
        {
            // pacman/desired position is in the bottom right corner relative to the current ghost
            Dir = checkoptions(Direction::DOWN, Direction::RIGHT, _ghost);
            if (Dir == Direction::NONE)
            {
                auto newDir = checkoptions(Direction::LEFT, Direction::UP, _ghost);
                Dir = newDir;
            }
        }
        else if ((pacPosition.x+6) < ghostPosition.x)
        {
            // pacman/desired position is in the bottom left corner relative to the current ghost
            Dir = checkoptions(Direction::DOWN, Direction::LEFT, _ghost);
            if (Dir == Direction::NONE)
            {
                auto newDir = checkoptions(Direction::RIGHT, Direction::UP, _ghost);
                Dir = newDir;
            }
        }
        else if ((pacPosition.x-6) < ghostPosition.x  &&  (pacPosition.x+6) > ghostPosition.x)
        {
            if(checkFuturePath(Direction::DOWN, _ghost))
            {
                Dir = Direction::DOWN;
            }
            else
            {
                Dir = checkoptions(Direction::LEFT, Direction::RIGHT, _ghost);
                if (Dir == Direction::NONE)
                {
                    if(checkFuturePath(Direction::UP, _ghost))
                    {
                        Dir = Direction::UP;
                    }
                }
            }
        }
    }
    else if ((pacPosition.y+6) < ghostPosition.y)
    {
        if ((pacPosition.x-6) > ghostPosition.x)
        {
            // pacman/desired position is in the top right corner relative to the current ghost
            Dir = checkoptions(Direction::UP, Direction::RIGHT, _ghost);
            if (Dir == Direction::NONE)
            {
                auto newDir = checkoptions(Direction::LEFT, Direction::DOWN, _ghost);
                Dir = newDir;
            }
        }
         else if ((pacPosition.x+6) < ghostPosition.x)
         {
             // pacman/desired position is in the top left corner relative to the current ghost
            Dir = checkoptions(Direction::UP, Direction::LEFT, _ghost);
            if (Dir == Direction::NONE)
            {
                auto newDir = checkoptions(Direction::RIGHT, Direction::DOWN, _ghost);
                Dir = newDir;
            }
         }
         else if ((pacPosition.x-6) < ghostPosition.x  &&  (pacPosition.x+6) > ghostPosition.x)
         {
             if(checkFuturePath(Direction::UP, _ghost))
            {
                Dir = Direction::UP;
            }
            else
            {
                Dir = checkoptions(Direction::LEFT, Direction::RIGHT, _ghost);
                if (Dir == Direction::NONE)
                {
                    if(checkFuturePath(Direction::DOWN, _ghost))
                    {
                        Dir = Direction::DOWN;
                    }
                }
            }
         }
    }
    else if ((pacPosition.y-6) < ghostPosition.y  &&  (pacPosition.y+6) > ghostPosition.y)
    {
        if ((pacPosition.x+6) < ghostPosition.x)
        {
            if(checkFuturePath(Direction::LEFT, _ghost))
            {
                Dir = Direction::LEFT;
            }
            else
            {
                Dir = checkoptions(Direction::UP, Direction::DOWN, _ghost);
                if (Dir == Direction::NONE)
                {
                    if(checkFuturePath(Direction::RIGHT, _ghost))
                    {
                        Dir = Direction::RIGHT;
                    }
                }
            }
        }
        else if ((pacPosition.x-6) > ghostPosition.x)
        {
            if(checkFuturePath(Direction::RIGHT, _ghost))
            {
                Dir = Direction::RIGHT;
            }
            else
            {
                Dir = checkoptions(Direction::UP, Direction::DOWN, _ghost);
                if (Dir == Direction::NONE)
                {
                    if(checkFuturePath(Direction::LEFT, _ghost))
                    {
                        Dir = Direction::LEFT;
                    }
                }
            }
        }
    }

    switch (Dir)
    {
    case Direction::UP:
        {
            _ghost->moveUp(time);
            break;
        }
    case Direction::DOWN:
        {
            _ghost->moveDown(time);
            break;
        }
    case Direction::LEFT:
        {
            _ghost->moveLeft(time);
            break;
        }
    case Direction::RIGHT:
        {
            _ghost->moveRight(time);
            break;
        }
    case Direction::NONE:
        break;
    }
}

Direction GhostMovementManager::checkoptions(Direction dir1, Direction dir2, std::shared_ptr<IDynamicMazeEntity> _ghost)
{
    int check1 = 0;
    int check2 = 0;
    if(checkFuturePath(dir1, _ghost))
    {
        check1 = _change;
    }
    if(checkFuturePath(dir2, _ghost))
    {
        check2 = _change; // member _change updated in checkFuturePath
    }
    if (check1 == 0 && check2 == 0)
    {
        return Direction::NONE; //if neither direction is viable
    }

    if (check1>check2)
        return dir1;
    else if (check1<check2)
        return dir2;
    else return dir1; //if both path lengths are the same - choose the first
}


bool GhostMovementManager::checkFuturePath(Direction dir, std::shared_ptr<IDynamicMazeEntity> _ghost)
{
    _change = 1;
    auto ghostGrid = _ghost->gridPosition();//retrieve entity grid pos
    sf::Vector2u newGridPos = ghostGrid;

// wanted to check longer paths to choose best route, currently meant that ghost couldn't reach ends of the maze
while (_change < 2)
{
    if(checkAhead(dir, _ghost, _change))
    {   _change++;      }
    else
    {
        _change--; //revert to last valid position
         break;
    }
}
//if (_change < 2)
  //  {return false;}
    switch (dir) //define new grid position
        {
        case Direction::UP:
            {
                newGridPos.x -= _change;
                break;
            }
        case Direction::DOWN:
            {
                newGridPos.x += _change;
                break;
            }
        case Direction::LEFT:
            {
                newGridPos.y -= _change;
                break;
            }
        case Direction::RIGHT:
            {
                newGridPos.y += _change;
                break;
            }
        case Direction::NONE:
            break;
        }
    if (dir == Direction::UP || dir == Direction::DOWN)
    {//look left and right of
        bool check1 = ObjectValid(newGridPos, sf::Vector2i(0,-1)) && ObjectValid(newGridPos, sf::Vector2i(0,0)) ;
        bool check2 = ObjectValid(newGridPos, sf::Vector2i(0,1)) && ObjectValid(newGridPos, sf::Vector2i(0,0));
        if (check1 && check2)
            return true;
        else
            return false;
    }
    else if (dir == Direction::LEFT || dir == Direction::RIGHT)
    {
        bool check1 = ObjectValid(newGridPos, sf::Vector2i(-1,0)) && ObjectValid(newGridPos, sf::Vector2i(0,0)) ;
        bool check2 = ObjectValid(newGridPos, sf::Vector2i(1,0)) && ObjectValid(newGridPos, sf::Vector2i(0,0));
        if (check1 && check2)
            return true;
            else
            return false;
    }
    else
        return false;
}

bool GhostMovementManager::checkAhead(Direction dir, std::shared_ptr<IDynamicMazeEntity> entity, int changenum)
{
    sf::Vector2u EntityGridPos = entity->gridPosition();
    sf::Vector2i change(0,0);
        switch(dir)
        {
        case Direction::UP:
            {
                change.x  = -changenum; // looks two objects above
                if (ObjectValid(EntityGridPos, change))
                {   return true;    }
                else
                {   return false;   }
                break;
            }
        case Direction::DOWN:
            {
                change.x = changenum;
                if (ObjectValid(EntityGridPos, change))
                {   return true;    }
                else
                {   return false;   }
                break;
            }
        case Direction::LEFT:
            {
                change.y = -changenum;
                if (ObjectValid(EntityGridPos, change))
                {   return true;    }
                else
                {   return false;   }
                break;
            }
        case Direction::RIGHT:
            {
                change.y = changenum;
                if (ObjectValid(EntityGridPos, change))
                {   return true;    }
                else
                {   return false;   }
                break;
            }
        case Direction::NONE:
            {   break;      }
        }
            return false;
}

bool GhostMovementManager::ObjectValid(sf::Vector2u EntityGridPos, sf::Vector2i change)
{
    std::shared_ptr<IMazeEntity> Obstacle;
    Obstacle = _maze->returnGridEntity(EntityGridPos.x+change.x, EntityGridPos.y+change.y);

    Entity_ID ObID = Obstacle->getEntityID();
    STATUS ObStat = Obstacle->getStatus();
    if (ObStat == STATUS::ACTIVE)
                {
                    switch(ObID)
                    {
                    case Entity_ID::PATH:
                        {   return true;    break;      }
                    case Entity_ID::WALL:
                        {   return false;   break;      }
                    case Entity_ID::DOOR:
                        {   return false;   break;      }
                    case Entity_ID::FRUIT:
                        {   return true;    break;      }
                    case Entity_ID::GHOST:
                        {   return true;    break;      }
                    case Entity_ID::KEY:
                        {   return true;    break;      }
                    case Entity_ID::PACMAN:
                        {   return true;    break;      }
                    case Entity_ID::POWER_PELLET:
                        {   return true;    break;      }
                    case Entity_ID::SUPER_PELLET:
                        {   return true;    break;      }
                    case Entity_ID::GHOST_DOOR: //makes sure Ghosts dont go back into their spawn box
                        {   return false;   break;      }
                    }
                }
                else
                {       return true;        }
                return false; //just in case nothing is returned
}

