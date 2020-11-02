#include "MainMenu.h"

MainMenu::MainMenu()
{
    _selection = static_cast<Menu>(MenuSelect);
    _menu.reset(new InputManager);
    _menu->setInputType(POLLED);
}

MainMenu::~MainMenu(){}

void MainMenu::LoadContent()
{
    //load fonts
    _titleFont.loadFromFile("StrangerBrush.ttf");
    _menuFont.loadFromFile("sansation.ttf");

    std::string title = "SUPER-PACMAN";
    sf::Text Title(title, _titleFont);
    _Title = Title;
    _Title.setCharacterSize(70);
    _Title.setFillColor(sf::Color::White);
    _Title.setPosition(gameWidth/3, 10);

    _MenuOptions.push_back(_Title); // vector of sf::Text for drawing

    MenuList[0].setString("Play");
    MenuList[1].setString("High-Scores");
    MenuList[2].setString("Map Editor");
    MenuList[3].setString("Settings");
    MenuList[4].setString("Quit");

    for (int i =0; i<5; i++)
    {
        MenuList[i].setFont(_menuFont);
        MenuList[i].setFillColor(sf::Color::Yellow);
        MenuList[i].setCharacterSize(35);
        MenuList[i].setPosition(gameWidth/3, 140+i*100);

        if (i==3) //grey out the settings option - not created
        {
            MenuList[i].setFillColor(sf::Color(128,128,128));
        }
        _MenuOptions.push_back(MenuList[i]);
    }
}

void MainMenu::RemoveContent(){}

void MainMenu::Update(sf::RenderWindow& _window, sf::Event& _event)
{
    _window.clear();
    _menu->retrieveInput(_window,_event);

    if (_menu->Down())
    {
        _selection++;
        _selection = _selection%5;
        if (_selection == 3)
        {
            _selection++;
        }

    }
    if (_menu->Up())
    {
        if (_selection == 0)
        {
            _selection = 4;
        }
        else
        _selection--;
        _selection = _selection%5;
        if (_selection == 3)
        {
            _selection--;
        }

    }
    if (_menu->confirm())
    {
        selected = true;
    }

    //highlight the selection
    for (int i =0; i<5; i++)
    {
        if (i == _selection)
        {
            _MenuOptions[i+1].setPosition(gameWidth/3, 130+i*100);
            _MenuOptions[i+1].setFillColor(sf::Color::Blue);
        }
        else
        {
            _MenuOptions[i+1].setPosition(gameWidth/3, 140+i*100);
            _MenuOptions[i+1].setFillColor(sf::Color::Yellow);
        }
        if (i == 3)
        {
            _MenuOptions[i+1].setFillColor(sf::Color(128,128,128));
        }
    }
    _window.clear();

}

void MainMenu::Draw(sf::RenderWindow& _window)
{
    for (auto& x : _MenuOptions)
    {        _window.draw(x);       }
}

Menu MainMenu::menuSelection()
{
    return static_cast<Menu>(_selection);
}
