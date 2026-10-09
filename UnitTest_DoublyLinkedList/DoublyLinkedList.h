#pragma once
#include <string>
#include <iostream>
#include <assert.h>

/**
* @brief 双方向リストクラス
*/
template<typename T>
class DoublyLinkedList
{
private:
	/**
	* @brief ノード
	* 
	* 前後のポインタと成績データを保持する構造体
	*/
	struct Node
	{
		Node* prev;	// 前ポインタ
		Node* next;	// 次ポインタ
		T data;		// 成績データ
	};

	/**
	* @brief ソートの順序
	* 
	* ソートをする際に昇順・降順を指定するための列挙型
	*/
	enum class SortOrder
	{
		Ascending,	// 昇順
		Descending,	// 降順
	};

	/**
	* @brief ソート対象
	* 
	* ソートをする対象を指定するための列挙型
	*/
	enum class SortKey
	{
		Score,	// スコア
		Name,	// ユーザー名
		Both,	// スコアとユーザー名の両方が対象
	};

private:
	Node* _sentinel = nullptr;	// 番兵ノード
	int _size = 0;				// 要素数

public:
	DoublyLinkedList();
	DoublyLinkedList(const DoublyLinkedList&) = delete;
	~DoublyLinkedList();
	DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

	class Iterator;
/**
* @brief コンストイテレータ
* 
* 読み取り専用のイテレータ
*/
	class  ConstIterator {
		friend class DoublyLinkedList<T>;
	protected:
		const DoublyLinkedList<T>* _list = nullptr;
		Node* _node = nullptr;

		ConstIterator(const DoublyLinkedList<T>* list, Node* node)
			: _list(list), _node(node) {
		}
	public:
		/**
		* @brief デフォルトコンストラクタ
		*/
		ConstIterator() = default;

		/**
		* @brief デフォルトデストラクタ
		*/
		virtual ~ConstIterator() = default;

		/**
		* @brief イテレータの指定する位置の要素を取得する(const)
		*
		* @retval data 指定位置のノードの要素を返す
		*/
		const T& operator*()const;

		/**
		* @brief リストの先頭に向かってイテレータを１つ進める(前置)
		*
		* @retval ConstIterator 前ノードのコンストイテレータを返す
		*/
		ConstIterator& operator--();

		/**
		* @brief リストの先頭に向かってイテレータを１つ進める(後置)
		*
		* @retval ConstIterator	 呼び出したコンストイテレータのコンストイテレータを返す
		*/
		ConstIterator operator--(int);

		/**
		* @brief リストの末尾に向かってイテレータを１つ進める(前置)
		*
		* @retval ConstIterator 次ノードのコンストイテレータを返す
		*/
		ConstIterator& operator++();

		/**
		* @brief リストの末尾に向かってイテレータを１つ進める(後置)
		*
		* @retval ConstIterator	 呼び出したコンストイテレータのコンストイテレータを返す
		*/
		ConstIterator operator++(int);

		/**
		* @brief コピーを行う(引数付きコンストラクタ)
		*
		* @param[in] node	コピー元のノード
		*/
		ConstIterator(Node* node) : _node(node) {}

		/**
		* @brief イテレータの代入をする
		*
		* @param[in] other			代入するイテレータ
		*
		* @retval ConstIterator		代入されたイテレータ
		*/
		ConstIterator& operator=(const Iterator& other);

		/**
		* @brief イテレータ同士が同一か比較する
		*
		* @param[in] other		比較対象のイテレータ
		*
		* @retval true			同一のイテレータであるため成功
		* @retval false			同一のイテレータでないため失敗
		*/
		bool operator==(const ConstIterator& other)const;

		/**
		* @brief イテレータ同士が異なるか比較する
		*
		* @param[in] other		比較対象のイテレータ
		*
		* @retval true			異なるイテレータであるため成功
		* @retval false			異なるイテレータでないため失敗
		*/
		bool operator!=(const ConstIterator& other)const;
	};

	/**
	* @brief イテレータクラス
	* @details コンストイテレータクラスを継承
	*/
	class Iterator : public ConstIterator
	{
		friend class DoublyLinkedList<T>;
		Iterator(const DoublyLinkedList<T>* list, Node* node)
			: ConstIterator(list, node) {
		}
	public:
		/**
		* @brief デフォルトコンストラクタ
		*/
		Iterator() = default;

		/**
		* @brief デフォルトデストラクタ
		*/
		~Iterator() = default;

		/**
		* @brief イテレータの指定する位置の要素を返す(非const)
		* 
		* @retval T ノード内にあるdataを返す
		*/
		T& operator*()const;

		/**
		* @brief リストの先頭に向かってイテレータを１つ進める(前置)
		*
		* @retval Iterator 前ノードのイテレータを返す
		*/
		Iterator& operator--();

		/**
		* @brief リストの先頭に向かってイテレータを１つ進める(後置)
		*
		* @retval Iterator 呼び出したイテレータのイテレータを返す
		*/
		Iterator operator--(int);

		/**
		* @brief リストの末尾に向かってイテレータを１つ進める(前置)
		*
		* @retval Iterator 次ノードのイテレータを返す
		*/
		Iterator operator++();

		/**
		* @brief リストの末尾に向かってイテレータを１つ進める(後置)
		*
		* @retval Iterator 呼び出したイテレータのイテレータを返す
		*/
		Iterator operator++(int);

	};

public:
	/**
	* @brief リスト内の要素数を返す
	* 
	* @retval _size 要素数
	*/
	int size() const { return _size; }

	/**
	* @brief 指定位置に要素を挿入する
	* 
	* @param[in] pos	挿入する位置を指定するイテレータ
	* @param[in] data	挿入する要素
	* 
	* @retval true		挿入に成功
	* @retval false		無効なイテレータを指定して失敗
	*/
	bool insert(const ConstIterator& pos, const T& data);

	/**
	* @brief 指定位置の要素を削除する
	* 
	* @param[in] pos	挿入する位置を指定するイテレータ
	* 
	* @retval true		削除に成功
	* @retval false		無効なイテレータを指定して失敗
	*/
	bool erase(const ConstIterator& pos);

	/**
	* @brief リスト内の全ての要素を削除する
	* 
	* @retval true		全ての要素の削除に成功
	* @retval false		リスト内に要素がないため失敗
	*/
	bool clear();
	
	/**
	* @brief 先頭のコンストイテレータを返す
	* 
	* @retval _sentinel->next	参照のみの番兵ノードの次ノードのイテレータを返す
	*/
	ConstIterator cbegin() const;

	/**
	* @brief 末尾のコンストイテレータを返す
	* 
	* @retval _sentinel		番兵ノードのイテレータを返す
	*/
	ConstIterator cend() const;

	/**
	* @brief 先頭のイテレータを返す
	*
	* @retval _sentinel->next	番兵ノードの次ノードのイテレータを返す
	*/
	Iterator begin();

	/**
	* @brief 末尾のイテレータを返す
	*
	* @retval _sentinel		番兵ノードのイテレータを返す
	*/
	Iterator end();

	/**
	* @brief クイックソートを行う関数
	* 
	* @param[in] order	ソート順を指定
	* @param[in] key	ソート対象を指定
	* 
	* @retval true		クイックソートが成功
	* @retval false		リスト内の要素数が１以下でソート失敗
	*/
	void QuickSort(SortOrder order, SortKey key);
};

#include "DoublyLinkedList.inl"