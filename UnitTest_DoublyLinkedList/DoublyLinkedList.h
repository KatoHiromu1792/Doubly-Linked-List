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
	int score = 0;
	std::string name = "";
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
	struct Node
	{
		Node* prev;			// 前のポインタ
		Node* next;			// 次のポインタ
		ScoreData data{};	// 成績データ
	};

	Node* _head = nullptr;	// 先頭ポインタ
	Node* _tail = nullptr;	// 末尾ポインタ
	int _size = 0;			// 要素数

public:
	DoublyLinkedList() = default;
	DoublyLinkedList(const DoublyLinkedList&) = delete;
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

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

		ConstIterator(const DoublyLinkedList* list, Node* node)
			: _list(list), _node(node){}
	public:
		ConstIterator() = default;

		// イテレータの指す要素を取得する(const)
		const ScoreData& operator*()const {
			assert(_list != nullptr);
			assert(_node != nullptr);
			return _node->data;
		}

		// リストの先頭に向かって１つ進める(前置)
		ConstIterator& operator--() {
			assert(_list != nullptr);
			if (_node == nullptr)
			{
				assert(_list->_tail != nullptr);
				_node = _list->_tail;
				return *this;
			}
			assert(_node != _list->_head);
			_node = _node->prev;
			return *this;
		}

		// リストの先頭に向かって１つ進める(後置)
		// 後置は値を参照ではなく、値で返す
		ConstIterator operator--(int) {
			ConstIterator tmp = *this;
			--(*this);
			return tmp;
		}

		// リストの末尾に向かって１つ進める（前置）
		ConstIterator& operator++() {
			assert(_list != nullptr);
			assert(_node != nullptr);
			_node = _node->next;// 次のノードへ
			return *this;
		};

		// リストの末尾に向かって１つ進める（後置）
		// 後置は値を参照ではなく、値で返す
		ConstIterator operator++(int) {
			ConstIterator tmp = *this;
			++(*this);
			return tmp;
		};

		// コピーを行う(引数付きコンストラクタ)
		ConstIterator(Node* node) : _node(node) {}

		// 代入を行う
		ConstIterator& operator=(const Iterator& other) {
			_list = other._list;
			_node = other._node;
			return *this;
		}

		// 同一か比較する
		bool operator==(const ConstIterator& other)const {
			return _list == other._list && _node == other._node;
		}

		// 異なるか比較する
		bool operator!=(const ConstIterator& other)const {
			return _list != other._list || _node != other._node;
		}

	};

	/**
	* @brief イテレータクラス
	* @details コンストイテレータクラスを継承
	* @fn ScoreData& operator*()const
	* @return 成績データ
	* @fn ScoreData* operator&()const
	* @return 成績データ
	* @fn bool hasNest()
	* @return 次ポインタの有無
	*/
	class Iterator : public ConstIterator
	{
		friend class DoublyLinkedList;
		Iterator(const DoublyLinkedList* list, Node* node)
			: ConstIterator(list, node){}
	public:
		Iterator() = default;
		

		// イテレータの指す要素を取得する(非const)
		ScoreData& operator*()const {
			assert(_list != nullptr);
			assert(_node != nullptr);
			return _node->data; 
		}

		// リストの先頭に向かって１つ進める(前置)
		Iterator& operator--()
		{
			assert(_list != nullptr);
			if (_node == nullptr)
			{
				assert(_list->_tail != nullptr);
				_node = _list->_tail;
				return *this;
			}
			assert(_node != _list->_head);
			_node = _node->prev;
			return *this;
		}

		// リストの先頭に向かって１つ進める(後置)
		Iterator operator--(int)
		{
			Iterator tmp = *this;
			--(*this);
			return tmp;
		}

		// リストの末尾に向かって１つ進める(前置)
		Iterator& operator++()
		{
			assert(_list != nullptr);
			assert(_node != nullptr);
			_node = _node->next;// 次のノードへ
			return *this;
		}

		// リストの末尾に向かって１つ進める(後置)
		Iterator operator++(int)
		{
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		// 次の要素があるか
		bool hasNest()
		{
			if (!_node->next) return false;

			return true;
		}
	};

public:
	~DoublyLinkedList() { this->clear(); }

	// 要素数を返す
	int size() const { return _size; }

	// データの挿入
	bool insert(const ConstIterator& pos, const ScoreData& data) {

		if (pos._list != this)return false;

		Node* next = pos._node;
		Node* prev = next ? next->prev : _tail;
		Node* n = new(std::nothrow) Node{prev,next,data};

		if (n == nullptr)return false;

		if (!next) { // end()への挿入→push_backと同じ
			if (!_head) {
				_head = _tail = n;
			}
			else {
				_tail->next = n;
				n->prev = _tail;
				_tail = n;
			}
			++_size;

			return true;
		}

		Node* p = next->prev;

		n->next = next;
		n->prev = p;

		if (p)p->next = n;
		else _head = n; // 先頭に挿入

		next->prev = n;

		++_size;

		return true;
	}

	// データの削除
	bool erase(const ConstIterator& pos) {

		if (pos._list != this)return false;
		Node* curr = pos._node;

		if (!curr) {
			if (curr) delete curr;
			return false;
		}

		Node* prev = curr->prev;
		Node* next = curr->next;

		if (prev) {
			prev->next = next;
		} 
		else _head = next;	// 先頭を削除

		if (next) {
			next->prev = prev;
		}
		else _tail = prev; // 末尾を削除

		if(curr) delete curr;
		--_size;

		return true;
	}

	// 全要素削除
	bool clear()
	{
		Node* curr = _head;
		if (!curr)return false;

		while (curr)
		{
			Node* next = curr->next;
			delete curr;
			curr = next;
		}
		_head = _tail = nullptr;

		_size = 0;

		return true;
	}

	ConstIterator cbegin() const{ return ConstIterator(this,_head); }
	ConstIterator cend() const{ return ConstIterator(this,nullptr); }

	Iterator begin() { return Iterator(this, _head); }
	Iterator end() { return Iterator(this, nullptr); }
};

