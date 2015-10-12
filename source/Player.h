/* 
 * File:   Player.h
 * Author: Silvermoon
 *
 * Created on 3 octobre 2015, 12:56
 */

#ifndef PLAYER_H
#define	PLAYER_H
#include "Block.h"

class Player : public Block {
public:
    Player();
    Player(sf2d_texture *text,int xPos,float yPos,int Height,int Width);
    Player(const Player& orig);
    virtual ~Player();
    void Jump();
    void MoveUD(float newPos);
    void MoveLR(int newPos);

    bool IsJumping() const {
        return jump;
    }

    float GetY() const {
        return y;
    }

    void SetJump(bool jump) {
        this->jump = jump;
    }

    bool IsOnCube() const {
        return OnCube;
    }

    void SetOnCube(bool OnCube) {
        this->OnCube = OnCube;
    }
    bool DrawAndHit(Player*,bool){return false;};
    

    
private:
    bool jump;
    float y;
    bool OnCube;
};

#endif	/* PLAYER_H */

