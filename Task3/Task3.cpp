#include <iostream>
#include <mutex>
#include <thread>

class Data {
public:
    Data(int val) : dat(val) {}

    void set_data(int val)
    {
        dat = val;
    }
    
    int get_data()
    {
        return dat;
    }

    std::mutex& get_mutex()
    {
        return m;
    }

private:
    int dat;
    std::mutex m;
};

void print(Data& A, Data& B)
{
    std::cout << "A = " << A.get_data() << std::endl;
    std::cout << "B = " << B.get_data() << std::endl;
}

void swap1(Data& A, Data& B) //scoped_lock
{
    std::mutex& m1 = A.get_mutex();
    std::mutex& m2 = B.get_mutex();
    std::scoped_lock l(m1, m2);
    std::cout << "\nscoped_lock: \n";
    print(A, B);
    int tmp = A.get_data();
    A.set_data(B.get_data());
    B.set_data(tmp);
    print(A, B);
}

void swap2(Data& A, Data& B)//lock
{
    std::lock(A.get_mutex(), B.get_mutex());
    std::cout << "\nlock: \n";
    print(A, B);
    int tmp = A.get_data();
    A.set_data(B.get_data());
    B.set_data(tmp);
    print(A, B);
    A.get_mutex().unlock();
    B.get_mutex().unlock();
}

void swap3(Data& A, Data& B)//unique_lock
{
    std::unique_lock<std::mutex> unloc1(A.get_mutex(), std::defer_lock);
    std::unique_lock<std::mutex> unloc2(B.get_mutex(), std::defer_lock);  
    std::lock(unloc1, unloc2);
    std::cout << "\nunique_lock: \n";
    print(A, B);
    int tmp = A.get_data();
    A.set_data(B.get_data());
    B.set_data(tmp);
    print(A, B);
}


int main()
{
    Data A(1);
    Data B(2);

    std::thread t1(swap1, std::ref(A), std::ref(B));
    std::thread t2(swap2, std::ref(A), std::ref(B));
    std::thread t3(swap3, std::ref(A), std::ref(B));

    t1.join();
    t2.join();
    t3.join();
}