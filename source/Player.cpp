/* 
 * File:   Player.cpp
 * Author: Silvermoon
 * 
 * Created on 3 octobre 2015, 12:56
 */

#include "Player.h"

Player::Player() {
}
Player::Player(sf2d_texture *text,int xPos,float yPos,int Height,int Width) : Block(text,xPos,0,Height,Width){
    y=yPos;
}

Player::Player(const Player& orig) {
}

Player::~Player() {
}

void Player::Jump(){
    jump=true;
}

void Player::MoveUD(float newPos){
    y=newPos;
}
void Player::MoveLR(int newPos){
    x=newPos;
}