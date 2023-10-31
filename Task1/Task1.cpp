#include <iostream>
#include <thread>
#include <atomic>

using namespace std::chrono_literals;

int max_clients = 8;
std::atomic<int> clients = 0;

void customers()
{
	do
	{
		std::this_thread::sleep_for(1000ms);
		clients.store(++clients, std::memory_order_relaxed);
		std::cout << clients.load() << std::endl;
	} while (clients.load() != max_clients);
}

void operators()
{
	do {
		std::this_thread::sleep_for(2000ms);
		clients.store(--clients, std::memory_order_relaxed);
		std::cout << clients.load() << std::endl;

	} while (clients.load() != 0);
}

int main()
{

	std::thread t1(customers);
	std::thread t2(operators);

	if (t1.joinable()) {
		t1.join();
	}
	if (t2.joinable()) {
		t2.join();
	}

	return 0;
}