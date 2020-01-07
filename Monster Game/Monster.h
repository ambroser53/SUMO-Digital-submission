using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include "Move.h"

//Move const allMoves

enum ELEMENT {FIRE = "Fire",WATER = "Water",GRASS = "Grass",ELECTRIC = "Electric"};

#ifndef Monster

/** This is the base class for all monsters, 
 *  containing the stats every monster has
 *  
 */
class Monster {
public:
        //basic name only constructor
	Monster(string);
        
        //overloaded every stat constructor
        Monster(string name, int attack, int defense, int speed, int lvl, 
            int exp, ELEMENT e, Move m1 = NULL, Move m2 = NULL, Move m3 = NULL);
       
	//getter functions
	string getMonsterName() const { return monsterName; };

	int getStatAttack() const { return statAttack; };

	int getStatSpeed() const { return statSpeed; };

	int getStatDefense() const { return statDefense; };

	int getStatLevel() const { return statLevel; };

	ELEMENT getElement() const { return monsterElement; }

	void teachMove(Move);
		//@params Move object being taught to the monster
		//if the monster already has 3 moves it will call a function 
		//that asks the player which they would like to remove if any
        
	///Mutator Functions
	void setStatAttack(int);

	void setStatSpeed(int);

	void setStatDefense(int);

	void setStatLevel(int);
        
        //this would only be called when creating a monster from save game
        void setStatEXP(int);

	void incrementEXP(Monster);
		//incrementEXP is passed the defeated monster and sets the new EXP of this monster, 
		//if ExpThreshold is reached the Monster's Level increases and EXP is reset to zero

	//~Monster();

protected:
	string monsterName;
	//an attack does damage: (attacker.attack*moveAttack)/defender.defense
	int statAttack;
	int statDefense;
	//whichever monster has higher speed goes first
	int statSpeed;
	int statLevel;
	//exp will increment after each battle by 1 for each level of defeated monster
	int EXP;
	//the ExpThreshold is always twice the monsters Level, therefore to level up 
	//a monster must beat two monsters the same level as it or equivalent
	int ExpThreshold = statLevel*2;
	ELEMENT const monsterElement;

	vector<Move> currentMoves;
        
private:
        ///takes in the new move the monster could potentially want to learn
        ///will forget the one the player doesn't want
        void replaceMove(Move);
        
        /**takes in the 3 moves it already knows and the new move it wants to learn
         * then lets the player decide which one the monster will forget
         *  @param oldMove1
         *  @param oldMove1
         *  @param oldMove1
         *  @param newMove the new move to potentially learn
         *  @return moveToForget the move the player wants to forget (could be new move)
         */
        Move chooseMove(Move,Move,Move,Move);
};

#endif // !Monster
