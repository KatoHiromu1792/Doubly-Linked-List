// イテレータの指す要素を取得する(const)
inline const ScoreData& DoublyLinkedList::ConstIterator::operator*()const {
	return _node->data;
}

// イテレータの指す要素のアドレスを取得する
inline const ScoreData* DoublyLinkedList::ConstIterator::operator&()const {
	assert(!_node);
	return &_node->data;
}

// リストの先頭に向かって１つ進める(前置)
inline DoublyLinkedList::ConstIterator& DoublyLinkedList::ConstIterator::operator--() {
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
inline DoublyLinkedList::ConstIterator& DoublyLinkedList::ConstIterator::operator--(int) {
	ConstIterator tmp = *this;
	--(*this);
	return tmp;
}

// リストの末尾に向かって１つ進める（前置）
inline DoublyLinkedList::ConstIterator& DoublyLinkedList::ConstIterator::operator++() {
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
inline DoublyLinkedList::ConstIterator& DoublyLinkedList::ConstIterator::operator++(int) {
	ConstIterator tmp = *this;
	++(*this);
	return tmp;
};

// 代入を行う
inline DoublyLinkedList::ConstIterator& DoublyLinkedList::ConstIterator::operator=(const Iterator& other) {
	_node = other._node;
	return *this;
}

// 同一か比較する
inline bool DoublyLinkedList::ConstIterator::operator==(const ConstIterator& other)const {
	return _node == other._node;
}

// 異なるか比較する
inline bool DoublyLinkedList::ConstIterator::operator!=(const ConstIterator& other)const {
	return _node != other._node;
}

// イテレータの指す要素を取得する(非const)
inline ScoreData& DoublyLinkedList::Iterator::operator*()const {
	return _node->data;
}

// イテレータの指す要素のアドレスを取得する
inline ScoreData* DoublyLinkedList::Iterator::operator&()const {
	assert(!_node);
	return &_node->data;
}

inline DoublyLinkedList::~DoublyLinkedList()
{ 
	this->clear(); 
}

inline int DoublyLinkedList::size()const
{
	return _size;
}

inline bool DoublyLinkedList::insert(
	ConstIterator pos, const ScoreData& data)
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

inline DoublyLinkedList::Iterator DoublyLinkedList::getter(int num)
{
		Iterator it = this->begin();
		while (num > 0) { ++it; --num; }
		while (num < 0) { --it; ++num; }
		return it;
}

inline bool DoublyLinkedList::CheckData(const ScoreData& data)
{
	if (data.name == "xxx") return false;
	return true;
}

inline bool DoublyLinkedList::LoadFile(const char* filePath)
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

		Node* newNode = new(std::nothrow)Node{ nullptr,nullptr,ScoreData() };

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