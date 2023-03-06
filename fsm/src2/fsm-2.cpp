#include "fsm-2.h"
#include<iostream>
//#include <fmt/format.h>

// vaš kod

std::unique_ptr<State> IdleState::on_event(Event const & event){
    if(dynamic_cast<const Connect *>(&event) ){
        std::cout<<"IdleState->ConnectingState (";
        std::cout<<'"'<<(event).get_address()<<'"'<<")\n";
        return std::make_unique<ConnectingState>();}
    else return nullptr;    
}

std::unique_ptr<State> ConnectingState::on_event(Event const & event){
    if(dynamic_cast<const Timeout *>(&event)){
        n++;
        if(n<n_max){
            std::cout<<"ConnectingState->ConnectingState";
            std::cout<<"\n";
            return std::make_unique<ConnectingState>(*this);
        } 
        std::cout<<"ConnectingState->IdleState";
        std::cout<<"\n";
        return std::make_unique<IdleState>();
    }
    if(dynamic_cast<const Connected *>(&event)){
        std::cout<<"ConnetingState->ConnectedState";
        std::cout<<"\n";
        return std::make_unique<ConnectedState>();
        }
    else return nullptr;
}

std::unique_ptr<State> ConnectedState::on_event(Event const & event){
    if(dynamic_cast<const Disconnect *>(&event)) {
        std::cout<<"ConnectedState->IdleState";
        std::cout<<"\n";
        return std::make_unique<IdleState>();}
    else return nullptr;   
}
