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
private:
	// ノード
	struct Node
	{
		Node* prev;			// 前のポインタ
		Node* next;			// 次のポインタ
		ScoreData data{};	// 成績データ
	};

	Node* _head = nullptr;// 先頭ポインタ
	Node* _tail = nullptr;// 末尾ポインタ
	Node* _dummy = nullptr ;// ダミーポインタ
	int _size;// 要素数

public:
	//DoublyLinkedList() : _head(nullptr), _tail(nullptr) {}

	class Iterator;

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
		const ScoreData& operator*()const { return _node->data; }

		// イテレータの指す要素のアドレスを取得する
		const ScoreData* operator&()const { return &_node->data; }

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

	//=======================================================
	// Iteratorクラス
	// 継承：ConstIterator
	//=======================================================
	class Iterator : public ConstIterator
	{
		friend class DoublyLinkedList;
		Iterator(const DoublyLinkedList* list, Node* node)
			: ConstIterator(list,node){}
	public:
		Iterator() = default;

		// イテレータの指す要素を取得する(非const)
		ScoreData& operator*()const { return _node->data; }

		// イテレータの指す要素のアドレスを取得する
		ScoreData* operator&()const { return &_node->data; }
	};

public:
	// 要素数を返す
	int size() const { return _size; }

	// データの挿入
	bool insert(ConstIterator pos, const ScoreData& data) {

		if (!CheckData(data)) return false;

		Node* next = pos._node;
		Node* prev = next ? next->prev : _tail;
		Node* n = new(std::nothrow) Node{prev,next,data};

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
	bool erase(ConstIterator pos) {
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

	// ID:3,4 データの挿入
	// 挿入先のポインタがリスト内に存在するかを判定
	//bool ContainsPointer(Iterator it)
	//{
	//	// リストが違うorノードがnullptrの場合もfalseを返す
	//	if (it._list != this || it._node == nullptr) return false;

	//	return true;
	//}
};

