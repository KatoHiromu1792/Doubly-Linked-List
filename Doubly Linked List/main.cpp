#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define SCORE_FILE_PATH ("Scores.txt")


typedef struct a_List
{
	typedef struct Score
	{
		int score;
	};

	typedef struct ID
	{
		std::string name;
	};

	Score score;	// スコア
	ID id;	// 名前 
	a_List* next = nullptr;	// 次の要素へのポインタ
	a_List* prev = nullptr;	// 前の要素へのポインタ
}list;

int main()
{
	std::ifstream scoreFile(SCORE_FILE_PATH);// ファイルを開く
	if (!scoreFile) {
		std::cout << SCORE_FILE_PATH <<"ファイルを開くことができませんでした\n";
		return 0;
	}
	else {
		std::cout << SCORE_FILE_PATH << "ファイルを開きました\n";
	}

	list* list_head = nullptr;	// リストの先頭を指すポインタ
	list* list_tail = nullptr;	// リストの末尾を指すポインタ

	std::string line;
	while (std::getline(scoreFile, line)) 
	{
		list* new_node = new list;	// 新しいノードを作成

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

		new_node->score.score = score;// スコアを設定
		new_node->id.name = name;	// 名前を設定

		if(list_head != nullptr && list_tail != nullptr)
		{
			list_tail->next = new_node;	// 末尾ノードの次のノードを設定
			new_node->prev = list_tail;	// 新しいノードの前のノードを設定
			list_tail = new_node;	// 末尾ノードを更新
		}
		else if(list_head == nullptr || list_tail == nullptr)
		{
			if(list_head == nullptr)
			{
				list_head = new_node;
			}
			if(list_tail == nullptr)
			{
				list_tail = new_node;
			}
		}
	}

	scoreFile.close();// ファイルを閉じる

	list* current_node = list_head;	// 現在のノードをリストの先頭に設定
	// リストの内容を表示
	while (true)
	{
		if(current_node == nullptr)
		{
			break;
		}
		std::cout << current_node->score.score << "　" << current_node->id.name << "\n";
		current_node = current_node->next;	// 次のノードに移動
	}

	//std::cout << "\n";

	//current_node = list_tail;	// 現在のノードをリストの末尾に設定
	//while (true)
	//{
	//	if (current_node == nullptr)
	//	{
	//		break;
	//	}
	//	std::cout << current_node->score << "\n";
	//	current_node = current_node->prev;	// 次のノードに移動
	//}

	return 0;
}