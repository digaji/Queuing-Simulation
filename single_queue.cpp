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
    Queue bank;
    srand (time(0));    // Randomize rand() output

    const int NUM_CASHIER = 3;
    int processed_customer = 0;
    int c_time = 0;
    int range, start_time, sim_time, arrival_time;

    cout << "Start of service time (e.g. 50): ";
    cin >> start_time;

    cout << "Range service time (e.g. 30): ";
    cin >> range;

    cout << "Arrival time: ";
    cin >> arrival_time;

    cout << "Simulation time (seconds): ";
    cin >> sim_time;

    std::ofstream myfile;
    myfile.open("single_queue.csv");
    myfile << "Start Time;Range;Arrival Time;Simulation Time\n" << start_time << ";" << range << ";" << arrival_time << ";" << sim_time << "\n\n";
    myfile << "Service Time;Processed Customers\n";

    // Start with 8 customers in the queue
    for (int i = 0; i < 8; i++) {
        bank.insert(rand() % range + start_time); // Random range from start -> start + range
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
            bank.insert(rand() % range + start_time);
        }

        for (int i = 0; i < NUM_CASHIER; i++) {
            if (cashierArray[i].active == false && bank.get_size() != 0) { // Dequeue if a teller is open
                cashierArray[i].active = true;
                cashierArray[i].time_At = bank.peek();
                bank.delete_element();
            }
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

    myfile.flush();
    myfile.close();
    cout << "\nTotal processed customers: " << processed_customer;

    // Prevent memory leaks
    delete cashierArray;
    cashierArray = NULL;
    bank.free();
}
