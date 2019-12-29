using namespace std;
#include <iostream>
#include <string>
#include "Monster.cpp"

#ifndef Party 

const int CAPACITY = 3;

class Party {
public:
	//constructor for empty party
	Party();
	//constructor for partial-to-full parties
	Party(Monster);
	Party(Monster,Monster);
	Party(Monster,Monster,Monster);

	//These methods return a bool if 
	//the monster was successfully added/removed
	bool addMonsterToParty(Monster);
	bool removeMonsterFromParty(Monster);
	Monster getMonsterAtPos(int);
	int getSize();
	bool isFull();
	bool isEmpty();

private:
	int size;
	Monster partyList[CAPACITY];
};

#endif // !Party