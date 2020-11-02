#ifndef IDYNAMICMAZEENTITY_H_INCLUDED
#define IDYNAMICMAZEENTITY_H_INCLUDED

#include "IStaticMazeEntity.h"
#include "Common.h"

/** \class IDynamicMazeEntity
 *  \brief This is a Interface Class that inherits from the IStaticMazeEntity class. It
 *  contains pure virtual functions that will be overridden by derived classes.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */

 class IDynamicMazeEntity :public IStaticMazeEntity
 {
 public:

    /** \brief A pure virtual function that resets the dynamic objects position to their spawn points.
     */
    virtual void reSpawn()=0;

    /** \brief A pure virtual function that resets the dynamic objects status back to NORMAL.
     */
    virtual void Reset()=0;

    /** \brief A pure virtual function that returns the dynamic entity ghost object ID
     *  \returns type Ghost_ID, an enumeration defined in Common.h
     */
    virtual Ghost_ID getGhostID()const = 0;

    /** \brief A pure virtual function that sets the position of dymanic objects.
     *  \param _position is of type sf::Vector2f.
     */
    virtual void setPosition(sf::Vector2f _position)=0;


    /** \brief A pure virtual function that gets the orientation of dymanic objects.
     *  \return type Orientation, an enumeration defined in Common.h
     */
    virtual Orientation getOrientation()const=0;

    /** \brief A pure virtual function that moves derived class objects up.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveUp(double delta)=0;

    /** \brief A pure virtual function that moves derived class objects down.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveDown(double delta)=0;

    /** \brief A pure virtual function that moves derived class objects left.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveLeft(double delta)=0;

    /** \brief A pure virtual function that moves derived class objects right.
     *  \param delta is of type double, it is the deltaTime used in the velocity equation of the entity.
     */
    virtual void moveRight(double delta)=0;

    /** \brief A pure virtual function that gets the derived class objects desired direction of movement.
     *  \return type Direction, an enumeration defined in Common.h
     */
    virtual Direction getDesiredDirection()const=0;

    /** \brief A pure virtual function that sets the derived class objects desired direction of movement.
     *  \param dir is of type Direction an enumeration defined in Common.h
     */
    virtual void setDesiredDirection(Direction dir)=0;

    /** \brief A pure virtual function that gets the derived class objects effect status due to power and super pellets.
     *  \return type EffectStatus, an enumeration defined in Common.h
     */
    virtual EffectStatus getEffectStatus()const=0;

    /** \brief A pure virtual function that sets the derived class objects effect status due to power and super pellets.
     *  \param _effectStatus of type EffectStatus an enumeration defined in Common.h
     */
    virtual void setEffectStatus(EffectStatus _effectStatus)=0;
 };

/*Pacman and ghosts are derived from this class */

#endif // IDYNAMICMAZEENTITY_H_INCLUDED
