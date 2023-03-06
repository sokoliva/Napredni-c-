#pragma once
#include <memory>
#include <string>
#include<iostream>

// Vaš kod dolazi ovdje. 
class Event;

class State{
	// vaš kod
	public:
		virtual ~State()=default;
		virtual std::unique_ptr<State> accept(Event const & )=0;
};

class IdleState final : public State{
	// vaš kod
	public:
			IdleState(){}
			std::unique_ptr<State> accept(Event const &) override;	
};

class ConnectingState final : public State{
	// vaš kod
	public:
		static const int n_max = 3;
		int n;
	    ConnectingState(){n=0;}
		ConnectingState(ConnectingState &C){n=C.n;}
		std::unique_ptr<State> accept(Event const &) override;	
};

class ConnectedState final : public State{
	// vaš kod
	public:
			ConnectedState(){}
			std::unique_ptr<State> accept(Event const &) override;
};

class Event{
	// vaš kod
	public:
		virtual ~Event()=default;
        virtual  std::unique_ptr<State> on_element(IdleState &) const = 0;
        virtual  std::unique_ptr<State> on_element(ConnectingState &) const = 0;
        virtual  std::unique_ptr<State> on_element(ConnectedState &) const = 0;
		//virtual std::string get_address() const =0;
};

class Connect final : public Event{
    public:
	// vaš kod
	    std::string address_;
	    Connect(std::string address){address_=address;}
	//std::string get_address() const {return address_;}
        std::unique_ptr<State> on_element(IdleState & S) const override{
            std::cout<<"IdleState->ConnectingState (";
            std::cout<<'"'<<address_<<'"'<<")\n";
            return std::make_unique<ConnectingState>();
        }
        std::unique_ptr<State> on_element(ConnectingState & S) const override{
            return nullptr;
        }
        std::unique_ptr<State> on_element(ConnectedState & S) const override{
            return nullptr;
        }
};

class Connected final : public Event{
	// vaš kod
	public:
		Connected(){}
		//std::string get_address() const {}
        std::unique_ptr<State> on_element(IdleState & S) const override{
            return nullptr;
        }
        std::unique_ptr<State> on_element(ConnectingState & S) const override{
            std::cout<<"ConnetingState->ConnectedState";
            std::cout<<"\n";
            return std::make_unique<ConnectedState>();
        }
        std::unique_ptr<State> on_element(ConnectedState & S) const override{
            return nullptr;
        }
};

class Disconnect final : public Event{
	// vaš kod
	public:
		Disconnect(){}
		//std::string get_address() const {}
        std::unique_ptr<State> on_element(IdleState & S) const override {
            return nullptr;
        }
        std::unique_ptr<State> on_element(ConnectingState & S) const override {
            return nullptr;
        }
        std::unique_ptr<State> on_element(ConnectedState & S) const override {
            std::cout<<"ConnectedState->IdleState \n";
            return std::make_unique<IdleState>();
        }
};

class Timeout final : public Event{
	// vaš kod
	public:
		Timeout(){}
        std::unique_ptr<State> on_element(IdleState & S) const override {
            return nullptr;
        }
        std::unique_ptr<State> on_element(ConnectedState & S) const override {
            return nullptr;
        }
        std::unique_ptr<State> on_element(ConnectingState & S) const override {
            S.n++;
            if(S.n<S.n_max){
                std::cout<<"ConnectingState->ConnectingState";
                std::cout<<"\n";
                return std::make_unique<ConnectingState>(S);
                } 
            std::cout<<"ConnectingState->IdleState";
            std::cout<<"\n";
            return std::make_unique<IdleState>();
        }		
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
			ptr=std::move(ptr->accept(event));
		}
};