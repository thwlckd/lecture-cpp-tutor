/*
*Lab11_21720956_박창협
*Author : 박창협
*Programed on November. 18. 2020
*Thesaurus Dictionary 구현을 위한 class HashDict 설계 및 구현
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
		fout << *pVoca << endl;  // value(MyVoca)를 받아가 출력
	}
	fout << endl;

	// print entry size of each bucket
	myVocaDict.fprintBucketSizes(fout);  // 각 bkt arr의 entry 개수 및 통계값 출력
	fout << endl;

	// test 1:N mapping
	string testWord = "present";
	range = myVocaDict.findAll(testWord);  // testWord(offer)를 key로 가지는 iterator의 범위를 class Range(b,p) 형태로 반환
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue();
		fout << *pVoca << endl;
	}
	fout << endl;
	fout.close();
} 