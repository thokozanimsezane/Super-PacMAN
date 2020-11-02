#include "SplashScreen.h"
#include <string>

SplashScreen::SplashScreen(){}

SplashScreen::~SplashScreen(){}

void SplashScreen::RemoveContent(){}

void SplashScreen::LoadContent()
{
    _splashTexture.loadFromFile("Splash.png");
    _background.setTexture(_splashTexture);

    font.loadFromFile("sansation.ttf");
}

void SplashScreen::Update(sf::RenderWindow& _window, sf::Event& _event)
{}


void SplashScreen::Draw(sf::RenderWindow& _window)
{

    std::string splashTitle = "Super PacMan";
    sf::Text title(splashTitle, font);
    title.setCharacterSize(58);
    title.setPosition(_window.getSize().x/3,_window.getSize().y/4);
    title.setStyle(sf::Text::Bold);
    title.setFillColor(sf::Color::Black);
    std::string splashControls = "Controls"
                                 "\n -Left arrow key moves Left"
                                 "\n -Right arrow key moves Right"
                                 "\n -Up arrow key moves Up"
                                 "\n -Down arrow key moves Down"
                                 "\n \n Press SpaceBar to continue...";

    sf::Text controls(splashControls,font);
    controls.setCharacterSize(25);
    controls.setPosition(_window.getSize().x/3,_window.getSize().y/2 - _window.getSize().y/10);
    controls.setStyle(sf::Text::Bold);
    controls.setFillColor(sf::Color::Black);

    _window.draw(_background);
    _window.draw(controls);
    _window.draw(title);
}

Game_Status SplashScreen::returnGameProgress()
{
    return Game_Status::LEVEL_INCOMPLETE;
}

