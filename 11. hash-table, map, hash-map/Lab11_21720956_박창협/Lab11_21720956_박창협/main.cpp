/*
*Lab11_21720956_��â��
*Author : ��â��
*Programed on November. 18. 2020
*Thesaurus Dictionary ������ ���� class HashDict ���� �� ����
*/

#include <iostream>
#include <fstream>
#include <string>
#include "HashMap.h"
#include "CyclicShiftHashCode.h"
#include "Entry.h"
#include "HashDictionary.h"
#include "MyVoca.h"
#include "MyVocaList.h"

void main()
{
	ofstream fout;
	MyVoca* pVoca, voca;
	List_Str thesaurus, usages;  // typedef list<string>
	int word_count;
	MyVoca mv;
	string keyWord;
	HashDict<string, MyVoca*> myVocaDict;
	HashDict<string, MyVoca*>::Iterator itr;
	HashDict<string, MyVoca*>::Range range;
	Entry<string, MyVoca*> vocaEntry;

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt !!" << endl;
		exit;
	}
	fout << "Inserting My Vocabularies to myVocaDict . . . " << endl;
	word_count = 0;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i];  // value(MyVoca) setting
		keyWord = myToeicVocaList[i].getKeyWord();  // key setting
		myVocaDict.insert(keyWord, pVoca);  // insert entry
	}
	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .."
		<< endl;

	// print dictionary
	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.getValue();
		fout << *pVoca << endl;  // value(MyVoca)�� �޾ư� ���
	}
	fout << endl;

	// print entry size of each bucket
	myVocaDict.fprintBucketSizes(fout);  // �� bkt arr�� entry ���� �� ��谪 ���
	fout << endl;

	// test 1:N mapping
	string testWord = "present";
	range = myVocaDict.findAll(testWord);  // testWord(offer)�� key�� ������ iterator�� ������ class Range(b,p) ���·� ��ȯ
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue();
		fout << *pVoca << endl;
	}
	fout << endl;
	fout.close();
} 