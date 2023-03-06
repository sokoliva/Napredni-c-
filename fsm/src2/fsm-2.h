#pragma once
#include <memory>
#include <string>

class Event{
	// vaš kod
	public:
		virtual ~Event()=default;
		virtual std::string get_address() const =0;
};

class Connect final : public Event{
public:
	// vaš kod
	std::string address_;
	Connect(std::string address){address_=address;}
	std::string get_address() const {return address_;}
};

class Connected final : public Event{
	// vaš kod
	public:
		Connected(){}
		std::string get_address() const {}
};

class Disconnect final : public Event{
	// vaš kod
	public:
		Disconnect(){}
		std::string get_address() const {} // NEMA RETURN NAREDBE!? (return "";)
};

class Timeout final : public Event{
	// vaš kod
	public:
		Timeout(){}
		std::string get_address() const {}
};

class State{
	// vaš kod
	public:
		virtual ~State()=default;
		virtual std::unique_ptr<State> on_event(Event const & )=0;
};


class IdleState final : public State{
	// vaš kod
	public:
			IdleState(){}
			virtual std::unique_ptr<State> on_event(Event const &) override;	
};

class ConnectingState final : public State{
	// vaš kod
	public:
		static const int n_max = 3;
		int n;
	    ConnectingState(){n=0;}
		ConnectingState(ConnectingState &C){n=C.n;}
		virtual std::unique_ptr<State> on_event(Event const &) override;
	
};

class ConnectedState final : public State{
	// vaš kod
	public:
			ConnectedState(){}
			virtual std::unique_ptr<State> on_event(Event const &) override;
};

class FSM{
	// vaš kod
	public:
		std::unique_ptr<State> ptr;
		FSM(){
			ptr= std::make_unique<IdleState>();
		}
		// Vaš kod
		virtual void dispatch(Event const& event){
			ptr=std::move(ptr->on_event(event));
		}
};

