#include "GameLogic.h"

GameLogic::GameLogic(int Lives, std::string filename)
{
    maze.reset(new MazeManager(filename, true,false));
    InitializeLogic(Lives);
}

GameLogic::~GameLogic(){}

void GameLogic::InitializeLogic(int Lives)
{
    CollisionManager collision(maze, Lives);
    _collisions = collision;
    _moveGhosts.reset(new GhostMovementManager(maze));
    _pathHandle.reset(new PathHandler(maze));
    _dynamic =  maze->packageDynamicElements();
    _pacman = maze->returnPacman();
    auto keyDoors = maze->packageKeysDoors();
    UnlockDoorManager doorManage(keyDoors);
    _doorManage = doorManage;
}


void GameLogic::InterpretInput(UserInput _input)
{
    switch(_input)
    {
    case UserInput::left:
        {
            _pacman->setDesiredDirection(Direction::LEFT);
            break;
        }
    case UserInput::right:
        {
            _pacman->setDesiredDirection(Direction::RIGHT);
            break;
        }
    case UserInput::up:
        {
            _pacman->setDesiredDirection(Direction::UP);
            break;
        }
    case UserInput::down:
        {
            _pacman->setDesiredDirection(Direction::DOWN);
            break;
        }
    case UserInput::space:
        {
            //! note to change!!!
            if (_pacman->getEffectStatus() == EffectStatus::SUPER)
                _pacman->setSpeed(24.f); //random speed
            //Must ONLY work while the button is held down
            //need something to reset the speed back to normal
            // maybe get effectstatus to process the input
            break;
        }
    }
}

//check state - all lives gone or not
Game_Status GameLogic::returnGameProgress()
{
    return _collisions.returnGameProgress();
}


void GameLogic::runMaze()
{
    _pathHandle->managePath(_pacman);//pointer to only pacamn
    _moveGhosts -> moveToValidPath(_dynamic);
    _collisions.ManageCollisions();

    _doorManage.updateDoors();
}

//return lives and score from collisions manager
int GameLogic::returnScore()
{
    return _collisions.returnScore();
}
int GameLogic::returnLives()
{
    return _collisions.returnLives();
}

std::vector<std::shared_ptr<IMazeEntity>>& GameLogic::packageEntities()
{
    return maze->packageEverything();
}

std::vector<std::shared_ptr<IDynamicMazeEntity>>& GameLogic::packageDynamic()
{
    return maze->packageDynamicElements();
}
