using namespace std;
#include <iostream>
#include "Party.h"

Party::Party()
{
	size = 0;
}

Party::Party(Monster mon)
{
	partyList[0] = mon;
	size = 1;
}

Party::Party(Monster mon1, Monster mon2)
{
	partyList[0] = mon1;
	partyList[1] = mon2;
}

Party::Party(Monster mon1, Monster mon2, Monster mon3)
{
	partyList[0] = mon1;
	partyList[1] = mon2;
	partyList[2] = mon3;
	size = 3;
}

bool Party::addMonsterToParty(Monster newMonster) {
	partyList
}

//returns true if the monster was successfully removed
bool Party::removeMonsterFromParty(Monster oldMonster)
{
	int foundPos = -1;
	for (int i = 0; i < size; i++) {
		if (partyList[i] == oldMonster) {
			foundPos = i;
		}
	}
	//need to shift all elements along to the front if 
	//the monster was in front of another monster
	if ((foundPos != -1) && (foundPos != size - 1)) {
		for (int j = foundPos; j < size; j++) {
			partyList[j] = partyList[j + 1];
		}
		return true;
	}
	//otherwise just return true that its been deleted
	else if (foundPos != -1) {
		return true;
	}
	else {
		return false;
	}
}

Monster Party::getMonsterAtPos(int i)
{
	return partyList[i];
}

int Party::getSize()
{
	return size;
}

bool Party::isFull()
{
	return (size==3);
}

bool Party::isEmpty()
{
	return (size==0);
}
