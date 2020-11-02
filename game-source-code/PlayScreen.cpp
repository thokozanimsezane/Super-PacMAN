#include "PlayScreen.h"
//Logic Presenter initialised with starting number of lives
PlayScreen::PlayScreen(const std::string mapFilename) : _logicP(3,mapFilename), PreviousScore(0), _level(1)
{
    _input.reset(new InputManager); // takes ownership of pointer
    _input->setInputType(LIVE);
    _mapFileName = mapFilename;
}

PlayScreen::~PlayScreen(){}

void PlayScreen::RemoveContent()
{
    //clear screen
}

void PlayScreen::LoadContent()
{
    _resource.setLevel(_level);
    mapEntityTex = _resource.returnMap();
}

void PlayScreen::manageInput(sf::RenderWindow& _window, sf::Event& _event)
{
    //! Manage user input
    _input->retrieveInput(_window, _event);
    // if else statements to make sure only ONE desired direction is set
    if(_input->Left())
    {
        //set desired direction - then need to call path handler
        _logicP.sendUserInput(UserInput::left);
    }
    else if(_input->Right())
    {
        _logicP.sendUserInput(UserInput::right);
    }
    else if(_input->Up())
    {
        _logicP.sendUserInput(UserInput::up);
    }
    else if(_input->Down())
    {
        _logicP.sendUserInput(UserInput::down);
    }
    /*if(_input->isSpeedUp()) // implemented if using a speed up button - currently pacman speeds up himself when super
    {
        //implemented in pacman itself
        //check effectsStatus
        //alter pacman's speed while the key is pressed
        // move to GAME LOGIC to change this!
        //_logicP.sendUserInput(UserInput::space);
    }*/
    if (_input->previous())
    {
        //close window
        _window.close();
    }
}

void PlayScreen::Update(sf::RenderWindow& _window, sf::Event& _event)
{
    /*
    1. Retrieve Game Entity
         1.a. Determine whether the entity is ACTIVE or INACTIVE (and therefore if it needs to be rendered)
    2. Retrieve the Entity's ID
    3. Load the corresponding Texture for the ID
    4. load texture onto a Sprite
    5. Retrieve the position and/or Grid Position of the Entity
    6. Set position of the sprite accordingly
    7. Allocate all ACTIVE sprites to a renderObjects vector
    */

    _logicP.PacMaze();
    // check status here
    if (_logicP.returnGameProgress() == Game_Status::LEVEL_COMPLETE)
    {
        changeLevel();
    }
    _renderObjects = _logicP.PackageEverything();
    _renderDynamicObjects = _logicP.PackageDynamic();

    manageInput(_window, _event);

    for (auto& objects : _renderObjects)
    {
        auto eID = objects->getEntityID();
        TextureID ID;
        if (objects->getStatus() == ACTIVE)
        {
            std::shared_ptr<sf::Sprite> tempSprite (new sf::Sprite);
            sf::Texture _tempTex;

			switch(eID)
        {
        case Entity_ID::PACMAN:
            {
                break;
            }
        case Entity_ID::GHOST:
            {
                break;
            }
        case Entity_ID::DOOR:
            {
                ID = TextureID::DoorTex;
                break;
            }
        case Entity_ID::FRUIT:
            {
                ID = TextureID::FruitTex;
                break;
            }
        case Entity_ID::GHOST_DOOR:
            {
                break;
            }
        case Entity_ID::PATH:
            {
                break;
            }
        case Entity_ID::KEY:
            {
                ID = TextureID::KeyTex;
                break;
            }
        case Entity_ID::POWER_PELLET:
            {
                ID = TextureID::PowerTex;
                break;
            }
        case Entity_ID::SUPER_PELLET:
            {
                ID = TextureID::SuperTex;
                break;
            }
        case Entity_ID::WALL:
            {
                ID = TextureID::WallTex;
                break;
            }
        }

            _tempTex = mapEntityTex[ID];
            tempSprite->setTexture(mapEntityTex[ID]);

            sf::Vector2u TextureDim = _tempTex.getSize();
            tempSprite->setOrigin(TextureDim.x/2,TextureDim.y/2);
            tempSprite->setPosition(objects->getPosition());
            _entitySprites.push_back(tempSprite);
        }
    }

    for (auto& entity : _renderDynamicObjects)
    {
        auto eID = entity->getEntityID();
        TextureID ID;
        if (entity->getStatus() == ACTIVE||entity->getStatus() == TRANSITION)
        {
        std::shared_ptr<sf::Sprite> tempSprite (new sf::Sprite);
        sf::Texture _tempTex;
		if (eID == Entity_ID::PACMAN)
		{
			auto EStatus = entity->getEffectStatus();
                if (EStatus == EffectStatus::NORMAL || EStatus == EffectStatus::POWER)
                {
                    ID = TextureID::PacmanTex;
                }
                else if (EStatus == EffectStatus::SUPER)
                {
                    ID = TextureID::SuperPacmanTex;
                }

				Orientation _orientation = entity->getOrientation();
                        switch(_orientation)
                        {
                        case FACING_DOWN:
                            {
                                tempSprite->setRotation(90);
                                break;
                            }
                        case FACING_LEFT:
                            {
                                tempSprite->setRotation(180);
                                break;
                            }
                        case FACING_RIGHT:
                            {
                                tempSprite->setRotation(0);
                                break;
                            }
                        case FACING_UP:
                            {
                                tempSprite->setRotation(270);
                                break;
                            }
                        }
		}
		else if (eID == Entity_ID::GHOST)
		{
            auto EStatus = entity->getEffectStatus();
			if(EStatus == EffectStatus::NORMAL)
            {
               auto gID  = entity->getGhostID();
                switch(gID)
                {
                case Ghost_ID::BLUE:
                    {
                        ID = TextureID::GhostBlueTex;
                        break;
                    }
                case Ghost_ID::RED:
                    {
                        ID = TextureID::GhostRedTex;
                        break;
                    }
                case Ghost_ID::PINK:
                    {
                        ID = TextureID::GhostPinkTex;
                        break;
                    }
                case Ghost_ID::ORANGE:
                    {
                        ID = TextureID::GhostOrangeTex;
                        break;
                    }
                }
            }
			else if(EStatus == POWER)
			{
			    ID = TextureID::DeadGhostTex;
			}
			else if(EStatus == SUPER)
			{
			    auto gID  = entity->getGhostID();
                switch(gID)
                {
                case Ghost_ID::BLUE:
                    {
                        ID = TextureID::FlatGhostBlueTex;
                        break;
                    }
                case Ghost_ID::RED:
                    {
                        ID = TextureID::FlatGhostRedTex;
                        break;
                    }
                case Ghost_ID::PINK:
                    {
                        ID = TextureID::FlatGhostPinkTex;
                        break;
                    }
                case Ghost_ID::ORANGE:
                    {
                        ID = TextureID::FlatGhostOrangeTex;
                        break;
                    }
                }
			}
		}

        if (entity->getStatus() == TRANSITION) // entity flashes once it has respawned
        {
            flashCount++;
            if(flashCount%2 == 0)
            {
                tempSprite->setColor(sf::Color::Transparent);
            }
        }
        _tempTex = mapEntityTex[ID];
        tempSprite->setTexture(mapEntityTex[ID]);

		sf::Vector2u TextureDim = _tempTex.getSize();
        tempSprite->setOrigin(TextureDim.x/2,TextureDim.y/2);
        tempSprite->setPosition(entity->getPosition());
        _entitySprites.push_back(tempSprite);
        }
    }
    _window.clear();
}
//call level up screen - refer to collisions class for what to do further

void PlayScreen::Draw(sf::RenderWindow& _window)
{
    for(auto entity: _entitySprites)
        _window.draw(*entity);

    sf::Font font;
    font.loadFromFile("sansation.ttf");
    int score = _logicP.returnScore();
    int totalScore = score + PreviousScore;
    // add previous saved score (ie from previous level)
    //create score entity
    std::string scoreText = "Score: " + std::to_string(totalScore);
    sf::Text sfScore(scoreText, font);
    sfScore.setCharacterSize(24);
    sfScore.setPosition(gameWidth+20,100);
    sfScore.setFillColor(sf::Color::Yellow);
    _window.draw(sfScore);

    if (totalScore > _highscore)
    {
        _highscore = totalScore;
        // only write at the end of the game
        //file.writeHighScore(totalScore, "Highscore.txt");
    }

    std::string highScoreText = "HighScore: " + std::to_string(_highscore);
    sf::Text sfHighScore(highScoreText, font);
    sfHighScore.setCharacterSize(24);
    sfHighScore.setPosition(gameWidth+20,50);
    sfHighScore.setFillColor(sf::Color::Yellow);
    _window.draw(sfHighScore);

    int lives = _logicP.returnLives();
    std::string livesText = "Lives: " + std::to_string(lives);
    sf::Text sfLives(livesText, font);
    sfLives.setCharacterSize(24);
    sfLives.setPosition(gameWidth+20,150);
    sfLives.setFillColor(sf::Color::Yellow);
    _window.draw(sfLives);

    _entitySprites.clear();
}

Game_Status PlayScreen::returnGameProgress()
{
    if (_level > 5)
    {
        return Game_Status::GAME_WON;
    }
    else
    return _logicP.returnGameProgress();
}

void PlayScreen::changeLevel()
{
    //set resourceManager Level
    _level += 1;
    _resource.setLevel(_level);
    mapEntityTex = _resource.returnMap();

    PreviousScore += _logicP.returnScore(); //update previousScoren
    CurrentLives = _logicP.returnLives(); //rather change the initialisation to include the number of lives...
    // so initilialise logicP with LivesNumber, which then initialises GameLogic with LivesNumber,
    // which in turn initialises collisions manager
    LogicPresenter logic(CurrentLives,_mapFileName);
    _logicP = logic;
}


HighScore PlayScreen::returnHighScore()
{
    HighScore high;
    int score = _logicP.returnScore();
    int totalScore = score + PreviousScore;
    high.score = totalScore;
    high.name = "no-name";
    return high;
}

//used to save the highscore that is displayed
void PlayScreen::saveHighScore(HighScore _newHighScore)
{
    _highscore = _newHighScore.score;
}
