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
template <typename T>
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
	struct Node {
		Node* prev;			// 前のポインタ
		Node* next;			// 次のポインタ
		T data{};			// 成績データ
	};

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
		const ScoreData& operator*()const;

		// イテレータの指す要素のアドレスを取得する
		const ScoreData* operator&()const;

		// リストの先頭に向かって１つ進める(前置)
		ConstIterator& operator--();

		// リストの先頭に向かって１つ進める(後置)
		ConstIterator& operator--(int);

		// リストの末尾に向かって１つ進める（前置）
		ConstIterator& operator++();

		// リストの末尾に向かって１つ進める（後置）
		ConstIterator& operator++(int);

		// コピーを行う（コピーコンストラクタ）
		ConstIterator(Node* node) : _node(node) {}

		// 代入を行う
		ConstIterator& operator=(const Iterator& other);

		// 同一か比較する
		bool operator==(const ConstIterator& other)const;

		// 異なるか比較する
		bool operator!=(const ConstIterator& other)const;
	};

	/**
	* @brief イテレータクラス
	* @details コンストイテレータクラスを継承
	* @fn ScoreData& operator*()const
	* @return 成績データ
	* @fn ScoreData* operator&()const
	* @return 成績データ
	*/
	class Iterator : public ConstIterator
	{
		friend class DoublyLinkedList;
		Iterator(const DoublyLinkedList* list, Node* node)
			: ConstIterator(list, node) {}

	public:
		Iterator() = default;

		// イテレータの指す要素を取得する(非const)
		ScoreData& operator*()const;

		// イテレータの指す要素のアドレスを取得する
		ScoreData* operator&()const;
	};

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

	// 引数の要素数のイテレータを返す
	Iterator getter(int num);

	ConstIterator cbegin() const{ return ConstIterator(this,_head); }
	ConstIterator cend() const{ return ConstIterator(this,nullptr); }

	Iterator begin() { return Iterator(this, _head); }
	Iterator end() { return Iterator(this, nullptr); }

	// ID:2 リスト末尾への挿入が失敗した際の戻り値
	// 挿入に失敗させる条件として指定された名前であった場合にfalseを返す
	bool CheckData(const ScoreData& data);

	bool LoadFile(const char* filePath);
};

#include "DoublyLinkedList.inl"