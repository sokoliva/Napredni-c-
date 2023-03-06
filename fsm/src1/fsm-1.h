#pragma once
#include <memory>
#include<iostream>

class State{
	public:
		enum Event {connect, connected, disconnect, timeout};
		// Vaš kod
		virtual ~State()=default;
		virtual std::unique_ptr<State> on_event(Event)=0;
};


class IdleState final : public State{
		// Vaš kod
		public:
			IdleState(){}
			virtual std::unique_ptr<State> on_event(Event) override;
};

class ConnectingState final : public State{
		// Vaš kod
	public:
		static const int n_max = 3;
		int n;
	    ConnectingState(){n=0;}
		ConnectingState(ConnectingState &C){n=C.n;}
		virtual std::unique_ptr<State> on_event(Event) override;
	
};

class ConnectedState final : public State{
		// Vaš kod
		public:
			ConnectedState(){}
			virtual std::unique_ptr<State> on_event(Event) override;
};

class FSM{
	public:
		std::unique_ptr<State> ptr;
		FSM(){
			ptr= std::make_unique<IdleState>();
		}
		// Vaš kod
		virtual void dispatch(State::Event event){
			ptr=std::move(ptr->on_event(event));
		}
};

