#include "MapEditor.h"



void MapEditor::setMapFilename(const std::string filename)
{    _mapFileName = filename;}


std::string MapEditor::returnMapName()
{
    return _eLogic.returnMapName();
}

MapEditor::MapEditor(const std::string defaultMap) : _eLogic(defaultMap)
{
    _input.reset(new InputManager);
    _input->setInputType(MAP);

    ResourceManager _resource;
    _resource.setLevel(1);
    mapEntityTex = _resource.returnMap();
    _mapStat = _eLogic.returnMapStatus();
}

void MapEditor::LoadContent()
{
    _mapStat = _eLogic.returnMapStatus();
    switch (_mapStat)
    {
    case Instructions:
        {
            break;
        }
    case EditorMenu:
        {
            break;
        }
    case Choices:
        {
            _eLogic.loadChoices();
            break;
        }
    case Designer:
        {
            _eLogic.loadDesigner();
            _optionGrid = _eLogic.returnOptionGrid();
            loadoptionSprites();

            //_optionSprites = loadSprites(_eLogic.returnOptionGrid());
            break;
        }
    case Errors:
        {
            break;
        }
    case SaveInput:
        {
            _eLogic.loadTextMode();
            break;
        }
    }
}


void MapEditor::createSprites()
{

    for (auto& one : _mazeGrid)
    {
        for (auto& objects : one)
        {
            auto eID = objects->getEntityID();
            TextureID ID;
            std::shared_ptr<sf::Sprite> tempSprite (new sf::Sprite);
            sf::Texture _tempTex;
            if (eID != Entity_ID::PATH && eID != Entity_ID::GHOST_DOOR)
            {
                switch(eID)
                {
                case Entity_ID::PACMAN:
                    {
                        ID = TextureID::PacmanTex;
                        break;
                    }
                case Entity_ID::GHOST:
                    {
                        ID = TextureID::GhostRedTex;
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
    }
}

void MapEditor::loadoptionSprites()
{
for (auto& one : _optionGrid)
    {
        for (auto& objects : one)
        {
            auto eID = objects->getEntityID();
            TextureID ID;
            std::shared_ptr<sf::Sprite> tempSprite (new sf::Sprite);
            sf::Texture _tempTex;
            if (eID != Entity_ID::PATH && eID != Entity_ID::GHOST_DOOR)
            {
                switch(eID)
                {
                case Entity_ID::PACMAN:
                    {
                        ID = TextureID::PacmanTex;
                        break;
                    }
                case Entity_ID::GHOST:
                    {
                        ID = TextureID::GhostRedTex;
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
                    _optionSprites.push_back(tempSprite);
            }
        }
    }
}


void MapEditor::RemoveContent()
{

}

void MapEditor::Update(sf::RenderWindow& _window, sf::Event& _event)
{
    _input->retrieveInput(_window, _event);
    _mapStat = _eLogic.returnMapStatus();

    switch (_mapStat)
    {
    case Instructions:
        {
            break;
        }
    case EditorMenu:
        {
            break;
        }
    case Choices:
        {
            _eLogic.InterpretMapInput(_input->leftClick(), _input->returnMousePos());
            _eLogic.chooseMap(); //run the choices
            writeText = _eLogic.returnText();

            if (_eLogic.returnMapStatus() == Designer)
            {
                LoadContent();
            }
            break;
        }
    case Designer:
        {
            _eLogic.InterpretMapInput(_input->leftClick(), _input->returnMousePos());
            _eLogic.Designer();

            _mazeGrid = _eLogic.returnMaze();
            createSprites();
            writeText = _eLogic.returnText();

            if (_eLogic.returnMapStatus() == SaveInput)
            {
                _input->setInputType(TEXT);
                LoadContent();
            }
            break;
        }
    case Errors:
        {
            break;
        }
    case SaveInput:
        {

            _eLogic.InterpretTextInput(_input->leftClick(), _input->returnMousePos(), _input->returnText());
            _eLogic.TextInputMode();
            writeText = _eLogic.returnText();
            break;
        }
    }
    _window.clear();
}


void MapEditor::Draw(sf::RenderWindow& _window)
{
sf::Font font;
        font.loadFromFile("sansation.ttf");
    if (_eLogic.returnMapStatus() == mapStatus::Choices)
    {
        std::string txt = "To navigate: please use the mouse button."
                            "\n To create a New/blank, map, please click on 'NEW'."
                            "\n To edit an existing map, please click on the map name you would like to edit and then click on 'EDIT'."
                            "\n To set an exising map as the default map for game play, please click on the map name you would like"
                            "\n           to use and then click on 'SET AS DEAFULT'"
                            "\n To return to the main menu, click on 'EXIT'";

        sf::Text mouse;
        mouse.setString(txt);
        mouse.setFont(font);
        mouse.setCharacterSize(15);
        mouse.setFillColor(sf::Color(128,128,128));
        mouse.setPosition(0, gameHeight-100);
        _window.draw(mouse);

        txt = "When creating your map, To navigate: please use the mouse"
                "\n button."
                "\n To select which object you would like to place, "
                "\n     click on the option on the right hand side,"
                "\n     the chosen object name will be highlighted."
                "\n To place your object, click on the displayed grid on the left hand"
                "\n   side and the highlighted option object will be placed there."
                "\n To save your map, click on the 'SAVE' button. To exit without"
                "\n   saving, click on 'EXIT'."
                "\n Please note: in order to be able to save your map: you must have"
                "\n   a multiple of 3 door objects, at least one key, only ONE pacman"
                "\n   object, no less than one and no more than 4 ghost objects, no "
                "\n   more than 2 super pellets and 4 powerpellets and at least one"
                "\n   fruit object.";

        //sf::Text mouse;
        mouse.setString(txt);
        mouse.setFont(font);
        mouse.setCharacterSize(15);
        mouse.setFillColor(sf::Color(128,128,128));
        mouse.setPosition(gameWidth-200, 10);
        _window.draw(mouse);
    }


    if (_eLogic.returnMapStatus() == mapStatus::Designer)
    {
        sf::Texture blank;
        blank.loadFromFile("square.png");
        sf::Vector2u TextureDim = blank.getSize();
        sf::Sprite _background;
        _background.setTexture(blank);
        _background.setOrigin(TextureDim.x/2,TextureDim.y/2);
        _background.setPosition(gameWidth/2,gameHeight/2);
        _window.draw(_background);

         sf::Text text;
        std::string txt = "SAVE";
        text.setString(txt);
        text.setFont(font);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);
        text.setPosition(gameWidth+100, 624);
        _window.draw(text);
    }

    sf::Text QuitText;
        std::string str = "EXIT";
        QuitText.setString(str);
        QuitText.setFont(font);
        QuitText.setCharacterSize(25);
        QuitText.setFillColor(sf::Color::White);
        QuitText.setPosition(gameWidth+100, 660);
        _window.draw(QuitText);

    if (_eLogic.returnMapStatus() == mapStatus::SaveInput)
    {
         sf::Text text, QuitText;
        std::string txt = "SAVE";
        text.setString(txt);
        text.setFont(font);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::White);
        text.setPosition(gameWidth+100, 624);
        _window.draw(text);

        txt = "Please use the keyboard to enter your filename."
                "\n To Save or quit(without saving), click on the options in the right hand corner."
                "\n Please note when creating your filename: Please do not include spaces in your filename."
                "\n If you press the enter button by accident, please press the backspace key to remove the newline character";
        sf::Text mouse;
        mouse.setString(txt);
        mouse.setFont(font);
        mouse.setCharacterSize(15);
        mouse.setFillColor(sf::Color(128,128,128));
        mouse.setPosition(0, 0);
        _window.draw(mouse);


    }


    for (auto& x : writeText)
    {
        _window.draw(x);
    }


    //draw option sprites
    for (auto& entity : _entitySprites)
        _window.draw(*entity);

    for(auto& entity: _optionSprites)
        _window.draw(*entity);


    _entitySprites.clear();
}


Game_Status MapEditor::returnGameProgress()
{
    return _eLogic.returnGameProgress();
}
