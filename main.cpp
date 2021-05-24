#include <iostream>
#include "queue.cpp"

using namespace std;

struct Cashier {
	bool active;
	int time_At;
};

int main() {
    Queue bank;

    // 8
    for (int i = 0; i < 8; i++)
    {
        bank.insert(4 + (rand() % 2));//change this random thing
    }

    const int ARRIVAL_TIME = 2;
    int c_time = 0;
    const int SIM_TIME = 30;
    int customers = 8;
    const int NUM_CASHIER = 3;
    int processed_customer = 0;

    //Dynamically allocate an array for the teller structure
		Cashier* cashierArray = new Cashier[NUM_CASHIER];
		
    //Set all tellers to empty
    for (int i = 0; i < NUM_CASHIER; i++) {
        cashierArray[i].active = false;
        cashierArray[i].time_At = 0;
    }

    while (c_time < SIM_TIME) {
        cout << "time\tno. of cust\n" << c_time+1 << "\t\t" << processed_customer << endl;

        if (c_time % ARRIVAL_TIME == 0) {
            bank.insert(4 + (rand() % 2)); //change this random thing
            customers++;
        }
        
        for (int i = 0; i < NUM_CASHIER; i++) {
            if (cashierArray[i].active == false && bank.get_size() != 0) { //Dequeue if a teller is open
                cashierArray[i].active = true;
                cashierArray[i].time_At = bank.peek();	
                bank.delete_element();					
            }
        }
			
			
        for (int i = 0; i < NUM_CASHIER; i++) {
            if (cashierArray[i].active == true) {
                cashierArray[i].time_At--;  //Decrement time spent at teller
            }
            if (cashierArray[i].active == true && cashierArray[i].time_At == 0) {
                cashierArray[i].active = false; //Set teller to open if time limit is reached
                processed_customer++;
            }
        }
        c_time++;
    }

    cout << "number of customers: " << customers;
}
