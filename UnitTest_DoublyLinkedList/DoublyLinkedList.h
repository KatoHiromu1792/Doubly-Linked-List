#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>

/**
* @brief 成績データ
* @details スコアとネーム用の変数を保持する構造体
* @var score
* @var name
*/
struct ScoreData
{
	int score;
	std::string name;
};

/**
* @brief 双方向リストクラス
* @details ノードを保持し、ノード間のつながりを制御するクラス
* @var _head 先頭ポインタ
* @var _tail 末尾ポインタ
* @var _size 要素数
* @fn int size() const
* @return 要素数
* @fn bool insert(ConstIterator pos, const ScoreData& data)
* @return 挿入結果
* @fn bool erase(ConstIterator pos)
* @return 削除結果
* @fn bool clear()
* @return 全要素削除結果
* @fn Iterator getter(int num)
* @return イテレータ
* @fn ConstIterator cbegin() const
* @return 先頭コンストイテレータ
* @fn ConstIterator cend() const
* @return 末尾コンストイテレータ
* @fn Iterator begin()
* @return 先頭イテレータ
* @fn Iterator end()
* @return 末尾イテレータ
*/
class DoublyLinkedList
{
private:
	/**
	* @brief ノード
	* @details 前後のポインタと成績データを保持する構造体
	* @var prev 前ポインタ
	* @var next 次ポインタ
	* @var data 成績データ
	*/
	struct Node;

	Node* _head = nullptr;	// 先頭ポインタ
	Node* _tail = nullptr;	// 末尾ポインタ
	int _size;				// 要素数

public:
	class Iterator;

	/**
	* @brief コンストイテレータ
	* @details 読み取り専用のイテレータ
	* 
	* @fn const ScoreData* operator&()const
	* @return 成績データ
	* @fn const ScoreData* operator&()const
	* @return 成績データのアドレス
	* @fn ConstIterator& operator--()
	* @return コンストイテレータ
	* @fn ConstIterator& operator--(int)
	* @return コンストイテレータ
	* @fn ConstIterator& operator++()
	* @return コンストイテレータ
	* @fn ConstIterator& operator++(int)
	* @return コンストイテレータ
	* @fn ConstIterator(Node* node) : _node(node)
	* @return void
	* @fn ConstIterator& operator=(const Iterator& other)
	* @return コンストイテレータ
	* @fn bool operator==(const ConstIterator& other)const
	* @return 比較結果
	* @fn bool operator!=(const ConstIterator& other)const
	* @return 比較結果
	*/
	class  ConstIterator {
		friend class DoublyLinkedList;
	protected:
		const DoublyLinkedList* _list = nullptr;
		Node* _node = nullptr;

		ConstIterator(const DoublyLinkedList* list,Node* node)
			: _list(list),_node(node){ }
	public:
		ConstIterator() = default;

		// イテレータの指す要素を取得する(const)
		const ScoreData& operator*()const {
			return _node->data;
		}

		// イテレータの指す要素のアドレスを取得する
		const ScoreData* operator&()const {
			assert(!_node);
			return &_node->data;
		}

		// リストの先頭に向かって１つ進める(前置)
		ConstIterator& operator--() {
			if (_node == nullptr) {
				if (_list == nullptr)return *this;
				_node = _list->_tail;
				return *this;
			}
			if (_node->prev == nullptr) {
				_node = nullptr;
				return *this;
			}

			_node = _node->prev;
			return *this;
		}

		// リストの先頭に向かって１つ進める(後置)
		ConstIterator& operator--(int) {
			ConstIterator tmp = *this;
			--(*this);
			return tmp;
		}

		// リストの末尾に向かって１つ進める（前置）
		ConstIterator& operator++() {
			if (_node == nullptr) {
				return *this;
			}
			if (_node->next == nullptr) {
				_node = nullptr;
				return *this;
			}
			_node = _node->next;// 次のノードへ
			return *this;
		};

		// リストの末尾に向かって１つ進める（後置）
		ConstIterator& operator++(int) {
			ConstIterator tmp = *this;
			++(*this);
			return tmp;
		};

		// コピーを行う（コピーコンストラクタ）
		ConstIterator(Node* node) : _node(node) {}

		// 代入を行う
		ConstIterator& operator=(const Iterator& other) {
			_node = other._node;
			return *this;
		}

		// 同一か比較する
		bool operator==(const ConstIterator& other)const {
			return _node == other._node;
		}

		// 異なるか比較する
		bool operator!=(const ConstIterator& other)const {
			return _node != other._node;
		}

	};

	/**
	* @brief イテレータクラス
	* @details コンストイテレータクラスを継承
	* @fn ScoreData& operator*()const
	* @return 成績データ
	* @fn ScoreData* operator&()const
	* @return 成績データ
	*/
	

public:
	~DoublyLinkedList();

	// 要素数を返す
	int size() const;

	// データの挿入
	bool insert(ConstIterator pos, const ScoreData& data);

	// データの削除
	bool erase(ConstIterator pos);

	// 全要素削除
	bool clear();

	Iterator getter(int num) {
		Iterator it = this->begin();
		while (num > 0) { ++it; --num; }
		while (num < 0) { --it; ++num; }
		return it;
	}

	ConstIterator cbegin() const{ return ConstIterator(this,_head); }
	ConstIterator cend() const{ return ConstIterator(this,nullptr); }

	Iterator begin() { return Iterator(this, _head); }
	Iterator end() { return Iterator(this, nullptr); }

	// ID:2 リスト末尾への挿入が失敗した際の戻り値
	// 挿入に失敗させる条件として指定された名前であった場合にfalseを返す
	bool CheckData(const ScoreData& data) {
		if (data.name == "xxx") return false;
		return true;
	}

	bool LoadFile(const char* filePath)
	{
		std::ifstream scoreFile(filePath);// ファイルを開く
		if (!scoreFile) {
			std::cout << filePath << "ファイルを開くことができませんでした\n";
			return false;
		}
		else {
			std::cout << filePath << "ファイルを開きました\n";
		}

		std::string line;
		while (std::getline(scoreFile, line))
		{

			Node* newNode = new(std::nothrow)Node{nullptr,nullptr,ScoreData()};

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

			newNode->data.score = score;// スコアを設定
			newNode->data.name = name;	// 名前を設定

			if (_head == nullptr || _tail == nullptr) 
			{
				_head = _tail = newNode;
			}
			else
			{
				_tail->next = newNode;	// 末尾ノードの次のノードを設定
				newNode->prev = _tail;	// 新しいノードの前のノードを設定
				_tail = newNode;	// 末尾ノードを更新
			}
		}

		scoreFile.close();// ファイルを閉じる

		return true;
	}
};

#include "DoublyLinkedList.inl"