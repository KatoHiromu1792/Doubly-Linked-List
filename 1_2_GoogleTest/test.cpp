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

			//ID:1
			TEST(GetDataNumTest, ID01_PushbackTest)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData()));
				EXPECT_EQ(1, list.size());
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			//ID:2
			TEST(GetDataNumTest, ID02_FaildPushbackTest)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator it;
				ASSERT_FALSE(list.insert(it, ScoreData()));
				EXPECT_EQ(0, list.size());
			}

			//ID:3
			TEST(GetDataNumTest, ID03_InsertTest)
			{
				DoublyLinkedList list{};
				auto it = list.begin();
				ASSERT_TRUE(list.insert(it, ScoreData()));
				EXPECT_EQ(1, list.size());
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			//ID:4
			TEST(GetDataNumTest, ID04_FaildInsertTest)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator it;

				ASSERT_FALSE(list.insert(it, ScoreData()));
				EXPECT_EQ(0, list.size());
			}

			//ID:5
			TEST(GetDataNumTest, ID05_EraseTest)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData()));
				EXPECT_EQ(1, list.size());
				ASSERT_TRUE(list.erase(list.begin()));
				EXPECT_EQ(0, list.size());
			}

			//ID:6
			TEST(GetDataNumTest, ID06_FaildEraseTest)
			{
				DoublyLinkedList list{};
				list.insert(list.end(), ScoreData());
				EXPECT_EQ(1, list.size());
				auto it = list.end();
				ASSERT_FALSE(list.erase(it));
				EXPECT_EQ(1, list.size());
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			//ID:7
			TEST(GetDataNumTest, ID07_EmptyEraseTest)
			{
				DoublyLinkedList list{};
				ASSERT_FALSE(list.erase(list.begin()));
				EXPECT_EQ(0, list.size());
			}

			//ID:9 先頭イテレータへ挿入
			TEST(InsertTest, ID09_EmptyPushfrontTest)
			{
				DoublyLinkedList list{};
				ScoreData data{ 0,"aaa" };
				ASSERT_TRUE(list.insert(list.begin(), data));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data.score && itData.name == data.name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:9 末尾イテレータへ挿入
			TEST(InsertTest, ID09_EmptyPushbackTest)
			{
				DoublyLinkedList list{};
				ScoreData data({ 10,"aaa" });
				ASSERT_TRUE(list.insert(list.end(),data));
				auto it = list.end();
				--it;
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data.score && itData.name == data.name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:10 
			TEST(InsertTest, ID10_PushFrontTest)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.begin(), ScoreData{10,"aaa"}));
				ScoreData itData1 = list.begin().operator*();
				ASSERT_TRUE(list.insert(list.begin(), ScoreData{20,"bbb"}));
				auto it = list.end();
				--it;
				ScoreData itData2 = it.operator*();
				ASSERT_TRUE(itData1.score == itData2.score && itData1.name == itData2.name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:11
			TEST(InsertTest, ID11_PushBackTest)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData{10,"aaa"}));
				auto it = list.end();
				ASSERT_TRUE(list.insert(it, ScoreData{ 20,"bbb" }));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
				it = list.end();
				--it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == 20 && itData.name == "bbb");
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:12 リストに複数の要素が入った状態で先頭に挿入
			TEST(InsertTest, ID12_InsertPushFrontTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.begin(), data[i]));
				}
				auto it = list.begin();
				ASSERT_TRUE(list.insert(it, data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:12 リストに複数の要素が入った状態で中央に挿入
			TEST(InsertTest, ID12_InsertPushCenterTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.begin(),data[i]));
				}
				auto it = list.begin();
				++it;
				ASSERT_TRUE(list.insert(it, data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:12 リストに複数の要素が入った状態で末尾に挿入
			TEST(InsertTest, ID12_InsertPushBuckTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.begin(), data[i]));
				}
				auto it = list.end();
				ASSERT_TRUE(list.insert(it, data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 ConstIteratorを指定して先頭に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushFrontTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.begin(), data[i]));
				}
				auto it = list.cbegin();
				ASSERT_TRUE(list.insert(it, data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 ConstIteratorを指定して中央に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushCenterTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.begin(), data[i]));
				}
				auto it = list.cbegin();
				++it;
				ASSERT_TRUE(list.insert(it, data[2]));

				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:13 リストに複数の要素が入った状態で
			//		 ConstIteratorを指定して末尾に挿入
			TEST(InsertTest, ID13_ConstIteratorInsertPushBackTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.begin(), data[i]));
				}
				ASSERT_TRUE(list.insert(list.cend(), data[2]));

				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:14 
			TEST(InsertTest, ID14_InvalidIteratorTest)
			{
				DoublyLinkedList list{}, list2{};
				DoublyLinkedList::ConstIterator bummy;

				ASSERT_FALSE(list.insert(bummy, ScoreData()));
				ASSERT_EQ(0, list.size());

				ASSERT_FALSE(list.insert(list2.begin(), ScoreData()));
				ASSERT_EQ(0, list.size());
			}

			// ID:16
			TEST(EraseTest, ID16_EmptyEraseTest)
			{
				DoublyLinkedList list{};

				ASSERT_FALSE(list.erase(list.begin()));
				ASSERT_FALSE(list.erase(list.end()));
			}

			// ID:17
			TEST(EraseTest, ID17_FrontEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(), data[i]));
				}
				auto it = list.begin();
		
				ASSERT_TRUE(list.erase(it));
				ASSERT_TRUE(it != list.begin());

				it = list.begin();
				auto itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);

				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:18
			TEST(EraseTest, ID18_BackEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(), data[i]));
				}
				auto it = list.end();
				ASSERT_FALSE(list.erase(it));
				ASSERT_TRUE(--it == --list.end());
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:19
			TEST(EraseTest, ID19_CenterEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.begin();
				++it;
				ASSERT_TRUE(list.erase(it));
				it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:20
			TEST(EraseTest, ID20_ConstIteratorEraseTest)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.cbegin();
				++it;
				ASSERT_TRUE(list.erase(it));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				it = list.end();
				--it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:21
			TEST(EraseTest, ID21_DummyIteratorEraseTest)
			{
				DoublyLinkedList list{}, list2{};
				DoublyLinkedList::Iterator it;

				ASSERT_FALSE(list.erase(it));
				ASSERT_FALSE(list.erase(list2.begin()));
			}

			// ID:23
			TEST(GetBeginIterator, ID23_EmptyGetIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator dummy;
				auto it = list.begin();
				ASSERT_TRUE(it.operator==(dummy));
			}

			// ID:24
			TEST(GetBeginIterator, ID24_OneElementGetIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData({10,"aaa"})));
				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:25
			TEST(GetBeginIterator, ID25_MultipleElementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:26 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_PushfrontGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} ,{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.begin(),data[3]));
				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[3].score && itData.name == data[3].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:26 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_InsertCenterGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} ,{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.begin();
				++it;
				ASSERT_TRUE(list.insert(it, data[3]));
				it = list.begin();
				++it;
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[3].score && itData.name == data[3].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:26 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID26_PushbackGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} ,{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.end(), data[3]));
				auto it = list.begin();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:27 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseBeginGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(list.begin()));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:27 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseCenterGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(++list.begin()));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:27 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginIterator, ID27_EraseEndGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(--list.end()));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:29 
			TEST(GetBeginConstIterator, ID29_EmptyGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::ConstIterator cIt;
				auto it = list.cbegin();
				ASSERT_TRUE(it.operator==(cIt));
			}

			// ID:30
			TEST(GetBeginConstIterator, ID30_OneElementGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(),ScoreData({ 10,"aaa" })));
				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:31
			TEST(GetBeginConstIterator, ID31_MultipleElementGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:32 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_PushfrontGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 2;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.begin(),data[2]));
				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:32 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_InsertCenterGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"},{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(++list.begin(), data[3]));
				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:32 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID32_PushbackGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[4] = { {10,"aaa"},{20,"bbb"},{30,"ccc"},{40,"ddd"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.end(),data[3]));
				ScoreData itData = list.cbegin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:33 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseBeginGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(list.begin()));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:33 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseCenterGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(++list.begin()));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:33 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetBeginConstIterator, ID33_EraseEndGetBeginConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(--list.end()));
				ScoreData itData = list.begin().operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:35
			TEST(GetEndIterator, ID35_EmptyGetEndIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::Iterator dummyIt;

				ASSERT_TRUE(list.end() == dummyIt);
			}

			// ID:36
			TEST(GetEndIterator, ID36_OneElementGetEndIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData{10,"aaa"}));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:37
			TEST(GetEndIterator, ID37_MultipleElementGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.end();
				--it;
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:38 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_PushfrontGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				list.insert(list.begin(), ScoreData());

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:38 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_InsertCenterGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(++list.begin(), ScoreData()));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = list.end();
				--it;
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:38 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID38_PushbackGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.end(), ScoreData{40,"ddd"}));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == 40 && itData.name == "ddd");
			}

			// ID:39 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseBeginGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(list.begin()));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:39 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseCenterGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(++list.begin()));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:39 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndIterator, ID39_EraseEndGetEndIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(--list.end()));

				ASSERT_TRUE(list.end() == nullptr);
				auto it = --list.end();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:41
			TEST(GetEndConstIterator, ID41_EmptyGetConstIterator)
			{
				DoublyLinkedList list{};
				DoublyLinkedList::ConstIterator dummy;

				ASSERT_TRUE(list.cend() == dummy);
			}

			// ID:42
			TEST(GetEndConstIterator, ID42_OneElementGetConstIterator)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData{10,"aaa"}));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == 10 && itData.name == "aaa");
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:43
			TEST(GetEndConstIterator, ID43_MultipleElementGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:44 先頭にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_PushfrontGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.begin(),ScoreData()));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:44 中央にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_InsertCentorGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(++list.begin(), ScoreData{100,"ddd"}));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:44 末尾にデータの挿入を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID44_PushbackGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.insert(list.end(), ScoreData{100,"ddd"}));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == 100 && itData.name == "ddd");
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:45 先頭のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseBeginGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(list.begin()));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:45 中央のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseCenterGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				ASSERT_TRUE(list.erase(++list.begin()));

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:45 末尾のデータの削除を行った後に、呼び出した際の挙動
			TEST(GetEndConstIterator, ID45_EraseEndGetConstIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				list.erase(--list.end());

				ASSERT_TRUE(list.cend() == nullptr);

				auto it = --list.cend();
				ScoreData itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}
		}
		
		namespace Iterator
		{
#ifdef _DEBUG
			// ID:00
			TEST(GetTheElementTheIteratorPoints, ID00_TheListHasNoReference)
			{
				DoublyLinkedList::Iterator it;
				DoublyLinkedList::ConstIterator cIt;
				EXPECT_DEATH(*it, "Assertion failed");
				EXPECT_DEATH(*cIt, "Assertion failed");
			}
#endif // _DEBUG

			// ID:01
			TEST(GetTheElementTheIteratorPoints, ID01_AssignValueToTheIterator)
			{
				DoublyLinkedList list{};

				ASSERT_TRUE(list.insert(list.end(), ScoreData{1, "a"}));
				auto it = list.begin();
				auto itData = it.operator*();
				ASSERT_TRUE(
					itData.score == 1 && 
					itData.name == "a"
				);

				it.operator*() = ScoreData{10,"b"};
				itData = it.operator*();
				ASSERT_TRUE(
					itData.score == 10 &&
					itData.name == "b"
				);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

#ifdef _DEBUG
			// ID:03
			TEST(GetTheElementTheIteratorPoints, ID03_ListEmptyGetBeginIterator)
			{
				DoublyLinkedList list{};
				EXPECT_DEATH(list.begin().operator*(), "Assertion failed");
			}

			// ID:04
			TEST(GetTheElementTheIteratorPoints, ID04_GetEndIterator)
			{
				DoublyLinkedList list{};
				EXPECT_DEATH(list.end().operator*(), "Assertion failed");
			}

			// ID:05
			TEST(IteratorMoveOneStepTowardEnd, ID05_ListNoReferanceGetEndIterator)
			{
				DoublyLinkedList::Iterator it;
				DoublyLinkedList::ConstIterator cIt;

				EXPECT_DEATH(++it, "Assertion failed");
				EXPECT_DEATH(++cIt, "Assertion failed");
			}

			// ID:06
			TEST(IteratorMoveOneStepTowardEnd, ID06_ListEmptyGetBeginIterator)
			{
				DoublyLinkedList list{};
				auto it = list.begin();
				EXPECT_DEATH(++it, "Assertion failed");
			}

			// ID:07
			TEST(IteratorMoveOneStepTowardEnd, ID07_GetEndIterator)
			{
				DoublyLinkedList list{};
				auto it = list.end();
				EXPECT_DEATH(++it, "Assertion failed");
			}
#endif

			// ID:08
			TEST(IteratorMoveOneStepTowardEnd, ID08_MultipleElementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.begin();
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				++it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:09
			TEST(IteratorMoveOneStepTowardEnd, ID09_PreIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.begin();
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);

				auto preIt = ++it;

				ASSERT_TRUE(it == preIt);

				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);

				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:10
			TEST(IteratorMoveOneStepTowardEnd, ID10_PostIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.begin();
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);

				auto postIt = it++;

				ASSERT_TRUE(it != postIt);

				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

#ifdef _DEBUG
			// ID:11
			TEST(IteratorMoveOneStepTowardBegin, ID11_ListNoReferanceGetEndIterator)
			{
				DoublyLinkedList::Iterator it;
				DoublyLinkedList::ConstIterator cIt;
				EXPECT_DEATH(--it, "Assertion failed");
				EXPECT_DEATH(--cIt, "Assertion failed");
			}

			// ID:12
			TEST(IteratorMoveOneStepTowardBegin, ID12_ListEmptyGetEndIterator)
			{
				DoublyLinkedList list{};
				auto it = list.end();
				EXPECT_DEATH(--it, "Assertion failed");
			}

			// ID:13
			TEST(IteratorMoveOneStepTowardBegin, ID13_GetBeginIterator)
			{
				DoublyLinkedList list{};
				auto it = list.begin();
				EXPECT_DEATH(--it, "Assertion failed");
			}
#endif // _DEBUG

			// ID:14
			TEST(IteratorMoveOneStepTowardBegin, ID14_MultipleElementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.end();
				--it;
				auto itData = it.operator*();
				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);
				--it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				--it;
				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[0].score && itData.name == data[0].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:15
			TEST(IteratorMoveOneStepTowardBegin, ID15_PreIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					ASSERT_TRUE(list.insert(list.end(),data[i]));
				}
				auto it = list.end();
				--it;
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);

				auto preIt = --it;
				
				ASSERT_TRUE(it == preIt);

				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:16
			TEST(IteratorMoveOneStepTowardBegin, ID16_PostIncrementGetIterator)
			{
				DoublyLinkedList list{};
				const ScoreData data[3] = { {10,"aaa"},{20,"bbb"},{30,"ccc"} };
				for (int i = 0;i < 3;++i) {
					list.insert(list.end(),data[i]);
				}
				auto it = list.end();
				it--;
				auto itData = it.operator*();

				ASSERT_TRUE(itData.score == data[2].score && itData.name == data[2].name);

				auto postIt = it--;

				ASSERT_TRUE(it != postIt);

				itData = it.operator*();
				ASSERT_TRUE(itData.score == data[1].score && itData.name == data[1].name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:18
			TEST(CopyIterator, ID18_CopyPreservesValue)
			{
				DoublyLinkedList list{};
				
				ASSERT_TRUE(list.insert(list.end(), ScoreData{10,"aaa"}));
				
				DoublyLinkedList::Iterator it = list.begin();
				DoublyLinkedList::Iterator copy = it;

				ScoreData originalData, copyData;
				originalData = it.operator*();
				copyData = copy.operator*();
				ASSERT_TRUE(
					originalData.score == copyData.score && 
					originalData.name == copyData.name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:20
			TEST(AssignIterator, ID20_AssignmentValueEqualsOriginal)
			{
				DoublyLinkedList list{};
				
				ASSERT_TRUE(list.insert(list.end(), ScoreData{ 10,"aaa" }));

				DoublyLinkedList::Iterator it = list.begin();
				DoublyLinkedList::Iterator copy;

				copy.operator=(it);

				ScoreData originalData, copyData;
				originalData = it.operator*();
				copyData = copy.operator*();

				ASSERT_TRUE(
					originalData.score == copyData.score &&
					originalData.name == copyData.name);
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
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
				ASSERT_TRUE(list.insert(list.end(), ScoreData{10,"aaa"}));
				ASSERT_TRUE(list.begin().operator==(list.begin()));
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:23
			TEST(IteratorEqualCheck, ID23_SameIteratorComparison)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData{ 10,"aaa" }));
				ASSERT_TRUE(list.insert(list.end(), ScoreData{ 20,"bbb" }));
				ASSERT_FALSE(list.begin().operator==(list.end()));
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
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
				ASSERT_TRUE(list.insert(list.end(), ScoreData{ 10,"aaa" }));
				ASSERT_FALSE(list.begin().operator!=(list.begin()));
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}

			// ID:26
			TEST(IteratorNotEqualCheck, ID26_SameIteratorComparison)
			{
				DoublyLinkedList list{};
				ASSERT_TRUE(list.insert(list.end(), ScoreData{ 10,"aaa" }));
				ASSERT_TRUE(list.insert(list.end(), ScoreData{ 20,"bbb" }));
				ASSERT_TRUE(list.begin().operator!= (list.end()));
				ASSERT_TRUE(list.clear());
				ASSERT_EQ(0, list.size());
			}
		}
	}
}