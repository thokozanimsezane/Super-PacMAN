#include "CollisionManager.h"

CollisionManager::CollisionManager(std::shared_ptr<MazeManager> maze, int Lives) : _maze(maze), _score(0), _lives(Lives), _FruitEaten(0), _gameStatus(LEVEL_INCOMPLETE)
{

}

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager(){}

//game state
// while gameState != levelUP etc
// play/draw
// if == to levelUP, then reload/update the playscreen with new content ..
// playscreen determines the content.
// playscreen.. save current score and lives.. unload content. then reload new content/sprites for new level

Game_Status CollisionManager::returnGameProgress()
{
    return _gameStatus;
}

void CollisionManager::checkStatus()
{
    if (_FruitEaten == _maze->returnFruitNumber())
    {
        _gameStatus = LEVEL_COMPLETE;
    }
    if (_lives == 0)
    {
        _gameStatus = GAME_OVER;
    }
}

int CollisionManager::returnScore()
{
    return _score;
}

int CollisionManager::returnLives()
{
    return _lives;
}

void CollisionManager::ManageCollisions()
{
    auto movingObjects = _maze->packageDynamicElements();
    checkCollisions(movingObjects);
    _effects.manageEffects(movingObjects); //called after in case pacman rode over a door in the past frame - limits possibility of pacman getting stuck
    checkStatus();
    ManageTransitions(movingObjects);
}

void CollisionManager::checkCollisions(std::vector<std::shared_ptr<IDynamicMazeEntity>> movingObjects)
{
    //Check collisions between dynamic entities
     sf::Vector2u Entity1GridPos, Entity2GridPos;
    std::shared_ptr<IMazeEntity> element;
    for (auto& entity1 : movingObjects)
    {
        if (entity1->getEntityID() == PACMAN) // process static object collisions first
        {
            Entity1GridPos = entity1->gridPosition();
            element = _maze->returnGridEntity(Entity1GridPos.x, Entity1GridPos.y);
            PacmanVsElements(entity1, element);

            for (auto& entity2 : movingObjects)
            {
                if (entity2->getEntityID() != PACMAN)
                {
                    Entity2GridPos = entity2->gridPosition();
                    //above and below ghost center
                    sf::Vector2u ghostUp(Entity2GridPos.x-1,Entity2GridPos.y);
                    sf::Vector2u ghostBelow(Entity2GridPos.x+1,Entity2GridPos.y);
                    // left and right of ghost center
                    sf::Vector2u ghostLeft(Entity2GridPos.x,Entity2GridPos.y-1);
                    sf::Vector2u ghostRight(Entity2GridPos.x,Entity2GridPos.y+1);
                    if (Entity2GridPos == Entity1GridPos || ghostUp == Entity1GridPos || ghostBelow == Entity1GridPos || ghostLeft == Entity1GridPos || ghostRight == Entity1GridPos)
                    {
                        PacmanVsGhosts(entity1, entity2);
                    }
                }

            }
        }
    }
}

void CollisionManager::PacmanVsGhosts(std::shared_ptr<IDynamicMazeEntity> entity1, std::shared_ptr<IDynamicMazeEntity> entity2)
{
    // check current status, if ghost (or pacman? ) status is transition - nothing happens
    STATUS E1Status = entity1->getStatus();
    STATUS E2Status = entity2->getStatus();
    if (entity1->getEntityID() == entity2->getEntityID())
    {
        //shouldn't get to this point
        throw "cant call collisions between entities that are the same";
    }

    if (E1Status == ACTIVE && E2Status == ACTIVE) // makes sure that collisions cant occur with entities that are in transition
    {
        EffectStatus EmanageStatus = _effects.viewStatus();
        switch(EmanageStatus)
        {
        case EffectStatus::NORMAL:
            {
                if (entity1->getEntityID() == PACMAN)
                {
                    deleteEntity(entity1);
                    //entity1->Delete();
                    if (_lives > 0)
                    {
                        entity1->reSpawn();
                        _lives -= 1;
                    }
                }
                if (entity2->getEntityID() == PACMAN)
                {
                    deleteEntity(entity2);
                    //entity2->Delete();
                    if (_lives > 0)
                    {
                        entity2->reSpawn();
                        _lives -= 1;
                    }
                }
                break;
            }
        case EffectStatus::POWER:
            {
                if (entity1->getEntityID() == GHOST)
                {
                    deleteEntity(entity1);
                    entity1->reSpawn(); //respawn movement to be-Managed by movement manager
                    _score += 25*_scoreMultiplier;

                }
                if (entity2->getEntityID() == GHOST)
                {
                    deleteEntity(entity2);
                    entity2->reSpawn(); //-Managed by movement manager
                    _score += 25*_scoreMultiplier;
                }
                break;
            }
        case EffectStatus::SUPER:
            {
                //nothing happens, pacman moves over them
                break;
            }
        }
    }
    //already determined that there HAS been a collision - both entities occupy the same gridblock
//check status and effectStatus
}

void CollisionManager::PacmanVsElements(std::shared_ptr<IDynamicMazeEntity> entity1, std::shared_ptr<IMazeEntity> element)
{
    //entity1 should always be Pacman - throw an error here if not pacman
    if (entity1->getEntityID() != Entity_ID::PACMAN)
    {
        throw ("should not consider the intersection with maze elements of entities that aren't pacman");
    }
    Entity_ID elementID = element->getEntityID();
    if (element->getStatus() == STATUS::ACTIVE)
    {
        switch (elementID)
        {
        case Entity_ID::FRUIT:
            {
                element->Delete();
                _score += 5*_scoreMultiplier; //score multiplier changeable for higher levels
                //
                _FruitEaten++;
                break;
            }
        case Entity_ID::KEY:
            {
                element->Delete();
                break;
            }
        case Entity_ID::DOOR: // limited by pathing function
            {
                //check status
                if (entity1->getEffectStatus() == SUPER )
                {
                    element->Delete();
                }
                else
                throw "Pacman should NEVER intersect with an Active door object";
                break;
            }
        case Entity_ID::POWER_PELLET:
            {
                element->Delete();
                _score += 15*_scoreMultiplier; //score multiplier changeable for higher levels
                //!call effectsManager
                _effects.setEffect(EffectStatus::POWER);
                break;
            }
        case Entity_ID::SUPER_PELLET:
            {
                element->Delete();
                _score += 20*_scoreMultiplier; //score multiplier changeable for higher levels
                //!call effectsManager
                _effects.setEffect(EffectStatus::SUPER);
                break;
            }
            //The following cases should not be possible
        case Entity_ID::GHOST:
            break;
        case Entity_ID::PACMAN:
            break;
        case Entity_ID::PATH:
            break;
        case Entity_ID::GHOST_DOOR:
            break;
        case Entity_ID::WALL:
            throw "Pacman should NEVER intersect with a wall object";
            break;

        }
    }
}


// set entity status to transition and reset their respective timer
void CollisionManager::deleteEntity(std::shared_ptr<IDynamicMazeEntity> entity)
{
    if(entity->getEntityID() == PACMAN)
    {
        _pacWatch.reset();
        entity->Delete();
    }
    if (entity->getEntityID() == GHOST)
    {
        auto ID = entity->getGhostID();
        switch(ID)
        {
        case RED:
            {
                _red.reset();
                break;
            }
        case BLUE:
            {
                _blue.reset();
                break;
            }
        case PINK:
            {
                _pink.reset();
                break;
            }
        case ORANGE:
            {
                _orange.reset();
                break;
            }
        }
        entity->Delete();
    }
}

void CollisionManager::ManageTransitions(std::vector<std::shared_ptr<IDynamicMazeEntity>> movingObjects)
{
    for (auto& entity : movingObjects)
    {
        if (entity->getEntityID()== PACMAN)
        {
            if (entity->getStatus() == TRANSITION && _lives!= 0)
            {
                if (_pacWatch.stop() > 4)
                {
                    entity->Reset();
                }
            }
        }

        else if (entity->getEntityID()== GHOST)
        {
            if (entity->getStatus() == TRANSITION)
            {
                auto ID = entity->getGhostID();
                switch(ID)
                {
                case RED:
                    {
                        if (_red.stop() > 4)
                        {
                            entity->Reset();
                        }
                        break;
                    }
                case BLUE:
                    {
                        if (_blue.stop() > 4)
                        {
                            entity->Reset();
                        }
                        break;
                    }
                case PINK:
                    {
                        if (_pink.stop() > 4)
                        {
                            entity->Reset();
                        }
                        break;
                    }
                case ORANGE:
                    {
                        if (_orange.stop() > 4)
                        {
                            entity->Reset();
                        }
                        break;
                    }
                }
            }
        }
    }
}
