# Package Exchange Documentation


## Entity Moving
> Client & Server

Type: MOVING

**Succes :**

    The server returns "OK" and keep calculating the entity's current position until the client sends
        - NOT_MOVING


**Failure:** 

    The server returns the last [VALID] postion for the client to roll-back.



**Server send**

    The server inform every user in the lobby that en entity is moving giving:
        - UUID
        - direction (so they can deduce the Entity deplacement).
        - speed


## Shoots
> Client & server

Type: SHOOTING

**Succes:**

    Server return "OK"

**Failure:** 

    The server returns "KO" and the user immediatly stop shooting.

**Server send**

    Inform users that an Entity is shooting 
        giving them:
        - UUID

    Since the users are aware of the entity positions they can deduce if they are in the trajectory (for the case of an ennemi).
    only sends: 
        - UUID

## Life points 
> Client & server

Type: LIFE


**Succes:**

    The server returns "OK" 

**Failure:** 

    The server returns the last valid life points that the user should have.

**Server send**

    The server inform every user in the lobby that an Entity has new life points
        - UUID
        - new life point

## Death
> Client: & server

Type: DEAD

**Succes:**

    The server returns "OK" 

**Failure:** 

    The server informs the user that he's not supposed to be dead and send him his last [VALID] health points.

**Server send**

    inform the other users that the current user is dead.

## Spawn
> Server only

Type: SPAWN

**Server send**

    The server inform every user in the lobby that an ennemi spawnd, and gives additional informations: 
        - Ennemi (positions, health, ennemie Type)
        - Bonus (position, bonus type)




