#include "pch.h"

#include "DoublyLinkedList.h"

#define MAX_DATA_NUM (4)

/**
* @brief 成績データ
*
* スコアとネーム用の変数を保持する構造体
*/
struct ScoreData
{
	int score = 0;			// スコア
	std::string name = "";	// ユーザー名
};

namespace {
	const ScoreData g_Data[MAX_DATA_NUM] = { {10,"aaa"},{20,"bbb"},{30,"ccc"},{40,"ddd"} };
}

namespace TestHelper
{
	/**
	* @brief 要素を追加する処理を行う関数
	* 
	* @param[in] list	対象のリスト
	* @param[in] num	追加する要素数
	*/
	template<typename T>
	void InsertLoop(DoublyLinkedList<T>& list,int num)
	{
		if (num >= MAX_DATA_NUM) num = 3;
		for (int i = 0;i < num;++i) {
			ASSERT_TRUE(list.insert(list.end(), g_Data[i]));
		}
	}

	/**
	* @brief 全要素を削除してリストの中身が空か確認するための関数
	* 
	* @param[in] list	対象のリスト
	*/
	template<typename T>
	void ClearCheck(DoublyLinkedList<T>& list)
	{
		ASSERT_TRUE(list.clear());
		ASSERT_EQ(0, list.size());
	}
}

namespace ex01_DataStructure
{
	namespace chapter2
	{
		namespace list
		{
			//====================================================
			// ID			：0 
			// 項目			：リストが空である場合の戻り値
			// 戻り値		：0
			// 意図する結果	：
			// 補足			：
			//====================================================
			TEST(GetDataNumTest, ID00_TestGetDataNumWhenEmpty)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_EQ(0, list.size());
			}

			//ID:1
			TEST(GetDataNumTest, ID01_PushbackTest)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_TRUE(list.insert(list.end(), ScoreData()));
				ASSERT_EQ(1, list.size());

				TestHelper::ClearCheck(list);
			}

			//ID:2
			TEST(GetDataNumTest, ID02_FaildPushbackTest)
			{
				DoublyLinkedList<ScoreData> list{};
				DoublyLinkedList<ScoreData>::Iterator it;

				ASSERT_FALSE(list.insert(it, ScoreData()));
				ASSERT_EQ(0, list.size());
			}

			//ID:3
			TEST(GetDataNumTest, ID03_InsertTest)
			{
				DoublyLinkedList<ScoreData> list{};
				auto it = list.begin();

				ASSERT_TRUE(list.insert(it, ScoreData()));
				ASSERT_EQ(1, list.size());

				TestHelper::ClearCheck(list);
			}

			//ID:4
			TEST(GetDataNumTest, ID04_FaildInsertTest)
			{
				DoublyLinkedList<ScoreData> list{};
				DoublyLinkedList<ScoreData>::Iterator it;

				ASSERT_FALSE(list.insert(it, ScoreData()));
				ASSERT_EQ(0, list.size());
			}

			//ID:5
			TEST(GetDataNumTest, ID05_EraseTest)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_TRUE(list.insert(list.end(), ScoreData()));
				ASSERT_EQ(1, list.size());

				ASSERT_TRUE(list.erase(list.begin()));
				ASSERT_EQ(0, list.size());
			}

			//ID:6
			TEST(GetDataNumTest, ID06_FaildEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_TRUE(list.insert(list.end(), ScoreData()));
				ASSERT_TRUE(1, list.size());

				DoublyLinkedList<ScoreData>::Iterator it;

				ASSERT_FALSE(list.erase(it));
				ASSERT_EQ(1, list.size());

				TestHelper::ClearCheck(list);
			}

			//ID:7
			TEST(GetDataNumTest, ID07_EmptyEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_FALSE(list.erase(list.begin()));
				ASSERT_EQ(0, list.size());
			}

			//ID:9 先頭イテレータへ挿入
			TEST(InsertTest, ID09_EmptyPushfrontTest)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.begin(), g_Data[0]));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:9 末尾イテレータへ挿入
			TEST(InsertTest, ID09_EmptyPushbackTest)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:10 
			TEST(InsertTest, ID10_PushFrontTest)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.begin(), g_Data[0]));

				ScoreData itData1 = list.begin().operator*();
				ASSERT_TRUE(list.insert(list.begin(), g_Data[1]));

				auto it = --list.end();
				ScoreData itData2 = it.operator*();
				ASSERT_TRUE(itData1.score == itData2.score && itData1.name == itData2.name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:11
			TEST(InsertTest, ID11_PushBackTest)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));
				ASSERT_TRUE(list.insert(list.end(), g_Data[1]));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				auto it = --list.end();
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:12 リストに複数の要素が入った状態で先頭に挿入
			TEST(InsertTest, ID12_InsertPushFrontTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 4);
				auto it = list.begin();
				ASSERT_TRUE(list.insert(it, g_Data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:12 リストに複数の要素が入った状態で中央に挿入
			TEST(InsertTest, ID12_InsertPushCenterTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 2);
				auto it = list.begin();
				++it;
				ASSERT_TRUE(list.insert(it, g_Data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:12 リストに複数の要素が入った状態で末尾に挿入
			TEST(InsertTest, ID12_InsertPushBuckTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 2);

				auto it = list.end();
				ASSERT_TRUE(list.insert(it, g_Data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 ConstIteratorを指定して先頭に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushFrontTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 2);

				auto it = list.cbegin();
				ASSERT_TRUE(list.insert(it, g_Data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 ConstIteratorを指定して中央に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushCenterTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 2);

				auto it = list.cbegin();
				++it;
				ASSERT_TRUE(list.insert(it, g_Data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 ConstIteratorを指定して末尾に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushBackTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 2);

				ASSERT_TRUE(list.insert(list.cend(), g_Data[2]));

				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:14 
			TEST(InsertTest, ID14_InvalidIteratorTest)
			{
				DoublyLinkedList<ScoreData> list{}, list2{};
				DoublyLinkedList<ScoreData>::ConstIterator dummy;

				ASSERT_FALSE(list.insert(dummy, ScoreData()));
				ASSERT_EQ(0, list.size());

				ASSERT_FALSE(list.insert(list2.begin(), ScoreData()));
				ASSERT_EQ(0, list.size());
			}

			// ID:16
			TEST(EraseTest, ID16_EmptyEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_FALSE(list.erase(list.begin()));
				ASSERT_FALSE(list.erase(list.end()));
			}

			// ID:17
			TEST(EraseTest, ID17_FrontEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};

				TestHelper::InsertLoop(list,3);

				auto it = list.begin();

				ASSERT_TRUE(list.erase(it));
				ASSERT_TRUE(it != list.begin());

				it = list.begin();
				auto itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:18
			TEST(EraseTest, ID18_BackEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};

				TestHelper::InsertLoop(list,3);

				auto it = list.end();
				ASSERT_FALSE(list.erase(it));
				ASSERT_TRUE(--it == --list.end());
			
				TestHelper::ClearCheck(list);
			}

			// ID:19
			TEST(EraseTest, ID19_CenterEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = ++list.begin();
				ASSERT_TRUE(list.erase(it));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				it = --list.end();
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:20
			TEST(EraseTest, ID20_ConstIteratorEraseTest)
			{
				DoublyLinkedList<ScoreData> list{};
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(), g_Data[i]));
				}
				auto it = ++list.cbegin();
				ASSERT_TRUE(list.erase(it));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				it = --list.end();
				itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:21
			TEST(EraseTest, ID21_DummyIteratorEraseTest)
			{
				DoublyLinkedList<ScoreData> list{}, list2{};
				DoublyLinkedList<ScoreData>::Iterator it;

				ASSERT_FALSE(list.erase(it));
				ASSERT_FALSE(list.erase(list2.begin()));
			}

			// ID:23
			TEST(GetBeginIterator, ID23_EmptyGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.begin() == list.end());
			}

			// ID:24
			TEST(GetBeginIterator, ID24_OneElementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:25
			TEST(GetBeginIterator, ID25_MultipleElementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:26 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_PushfrontGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(list.begin(), g_Data[3]));

				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[3].score && itData.name == g_Data[3].name);

				TestHelper::ClearCheck(list);
			}

			// ID:26 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_InsertCenterGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = ++list.begin();
				ASSERT_TRUE(list.insert(it, g_Data[3]));

				it = ++list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[3].score && itData.name == g_Data[3].name);

				TestHelper::ClearCheck(list);
			}

			// ID:26 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_PushbackGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(list.end(), g_Data[3]));

				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:27 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseBeginGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(list.begin()));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:27 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseCenterGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(++list.begin()));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:27 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseEndGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(--list.end()));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:29 
			TEST(GetBeginConstIterator, ID29_EmptyGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.cbegin() == list.cend());
			}

			// ID:30
			TEST(GetBeginConstIterator, ID30_OneElementGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:31
			TEST(GetBeginConstIterator, ID31_MultipleElementGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:32 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_PushfrontGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 2);
				ASSERT_TRUE(list.insert(list.begin(), g_Data[2]));

				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:32 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_InsertCenterGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(++list.begin(), g_Data[3]));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:32 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_PushbackGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(list.end(), g_Data[3]));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:33 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseBeginGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(list.begin()));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);

				TestHelper::ClearCheck(list);
			}

			// ID:33 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseCenterGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(++list.begin()));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:33 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseEndGetBeginConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(--list.end()));

				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:35
			TEST(GetEndIterator, ID35_EmptyGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.end() == list.begin());
			}

			// ID:36
			TEST(GetEndIterator, ID36_OneElementGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				ASSERT_TRUE(list.end() != list.begin());
				auto it = --list.end();

				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:37
			TEST(GetEndIterator, ID37_MultipleElementGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:38 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_PushfrontGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				list.insert(list.begin(), ScoreData());
				ASSERT_TRUE(list.end() != list.begin());

				auto it = --list.end();

				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:38 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_InsertCenterGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(++list.begin(), ScoreData()));
				ASSERT_TRUE(list.end() != list.begin());

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:38 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_PushbackGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(list.end(), g_Data[3]));
				ASSERT_TRUE(list.end() != list.begin());

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[3].score && itData.name == g_Data[3].name);

				TestHelper::ClearCheck(list);
			}

			// ID:39 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseBeginGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(list.begin()));
				ASSERT_TRUE(list.end() != list.begin());

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:39 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseCenterGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(++list.begin()));
				ASSERT_TRUE(list.end() != list.begin());

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[2].score && itData.name == g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:39 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseEndGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(--list.end()));
				ASSERT_TRUE(list.end() != list.begin());

				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[1].score && itData.name == g_Data[1].name);

				TestHelper::ClearCheck(list);
			}

			// ID:41
			TEST(GetEndConstIterator, ID41_EmptyGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.cend() == list.cbegin());
			}

			// ID:42
			TEST(GetEndConstIterator, ID42_OneElementGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				TestHelper::ClearCheck(list);
			}

			// ID:43
			TEST(GetEndConstIterator, ID43_MultipleElementGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:44 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_PushfrontGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				 
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(list.begin(), ScoreData()));
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:44 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_InsertCentorGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				 
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(++list.begin(), g_Data[3]));
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:44 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_PushbackGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				 
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.insert(list.end(), g_Data[3]));
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == g_Data[3].score && itData.name == g_Data[3].name);

				TestHelper::ClearCheck(list);
			}

			// ID:45 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseBeginGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				 
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(list.begin()));
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:45 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseCenterGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				 
				TestHelper::InsertLoop(list, 3);
				ASSERT_TRUE(list.erase(++list.begin()));
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);

				TestHelper::ClearCheck(list);
			}

			// ID:45 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseEndGetConstIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				 
				TestHelper::InsertLoop(list, 3);
				list.erase(--list.end());
				ASSERT_TRUE(list.cend() != list.cbegin());

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);

				TestHelper::ClearCheck(list);
			}
		}

		namespace Iterator
		{
#ifdef _DEBUG
			// ID:00
			TEST(GetTheElementTheIteratorPoints, ID00_TheListHasNoReference)
			{
				DoublyLinkedList<ScoreData>::Iterator it;
				DoublyLinkedList<ScoreData>::ConstIterator cIt;
				EXPECT_DEATH(*it, "Assertion failed");
				EXPECT_DEATH(*cIt, "Assertion failed");
			}
#endif // _DEBUG

			// ID:01
			TEST(GetTheElementTheIteratorPoints, ID01_AssignValueToTheIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				auto it = list.begin();
				auto itData = it.operator*();
				ASSERT_TRUE( itData.score == g_Data[0].score && itData.name == g_Data[0].name);

				it.operator*() = g_Data[1];
				itData = it.operator*();
				ASSERT_TRUE( itData.score == g_Data[1].score && itData.name == g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

#ifdef _DEBUG
			// ID:03
			TEST(GetTheElementTheIteratorPoints, ID03_ListEmptyGetBeginIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				EXPECT_DEATH(list.begin().operator*(), "Assertion failed");
			}

			// ID:04
			TEST(GetTheElementTheIteratorPoints, ID04_GetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				EXPECT_DEATH(list.end().operator*(), "Assertion failed");
			}

			// ID:05
			TEST(IteratorMoveOneStepTowardEnd, ID05_ListNoReferanceGetEndIterator)
			{
				DoublyLinkedList<ScoreData>::Iterator it;
				DoublyLinkedList<ScoreData>::Iterator cIt;
				EXPECT_DEATH(++it,"Assertion failed");
				EXPECT_DEATH(++cIt, "Assertion failed");
			}

			// ID:06
			TEST(IteratorMoveOneStepTowardEnd, ID06_ListEmptyGetBeginIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				auto it = list.begin();
				EXPECT_DEATH(++it, "Assertion failed");
			}

			// ID:07
			TEST(IteratorMoveOneStepTowardEnd, ID07_GetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				auto it = list.end();
				EXPECT_DEATH(++it, "Assertion failed");
			}
#endif

			// ID:08
			TEST(IteratorMoveOneStepTowardEnd, ID08_MultipleElementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = list.begin();
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score ==  g_Data[0].score && itData.name ==  g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:09
			TEST(IteratorMoveOneStepTowardEnd, ID09_PreIncrementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = list.begin();
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score ==  g_Data[0].score && itData.name ==  g_Data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:10
			TEST(IteratorMoveOneStepTowardEnd, ID10_PostIncrementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = list.begin();
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score ==  g_Data[0].score && itData.name ==  g_Data[0].name);
				it++;
				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

#ifdef _DEBUG
			// ID:11
			TEST(IteratorMoveOneStepTowardBegin, ID11_ListNoReferanceGetEndIterator)
			{
				DoublyLinkedList<ScoreData>::Iterator it;
				DoublyLinkedList<ScoreData>::ConstIterator cIt;
				EXPECT_DEATH(--it, "Assertion failed");
				EXPECT_DEATH(--cIt, "Assertion failed");
			}

			// ID:12
			TEST(IteratorMoveOneStepTowardBegin, ID12_ListEmptyGetEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				auto it = list.end();
				EXPECT_DEATH(--it, "Assertion failed");
			}

			// ID:13
			TEST(IteratorMoveOneStepTowardBegin, ID13_GetBeginIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				auto it = list.begin();
				EXPECT_DEATH(--it, "Assertion failed");
			}
#endif // _DEBUG

			// ID:14
			TEST(IteratorMoveOneStepTowardBegin, ID14_MultipleElementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);

				auto it = list.end();
				--it;
				auto itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);
				--it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);
				--it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[0].score && itData.name ==  g_Data[0].name);
				ASSERT_TRUE(it == list.begin());

				TestHelper::ClearCheck(list);
			}

			// ID:15
			TEST(IteratorMoveOneStepTowardBegin, ID15_PreIncrementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				
				auto it = list.end();
				--it;
				auto itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);
				
				auto preIt = --it;
				ASSERT_TRUE(it == preIt);

				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:16
			TEST(IteratorMoveOneStepTowardBegin, ID16_PostIncrementGetIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				TestHelper::InsertLoop(list, 3);
				
				auto it = list.end();
				it--;
				auto itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[2].score && itData.name ==  g_Data[2].name);

				auto postIt = it--;
				ASSERT_TRUE(it != postIt);

				itData = it.operator*();
				ASSERT_TRUE(itData.score ==  g_Data[1].score && itData.name ==  g_Data[1].name);
				
				TestHelper::ClearCheck(list);
			}

			// ID:18
			TEST(CopyIterator, ID18_CopyPreservesValue)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				DoublyLinkedList<ScoreData>::Iterator it = list.begin();
				DoublyLinkedList<ScoreData>::Iterator copy = it;

				ScoreData originalData, copyData;
				originalData = it.operator*();
				copyData = copy.operator*();
				ASSERT_TRUE(
					originalData.score == copyData.score &&
					originalData.name == copyData.name);

				TestHelper::ClearCheck(list);
			}

			// ID:20
			TEST(AssignIterator, ID20_AssignmentValueEqualsOriginal)
			{
				DoublyLinkedList<ScoreData> list{};

				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));

				DoublyLinkedList<ScoreData>::Iterator it = list.begin();
				DoublyLinkedList<ScoreData>::Iterator copy;

				copy.operator=(it);

				ScoreData originalData, copyData;
				originalData = it.operator*();
				copyData = copy.operator*();

				ASSERT_TRUE(
					originalData.score == copyData.score &&
					originalData.name == copyData.name);

				TestHelper::ClearCheck(list);
			}

			// ID:21
			TEST(IteratorEqualCheck, ID21_ListEmptyCheckToBeginAndEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.begin().operator==(list.end()));
			}

			// ID:22
			TEST(IteratorEqualCheck, ID22_SameIteratorComparison)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));
				ASSERT_TRUE(list.begin().operator==(list.begin()));

				TestHelper::ClearCheck(list);
			}

			// ID:23
			TEST(IteratorEqualCheck, ID23_SameIteratorComparison)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));
				ASSERT_TRUE(list.insert(list.end(), g_Data[1]));
				ASSERT_FALSE(list.begin().operator==(list.end()));

				TestHelper::ClearCheck(list);
			}

			// ID:24
			TEST(IteratorNotEqualCheck, ID24_ListEmptyCheckToBeginAndEndIterator)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_FALSE(list.begin().operator!=(list.end()));
			}

			// ID:25
			TEST(IteratorNotEqualCheck, ID25_SameIteratorComparison)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));
				ASSERT_FALSE(list.begin().operator!=(list.begin()));

				TestHelper::ClearCheck(list);
			}

			// ID:26
			TEST(IteratorNotEqualCheck, ID26_SameIteratorComparison)
			{
				DoublyLinkedList<ScoreData> list{};
				ASSERT_TRUE(list.insert(list.end(), g_Data[0]));
				ASSERT_TRUE(list.insert(list.end(), g_Data[1]));
				ASSERT_TRUE(list.begin().operator!= (list.end()));

				TestHelper::ClearCheck(list);
			}
		}
	}
}