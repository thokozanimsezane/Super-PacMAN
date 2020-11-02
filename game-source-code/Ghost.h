#ifndef GHOST_H_INCLUDED
#define GHOST_H_INCLUDED

#include "IDynamicMazeEntity.h"
#include "Common.h"

/** \class Ghost
 *  \brief This is a Class that inherits from the IDynamicMazeEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a ghost object. A ghost chases pacman and can be eaten by pacman when he has eaten a power pellet.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

    const float _speed = 35.f;  /**< The speed of the ghost */

    class Ghost : public IDynamicMazeEntity
    {
    public:

        /** \brief Parameterized constructor. Creates a Ghost object.
         *  \param position is of type sf::Vector2f, contains spawn point of a ghost.
         */
        Ghost(sf::Vector2f position);

        /** \brief Default Destructor. Destroys a Ghost object.
         */
        ~Ghost();

        /** \brief Inherited from IMazeEntity. A virtual function that
          *  gets the position of a ghost object.
          *  \return sf::vector2f with the position.
          */
        virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object

        /** \brief Inherited from IMazeEntity. A virtual function that
         *  gets the ID of a Ghost object.
         *  \return Entity_ID an enumeration type defined in Common.h
         */
        virtual Entity_ID getEntityID() const override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  sets the position of a ghost object.
         *  \param _position is of type sf::Vector2f with the x,y position coordonates to be set
         */
        virtual void setPosition(sf::Vector2f _position) override;

        /** \brief Inherited from IMazeEntity. A virtual function that
         *  gets the status (active/inactive/transition) of a ghost object.
         *  \return STATUS, an enumeration type defined in Common.h
         */
        virtual STATUS getStatus() const override; //returns the status of the object

        /** \brief Inherited from IMazeEntity. A virtual function that
         *  sets ghost object status to transitional (ghost is moving back to the ghost home).
         */
        virtual void Delete() override; //sets the object status to transitional (ghost is moving back home)

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  sets ghost object status back to active, called after a certain amount of time has elapsed.
         */
        virtual void Reset() override; // sets object status back to active (ghost has arrived home)

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  resets the ghost object position to the ghost house.
         */
        virtual void reSpawn() override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  gets the ghost object desired direction of movement.
         *  \return Direction, an enumeration type defined in Common.h
         */
        virtual Direction getDesiredDirection() const override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  sets the ghost object desired direction of movement.
         *  \param dir is of type Direction, an enumeration type defined in Common.h
         */
        virtual void setDesiredDirection(Direction dir) override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  gets the ghost object orientation.
         *  \return Orientation, an enumeration type defined in Common.h
         */
        virtual Orientation getOrientation() const override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  moves the ghost object in the up direction.
         *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
         */
        virtual void moveUp(double delta) override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  moves the ghost object in the down direction.
         *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
         */
        virtual void moveDown(double delta) override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  moves the ghost object in the left direction.
         *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
         */
        virtual void moveLeft(double delta) override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  moves the ghost object in the right direction.
         *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
         */

        virtual void moveRight(double delta) override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  returns the ghost object effect status (NORMAL, POWER or SUPER).
         *  \return EffectStatus
         */
        virtual EffectStatus getEffectStatus() const override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  sets the ghost object effect status (NORMAL, POWER or SUPER).
         *  \param EStatus is of type EffectStatus an enumeration type defined in Common.h
         */
        virtual void setEffectStatus(EffectStatus _EStatus);

        /** \brief Inherited from IStaticMazeEntity. A virtual function that
         *  gets the grid position of a ghost object.
         *  \return sf::vector2u with the grid position.
         */
        virtual sf::Vector2u gridPosition() const override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  gets the ID of a ghost object.
         *  \return Ghost_ID, an enumeration type defined in Common.h.
         */
        virtual Ghost_ID getGhostID() const override;

        /** \brief Inherited from IDynamicMazeEntity. A virtual function that
         *  sets the ID of a ghost object.
         *  \param gID is of type Ghost_ID an enumeration type defined in Common.h.
         */
        void setGhostID(Ghost_ID gID);

    private:
        STATUS Current_Status;
        sf::Vector2f _GhostPosition;
        EffectStatus _effectStatus;
        Entity_ID _ID;
        Direction _dir;
        sf::Vector2f spawnPoint;
        Ghost_ID _gID;

    };
#endif
