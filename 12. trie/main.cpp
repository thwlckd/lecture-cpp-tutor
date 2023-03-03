/*
*Lab12_21720956_��â��
*Author : ��â��
*Programed on November. 26. 2020
*��������(predictive text) Ž���� ���� Trie �ڷᱸ�� ����
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
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]);  // trie ������ MyVoca�� value�� insert
	}
	trie_myVoca.fprintTrie(fout);  // MyVoca key�� �� �ܾ key�� �������� ������ tire ������ ���

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
		trie_myVoca.insert(keyStr, pVoca);  // myToeicVocaList[i]�� trie�� insert
		pVoca++;  // next MyVoca
	}
	fout << "Total " << trie_myVoca.size() << " words in trie_myVoca .." << endl;
	trie_myVoca.fprintTrie(fout);  // print tire

	/* testing keyWord search in trie */
	while (1)
	{
		cout << "\nInput any prefix to search in trie (. to finish) : ";
		cin >> keyStr;  // search key �Է�
		if (keyStr == string("."))
			break;
		predictVocas.clear();  // clear list
		trie_myVoca.findPrefixMatch(keyStr, predictVocas);  // prefix�� �����ϴ� �ܾ� ã�� predictVocas�� ����
		cout << "list of predictive wors with prefix (" << keyStr << ") :" << endl;
		itr = predictVocas.begin();  // start from predictVocas[0]
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr;  // predictVocas�� iterator ����
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