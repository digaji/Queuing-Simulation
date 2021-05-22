#include <iostream>
#include "queue.cpp"

using namespace std;

int main() {
    Queue bank;

    // 8
    bank.insert(1);
    bank.insert(1);
    bank.insert(1);
    bank.insert(1);
    bank.insert(1);
    bank.insert(1);
    bank.insert(1);
    bank.insert(1);

    const int ARRIVAL_TIME = 3;
    int c_time = 0;
    const int SIM_TIME = 30;
    int customers = 8;

    while (c_time < SIM_TIME) {
        if (c_time % ARRIVAL_TIME == 0) {
            bank.insert(1);
            customers++;
        }
        c_time++;
    }

    bank.display();
    cout << "number of customers: " << customers;
}
