#include <vector>

#include "Monster.h"
#include "Move.h"

/// Empty constructor for monster to have stats set later
Monster::Monster(string name) {
        monsterName = name;
}


/// Overloaded constructor for fully set monster
/// I.E from save or from a set new monster
Monster::Monster(string name, int attack, int defense, int speed, int lvl, 
            int exp, ELEMENT e, Move m1, Move m2, Move m3) : monsterElement(e) {
        monsterName = name;
        statAttack = attack;
        statDefense = defense;
	statSpeed = speed;
	statLevel = lvl;
	EXP = exp;

        //TODO? make it so that it takes in an optional vector/list and then assigns
        //them instead
        
        //assign moves if they have been passed
	if (m1 != NULL) {
            currentMoves.at(0) = m1;
        }
        if (m2 != NULL) {
            currentMoves.at(1) = m2;
        }
        if (m3 != NULL) {
            currentMoves.at(2) = m3;
        }
}

void Monster::replaceMove(Move newMove) {
        //TODO change it so that it is only ever iterating through currentMoves
            //for robustness/reusability 
        Move oldMove1 = currentMoves.at(0);
        Move oldMove2 = currentMoves.at(1);
        Move oldMove3 = currentMoves.at(2);
        bool resolved = false;
        while (!resolved) {
            cout << getMonsterName() << " wants to learn the move "
                 << newMove.getMoveName() << "\n" << "However, " << getMonsterName()
                 << " already knows three moves \n" << "Would you like " 
                 << getMonsterName() << " to forget a move?";
            string reply;
            cin >> reply;
            transform(reply.begin(), reply.end(), reply.begin(),
                [](unsigned char c){ return tolower(c); });
            if (reply.substr(0,1) == "y") {
                //let user decide which move to lose
                Move replacement = chooseMove(oldMove1, oldMove2, oldMove3, newMove);
                //if its the new move nothing changes
                if (replacement==newMove) {
                    cout << getMonsterName() << " gave up on learning the move "
                         << newMove.getMoveName();
                }
                else {
                    //otherwise replace the old move with newMove in currentMoves
                    replace(currentMoves.begin(),currentMoves.end(), replacement, newMove);
                }
                resolved = true;
            }
            else if (reply.substr(0,1) == "n") {
                resolved = true;
            }
        }
}

Move Monster::chooseMove(Move oldMove1, Move oldMove2, Move oldMove3, Move newMove) {
        cout << "The current moves are: \n"
             << "1" << oldMove1.getMoveName() << "\n"
             << "2" << oldMove2.getMoveName() << "\n"
             << "3" << oldMove3.getMoveName() << "\n"
             << "Enter a number to replace that move \n"
             << "Or enter 'info moveNumber' (e.g. info 1)"
             << "to find out more about that move \n"
             << "Or enter q to quit and give up on learning " 
             << newMove.getMoveName() << "\n";
        
        string choice;
        cin >> choice;
        while (choice != "q") {
            //TODO check substring 0-3 to see if its info, if so call printMoveInfo
            //on that move other wise have a switch case for each number
        }
        if (choice=="q"){
            return newMove;
        }
}

void Monster::teachMove(Move newMove) {
	if (newMove.getMoveElement() == monsterElement) {
		if (currentMoves.empty()) {
			currentMoves[0] = newMove;
		}
		else if (currentMoves.size()==3) {
			//user decides which move to forget
                        replaceMove(newMove);
		}
		else {
			currentMoves.push_back(newMove);
		}
	}
}

void Monster::setStatAttack(int inpAttack) {
	statAttack = inpAttack;
}

void Monster::setStatSpeed(int inpSpeed) {
	statSpeed = inpSpeed;
}

void Monster::setStatDefense(int inpDefense) {
	statDefense = inpDefense;
}

void Monster::setStatLevel(int inpLevel) {
	statLevel = inpLevel;
}

void Monster::setStatEXP(int inpEXP) {
	EXP = inpEXP;
}

//@param the defeated Monster object and increases the EXP of the current monster
//if ExpThreshold is reached the Monster's Level increases and EXP is reset to zero
//if ExpThreshold is more than reached the remaining EXP goes on to the EXP towards the next level
	//this is in the case where a monster beats a monster many times its level
void Monster::incrementEXP(Monster defeated) {
        int ExpGained = defeated.getStatLevel();
	while (ExpGained > 0) {
		EXP += ExpGained;
		if (EXP == ExpThreshold) {
			statLevel++;
			EXP, ExpGained = 0;
		}
		else if (EXP > ExpThreshold) {
			ExpGained = EXP - ExpThreshold;
			statLevel++;
			EXP = 0;
		}
		else {
			ExpGained = 0;
		}
	}
}