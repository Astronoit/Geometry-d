/* 
 * File:   Cube.h
 * Author: Silvermoon
 *
 * Created on 3 octobre 2015, 15:28
 */

#ifndef CUBE_H
#define	CUBE_H
#include "Player.h"
#include "Block.h"
class Cube : public Block{
public:
    Cube();
    Cube(const Cube& orig);
    virtual ~Cube();
    bool DrawAndHit(Player*);
private:

};

#endif	/* CUBE_H */

