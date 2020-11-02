#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "Common.h"


/** \class ResourceManager
 *  \brief A Data layer class that maps entities to their respective textures, loads maze/fruit for the difeerent game levels.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class ResourceManager
{
    public:

        /** \brief A default Constructor, creates a ResourceManager object.
         */
        ResourceManager();

        /** \brief Default Destructor. Destroys a ResourceManager object.
         */
        ~ResourceManager();

        /** \brief Loads all the textures for the game objects for the corresponding level,
         *   stores each texture and its texture ID in a map
         */
        void LoadContent();

        /** \brief Sets the current game level.
         *  \param level is of type int and designates the game level.
         */
        void setLevel(int level);

        /** \brief Returns a map with textures and entity IDs.
         *  \return map object of TextureID (an enum defined in Common.h) and sf::Texture
         */
        std::map<TextureID, sf::Texture> returnMap();

    private:
        std::map<TextureID, sf::Texture> mapTextureTex;
        int _level;
        sf::Texture _texture;
};

#endif // RESOURCEMANAGER_H
