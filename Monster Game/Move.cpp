using namespace std;
#include <iostream>
#include "Move.h"

//constructor for a Move object
Move::Move(string name, int attack, int accuracy, ELEMENT element) {
	string moveName = name;
	int moveAttack = attack;
	int moveAccuracy = accuracy;
	ELEMENT moveElement = element;
}

void Move::printMoveInfo(){
        cout << getMoveName() << ".\n"
             << "Element: " << getMoveElement() << "\n"
             << "Attack: " << getMoveAttack() << "\n"
             << "Accuracy: " << getMoveAccuracy() << "\n";
}
