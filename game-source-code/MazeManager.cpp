#include "MazeManager.h"

MazeManager::MazeManager(const std::string filename, bool isGame, bool isOptions)
{
    FileManager file;
    file.readMapFile(filename);
    _tiles = file.returnMap();
    Initialize(isGame, isOptions);
}

MazeManager::~MazeManager(){}

//initialize the game objects as defined in the
void MazeManager::Initialize(bool isGame, bool isOptions)
{
    const int map_height = 60;
    int map_width;
    if (isOptions)
    {
        map_width = 3;
    }
    else if (!isOptions)
    {
        map_width = 55;
    }
std::vector<std::vector<std::shared_ptr<IMazeEntity>>> mazeGrid(map_height, std::vector<std::shared_ptr<IMazeEntity>>(map_width,0));
sf::Vector2f position;
sf::Vector2f startpos; //start position for comparison
float xendpos, yendpos;

for (unsigned int counterX = 0; counterX < map_width; ++counterX)
	{
		for (unsigned int counterY = 0; counterY < map_height; ++counterY)
		{
            if (isOptions)
            {
                startpos = sf::Vector2f((counterX+60) * mapTileSize.x, counterY * mapTileSize.y);
                xendpos = ((counterX+60) + 1) * mapTileSize.x;
            }
            else
            {
                startpos = sf::Vector2f(counterX * mapTileSize.x, counterY * mapTileSize.y);
                xendpos = (counterX + 1) * mapTileSize.x;
            }

            yendpos = (counterY + 1) * mapTileSize.y;

			position.x = (startpos.x + xendpos)/2;
			position.y = (startpos.y + yendpos)/2;

			switch(_tiles[counterX + counterY * map_width])
			{
			    case 0:
                    {
			            auto path = std::make_shared<Path>(position);
                        _path_objects.push_back(path);
                        mazeGrid[counterY][counterX] = path;
                        break;
			        }

			    case 1:
			        {
                        auto wall = std::make_shared<Wall>(position);
                        _wall_objects.push_back(wall);
                        mazeGrid[counterY][counterX] = wall;
			            break;
			        }

			    case 2:
                    {
                        auto door = std::make_shared<Doors>(position);
                        _door_objects.push_back(door);
                        mazeGrid[counterY][counterX] = door;
                        break;
                    }
			    case 3:
                    {
                        auto fruit = std::make_shared<Fruit>(position);
                        _fruit_objects.push_back(fruit);
                        mazeGrid[counterY][counterX] = fruit;
                        break;
                    }
			    case 4:
                    {
                        _pacman = std::make_shared<Pacman>(position);
                        // create a path object to render since this is only a 'spawn point'
                        auto path = std::make_shared<Path>(position);
                        _path_objects.push_back(path);
                        if(isGame)
                            mazeGrid[counterY][counterX] = path;
                        else
                            mazeGrid[counterY][counterX] = _pacman;
                        break;
                    }
			    case 5:
                    {
                        auto ghost = std::make_shared<Ghost>(position);
                        _Ghost_objects.push_back(ghost);
                        // create a path object to render since this is only a 'spawn point'
                        auto path = std::make_shared<Path>(position);
                        _path_objects.push_back(path);
                        if (isGame)
                            mazeGrid[counterY][counterX] = path;
                        else
                            mazeGrid[counterY][counterX] = ghost;
                        break;
                    }
			    case 6:
                    {
                        auto power = std::make_shared<PowerPellet>(position);
                        _power_objects.push_back(power);
                        mazeGrid[counterY][counterX] = power;
                        break;
                    }
			    case 7:
                    {
                        auto super = std::make_shared<SuperPellet>(position);
                        _super_objects.push_back(super);
                        mazeGrid[counterY][counterX] = super;
                        break;
                    }
			    case 8:
                    {
                        auto key = std::make_shared<Keys>(position);
                        _key_objects.push_back(key);
                        mazeGrid[counterY][counterX] = key;
                        break;
                    }
                case 9:
                    {
                        auto ghostDoor = std::make_shared<GhostDoor>(position);
                        mazeGrid[counterY][counterX] = ghostDoor;
                        auto path = std::make_shared<Path>(position);
                        _path_objects.push_back(path);
                    }
			}
		}
	}
	_mazeGrid = mazeGrid;
	packEverything();
	if (isGame)
        updateGrid();
}

void MazeManager::updateGrid()
{
    //copy into a new grid
    auto newGrid = _mazeGrid;

    for (int row = 0; row< 60; row++)
    {
        for (int col = 0; col<55; col++)
        {
            auto entity = _mazeGrid[row][col];
            auto ID = entity->getEntityID();
            switch (ID)
            {
            case Entity_ID::DOOR:
                break;
            case Entity_ID::PATH:
                break;
            case Entity_ID::WALL:
                break;
            case Entity_ID::GHOST:
                break;
            case Entity_ID::GHOST_DOOR:
                break;
            case Entity_ID::PACMAN:
                break;
            case Entity_ID::KEY:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::POWER_PELLET:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::SUPER_PELLET:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            case Entity_ID::FRUIT:
                {
                    newGrid[row-1][col] = entity;
                    newGrid[row+1][col] = entity;

                    newGrid[row][col-1] = entity;
                    newGrid[row][col+1] = entity;
                    break;
                }
            }
        }
    }
    _mazeGrid = newGrid;
}

std::vector<std::vector<std::shared_ptr<IMazeEntity>>> MazeManager::ReturnMazeGrid()
{
    return _mazeGrid;
}

std::shared_ptr<IMazeEntity> MazeManager::returnGridEntity(int row, int column)
{
    auto Entity = _mazeGrid[row][column];
    return Entity;
}
int MazeManager::returnFruitNumber()
{
    return static_cast<int>(_fruit_objects.size());
}

shared_ptr<Pacman>& MazeManager::returnPacman()
{
    return _pacman;
}

    //packages the boundary tiles
void MazeManager::packPaths()
{
    obstruction_objects_.clear();
    for (auto& wall : _wall_objects)
    {
        obstruction_objects_.push_back(wall);
    }
    for (auto& door : _door_objects)
    {
        obstruction_objects_.push_back(door);
    }
}

void MazeManager::packElements()
{
    Maze_objects_.clear();
    for (auto& fruit : _fruit_objects)
    {
        Maze_objects_.push_back(fruit);
    }
    for (auto& super : _super_objects)
    {
        Maze_objects_.push_back(super);
    }
    for (auto& power : _power_objects)
    {
        Maze_objects_.push_back(power);
    }
    //for (auto& door : _door_objects)  //packaged in packagePaths
    //{
    //    Maze_objects_.push_back(door);
    //}
    for (auto& key : _key_objects)
    {
        Maze_objects_.push_back(key);
    }
}

void MazeManager::PackDynamicElements()
{
    Dynamic_objects_.clear();
    //while packaging the ghosts - set their respective ghost ID's
    for (int i = 0; i < static_cast<int>(_Ghost_objects.size()); i++)
    {
        _Ghost_objects[i]->setGhostID(Ghost_ID(i));
        Dynamic_objects_.push_back(_Ghost_objects[i]);
    }
    Dynamic_objects_.push_back(_pacman);
}

vector<shared_ptr<IDynamicMazeEntity>>& MazeManager::packageDynamicElements()
{
    return Dynamic_objects_;
}

void MazeManager::packEverything() //package everything (IMazeEntity) but dynamic objects
{
    obstruction_objects_.clear();
    Maze_objects_.clear();
    Dynamic_objects_.clear();
    packPaths();
    packElements();
    PackDynamicElements();
    for (auto& pathing : obstruction_objects_) //solid obstruction
    {
        package_everything_.push_back(pathing);
    }
    for (auto& mazeObj : Maze_objects_)
    {
        package_everything_.push_back(mazeObj);
    }
}

vector<shared_ptr<IMazeEntity>>& MazeManager::packageEverything()
{
    return package_everything_; //everything but dynamic objects
}

vector<shared_ptr<IStaticMazeEntity>>& MazeManager::packageKeysDoors()
{
    _keyAndDoors.clear();
    for (auto& door : _door_objects)
    {
        _keyAndDoors.push_back(door);
    }
    for (auto& key : _key_objects)
    {
        _keyAndDoors.push_back(key);
    }
    return _keyAndDoors;
}
