/*
*Lab10_21720956_박창협
*Author : 박창협
*Programed on November. 10. 2020
*서적 정보 관리 및 탐색을 위한 균형화된 이진 탐색 트리
*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "T_BST.h"
#include "T_Entry.h"
#include "T_Array.h"
#include "Book.h"
#include "Date.h"

using namespace std;

#define NUM_BOOKS 15

void main()
{
    Book books[NUM_BOOKS] =
    {
        //Book( string bk_title, string bk_author, Date dt)
        Book(string("Book_01"), string("Kim"), Date(2020, 1, 1)),
        Book(string("Book_02"), string("Kim"), Date(2010, 1, 1)),
        Book(string("Book_03"), string("Kim"), Date(2013, 1, 1)),
        Book(string("Book_04"), string("Lee"), Date(2011, 1, 1)),
        Book(string("Book_05"), string("Hwang"), Date(2001, 1, 1)),
        Book(string("Book_06"), string("Choi"), Date(2003, 1, 1)),
        Book(string("Book_07"), string("Park"), Date(2009, 1, 1)),
        Book(string("Book_08"), string("Brown"), Date(2012, 1, 1)),
        Book(string("Book_09"), string("Alpha"), Date(1980, 1, 1)),
        Book(string("Book_10"), string("Chalie"), Date(1970, 1, 1)),
        Book(string("Book_11"), string("Tango"), Date(1985, 1, 1)),
        Book(string("Book_12"), string("Yankee"), Date(1977, 1, 1)),
        Book(string("Book_13"), string("Zulu"), Date(2018, 1, 1)),
        Book(string("Book_14"), string("Foxtrot"), Date(2015, 1, 1)),
        Book(string("Book_15"), string("Delta"), Date(2000, 1, 1)),
    };
    ofstream fout("output.txt");
    if (fout.fail())
    {
        cout << "Fail to create output.txt for results !!" << endl;
        exit;
    }

    fout << "Input books[] array : " << endl;
    for (int i = 0; i < NUM_BOOKS; i++)
    {
        fout << books[i] << endl;
    }
    fout << endl;
    fout << endl << "Balanced Binary Search Tree (BBST) with key book-title" << endl;
    T_Entry<string, Book*> entry_title_pBK;
    T_BST<string, Book*> BBST_BK_keyTitle("BBST_BK_keyTitle");
    T_BSTN<string, Book*>* pRoot, ** ppBBST_BK_root;
    ppBBST_BK_root = BBST_BK_keyTitle.getRootAddr();  // BST의 root포인터 주소를 이중포인터에 전달
    for (int i = 0; i < NUM_BOOKS; i++)
    {
        entry_title_pBK.setKey(books[i].getTitle());  // 책이름을 key로 설정
        entry_title_pBK.setValue(&books[i]);  // Book을 value로 설정
        //fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
        BBST_BK_keyTitle.insertAndRebalance(entry_title_pBK);  // BST에 Entry insert and rebalance
    }
    fout << "\nEntries in " << BBST_BK_keyTitle.getName() << " (in order of Book Title) : " << endl;
    fout << "BBST_BK_ketTitle: curruent size (" << BBST_BK_keyTitle.size() << ")\n";
    //BBST_BK_keyTitle.fprint_inOrder(fout);
    BBST_BK_keyTitle.fprint_with_Depth(fout);  // 깊이에 따른 BST 출력

    fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
    T_Entry<string, Book*> entry_Author_pBK;
    T_BST<string, Book*> BBST_BK_keyAuthor("BBST_BK_keyAuthor");
    T_BSTN<string, Book*>** ppRoot_BBST_BK_keyAuthor, * pBBST_BK_keyAuthor;
    ppRoot_BBST_BK_keyAuthor = BBST_BK_keyAuthor.getRootAddr();  // BST의 root포인터 주소를 이중포인터에 전달
    for (int i = 0; i < NUM_BOOKS; i++)
    {
        entry_Author_pBK.setKey(books[i].getAuthor());  // 저자를 key로 설정
        entry_Author_pBK.setValue(&books[i]);  // Book을 value로 설정
        //fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
        BBST_BK_keyAuthor.insertAndRebalance(entry_Author_pBK);  // BST에 Entry insert and rebalance
    }
    fout << "\nEntries in " << BBST_BK_keyAuthor.getName() << " (in order of Book Author) : " << endl;
    fout << "BBST_BK_ketAuthor: curruent size (" << BBST_BK_keyAuthor.size() << ")\n";
    //BBST_BK_keyAuthor.fprint_inOrder(fout);
    BBST_BK_keyAuthor.fprint_with_Depth(fout);  // 깊이에 따른 BST 출력
    // Testing Search on Binary Search Tree

    string author = books[0].getAuthor();
    Date d1, d2;
    Book* pBk;
    T_Array<Book*> array_pBook(1, string("Array_Book"));
    d1.setDate(2010, 1, 1);
    d2.setDate(2015, 12, 31);
    pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author);
    BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, array_pBook);
    fout << "Books of author (" << author << ") published during (" << d1 << ") ~ (" << d2 << "):" << endl;
    for (int i = 0; i < array_pBook.size(); i++)
    {
        if (array_pBook[i]->getAuthor() == author)
        {
            pBk = array_pBook[i];
            if ((pBk->getPubDate() >= d1) && (pBk->getPubDate() <= d2))
                fout << *(array_pBook[i]) << endl;
        }
    }

    fout << endl << "Balanced Binary Search Tree (BBST) with key publication date" << endl;
    T_Entry<Date, Book*> entry_PubDate_pBK;
    T_BST<Date, Book*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
    T_BSTN<Date, Book*>** ppRoot_BBST_BK_keyPubDate;
    ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.getRootAddr();
    for (int i = 0; i < NUM_BOOKS; i++)
    {
        entry_PubDate_pBK.setKey(books[i].getPubDate());  // 출판일을 key로 설정
        entry_PubDate_pBK.setValue(&books[i]);  // Book을 value로 설정
        //fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
        BBST_BK_keyPubDate.insertAndRebalance(entry_PubDate_pBK);  // BST에 Entry insert and rebalance
    }
    fout << "\nEntries in " << BBST_BK_keyPubDate.getName() << " (in order of Book Publication Date) : " << endl;
    fout << "BBST_BK_keyPubDate: curruent size (" << BBST_BK_keyPubDate.size() << ")\n";
    //BBST_BK_keyPubDate.fprint_inOrder(fout);
    BBST_BK_keyPubDate.fprint_with_Depth(fout);  // 깊이에 따른 BST 출력

    fout << "\nRemoving the root entry in sequence ..." << endl;
    for (int i = 0; i < NUM_BOOKS; i++)
    {
        pRoot = BBST_BK_keyTitle.getRoot();
        entry_title_pBK = pRoot->getEntry();
        fout << "\nremove " << entry_title_pBK << endl;
        fout << "BBST_BK_keyTitle: curruent size (" << BBST_BK_keyTitle.size() - 1 << ")\n";
        BBST_BK_keyTitle.eraseBSTN(&pRoot);  // remove Root Entry
        BBST_BK_keyTitle.fprint_with_Depth(fout);  // remove monitoring
    }
    fout << "\nClearing BBST_BKs . . . " << endl;
    BBST_BK_keyTitle.clear();
    BBST_BK_keyAuthor.clear();
    BBST_BK_keyPubDate.clear();
    fout << "All BBST_BKs cleared !! " << endl;
    fout.close();
}