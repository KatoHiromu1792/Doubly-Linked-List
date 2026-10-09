#include <iostream>
#include <fstream>
#include <sstream>
#include "DoublyLinkedList.h"

#define SCORE_FILE_PATH ("Scores.txt")

/**
* @brief 成績データ
*
* スコアとネーム用の変数を保持する構造体
*/
struct ScoreData
{
	int score = 0;			// スコア
	std::string name = "";	// ユーザー名
};

template<typename T>
bool LoadFile(DoublyLinkedList<T>* list, const char* filePath);

int main()
{
	DoublyLinkedList<ScoreData> list{};
	LoadFile(&list, SCORE_FILE_PATH);

	DoublyLinkedList<ScoreData>::Iterator it = list.begin();
	while (it != list.end())
	{
		std::cout << it.operator*().score << "  ";
		std::cout << it.operator*().name << "\n";
		++it;
	}

	return 0;
}

template<typename T>
bool LoadFile(DoublyLinkedList<T> *list, const char* filePath)
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