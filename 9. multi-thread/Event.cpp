#include "Event.h"

Event::Event(int evt_id, int evt_pri, int evtGenAddr)
{
	event_no = evtGenAddr; 
	event_gen_addr = evt_id;
	event_handler_addr = -1;  // event handler is not defined at this moment
	event_pri = evt_pri;
	eventStatus = GENERATED;
}

Event* genRandEvent(int evt_no)
{
	Event* pEv;
	int evt_prio;
	int evt_generator_id;

	evt_prio = rand() % MAX_EVENT_PRIORITY;
	evt_generator_id = rand() % NUM_EVENT_GENERATORS;
	pEv = (Event*) new Event(evt_no, evt_prio, evt_generator_id);

	return pEv;
}

void Event::printEvent_proc()
{
	cout << "Ev(pri:" << setw(2) << event_pri << ", no:" << setw(2) << event_no;
	cout.precision(2);
	cout.setf(ios::fixed);
	cout << ", t_elapsed:" << setw(8) << t_elapsed_time_ms << ") ";
}

ostream& operator<<(ostream& fout, const Event& evt)
{
	fout << "Event(pri:" << setw(3) << evt.event_pri;
	fout << ", no:" << setw(3) << evt.event_no << ")";
	return fout;
}