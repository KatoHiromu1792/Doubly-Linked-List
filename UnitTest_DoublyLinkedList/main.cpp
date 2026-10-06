#include <iostream>
#include "DoublyLinkedList.h"

#define SCORE_FILE_PATH ("Scores.txt")

bool LoadFile(DoublyLinkedList* list,const char* filePath);

int main()
{
	DoublyLinkedList list{};
	LoadFile(&list,SCORE_FILE_PATH);

	DoublyLinkedList::Iterator it = list.begin();
	while (it.hasNest())
	{
		std::cout << it.operator*().score << "  ";
		std::cout << it.operator*().name << "\n";
		++it;
	}

	return 0;
}

bool LoadFile(DoublyLinkedList* list,const char* filePath)
{
	std::ifstream scoreFile(filePath);// ファイルを開く
	if (!scoreFile) {
		std::cout << filePath << "Failed to open the file\n";
		return false;
	}
	else {
		std::cout << filePath << "File opened successfully\n";
	}

	std::string line;
	while (std::getline(scoreFile, line))
	{
		std::stringstream ss(line); // 行を文字列ストリームに変換
		std::string word;

		std::string sScore;
		std::string name;
		int i = 0;
		int score;
		while (ss >> word) {	// 空白区切りで単語取得
			if (i == 0)
			{
				sScore = word;
			}
			else {
				name = word;
			}
			i++;
		}

		score = std::stoi(sScore);

		// スコアと名前をinsertで追加
		list->insert(list->end(), ScoreData(score, name));
	}

	scoreFile.close();// ファイルを閉じる

	return true;
}