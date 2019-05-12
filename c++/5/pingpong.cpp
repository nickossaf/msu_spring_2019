#include<iostream>
#include<mutex>
#include<thread>

const int MAX_N = 1000000;
std::mutex m;
int counter = 0;

void ping(){
    while(counter < MAX_N){
        if(counter % 2 == 0 && m.try_lock()){
            std::cout << "ping" << std::endl;
            counter++;
            m.unlock();
        }
        std::this_thread::yield();
    }
}

void pong(){
    while(counter < MAX_N){
        if(counter % 2 == 1 && m.try_lock()){
            std::cout << "pong" << std::endl;
            counter++;
            m.unlock();
        }
        std::this_thread::yield();
    }
}


int main(){
    std::thread t1(ping);
    std::thread t2(pong);

    t1.join();
    t2.join();

    return 0;
}
