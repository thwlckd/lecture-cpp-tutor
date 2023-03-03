#include "Event.h"

Event::Event(int evt_id, int evt_pri, string title, int gen_addr)
{
	event_no = evt_id;
	event_title = title;
	event_gen_addr = gen_addr;
	event_handler_addr = -1;
	event_pri = evt_pri;
	eventStatus = GENERATED;
}

Event* genRandEvent(int evt_no)
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;

	string title;
	int title_length;
	title_length = rand() % 3 + 4;  // 4~6글자
	title[0] = rand() % 26 + 'A';  // 첫글자 랜덤 대문자 알파벳
	for (int i = 1; i < title_length; i++)
	{
		title[i] = rand() % 26 + 'a';  // 나머지 랜덤 소문자 알파벳
	}
	evt_prio = rand() % MAX_EVENT_PRIORITY;
	evt_generator_id = rand() % NUM_EVENT_GENERATORS;
	pEv = (Event*) new Event(evt_no, evt_prio, title, evt_generator_id);  // rand_event 생성

	return pEv;
}

void Event::printEvent(ostream& fout)
{
	fout << "Event(pri:" << setw(3) << event_pri << ", gen:" << setw(3) << event_gen_addr;
	fout << ", no:" << setw(3) << event_no << ")";
}

ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Event(pri:" << setw(3) << evt.event_pri << ", gen:" << setw(3) << evt.event_gen_addr;
	fout << ", no:" << setw(3) << evt.event_no << ")";

	return fout;
}