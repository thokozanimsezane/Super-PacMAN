#include "ResourceManager.h"

ResourceManager::ResourceManager(): _level(1)
{

}
ResourceManager::~ResourceManager(){}

void ResourceManager::LoadContent(){

    if(!_texture.loadFromFile("pacSmall.png"))
    throw "pacman texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(PacmanTex, _texture));

    //! change this according to level. add multiple fruit textures, then use modulo depending on level to choose which fruit we load
    switch(_level)
    {
    case 1:
        {
          if(!_texture.loadFromFile("cherry.png"))
          throw "cherry texture doesn't exist";
          mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FruitTex, _texture));
          break;
        }
    case 2:
        {
          if(!_texture.loadFromFile("banana.png"))
          throw "banana texture doesn't exist";
          mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FruitTex, _texture));
          break;
        }
    case 3:
        {
          if(!_texture.loadFromFile("apple.png"))
          throw "apple texture doesn't exist";
          mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FruitTex, _texture));
          break;
        }
    case 4:
        {
          if(!_texture.loadFromFile("donut.png"))
          throw "donut texture doesn't exist";
          mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FruitTex, _texture));
          break;
        }
    case 5:
        {
          if(!_texture.loadFromFile("coinpurse.png"))
          throw "coinpurse texture doesn't exist";
          mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FruitTex, _texture));
          break;
        }

    }

    if(!_texture.loadFromFile("redGhost.png"))
        throw "redghost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(GhostRedTex, _texture));

    if(!_texture.loadFromFile("blueGhost.png"))
        throw "blueghost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(GhostBlueTex, _texture));

    if(!_texture.loadFromFile("pinkGhost.png"))
        throw "pinkghost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(GhostPinkTex, _texture));

    if(!_texture.loadFromFile("orangeGhost.png"))
        throw "orangeghost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(GhostOrangeTex, _texture));


    if(!_texture.loadFromFile("wall.png"))
        throw "wall texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(WallTex, _texture));

    if(!_texture.loadFromFile("door.png"))
        throw "door texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(DoorTex, _texture));

    if(!_texture.loadFromFile("superPellet.png"))
        throw "superPellet texture doesn't exist";
   mapTextureTex.insert(std::pair<TextureID,sf::Texture>(SuperTex, _texture));

    if(!_texture.loadFromFile("powerPellet.png"))
        throw "Power_pellet texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(PowerTex, _texture));

    if(!_texture.loadFromFile("key.png"))
        throw "key texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(KeyTex, _texture));


    if(!_texture.loadFromFile("superPacman.png"))
       throw "superpacman texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(SuperPacmanTex, _texture));

    if(!_texture.loadFromFile("flatBlueGhost.png"))
        throw "flatBlueGhost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FlatGhostBlueTex, _texture));

    if(!_texture.loadFromFile("flatRedGhost.png"))
        throw "flatRedGhost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FlatGhostRedTex, _texture));

    if(!_texture.loadFromFile("flatPinkGhost.png"))
        throw "flatPinkGhost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FlatGhostPinkTex, _texture));

    if(!_texture.loadFromFile("flatOrangeGhost.png"))
        throw "flatOrangeGhost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(FlatGhostOrangeTex, _texture));

    if(!_texture.loadFromFile("deadGhost.png"))
        throw "deadghost texture doesn't exist";
    mapTextureTex.insert(std::pair<TextureID,sf::Texture>(DeadGhostTex, _texture));


}

void ResourceManager::setLevel(int level){

    _level = level;
    mapTextureTex.clear();
    LoadContent();
}

std::map<TextureID, sf::Texture> ResourceManager::returnMap(){

    return mapTextureTex;
}


