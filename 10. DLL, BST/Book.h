#pragma once

#ifndef BOOK_H
#define BOOK_H

#include "Date.h"
#include<iomanip>
#include<iostream>

using namespace std;

class Book
{
	friend ostream& operator<<(ostream& fout, Book &bk)
	{
		fout << left << "[" << setw(8) << bk.title << ", " << setw(8) << bk.author << ", (" << bk.pubDate << ") ]";
		return fout;
	}
public:
    Book(string bk_title, string bk_author, Date dt):title(bk_title), author(bk_author), pubDate(dt) {}
    string& getTitle() { return title; }
    string getAuthor() { return author; }
    Date getPubDate() { return pubDate; }
    void setTitle(string bk_title) { title = bk_title; }
    void setAuthor(string bk_author) { author = bk_author; }
private:
    string title;
    string author;
    Date pubDate;  // date of publish
};

#endif