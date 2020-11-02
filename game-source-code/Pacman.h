#ifndef PACMAN_H_INCLUDED
#define PACMAN_H_INCLUDED

#include "Common.h"
#include "IDynamicMazeEntity.h"

/** \class Pacman
 *  \brief This is a Pacman Class that inherits from the IDynamicMazeEntity class. It
 *  contains virtual functions that have been overridden. It models
 *	a Pacman object. Pacman can be moved left, right, up and down and can be eat fruits. Pacman can also eat ghosts when he has eaten a power pellet.
 *  When pacman eats a super pellet he can eat through doors and cant be eaten by ghosts, he also triples in size and become faster
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

class Pacman : public IDynamicMazeEntity
{
public:

    /** \brief Parameterized constructor. Creates a Pacman object.
     *  \param position is of type sf::Vector2f, contains spawn point of a pacman.
     */
    Pacman(sf::Vector2f position);

    /** \brief Default Destructor. Destroys a Pacman object.
     */
    ~Pacman();

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the ID of a Pacman object.
     *  \return Entity_ID an enumeration type defined in Common.h
     */
    virtual Entity_ID getEntityID() const override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the position of a Pacman object.
     *  \return sf::vector2f with the position
     */
    virtual sf::Vector2f getPosition() const override; //2D vector representing the position of the object


    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  sets the position of a Pacman object.
     *  \param _position is of type sf::Vector2f
     *  \return _position is of type sf::Vector2f with the x,y position coordonates to be set
     */
    virtual void setPosition(sf::Vector2f _position) override;

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  gets the status (active/inactive/transition) of a Pacman object.
     *  \return STATUS, an enumeration type defined in Common.h
     */
    virtual STATUS getStatus() const override; //returns the status of the object

    /** \brief Inherited from IMazeEntity. A virtual function that
     *  sets Pacman object status to transitional.
     */
    virtual void Delete() override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  sets Pacman object status back to active...
     */
    virtual void Reset() override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  resets the Pacman object position to the spawn position.
     */
    virtual void reSpawn() override;


    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  gets the Pacman object desired direction of movement.
     * \return Direction, an enumeration type defined in Common.h
     */
    virtual Direction getDesiredDirection() const override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  sets the Pacman object desired direction of movement.
     *  \param dir is of type Direction, an enumeration type defined in Common.h
     */
    virtual void setDesiredDirection(Direction dir) override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  gets the Pacman object orientation.
     *  \return Orientation, an enumeration type defined in Common.h
     */
    virtual Orientation getOrientation() const override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  moves the Pacman object in the up direction.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveUp(double delta) override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  moves the Pacman object in the up direction.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveDown(double delta) override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  moves the Pacman object in the up direction.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveLeft(double delta) override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  moves the Pacman object in the up direction.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveRight(double delta) override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  returns the Pacman object effect status (NORMAL, POWER or SUPER).
     *  \return EffectStatus
     */
    virtual EffectStatus getEffectStatus() const override;

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  sets the Pacman object effect status (NORMAL, POWER or SUPER).
     *  \param EStatus is of type EffectStatus an enumeration type defined in Common.h
     */
    virtual void setEffectStatus(EffectStatus _EStatus);

    /** \brief Inherited from IDynamicMazeEntity. A virtual function that
     *  gets the ID of the Pacman object.
     *  \return Ghost_ID, an enumeration type defined in Common.h.
     */
    virtual Ghost_ID getGhostID() const override;

    /** \brief Inherited from IStaticMazeEntity. A virtual function that
     *  gets the grid position of the Pacman object.
     *  \return sf::vector2u with the grid position.
     */
    virtual sf::Vector2u gridPosition() const override;

    /** \brief A virtual function that
     *  sets the speed of the Pacman object.
     *  \param speed is of type float.
     *  \note Speed only changed by EffectsManager
     */
    void setSpeed(float Speed); //only changed by effect manager

private:
    sf::Vector2f _PacPosition;
    STATUS Current_Status;
    EffectStatus _effectStatus;
    Entity_ID _ID;
    float _speed;
    sf::Vector2f spawnPoint;
    Orientation _orientation;

    void setStatus(STATUS);
    Direction _DesiredDir;

};

#endif // PACMAN_H_INCLUDED
