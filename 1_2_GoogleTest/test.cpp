#include "pch.h"

#include "DoublyLinkedList.h"

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
				DoublyLinkedList list{};
				EXPECT_EQ(0, list.size());
			}

			//====================================================
			// ID			：1 
			// 項目			：リスト末尾への挿入を行った際の戻り値
			// 戻り値		：1
			// 意図する結果	：
			// 補足			：
			//====================================================
			TEST(GetDataNumTest, ID01_PushbackTest)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData());
				EXPECT_EQ(1, list.size());
			}

			//====================================================
			// ID			：2 
			// 項目			：リスト末尾への挿入が失敗した際の戻り値
			// 戻り値		：0
			// 意図する結果	：
			// 補足			：
			//====================================================
			TEST(GetDataNumTest, ID02_FaildPushbackTest)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 0,"xxx" });
				EXPECT_EQ(0, list.size());
			}

			//====================================================
			// ID			：3 
			// 項目			：データの挿入を行った際の戻り値
			// 戻り値		：1
			// 意図する結果	：
			// 補足			：
			//====================================================
			TEST(GetDataNumTest, ID03_InsertTest)
			{
				DoublyLinkedList list{};
				auto it = list.begin();
				list.insert(it, ScoreData());
				EXPECT_EQ(1, list.size());
			}

			//====================================================
			// ID			：4 
			// 項目			：データの挿入に失敗した際の戻り値
			// 戻り値		：0
			// 意図する結果	：
			// 補足			：
			//====================================================
			TEST(GetDataNumTest, ID04_FaildInsertTest)
			{
				DoublyLinkedList list{};
				auto it = list.begin();
				--it;
				list.insert(it, ScoreData{ 0,"xxx" });
				EXPECT_EQ(0, list.size());
			}

			//====================================================
			// ID			：5 
			// 項目			：データの削除を行った際の戻り値
			// 戻り値		：0
			// 意図する結果	：
			// 補足			：
			//====================================================
			TEST(GetDataNumTest, ID05_EraseTest)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData());
				EXPECT_EQ(1, list.size());
				list.erase(list.begin());
				EXPECT_EQ(0, list.size());
			}

			//====================================================
			// ID			：6 
			// 項目			：データの削除が失敗した際の戻り値
			// 戻り値		：1
			// 意図する結果	：
			// 補足			：データを挿入した後、削除した場合。
			//====================================================
			TEST(GetDataNumTest, ID06_FaildEraseTest)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData());
				EXPECT_EQ(1, list.size());
				auto it = list.begin();
				--it;
				list.erase(it);
				EXPECT_EQ(1, list.size());
			}

			//====================================================
			// ID			：7 
			// 項目			：リストが空である場合に、データの削除を行った際の戻り値
			// 戻り値		：0
			// 意図する結果	：
			// 補足			：マイナスにならないかどうか
			//====================================================
			TEST(GetDataNumTest, ID07_EmptyEraseTest)
			{
				DoublyLinkedList list{};
				list.erase(list.begin());
				EXPECT_EQ(0, list.size());
			}

			//====================================================
			// ID			：9 
			// 項目			：リストが空である場合に、先頭に挿入した際の挙動
			// 戻り値		：TRUE
			// 意図する結果	：イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
			// 補足			：先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックすること
			//====================================================
			TEST(InsertTest, ID09_EmptyPushfrontTest)
			{
				DoublyLinkedList list{};
				ScoreData data{ 0,"aaa" };
				list.insert(list.begin(), data);
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == data.score && itData.name == data.name);
			}

			//====================================================
			// ID			：9 
			// 項目			：リストが空である場合に、末尾に挿入した際の挙動
			// 戻り値		：TRUE
			// 意図する結果	：イテレータの指す位置に要素が挿入されその位置にあった要素が後ろにずれる。
			// 補足			：先頭イテレータ、末尾イテレータを引数で渡した場合について、個別に挙動をチェックすること
			//====================================================
			TEST(InsertTest, ID09_EmptyPushbackTest)
			{
				DoublyLinkedList list{};
				ScoreData data({ 10,"aaa" });
				list.push_back(data);
				auto it = list.end();
				--it;
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data.score && itData.name == data.name);
			}

			//====================================================
			// ID			：10
			// 項目			：リストに複数の要素がある場合に、先頭イテレータを渡して、挿入した際の挙動
			// 戻り値		：TRUE
			// 意図する結果	：先頭に要素が挿入され、元々先頭だった要素が２番目になる。
			// 補足			：
			//====================================================		
			TEST(InsertTest, ID10_PushFrontTest)
			{
				DoublyLinkedList list{};
				list.push_front(ScoreData{ 10,"aaa" });
				ScoreData itData1 = list.begin().operator*().data;
				list.push_front(ScoreData{ 20,"bbb" });
				auto it = list.end();
				--it;
				ScoreData itData2 = it.operator*().data;
				ASSERT_TRUE(itData1.score == itData2.score && itData1.name == itData2.name);
			}

			//====================================================
			// ID			：11
			// 項目			：リストに複数の要素がある場合に、末尾イテレータを渡して、挿入した際の挙動
			// 戻り値		：TRUE
			// 意図する結果	：イテレータの指す位置に要素が挿入される
			// 補足			：
			//====================================================
			TEST(InsertTest, ID11_PushBackTest)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				auto it = list.end();
				ASSERT_TRUE(list.insert(it, ScoreData{ 20,"bbb" }));
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
				it = list.end();
				--it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == 20 && itData.name == "bbb");
			}

			// ID:12 リストに複数の要素が入った状態で先頭に挿入
			TEST(InsertTest, ID12_InsertPushFrontTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_front(data[i]);
				}
				auto it = list.begin();
				list.insert(it, data[2]);

				it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:12 リストに複数の要素が入った状態で中央に挿入
			TEST(InsertTest, ID12_InsertPushCenterTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_front(data[i]);
				}
				auto it = list.begin();
				++it;
				list.insert(it, data[2]);

				it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:12 リストに複数の要素が入った状態で末尾に挿入
			TEST(InsertTest, ID12_InsertPushBuckTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_front(data[i]);
				}
				auto it = list.end();
				list.insert(it, data[2]);

				it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 Const_Iteratorを指定して先頭に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushFrontTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_front(data[i]);
				}
				auto it = list.cbegin();
				list.insert(it, data[2]);

				it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 Const_Iteratorを指定して中央に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushCenterTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_front(data[i]);
				}
				auto it = list.cbegin();
				++it;
				list.insert(it, data[2]);

				it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 Const_Iteratorを指定して末尾に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushBackTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_front(data[i]);
				}
				auto it = list.cend();
				list.insert(it, data[2]);

				it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
			}

			// ID:14 
			TEST(InsertTest, ID14_InvalidIteratorTest)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Const_Iterator bummy;
				auto it = list.insert(bummy, { 11,"aaa" });

				ASSERT_FALSE(list.size() < 1);
			}

			// ID:16
			TEST(EraseTest, ID16_EmptyEraseTest)
			{
				DoublyLinkedList list{};
				ASSERT_FALSE(list.erase(list.begin()));
			}

			// ID:17
			TEST(EraseTest, ID17_FrontEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				list.erase(it);
				ASSERT_TRUE(it != list.begin());
			}

			// ID:18
			TEST(EraseTest, ID18_BackEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.end();
				list.erase(it);
				ASSERT_TRUE(--it == --list.end());
			}

			// ID:19
			TEST(EraseTest, ID19_CenterEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				++it;
				list.erase(it);
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				it = list.end();
				--it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
			}

			// ID:20
			TEST(EraseTest, ID20_ConstIteratorEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.cbegin();
				++it;
				list.erase(it);
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				it = list.end();
				--it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
			}

			// ID:21
			TEST(EraseTest, ID21_DummyIteratorEraseTest)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator it;

				ASSERT_FALSE(list.erase(it));
			}

			// ID:23
			TEST(GetBeginIterator, ID23_EmptyGetIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator dummyIt;
				auto it = list.begin();
				ASSERT_TRUE(it.operator==(dummyIt));
			}

			// ID:24
			TEST(GetBeginIterator, ID24_OneElementGetIterator)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData({ 10,"aaa" }));
				auto it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
			}

			// ID:25
			TEST(GetBeginIterator, ID25_MultipleElementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:26 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_PushfrontGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} ,{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.push_front(data[3]);
				auto it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[3].score && itData.name == data[3].name);
			}

			// ID:26 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_InsertCenterGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} ,{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				++it;
				list.insert(it, data[3]);
				it = list.getter(1);
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[3].score && itData.name == data[3].name);
			}

			// ID:26 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_PushbackGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} ,{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.push_back(data[3]);
				auto it = list.begin();
				ScoreData itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:27 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseBeginGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.erase(list.begin());
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
			}

			// ID:27 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseCenterGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.erase(list.getter(1));
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:27 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseEndGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.erase(list.end());
				ScoreData itData = list.begin().operator*().data;
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:29 
			TEST(GetBeginConstIterator, ID29_EmptyGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Const_Iterator cIt;
				auto it = list.cbegin();
				ASSERT_TRUE(it.operator==(cIt));
			}

			// ID:30
			TEST(GetBeginConstIterator, ID30_OneElementGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData({ 10,"aaa" }));
				auto it = list.cbegin().operator*();
				ASSERT_TRUE(it.prev == nullptr);
			}

			// ID:31
			TEST(GetBeginConstIterator, ID31_MultipleElementGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.cbegin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:32 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_PushfrontGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					list.push_back(data[i]);
				}
				list.push_front(data[2]);
				auto it = list.cbegin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:32 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_InsertCenterGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"},{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.insert(list.getter(1), data[3]);
				auto it = list.cbegin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:32 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_PushbackGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"},{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.push_back(data[3]);
				auto it = list.cbegin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:33 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseBeginGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.erase(list.begin());
				auto it = list.begin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:33 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseCenterGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.erase(list.getter(1));
				auto it = list.begin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:33 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseEndGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				list.erase(list.end());
				auto it = list.begin().operator*();
				ASSERT_TRUE(it.prev == nullptr && it.next != nullptr);
			}

			// ID:35
			TEST(GetEndIterator, ID35_EmptyGetEndIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator dummyIt;

				auto it = list.end();
				ASSERT_TRUE(it == dummyIt);
			}

			// ID:36
			TEST(GetEndIterator, ID36_OneElementGetEndIterator)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				auto node = it.operator*();
				ASSERT_TRUE(node.prev == nullptr && node.next == nullptr);
			}

			// ID:37
			TEST(GetEndIterator, ID37_MultipleElementGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:38 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_PushfrontGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);

				list.push_front(ScoreData());

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:38 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_InsertCenterGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);


				list.insert(list.getter(1), ScoreData());

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:38 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_PushbackGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);

				list.push_back(ScoreData());

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:39 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseBeginGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);

				list.erase(list.begin());

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:39 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseCenterGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);

				list.erase(list.getter(1));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:39 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseEndGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.end() == nullptr);

				list.erase(--list.end());

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:41
			TEST(GetEndConstIterator, ID41_EmptyGetConstIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Const_Iterator cIt;

				ASSERT_TRUE(list.cend() == cIt);
			}

			// ID:42
			TEST(GetEndConstIterator, ID42_OneElementGetConstIterator)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev == nullptr && node.next == nullptr);
			}

			// ID:43
			TEST(GetEndConstIterator, ID43_MultipleElementGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:44 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_PushfrontGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				list.push_front(ScoreData());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:44 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_InsertCentorGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				list.insert(list.getter(1), ScoreData());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:44 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_PushbackGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				list.push_back(ScoreData());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:45 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseBeginGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				list.erase(list.begin());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:45 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseCenterGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				list.erase(list.getter(1));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}

			// ID:45 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseEndGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}

				ASSERT_TRUE(list.cend() == nullptr);

				list.erase(--list.end());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				auto node = it.operator*();
				ASSERT_TRUE(node.prev != nullptr && node.next == nullptr);
			}
		}
		
		namespace Iterator
		{
			// ID:00
			TEST(GetTheElementTheIteratorPoints, ID00_TheListHasNoReference)
			{
				DoublyLinkedList::Iterator it;
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:01
			TEST(GetTheElementTheIteratorPoints, ID01_AssignValueToTheIterator)
			{
				DoublyLinkedList list{};

				list.push_back(ScoreData{1, "a"});
				auto it = list.begin();
				auto itData = it.operator*().data;
				ASSERT_TRUE(
					itData.score == 1 && 
					itData.name == "a"
				);

				it.operator*().data = ScoreData{10,"b"};
				itData = it.operator*().data;
				ASSERT_TRUE(
					itData.score == 10 &&
					itData.name == "b"
				);
			}

			// ID:03
			TEST(GetTheElementTheIteratorPoints, ID03_ListEmptyGetBeginIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.begin().operator&()) << "the node is a nullptr";
			}

			// ID:04
			TEST(GetTheElementTheIteratorPoints, ID04_GetEndIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.end().operator&()) << "the node is a nullptr";
			}

			// ID:05
			TEST(IteratorMoveOneStepTowardEnd, ID05_ListNoReferanceGetEndIterator)
			{
				DoublyLinkedList::Iterator it;
				++it;
				it.operator=(it);
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:06
			TEST(IteratorMoveOneStepTowardEnd, ID06_ListEmptyGetBeginIterator)
			{
				DoublyLinkedList list{};
				auto it = list.begin();

				++it;
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:07
			TEST(IteratorMoveOneStepTowardEnd, ID07_GetEndIterator)
			{
				DoublyLinkedList list{};
				auto it = list.end();

				++it;
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:08
			TEST(IteratorMoveOneStepTowardEnd, ID08_MultipleElementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				auto itData = it.operator*().data;

				for (int i = 0;i < 3;++i)
				{
					ASSERT_TRUE(itData.score == data[i].score && itData.name == data[i].name);
					it.operator++();
					if (it.operator&() == nullptr)continue;
					itData = it.operator*().data;
				}
			}

			// ID:09
			TEST(IteratorMoveOneStepTowardEnd, ID09_PreIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				auto itData = it.operator*().data;

				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);

				++it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
			}

			// ID:10
			TEST(IteratorMoveOneStepTowardEnd, ID10_PostIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.begin();
				auto itData = it.operator*().data;

				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);

				it++;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
			}

			// ID:11
			TEST(IteratorMoveOneStepTowardBegin, ID11_ListNoReferanceGetEndIterator)
			{
				DoublyLinkedList::Iterator it;
				it.operator--();
				it.operator=(it);
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:12
			TEST(IteratorMoveOneStepTowardBegin, ID12_ListEmptyGetEndIterator)
			{
				DoublyLinkedList list{};
				auto it = list.end();
				it.operator--();
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:13
			TEST(IteratorMoveOneStepTowardBegin, ID13_GetBeginIterator)
			{
				DoublyLinkedList list{};
				auto it = list.begin();
				it.operator--();
				ASSERT_TRUE(it.operator&()) << "the node is a nullptr";
			}

			// ID:14
			TEST(IteratorMoveOneStepTowardBegin, ID14_MultipleElementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.end();
				it.operator--();
				auto itData = it.operator*().data;

				for (int i = 2; i > 0; --i)
				{
					ASSERT_TRUE(itData.score == data[i].score && itData.name == data[i].name);
					it.operator--();
					if (it.operator&() == nullptr)continue;
					itData = it.operator*().data;
				}
			}

			// ID:15
			TEST(IteratorMoveOneStepTowardBegin, ID15_PreIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.end();
				--it;
				auto itData = it.operator*().data;

				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);

				--it;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
			}

			// ID:16
			TEST(IteratorMoveOneStepTowardBegin, ID16_PostIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.push_back(data[i]);
				}
				auto it = list.end();
				it--;
				auto itData = it.operator*().data;

				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);

				it--;
				itData = it.operator*().data;
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
			}

			// ID:18
			TEST(CopyIterator, ID18_CopyPreservesValue)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				DoublyLinkedList::Iterator it = list.begin();
				DoublyLinkedList::Iterator copy = it;

				DoublyLinkedList::Node originalNode, copyNode;
				originalNode = it.operator*();
				copyNode = copy.operator*();
				ASSERT_TRUE(
					originalNode.prev == copyNode.prev &&
					originalNode.next == copyNode.next &&
					originalNode.data.score == copyNode.data.score && 
					originalNode.data.name == copyNode.data.name);
			}

			// ID:20
			TEST(AssignIterator, ID20_AssignmentValueEqualsOriginal)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				DoublyLinkedList::Iterator it = list.begin();
				DoublyLinkedList::Iterator copy;
				copy.operator=(it);

				DoublyLinkedList::Node originalNode, copyNode;
				originalNode = it.operator*();
				copyNode = copy.operator*();

				ASSERT_TRUE(
					originalNode.prev == copyNode.prev &&
					originalNode.next == copyNode.next &&
					originalNode.data.score == copyNode.data.score &&
					originalNode.data.name == copyNode.data.name);
			}

			// ID:21
			TEST(IteratorEqualCheck, ID21_ListEmptyCheckToBeginAndEndIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.begin().operator==(list.end()));
			}

			// ID:22
			TEST(IteratorEqualCheck, ID22_SameIteratorComparison)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				ASSERT_TRUE(list.begin().operator==(list.begin()));
			}

			// ID:23
			TEST(IteratorEqualCheck, ID23_SameIteratorComparison)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				list.push_back(ScoreData{ 20,"bbb" });
				ASSERT_FALSE(list.begin().operator==(list.end()));
			}

			// ID:24
			TEST(IteratorNotEqualCheck, ID24_ListEmptyCheckToBeginAndEndIterator)
			{
				DoublyLinkedList list{};
				ASSERT_FALSE(list.begin().operator!=(list.end()));
			}

			// ID:25
			TEST(IteratorNotEqualCheck, ID25_SameIteratorComparison)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				ASSERT_FALSE(list.begin().operator!=(list.begin()));
			}

			// ID:26
			TEST(IteratorNotEqualCheck, ID26_SameIteratorComparison)
			{
				DoublyLinkedList list{};
				list.push_back(ScoreData{ 10,"aaa" });
				list.push_back(ScoreData{ 20,"bbb" });
				ASSERT_TRUE(list.begin().operator!= (list.end()));
			}
		}
	}
}