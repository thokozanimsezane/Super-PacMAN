#include "GameStateManager.h"

    int GameStateManager::GameInstance = 0;

GameStateManager::GameStateManager(): _gameState(GameState::MAIN_MENU), _gameStatus(Game_Status::LEVEL_INCOMPLETE)
{
    if (GameInstance == 1)
        throw "an instance is already running";
    GameInstance++;
    file.readAllHighScores();
    _fileHighScore = file.returnHighScore();
    _mapFilename = "original.txt"; //initialise as default map - in main resource folder in case other files are overwritten

}

GameStateManager::~GameStateManager(){}

void GameStateManager::createState(GameState _State)
{
    switch(_State)
    {
    case GameState::SPLASH:
        {
            std::shared_ptr<IGameScreen> Current(new SplashScreen);
            _screenStack.push(Current);
            break;
        }
    case GameState::MAIN_MENU:
        {
            std::shared_ptr<IGameScreen> Current(new MainMenu);
            _screenStack.push(Current);
            break;
        }
    case GameState::HIGHSCORES:
        {
            break; //uses cleared main menu screen to display
        }
    case GameState::MAP_CREATOR:
        {
            std::shared_ptr<IGameScreen> Current(new MapEditor(_mapFilename));
            _screenStack.push(Current);
            break;
        }
    case GameState::ACTIVE:
        {
            std::shared_ptr<IGameScreen> Current(new PlayScreen(_mapFilename));
            _screenStack.push(Current);
            _screenStack.top()->saveHighScore(_fileHighScore);
            break;
        }
    case GameState::GAME_OVER:
        {
            std::shared_ptr<IGameScreen> Current(new GameOverScreen);
            _screenStack.push(Current);
            _screenStack.top()->saveHighScore(_newHighScore); //create as member function

            break;
        }
    case GameState::GAME_WON:
        {
            std::shared_ptr<IGameScreen> Current(new GameWonScreen);
            _screenStack.push(Current);
            _screenStack.top()->saveHighScore(_newHighScore); //create as member function
            break;
        }
    }
    _screenStack.top()->LoadContent();
}

void GameStateManager::clearState()
{
    if(_screenStack.size()>1)
        _screenStack.pop();
}

void GameStateManager::updateState(GameState _State, sf::RenderWindow& _window)
{
    switch(_State)
    {
    case GameState::SPLASH:
        {
            _screenStack.top()->Update(_window,_event);
            _screenStack.top()->Draw(_window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
            {
                _gameState = GameState::ACTIVE;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                _window.close();
            }

            break;
        }
    case GameState::MAIN_MENU:
        {
            _screenStack.top()->Update(_window,_event);
            _screenStack.top()->Draw(_window);
            auto menuSelect = _screenStack.top()->menuSelection();
            if (button.stop()>0.1)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
            {
                if (menuSelect == Menu::Play)
                {
                    clearState();
                    _gameState = GameState::SPLASH; //start the splash screen
                }
                if (menuSelect == Menu::HighScores)
                {
                    _gameState = GameState::HIGHSCORES;
                }
                if (menuSelect == Menu::MapCreator)
                {
                    _gameState = GameState::MAP_CREATOR;
                }
                if (menuSelect == Menu::Quit)
                {
                    _window.close();
                }
                button.reset();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                _window.close();
            }

            break;
        }
    case GameState::HIGHSCORES:
        {
            _window.clear();
            displayHighScores(_window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::BackSpace))
            {
                _gameState = GameState::MAIN_MENU;
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                _window.close();
            }
            break;
        }
    case GameState::MAP_CREATOR: // Implement eventually
        {
            _screenStack.top()->Update(_window, _event);
            _screenStack.top()->Draw(_window);
            _gameStatus = _screenStack.top()->returnGameProgress();
            if (_gameStatus == Game_Status::LEVEL_COMPLETE)
            {
                _gameState = GameState::MAIN_MENU;
                _mapFilename = _screenStack.top()->returnMapName();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                _window.close();
            }
            break;
        }
    case GameState::ACTIVE:     //game currently active
        {
            _screenStack.top()->Update(_window, _event);
            _screenStack.top()->Draw(_window);
            _gameStatus = _screenStack.top()->returnGameProgress();

            //check if game state is complete, ie commence to next level or game over
            if (_gameStatus == Game_Status::GAME_OVER)
            {
                _gameState = GameState::GAME_OVER;
                _newHighScore = _screenStack.top()->returnHighScore();
            }
            if (_gameStatus == Game_Status::LEVEL_COMPLETE)
            {
                _gameState = GameState::ACTIVE; //make sure active
            }
            if (_gameStatus == Game_Status::GAME_WON)
            {
                _gameState = GameState::GAME_WON;
                _newHighScore = _screenStack.top()->returnHighScore();
            }
            break;
        }
        //can rather create a credits class which takes in a string
    case GameState::GAME_OVER:
        {
            _screenStack.top()->Update(_window,_event);
            _screenStack.top()->Draw(_window);

            if (button.stop() > 0.1)
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
            {
                _gameState = GameState::MAIN_MENU;
                auto check = _screenStack.top()->returnHighScore();
                if (file.findNewScore(check))
                    file.saveNewScore(check);
                if (check.score > _fileHighScore.score)
                {
                    _fileHighScore = check;
                }
                button.reset();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                _window.close();
            }
            break;
        }
    case GameState::GAME_WON:
        {
            _screenStack.top()->Update(_window,_event);
            _screenStack.top()->Draw(_window);
            if(button.stop()>0.1)
             if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return))
            {
                _gameState = GameState::MAIN_MENU;
                auto check = _screenStack.top()->returnHighScore();
                if (file.findNewScore(check))
                    file.saveNewScore(check);
                if (check.score > _fileHighScore.score)
                {
                    _fileHighScore = check;
                }
                button.reset();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
            {
                _window.close();
            }
            break;
        }
    }
}

GameState GameStateManager::returnState()
{
    return _gameState;
}

void GameStateManager::displayHighScores(sf::RenderWindow& _window)
{
    sf::Font font;
    font.loadFromFile("sansation.ttf");
    sf::Text Title("High Scores: ", font);
    Title.setCharacterSize(45);
    Title.setFillColor(sf::Color::White);
    Title.setPosition(gameWidth/3, 10);
    _window.draw(Title);

    auto allHighScores = file.returnAllHighScores();
    sf::Text tempText;
    std::vector<sf::Text> highScoreVect;
    for (int i = 0; i < static_cast<int>(allHighScores.size()); i++)
    {
        std::string text = std::to_string(i+1) + ". " + allHighScores[i].name + " - " + std::to_string(allHighScores[i].score);
        tempText.setString(text);
        tempText.setFont(font);
        tempText.setCharacterSize(25);
        tempText.setFillColor(sf::Color::Yellow);
        tempText.setPosition(gameWidth/3, 100+(i*60));
        highScoreVect.push_back(tempText);
        _window.draw(tempText);
    }

    sf::Text control("Press Backspace to return \n to main menu",font);
    control.setCharacterSize(25);
    control.setFillColor(sf::Color(128,128,128));
    control.setPosition(gameWidth-100,640);
    _window.draw(control);
}
