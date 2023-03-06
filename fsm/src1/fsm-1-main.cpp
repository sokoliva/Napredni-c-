#include "fsm-1.h"

// Ovdje ništa ne mijenjati. 
template <typename... Events>
void dispatch(FSM & fsm, Events... events){
	(fsm.dispatch(events),...);
}

int main(){
	FSM fsm;
	dispatch(fsm, State::connect, State::timeout, State::timeout, State::timeout, 
			 State::connect, State::connected, State::disconnect, State::connect, State::timeout,
			 State::connected, State::disconnect);
	return 0;
}
