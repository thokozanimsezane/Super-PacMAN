#include "GameWonScreen.h"

GameWonScreen::GameWonScreen()
{
    //ctor
    _input.reset(new InputManager);
    _input->setInputType(TEXT);
}

GameWonScreen::~GameWonScreen()
{
    //dtor
}

void GameWonScreen::LoadContent()
{
    _gameWonTexture.loadFromFile("Splash.png");
    _background.setTexture(_gameWonTexture);
    font.loadFromFile("sansation.ttf");

    std::string splashTitle = "YOU WIN!!!";
    sf::Text title(splashTitle, font);
    title.setCharacterSize(58);
    title.setStyle(sf::Text::Bold);
    title.setColor(sf::Color::Black);
    _title = title;

    FileManager file;
    file.readAllHighScores();
    if (file.findNewScore(_highScore))
    {
        _newHighScoreString = "You got a new High Score!!";
        enterName = "Please enter your name below: ";
        newHigh = true;
    }
    else
    {
        _newHighScoreString = " ";
        enterName = "";
        newHigh = false;
        stringCheck = "";
    }

    std::string gameWonControls =
                                 "Press Escape To Quit"
                                 "\n \n Press Enter key to ";
    if (newHigh)
    {
        gameWonControls = gameWonControls + "save your score and ";
    }
    gameWonControls = gameWonControls + "\n Return to Main Menu...";
    sf::Text controls(gameWonControls,font);
    controls.setCharacterSize(25);
    controls.setStyle(sf::Text::Bold);
    controls.setColor(sf::Color::Black);
    _controls = controls;

    //create player score text
    std::string yourHighScoreText = "Your Score:" + std::to_string(_highScore.score);
    sf::Text yourHS(yourHighScoreText, font);
    yourHS.setCharacterSize(24);
    yourHS.setFillColor(sf::Color::Black);
    _yourHS = yourHS;

    //create highest score text
    auto highestScore = file.returnHighScore();
    std::string HighestScoreText = "High Score: " + std::to_string(highestScore.score);
    sf::Text HighestS(HighestScoreText, font);
    HighestS.setCharacterSize(24);
    HighestS.setFillColor(sf::Color::Black);
    _highHS = HighestS;
}

void GameWonScreen::RemoveContent()
{

}

void GameWonScreen::Update(sf::RenderWindow& _window, sf::Event& _event)
{
    if (newHigh)
    {
        _input->retrieveInput(_window, _event);
        auto TextInput = _input->returnText();
        stringCheck = TextInput;
        sf::Text in(TextInput,font);
        _TextInput = in;
    }
}

void GameWonScreen::Draw(sf::RenderWindow& _window)
{
    sf::Text Name(enterName, font);
    Name.setCharacterSize(25);
    Name.setFillColor(sf::Color::Blue);
    // Display you got a new High Score
    sf::Text newHighScore(_newHighScoreString,font);
    newHighScore.setCharacterSize(25);
    newHighScore.setFillColor(sf::Color::Black);

     //display user input text
    _TextInput.setCharacterSize(25);
    _TextInput.setFillColor(sf::Color::Black);

    _title.setPosition(_window.getSize().x/3,_window.getSize().y/5- _window.getSize().y/8);
    _highHS.setPosition(2*_window.getSize().x/3,_window.getSize().y/2-_window.getSize().y/4);
    _yourHS.setPosition(_window.getSize().x/3,_window.getSize().y/2-_window.getSize().y/4);
    newHighScore.setPosition(_window.getSize().x/3,_window.getSize().y/2 - _window.getSize().y/3);
    Name.setPosition(_window.getSize().x/3,_window.getSize().y/2);
    _TextInput.setPosition(_window.getSize().x/3, _window.getSize().y/2+25);
    _controls.setPosition(_window.getSize().x/3,_window.getSize().y - _window.getSize().y/5);

    _window.draw(_background);
    _window.draw(_title);
    _window.draw(_controls);
    _window.draw(_yourHS);
    _window.draw(_highHS);
    _window.draw(_TextInput);
    _window.draw(Name);
    _window.draw(newHighScore);
}

Game_Status GameWonScreen::returnGameProgress()
{
    return Game_Status::GAME_WON;
}

HighScore GameWonScreen::returnHighScore()
{
    if (newHigh)
    {stringCheck.erase(stringCheck.getSize()-1, 1);}
    _highScore.name = stringCheck;
    return _highScore;
}

void GameWonScreen::saveHighScore(HighScore _newHighScore)
{
    _highScore = _newHighScore;
}
