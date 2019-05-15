#include<iostream>
#include<mutex>
#include<thread>
#include<limits>
#include<fstream>
#include<ostream>
#include<condition_variable>

// решение: сортировка пузырьком, один поток читает, а второй выводит; 
// выводим не в бинарный файл, т.к. про формат нового файла в условии 
// ничего не сказано;


uint64_t counter = 0;
std::mutex m;
std::condition_variable dataReady;
bool ready = false;
bool allarm = false;

void countN(std::string const& ifilename) {
	for (uint64_t x = 0; x <= std::numeric_limits<uint64_t>::max(); x++) {
		std::unique_lock<std::mutex> lock(m);
		while (!allarm) dataReady.wait(lock);
		counter = 0;
		std::ifstream in(ifilename, std::ios::binary | std::ios::in);
		for (uint64_t y; in.read((char *) &y, sizeof(uint64_t));) {
			if (y != x) continue;
			counter++;
			//std::cout << x << " ";
		}
		in.close();
		ready = true;
		allarm = false;
		lock.unlock();
		dataReady.notify_one();
	}
}

void writeX(std::string const& ofilename) {
	std::ofstream out(ofilename, std::ios_base::app);
	for (uint64_t x = 0; x <= std::numeric_limits<uint64_t>::max(); x++) {
		std::unique_lock<std::mutex> lock(m);
		allarm = true;
		dataReady.notify_one();
		while (!ready) dataReady.wait(lock);
		uint64_t local_counter = counter;
		
		for (uint64_t i = 0; i < local_counter; i++) {
			out << x << ' ';
		}
		ready = false;
		lock.unlock();
	}
	out.close();
}


int main() {
	std::thread t1(countN, "bin.bin");
	std::thread t2(writeX, "out.txt");

	t1.join();
	t2.join();

	return 0;
}
