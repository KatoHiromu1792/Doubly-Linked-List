#include <iostream>
#include "DoublyLinkedList.h"

#define SCORE_FILE_PATH ("Scores.txt")

int main()
{
	DoublyLinkedList list{};
	list.LoadFile(SCORE_FILE_PATH);

	DoublyLinkedList::Iterator it = list.begin();
	while (it.hasNest())
	{
		std::cout << it.operator*().score << "  ";
		std::cout << it.operator*().name << "\n";
		++it;
	}

	return 0;
}