/* 
 * File:   Zacrim.cpp
 * Author: Ambrose Robinson
 * 
 * Created on 07 January 2020, 19:50
 */

#include "Zacrim.h"

///Constructor from a predefined Zacrim monster (e.g. save etc)
Zacrim::Zacrim(string name, int attack, int defense, int speed, int lvl, int exp,
        Move m1, Move m2, Move m3) : Monster(name, attack, defense, speed, lvl,
            exp, ELECTRIC, Move m1 = NULL, Move m2 = NULL, Move m3 = NULL) { }

/**Default constructor with only level argument, name is just Zacrim and stats 
 * are randomly generated according to average for that species at that level
 * USED for when creating a random encounter of this species of monster given the level
 */
Zacrim::Zacrim(int lvl) {
        monsterName = "Zacrim";
        //TODO create random number generators that create Zacrim stats 
        //according to the given level, each level has a pretermined amount of points
        //these generators must distribute these point varying around an average for
        //a zacrim
}

Zacrim::~Zacrim() {
}

