#include "pch.h"
#include "List_ManualTest.h"
#include "DoublyLinkedList.h"

namespace ex01_DataStructure
{
	namespace chapter2
	{
		// -----------------------------------------------
		// コンパイル関連手動テスト
		// -----------------------------------------------

		namespace list
		{
			// ID:08
			TEST(GetDataNumTest, ID08_TestGetDataNumWhenConst)
			{
#if defined TT_TEST_GET_DATA_NUM_WHEN_CONST
				const DoublyLinkedList list{};
				EXPECT_EQ(0, list.size());
#endif
				SUCCEED();
			}

			// ID:15
			TEST(ListManualTest, ID15_TestInsertWhenConst)
			{
	#if defined TT_TEST_INSERT_WHEN_CONST
				const DoublyLinkedList list{};
				DoublyLinkedList::ConstIterator it = list.cbegin();
				//list.insert(it, 1);//コンパイラエラー
	#endif
				SUCCEED();
			}

			// ID:22
			TEST(EraseTest, ID22_TestEraseWhenConst)
			{
	#if defined TT_TEST_ERASE_WHEN_CONST
				const DoublyLinkedList list{};
				DoublyLinkedList::ConstIterator it = list.cbegin();
				//list.erase(it); コンパイルエラー
	#endif
				SUCCEED();
			}

			// ID:28
			TEST(GetBeginIterator,ID28_TestGetBeginIteratorWhenConst)
			{
	#if defined TT_TEST_GET_BEGIN_ITERATOR_WHEN_CONST
				const DoublyLinkedList list{};
				//list.begin();// コンパイルエラー
	#endif
				SUCCEED();
			}

			// ID:34
			TEST(GetBeginConstIterator, ID34_TestGetBeginConstIteratorWhenConst)
			{
#if defined TT_TEST_GET_BEGIN_CONSTITERATOR_WHEN_CONST
				const DoublyLinkedList list{};
				list.cbegin();
#endif
				SUCCEED();
			}

			// ID:40
			TEST(GetEndIterator, ID40_TestGetEndIteratorWhenConst)
			{
	#if defined TT_TEST_GET_END_ITERATOR_WHEN_CONST
				const DoublyLinkedList list{};
				//list.end();// コンパイルエラー
	#endif
				SUCCEED();
			}

			// ID:46
			TEST(GetEndConstIterator, ID46_TestGetEndConstIteratorWhenConst)
			{
#if defined TT_TEST_GET_END_CONSTITERATOR_WHEN_CONST
				const DoublyLinkedList list{};
				list.cend();
#endif
				SUCCEED();
			}
		}
		

		namespace iterator
		{
			// ID:02
			TEST(GetTheElementTheIteratorPoints, ID02_ConstIteratorCannotAssignToDereferencedElement)
			{
#if defined TT_TEST_CONSTITERATOR_CANNOT_ASSIGN_DEREFERANCED_ELEMENT
				DoublyLinkedList list{};
				list.insert(ScoreData{ 10,"aaa" });
				auto it = list.cbegin();
				//it.operator*() = ScoreData{ 20,"bbb" };// コンパイルエラー
#endif
				SUCCEED();
			}

			// ID:17
			TEST(CopyIterator, ID17_IteratorCopyFromConstIterator)
			{
#if defined TT_TEST_COPY_ITERATOR
				DoublyLinkedList list{};
				DoublyLinkedList::ConstIterator cIt = list.cbegin();
				//DoublyLinkedList::Iterator it = cIt;// コンパイルエラー
#endif
				SUCCEED();
			}

			// ID:19
			TEST(AssignIterator, ID19_IteratorAssignFromConstIterator)
			{
#if defined TT_TEST_ASSIGNE_ITERATOR
				DoublyLinkedList list{};
				DoublyLinkedList::ConstIterator cIt = list.cbegin();
				DoublyLinkedList::Iterator it;
				//it.operator=(cIt); // コンパイルエラー
#endif
				SUCCEED();
			}
		}
	}	// chapter2
}