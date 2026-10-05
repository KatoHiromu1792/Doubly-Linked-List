#pragma once
#include <string>

// 成績データ
struct ScoreData
{
	int score;			// スコア
	std::string name;	// ユーザー名
};

// === 双方向リスト ===
class DoublyLinkedList
{
public:
	// ノード
	struct Node
	{
		Node* prev;			// 前のポインタ
		Node* next;			// 次のポインタ
		ScoreData data{};	// 成績データ
	};

private:
	Node* _head;// 先頭ポインタ
	Node* _tail;// 末尾ポインタ
	int _size;// 要素数

public:
	//DoublyLinkedList() : _head(nullptr), _tail(nullptr) {}

	class Iterator;

	class  Const_Iterator {
		friend class DoublyLinkedList;
	protected:
		const DoublyLinkedList* _list = nullptr;
		Node* _node = nullptr;

		Const_Iterator(const DoublyLinkedList* list,Node* node)
			: _list(list),_node(node){ }
	public:
		Const_Iterator() = default;

		// イテレータの指す要素を取得する(const)
		const Node& operator*()const { return *_node; }

		// イテレータの指す要素のアドレスを取得する
		const Node* operator&()const { return _node; }

		// リストの先頭に向かって１つ進める(前置)
		Const_Iterator& operator--() {
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
		Const_Iterator& operator--(int) {
			Const_Iterator tmp = *this;
			--(*this);
			return tmp;
		}

		// リストの末尾に向かって１つ進める（前置）
		Const_Iterator& operator++() {
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
		Const_Iterator& operator++(int) {
			Const_Iterator tmp = *this;
			++(*this);
			return tmp;
		};

		// コピーを行う（コピーコンストラクタ）
		Const_Iterator(Node* node) : _node(node) {}

		// 代入を行う
		Const_Iterator& operator=(const Iterator& other) {
			_node = other._node;
			return *this;
		}

		// 同一か比較する
		bool operator==(const Const_Iterator& other)const {
			return _node == other._node;
		}

		// 異なるか比較する
		bool operator!=(const Const_Iterator& other)const {
			return _node != other._node;
		}

	};

	//=======================================================
	// Iteratorクラス
	// 継承：Const_Iterator
	//=======================================================
	class Iterator : public Const_Iterator
	{
		friend class DoublyLinkedList;
		Iterator(const DoublyLinkedList* list, Node* node)
			: Const_Iterator(list,node){}
	public:
		Iterator() = default;

		// イテレータの指す要素を取得する(非const)
		Node& operator*()const { return *_node; }

		// イテレータの指す要素のアドレスを取得する
		Node* operator&()const { return _node; }
	};
	//{
	//	friend class DoublyLinkedList;
	//	Iterator(DoublyLinkedList* list,Node* node):Const_Iterator(list,node){}
	//public:
	//	Iterator() = default;

	//	/*T& operator*() const{ return this->operator*; }
	//	T* operator->()const { return &this->_node->value; }*/

	//	/*const T& operater* ()const {
	//		return this->_node->value;
	//	}*/
	//	Iterator& operater++() {
	//		Const_Iterator::operator++();
	//		return *this;
	//	}

	//	Iterator& operator--() {
	//		Const_Iterator::operator--();
	//		return *this;
	//	}
	//};

public:
	// 要素数を返す
	int size() const { return _size; }

	// データを末尾に挿入
	bool push_back(const ScoreData& data) {
		if (!CheckData(data))return false;

		Node* n = new(std::nothrow) Node{_tail,nullptr,data};

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

	// データを先頭に挿入
	bool push_front(const ScoreData& data) {
		if (!CheckData(data))return false;

		Node* n = new(std::nothrow) Node{ nullptr,_head,data };

		if (!_head) {
			_head = _tail = n;
		}
		else {
			_head->prev = n;
			n->next = _head;
			_head = n;
		}
		++_size;

		return true;
	}

	// データの挿入
	bool insert(Const_Iterator pos, const ScoreData& data) {

		if (!CheckData(data)) return false;

		Node* next = pos._node;
		Node* prev = next ? next->prev : _tail;
		Node* n = new(std::nothrow) Node{prev,next,data};

		if (!next) { // end()への挿入→push_backと同じ
			push_back(data);
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
	bool erase(Const_Iterator pos) {
		if (pos._node == nullptr)return false;
		Node* curr = pos._node;
		if (!curr) {
			return false;
		}

		Node* p = curr->prev;
		Node* n = curr->next;

		if (p) p->next = n;
		else _head = n;	// 先頭を削除

		if (n)n->prev = p;
		else _tail = p; // 末尾を削除

		delete curr;
		--_size;

		return true;
	}

	Iterator getter(int num) {
		Iterator it = this->begin();
		while (num > 0) { ++it; --num; }
		while (num < 0) { --it; ++num; }
		return it;
	}

	Const_Iterator cbegin() const{ return Const_Iterator(this,_head); }
	Const_Iterator cend() const{ return Const_Iterator(this,nullptr); }

	Iterator begin() { return Iterator(this, _head); }
	Iterator end() { return Iterator(this, nullptr); }

	// ID:2 リスト末尾への挿入が失敗した際の戻り値
	// 挿入に失敗させる条件として指定された名前であった場合にfalseを返す
	bool CheckData(const ScoreData& data) {
		if (data.name == "xxx") return false;
		return true;
	}

	// ID:3,4 データの挿入
	// 挿入先のポインタがリスト内に存在するかを判定
	//bool ContainsPointer(Iterator it)
	//{
	//	// リストが違うorノードがnullptrの場合もfalseを返す
	//	if (it._list != this || it._node == nullptr) return false;

	//	return true;
	//}
};

