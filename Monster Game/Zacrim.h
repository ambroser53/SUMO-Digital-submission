
/* 
 * File:   Zacrim.h
 * Author: Ambrose Robinson
 *
 * Sub-class of Monster as it is a species of monster
 */

#ifndef ZACRIM_H
#define ZACRIM_H

#include "Monster.h"

class Zacrim : public Monster {
public:
        Zacrim(string name, int attack, int defense, int speed, int lvl, 
            int exp, Move m1, Move m2, Move m3);
        Zacrim(int lvl);
        ~Zacrim();
private:

};

#endif /* ZACRIM_H */

