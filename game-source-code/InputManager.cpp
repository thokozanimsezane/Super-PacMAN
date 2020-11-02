#include "InputManager.h"

InputManager::InputManager()
{
    ResetInput();
    _input = LIVE;
    // set Live as the default, since the main game will always use this type
    // and the other screens using the input manager will always call the setInputType function.
}

InputManager::~InputManager(){}

void InputManager::ResetInput()
{
    _left = false;
    _right = false;
    _up = false;
    _down = false;
    _confirm = false;
    _escape = false;
    _speedUp = false;

    _leftClick = false;
    _rightClick = false;
}

void InputManager::setInputType(InputType input)
{
    _input = input;
    playerInput = "";
}

void InputManager::retrieveInput(sf::RenderWindow& _GameWindow, sf::Event& _event)
{

    ResetInput();
    if (_input == POLLED)
    {

        while(_GameWindow.pollEvent(_event))
        {
            if(_event.type == sf::Event::KeyPressed) // only cares if a key HAS been pressed
            {
                switch(_event.key.code)
                {
                case sf::Keyboard::Left:
                    {
                        _left = true;
                        break;
                    }
                case sf::Keyboard::Right:
                    {
                        _right = true;
                        break;
                    }
                case sf::Keyboard::Up:
                    {
                        _up = true;
                        break;
                    }
                case sf::Keyboard::Down:
                    {
                        _down = true;
                        break;
                    }
                case sf::Keyboard::Return:
                    {
                        _confirm = true;
                        //confirm
                        break;
                    }
                case sf::Keyboard::Escape:
                    {
                        _escape = true;
                        break;
                    }
                    default: return;
                }
            }
        }
    }
    else if (_input == LIVE)
    {

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
        {             _left = true;     }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
        {            _right = true;     }

        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
        {            _up = true;        }
        else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
        {            _down = true;     }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
        {            _speedUp = true;     }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            _escape = true;
        }
    }
    else if (_input == TEXT)
    {
        while(_GameWindow.pollEvent(_event))
        {
            switch(_event.type)
            {
            case sf::Event::Closed:
                {
                     _GameWindow.close();
                     break;
                }
            case sf::Event::TextEntered:
                {
                    if(_event.text.unicode == '\b' && playerInput.end() != playerInput.begin())
                    {
                        playerInput.erase(playerInput.getSize() - 1,2);
                    }
                    else if (_event.text.unicode < 128)
                    {
                        playerInput += _event.text.unicode;
                    }
                    break;
                }
                case sf::Event::KeyPressed: // only cares if a key HAS been pressed
                {
                    if (_event.key.code == sf::Keyboard::Return)
                    {
                        _confirm = true;
                            //confirm
                            break;
                    }
                }
                case sf::Event::MouseButtonPressed:
                {
                  if (_event.mouseButton.button == sf::Mouse::Left)//left click
                    {
                        _leftClick = true;
                        //select/place object
                    }
                    else if (_event.mouseButton.button == sf::Mouse::Right)//right click
                    {
                        _rightClick = true;
                        //remove object
                   }
                    mousePosition.x = sf::Mouse::getPosition(_GameWindow).x;
                    mousePosition.y = sf::Mouse::getPosition(_GameWindow).y;
                    break;
                }

            default:
                break;
            }
        }
    }
    else if (_input == MAP)
    {
        while(_GameWindow.pollEvent(_event))
        {
            switch(_event.type)
            {
            case sf::Event::Closed:
                {
                     _GameWindow.close();
                     break;
                }
            case sf::Event::MouseButtonPressed:
                {
                  if (_event.mouseButton.button == sf::Mouse::Left)//left click
                    {
                        _leftClick = true;
                        //select/place object
                    }
                    else if (_event.mouseButton.button == sf::Mouse::Right)//right click
                    {
                        _rightClick = true;
                        //remove object
                   }
                    mousePosition.x = sf::Mouse::getPosition(_GameWindow).x;
                    mousePosition.y = sf::Mouse::getPosition(_GameWindow).y;
                    break;
                }
            case sf::Event::KeyPressed: // only cares if a key HAS been pressed
            {
                if (_event.key.code == sf::Keyboard::Return)
                {
                    _confirm = true;
                        //confirm
                        break;
                }
            }
            case sf::Event::MouseButtonReleased:
                    break;
            default:
                break;
            }
        }
    }
}

//cannot reset the same way as the other returns.
void InputManager::clearText()
{
    playerInput = "";
}

sf::String InputManager::returnText()
{
    return playerInput;
}

sf::Vector2f InputManager::returnMousePos()
{
    return mousePosition;
}

//! can maybe use a keyManager Enumeration

bool InputManager::Left()
{
    return _left;
}

bool InputManager::Right()
{
    return _right;
}

bool InputManager::Up()
{
    return _up;
}

bool InputManager::Down()
{
    return _down;
}

bool InputManager::confirm()
{
    return _confirm;
}

bool InputManager::previous()
{
    return _escape;
}

bool InputManager::isSpeedUp()
{
    return _speedUp;
}

bool InputManager::leftClick()
{
    return _leftClick;
}

bool InputManager::rightClick()
{
    return _rightClick;
}
