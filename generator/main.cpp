#define _USE_MATH_DEFINES
#include <coroutine>
#include <thread>
#include <chrono>
#include <iostream>
#include <cmath>
#include <ranges>
#include <cassert>

class Task{
public:
    struct promise_type{
        double current_value;
        auto get_return_object(){ return Task(std::coroutine_handle<promise_type>::from_promise(*this)); }
        auto initial_suspend() { return std::suspend_always{}; }
        auto final_suspend() noexcept { return std::suspend_always{}; }
        void return_void() { }
        void unhandled_exception(){ std::terminate(); }
        auto yield_value(double val) noexcept {
            current_value = std::move(val);
            return std::suspend_always{};
        }
    };

    struct iterator{
        std::coroutine_handle<promise_type> handle;
        iterator(auto h) : handle{h} {}

        void next(){  // Pomoćna rutina koju koristimo u ++ i begin()
            if(handle)
                handle.resume();
            if(handle.done())
                handle = nullptr;
        }

        iterator & operator++(){
            next();
            return *this;
        }
        double operator*() const{
            assert(handle != nullptr);
            return handle.promise().current_value;
        }
        bool operator==(iterator const &) const = default;
    };

private:
    std::coroutine_handle<promise_type> cHandle;
public:
    Task(auto h) : cHandle{h} {}
    Task() = default;
    ~Task(){
        if(cHandle)
            cHandle.destroy();
    }
    Task(Task const &) = delete;
    Task& operator=(Task const &) = delete;

    bool resume() const{
        if(!cHandle)
            return false;
        cHandle.resume();
        return !cHandle.done();
    }
    auto getValue(){
        return cHandle.promise().current_value;
    }

    iterator begin() const {
        if(!cHandle || cHandle.done()){
            return iterator{nullptr};
            }
        iterator it{cHandle};
        it.next(); // da prva
        return it;
    }

    iterator end() const {
        return iterator{nullptr};
    }
};


Task wallis(){
    double x0 = M_PI/2;
    double x1 = 1;
    double x2;
    co_yield x0;
    co_yield x1;
    double n = 2;
    while(1){
        x2 = ((n-1)/(n++))*x0;
        x0 = x1;
        x1 = x2;
        co_yield x2;
    }
}


int main(){
    using namespace std::literals;

    Task generator = wallis();

    int i = 0;
    for(double x : generator){
		std::cout << "I_" << i++ <<" : " << (double)x << "\n";;
		std::this_thread::sleep_for(1s);
		if(i > 10) break;
    }
    return 0;
}
