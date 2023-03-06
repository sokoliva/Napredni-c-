#include "fsm-3.h"

// Ovaj kod ne mijenjati. 

template <typename... Events>
void dispatch(FSM & fsm, Events... events){
	(fsm.dispatch(events),...);
}

int main(){
	FSM fsm;
	dispatch(fsm, Connect{"www.test.com"}, Timeout{}, Timeout{}, Timeout{}, 
			 Connect{"www.google.com"}, Connected{}, Disconnect{}, Connect{"web.math.hr"}, 
			 Timeout{}, Timeout{}, Connected{}, Disconnect{});
	return 0;
}
