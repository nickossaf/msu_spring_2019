#include<iostream>
#include<mutex>
#include<thread>

const int MAX_N = 1000000;
std::mutex m;
int counter = 0;

void ping(){
    while(counter < MAX_N - 1){
        if(counter % 2 == 0){
            std::lock_guard<std::mutex> lock(m);
            //std::cout << counter << std::endl;
            std::cout << "ping" << std::endl;
            counter++;
        }
        std::this_thread::yield();
    }
}

void pong(){
    while(counter < MAX_N){
        if(counter % 2 == 1){
            std::lock_guard<std::mutex> lock(m);
            //std::cout << counter << std::endl;
            std::cout << "pong" << std::endl;
            counter++;
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
