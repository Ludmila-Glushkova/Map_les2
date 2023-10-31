﻿#include <iostream>
#include <windows.h>
#include <locale.h>
#include <thread>
#include <mutex>
#include <chrono>
#include <vector>
#include "ConsParam.h"

using namespace std::chrono_literals;

std::mutex m;

void ProgressBar(int threads, int ind, int wid) {

    m.lock();
    consoleParameter::setPos(1, ind);
    std::cout << ind;
    consoleParameter::setPos(5, ind);
    std::cout << std::this_thread::get_id();
    m.unlock();

    auto start = std::chrono::high_resolution_clock::now();
    for (int j = 16; j < wid + 16; ++j) {
        std::this_thread::sleep_for(400ms);
        m.lock();
        consoleParameter::setPos(j, ind);
        std::cout << "-";
        m.unlock();
    }

    m.lock();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> time = end - start;
    consoleParameter::setPos(40, ind);
    std::cout << time.count();
    m.unlock();
}

void create(int threads, int wid) {
    std::vector<std::thread> t;
    std::cout << " #\t" << "Id\t" << "Progress Bar\t" << "\tTime" << std::endl;
    for (int i = 0; i < threads; ++i)
    {
        std::thread thread(ProgressBar, threads, i+1, wid);
        t.push_back(move(thread));
    }

    for (int i = 0; i < threads; ++i)
    {
        t[i].join();
    }
}

int main()
{

    const int threads = 10;
    const int wid = 20;
    create(threads, wid);
}