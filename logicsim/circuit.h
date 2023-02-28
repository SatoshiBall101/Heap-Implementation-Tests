#ifndef CIRCUIT_H
#define CIRCUIT_H
#include <vector>

#include "../heap.h"
#include "event.h"
#include "gate.h"

class Circuit 
{
	public:
		Circuit();
		~Circuit();
		void test(); // directly instantiate simple AND circuit
		bool advance(std::ostream&); // to simulate the circuit; advance the next set of events 
		void run(std::ostream&); // outputs a log of a certain wires change state
    bool parse(const char*);
    void startUml(std::ostream&); // generate timing design w/ java
    void endUml(std::ostream&); // generate timing design w/ java
		
	private:
		uint64_t m_current_time;
    std::vector<Gate*> m_gates; // pointers to gates in the circuit
    std::vector<Wire*> m_wires; // pointers to wires in the circuit
		Heap<Event*, EventLess> m_pq;
		// we need to add the m_pq data member. It should be a min-heap of Event*;
        
};

#endif