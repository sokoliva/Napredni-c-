#include "fsm-1.h"
//#include <fmt/format.h>

// Vaš kod

std::unique_ptr<State> IdleState::on_event(Event event){
    if(event==Event::connect){
        std::cout<<"IdleState->ConnectingState";
        std::cout<<"\n";
        return std::make_unique<ConnectingState>();}
    else return nullptr;  
}

std::unique_ptr<State> ConnectingState::on_event(Event event){
    if(event==Event::timeout){
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
    if(event==Event::connected){
        std::cout<<"ConnetingState->ConnectedState";
        std::cout<<"\n";
        return std::make_unique<ConnectedState>();
        }
    else return nullptr;
}

std::unique_ptr<State> ConnectedState::on_event(Event event){
    if(event==Event::disconnect) {
        std::cout<<"ConnectedState->IdleState";
        std::cout<<"\n";
        return std::make_unique<IdleState>();}
    else return nullptr;  
}

