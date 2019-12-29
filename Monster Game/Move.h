using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include "Monster.cpp"

//Move const allMoves

//TODO moves that don't do damage but temporarily lower the opponents/
//raise current monsters attack/defense/speed etc

#ifndef Move

class Move
{
public:
	string getMoveName() const { return moveName; };
	int getMoveAttack() const { return moveAttack; };
	int getMoveAccuracy() const { return moveAccuracy; };
	ELEMENT getMoveElement() const { return moveElement; };
        void printMoveInfo();
	//~Move();
private:
	Move(string, int, int, ELEMENT);
	string moveName;
	int moveAttack;
	int moveAccuracy;
	ELEMENT moveElement;
};

#endif // !Move

//OVERRIDING equality operator for moves
bool operator == (const Move &L, const Move &R)
{
    return(L.getMoveName() == R.getMoveName());
}