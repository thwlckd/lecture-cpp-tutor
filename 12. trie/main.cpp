/*
*Lab12_21720956_박창협
*Author : 박창협
*Programed on November. 26. 2020
*예측구문(predictive text) 탐색을 위한 Trie 자료구조 구현
*/

#include <iostream>
#include <fstream>
#include <list>
#include "Trie.h"
#include "TrieNode.h"
#include"MyVoca.h"
#include"MyVocaList.h"

using namespace std;

#define NUM_TEST_VOCAS 7

void main()
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		printf("Error in opening output file !\n");
		exit;
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca");
	TrieNode<MyVoca*>* pTN;
	MyVoca* pVoca;
	int word_count;
	string keyStr;
	char keyWord[MAX_STR_LEN];
	List_String predictVocas;
	List_String_Iter itr;

	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz", NOUN, { "" }, { "" }),
		MyVoca("ABCD", NOUN, { "" }, { "" }),
		MyVoca("ABC", NOUN, { "" }, { "" }),
		MyVoca("AB", NOUN, { "" }, { "" }),
		MyVoca("A", NOUN, { "" }, { "" }),
		MyVoca("xy", NOUN, { "" }, { "" }),
		MyVoca("x", NOUN, { "" }, { "" }),
	};

	fout << "Testing basic operations of trie inserting ..... " << endl;
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
	{
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]);  // trie 구조에 MyVoca를 value로 insert
	}
	trie_myVoca.fprintTrie(fout);  // MyVoca key의 각 단어를 key로 가지도록 구성된 tire 구조를 출력

	/* erase testVocas in trie */
	fout << "\nTesting TrieDestroy...\n";
	trie_myVoca.eraseTrie();  // clear trie
	trie_myVoca.fprintTrie(fout);

	/* inserting MyVocaList into trie */
	fout << "\nInserting My Vocabularies to myVocaDict . . . " << endl;
	word_count = 0;
	pVoca = &myToeicVocaList[0];  // start from myToeicVocaList[0]
	while (pVoca->getKeyWord() != "-1")
	{
		keyStr = pVoca->getKeyWord();
		trie_myVoca.insert(keyStr, pVoca);  // myToeicVocaList[i]를 trie에 insert
		pVoca++;  // next MyVoca
	}
	fout << "Total " << trie_myVoca.size() << " words in trie_myVoca .." << endl;
	trie_myVoca.fprintTrie(fout);  // print tire

	/* testing keyWord search in trie */
	while (1)
	{
		cout << "\nInput any prefix to search in trie (. to finish) : ";
		cin >> keyStr;  // search key 입력
		if (keyStr == string("."))
			break;
		predictVocas.clear();  // clear list
		trie_myVoca.findPrefixMatch(keyStr, predictVocas);  // prefix를 포함하는 단어 찾아 predictVocas에 저장
		cout << "list of predictive wors with prefix (" << keyStr << ") :" << endl;
		itr = predictVocas.begin();  // start from predictVocas[0]
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr;  // predictVocas의 iterator 전달
			cout << *pVoca << endl;  // print predictVocas
			++itr; // next predictVocas
		}
	}
	cout << "\nErasing trie_myVoca ....\n" << endl;
	fout << "\nErasing trie_myVoca ....\n" << endl;
	trie_myVoca.eraseTrie();  // clear trie
	trie_myVoca.fprintTrie(fout);

	fout.close();
}