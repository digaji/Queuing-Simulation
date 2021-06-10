#include <iostream>
#include <ctime>
#include <fstream>
#include <chrono>
#include <cmath>
#include "queue.cpp"

using namespace std;

struct Cashier {
	bool active;
	int time_At;
};

int main() {
    Queue bank1;
    Queue bank2;
    Queue bank3;
    srand (time(0));    // Randomize rand() output

    std::ofstream myfile;
    myfile.open ("multi_queue.csv");
    myfile << "service time;processed customers\n";

    const int NUM_CASHIER = 3;
    int processed_customer = 0;
    int c_time = 0;
    int range, start_time, sim_time, arrival_time;

    cout << "Start of service time (e.g. 50): ";
    cin >> start_time;

    cout << "Range service time (e.g. 30): ";
    cin >> range;

    cout << "Arrival time (must be between the range of service time): ";
    cin >> arrival_time;

    cout << "Simulation time (seconds): ";
    cin >> sim_time;

    // Start with 8 customers in the queue
    for (int i = 0; i < 8; i++) {
        bank1.insert(rand() % range + start_time); // Random range from start -> start + range
        bank2.insert(rand() % range + start_time);
        bank3.insert(rand() % range + start_time);
    }

    // Dynamically allocate an array for the teller structure
    Cashier* cashierArray = new Cashier[NUM_CASHIER];

    // Set all tellers to empty
    for (int i = 0; i < NUM_CASHIER; i++) {
        cashierArray[i].active = false;
        cashierArray[i].time_At = 0;
    }

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    int elapsed_time = int(chrono::duration_cast<chrono::seconds> (end - start).count());

    while (elapsed_time < sim_time) {

        if (c_time % arrival_time == 0){
            // Keep adding customers to the queue
            bank1.insert(rand() % range + start_time);
            bank2.insert(rand() % range + start_time);
            bank3.insert(rand() % range + start_time);
        }
        

        if (cashierArray[0].active == false && bank1.get_size() != 0) { // Dequeue if teller1 is open
            cashierArray[0].active = true;
            cashierArray[0].time_At = bank1.peek();
            bank1.delete_element();
        }

        if (cashierArray[1].active == false && bank2.get_size() != 0) { // Dequeue if teller2 is open
            cashierArray[1].active = true;
            cashierArray[1].time_At = bank2.peek();
            bank2.delete_element();
        }

        if (cashierArray[2].active == false && bank3.get_size() != 0) { // Dequeue if teller3 is open
            cashierArray[2].active = true;
            cashierArray[2].time_At = bank3.peek();
            bank3.delete_element();
        }

        for (int i = 0; i < NUM_CASHIER; i++) {
            if (cashierArray[i].active == true) {
                cashierArray[i].time_At--;      // Decrement time spent at teller
            }

            if (cashierArray[i].active == true && cashierArray[i].time_At == 0) {
                cashierArray[i].active = false; // Set teller to open if time limit is reached
                processed_customer++;
            }
        }

        int previous_time = elapsed_time;

        end = chrono::steady_clock::now();
        elapsed_time = int(chrono::duration_cast<chrono::seconds> (end - start).count());

        if (elapsed_time != previous_time) {
            myfile << elapsed_time << ";" << processed_customer << "\n";
            cout << elapsed_time << " ";
        }

        c_time++;
    }

    myfile.close();
    cout << "\nTotal processed customers:\t" << processed_customer;


    // Prevent memory leaks
    delete cashierArray;
    cashierArray = NULL;
    bank1.free();
    bank2.free();
    bank3.free();
}
