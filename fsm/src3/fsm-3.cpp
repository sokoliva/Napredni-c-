#include "fsm-3.h"
//#include <fmt/format.h>

// Vaš kod dolazi ovdje.
std::unique_ptr<State> IdleState::accept(Event const & v){
         return v.on_element(*this);
}

std::unique_ptr<State> ConnectingState::accept(Event const & v){
         return v.on_element(*this);
}

std::unique_ptr<State> ConnectedState::accept(Event const & v){
         return v.on_element(*this);
}

