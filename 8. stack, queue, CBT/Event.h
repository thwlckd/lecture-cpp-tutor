#pragma once

#ifndef EVENT_H
#define EVENT_H

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <Windows.h> 

using namespace std;

enum EventStatus { GENERATED, ENQUEUED, PROCESSED, UNDEFINED };

#define MAX_EVENT_PRIORITY 100
#define NUM_EVENT_GENERATORS 10

class Event
{
	friend ostream& operator<<(ostream& fout, const Event& e);
public:
	Event() {}  // default constructor
	Event(int event_id, int event_pri, string title, int gen_addr); //constructor
	void printEvent(ostream& fout);
	void setEventHandlerAddr(int evtHndlerAddr) { event_handler_addr = evtHndlerAddr; }
	void setEventGenAddr(int genAddr) { event_gen_addr = genAddr; }
	void setEventNo(int evtNo) { event_no = evtNo; }
	void setEventPri(int pri) { event_pri = pri; }
	void setEventStatus(EventStatus evtStatus) { eventStatus = evtStatus; }
	int getEventPri() { return event_pri; }
	int getEventNo() { return event_no; }
	bool operator>(Event& e) { return (event_pri > e.event_pri); }
	bool operator<(Event& e) { return (event_pri < e.event_pri); }

	void set_elapsed_time(double t) { elapsed_time = t; }
	double get_elapsed_time() { return elapsed_time; }

	LARGE_INTEGER get_before_t() { return t_before; }
	void set_before_t(LARGE_INTEGER t) { t_before = t; }

	LARGE_INTEGER get_after_t() { return t_after; }
	void set_after_t(LARGE_INTEGER t) { t_after = t; }

protected:
	int event_no;
	string event_title;
	int event_gen_addr;
	int event_handler_addr;
	int event_pri; // event_priority
	EventStatus eventStatus;

	LARGE_INTEGER  t_before, t_after;

	double elapsed_time;

};

#endif