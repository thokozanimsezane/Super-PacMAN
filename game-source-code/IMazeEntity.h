#ifndef IMAZEENTITY_H_INCLUDED
#define IMAZEENTITY_H_INCLUDED
 //! Abstract/Interface class
 //! Base class object for all entities/game objects

 #include "Common.h"
 //Status - always present/active

/** \class IMazeEntity
 *  \brief This is an Interface Class containing pure virtual functions that
 *  will be overridden by derived classes.
 *  \author 719597 Tarryn Maggs and 1033379 Thokozani Msezane.
 *  \version 3.0
 */
 class IMazeEntity
 {
 public:

    /** \brief A pure virtual function that returns a Position of the
     *  derived class object.
     *  \return Position of the derived class object containing its current position type sf::Vector2f.
     */
    virtual sf::Vector2f getPosition()const=0; //2D vector representing the position of the object

    /** \brief A pure virtual function that returns a the ID of the
     *  derived class object.
     *  \return entity ID of the derived class object, type Entity_ID an enumeration defined in Common.h
     */
    virtual Entity_ID getEntityID()const=0;

    /** \brief A pure virtual function that returns a the Status of the
     *  derived class object.
     *  \return type STATUS, an enumeration defined in Common.h.
     */
    virtual STATUS getStatus()const=0;
    // paths and walls have this defined but do not use this function whatsoever. function is defined as empty
    // this is necessary here because the maze grid is populated with all objects, including
    // walls and paths. the data from this is then used to manage objects in the collision handler

    /** \brief A pure virtual function that sets derived class objects status to inactive.
     */
    virtual void Delete()=0;
 };

/* maze objects like path and walls are derived from this class */


#endif // MAZEENTITY_H_INCLUDED



