// List_ManualTest.h
// GoogleTest手動テストコードの書き方

#if !defined ___TECHTRAINING_CHAPTER2_LIST_MANUAL_TEST___
#define		 ___TECHTRAINING_CHAPTER2_LIST_MANUAL_TEST___

// コンパイル関連手動テスト（リスト）

// ※コンパイルが通れば成功
#define TT_TEST_GET_DATA_NUM_IS_CONST

// ※コンパイルが通らなければ成功
#define TT_TEST_INSERT_WHEN_CONST

// ※コンパイルが通らなければ成功
#define TT_TEST_ERASE_WHEN_CONST

// ※コンパイルが通らなければ成功
#define TT_TEST_GET_BEGIN_ITERATOR_WHEN_CONST

// ※コンパイルが通れば成功
#define TT_TEST_GET_BEGIN_CONSTITERATOR_WHEN_CONST

// ※コンパイルが通らなければ成功
#define TT_TEST_GET_END_ITERATOR_WHEN_CONST

// ※コンパイルが通れば成功
#define TT_TEST_GET_END_CONSTITERATOR_WHEN_CONST

// ※コンパイルが通らなければ成功
#define TT_TEST_CONSTITERATOR_CANNOT_ASSIGN_DEREFERANCED_ELEMENT

// ※コンパイルが通らなければ成功
#define TT_TEST_COPY_ITERATOR

// ※コンパイルが通らなければ成功
#define TT_TEST_ASSIGNE_ITERATOR
#endif