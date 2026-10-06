struct DoublyLinkedList::Node
{
	Node* prev;			// 前のポインタ
	Node* next;			// 次のポインタ
	ScoreData data{};	// 成績データ
};

class DoublyLinkedList::Iterator : public ConstIterator
{
	friend class DoublyLinkedList;
	Iterator(const DoublyLinkedList* list, Node* node)
		: ConstIterator(list, node) {
	}
public:
	Iterator() = default;

	// イテレータの指す要素を取得する(非const)
	ScoreData& operator*()const {
		return _node->data;
	}

	// イテレータの指す要素のアドレスを取得する
	ScoreData* operator&()const {
		assert(!_node);
		return &_node->data;
	}
};

inline DoublyLinkedList::~DoublyLinkedList()
{ 
	this->clear(); 
}

inline int DoublyLinkedList::size()const
{
	return _size;
}

inline bool DoublyLinkedList::insert(
	DoublyLinkedList::ConstIterator pos, const ScoreData& data)
{

	//if (!CheckData(data)) return false;

	Node* next = pos._node;
	Node* prev = next ? next->prev : _tail;
	Node* n = new(std::nothrow) Node{ prev,next,data };

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

inline bool DoublyLinkedList::erase(ConstIterator pos)
{
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

	if (curr) delete curr;
	--_size;

	return true;
}

inline bool DoublyLinkedList::clear()
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

	return true;
}

inline Iterator DoublyLinkedList::getter(int num)
{

}