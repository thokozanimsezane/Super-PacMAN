#include "GameApplication.h"

GameApplication::GameApplication()
{
    _window.clear();
    _window.display();
}

GameApplication::~GameApplication(){}

void GameApplication::MainMenu()
{
    _window.clear();
    while (_gameManager.returnState() == GameState::MAIN_MENU || _gameManager.returnState() == GameState::HIGHSCORES)
    {
        while (_gameManager.returnState() == GameState::MAIN_MENU)
        {
            _window.setTitle("Super_Pacman Main Menu");
            _gameManager.updateState(GameState::MAIN_MENU,_window);
            _window.display();
        }
        while (_gameManager.returnState() == GameState::HIGHSCORES)
        {
            _window.setTitle("Super_Pacman High Scores");
            _gameManager.updateState(GameState::HIGHSCORES,_window);
            _window.display();
        }
    }

    if (_gameManager.returnState() == GameState::SPLASH)
    {
        _gameManager.createState(GameState::SPLASH);
    }
    if (_gameManager.returnState() == GameState::MAP_CREATOR)
    {
         _gameManager.createState(GameState::MAP_CREATOR);
    }

}

void GameApplication::MapEditor()
{
    _window.clear();
    while (_gameManager.returnState() == GameState::MAP_CREATOR)
    {
        _window.setTitle("Super_Pacman V2.1 Map Editor");
        _gameManager.updateState(GameState::MAP_CREATOR, _window);
        _window.display();
    }
}

void GameApplication::Splash()
{
    _window.clear();
    while (_gameManager.returnState() == GameState::SPLASH){
        _window.setTitle("Super_Pacman V2.1 SPlashScreen");
        _gameManager.updateState(GameState::SPLASH,_window);
        _window.display();
    }
    _gameManager.clearState();
    _gameManager.createState(GameState::ACTIVE);

}

void GameApplication::GameOver()
{
    _window.clear();
    while (_gameManager.returnState() == GameState::GAME_OVER){
        _window.setTitle("Super_Pacman V2.1 GameOverScreen");
        _gameManager.updateState(GameState::GAME_OVER,_window);
        _window.display();
    }
	_gameManager.clearState();
}


void GameApplication::GameWon()
{
    _window.clear();
    while (_gameManager.returnState() == GameState::GAME_WON){
        _window.setTitle("Super_Pacman V2.1 GameOverScreen");
        _gameManager.updateState(GameState::GAME_WON,_window);
        _window.display();
    }
	_gameManager.clearState();
}

void GameApplication::Play()
{
    _window.clear();
    StopWatch gameTimer;


    while(_gameManager.returnState() == GameState::ACTIVE)
    {
        if (gameTimer.stop() > 0.01)
        {
            _window.setTitle("Super-Pacman V2.1");
            _gameManager.updateState(GameState::ACTIVE, _window);
            _window.display();
            gameTimer.reset();
        }

    }

    if(_gameManager.returnState() == GameState::GAME_OVER)
    {
        _gameManager.createState(GameState::GAME_OVER);
    }
    if(_gameManager.returnState() == GameState::GAME_WON)
    {
        _gameManager.createState(GameState::GAME_WON);
    }
}

void GameApplication::StartGame()
{
    _window.create(sf::VideoMode(totalWidth, gameHeight), "Super Pacman", sf::Style::Titlebar | sf::Style::Close | sf::Style::Resize);
    _gameManager.createState(GameState::MAIN_MENU);

    while(_window.isOpen())
    {
        while(_window.pollEvent(_event))
        {
            MainMenu();
            MapEditor();
            Splash();
            Play();
            GameOver();
            GameWon();
            //_window.close();
        }
    }
}
