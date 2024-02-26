//
// Created by sgvch on 25/02/2024.
//

//#include "Field.h"
//
//
//void Field::addRate(float player_rate) {
//    if (numRates == capacity)
//    {
//        int new_capacity;
//        if(capacity == 0)
//            new_capacity = 1;
//        else
//            new_capacity = capacity * 2;
//        float * newRates = new float [new_capacity];
//
//        for (int i = 0; i < numRates; ++i) {
//            newRates[i] = rates[i];
//        }
//
//        delete [] rates;
//        rates = newRates;
//        capacity = new_capacity;
//    }
//    rates[numRates++] = player_rate;
//    cout << "Rating added successfully." << endl;
//}

//Order* Field::addOrder(const Order& order) {
//    // Check if the orders array is null or full
//    if (numRates == capacity) {
//        // Calculate new capacity (double the current capacity)
//        int new_capacity = (capacity == 0) ? 1 : capacity * 2;
//
//        // Create a new array with the new capacity
//        Order *newOrder;
//        newOrder = new Order[new_capacity];
//
//        // Copy existing orders to the new array
//        for (int i = 0; i < numRates; ++i) {
//            newOrder[i] = orders[i];
//        }
//
//        // Deallocate memory for the old array
//        delete[] orders;
//
//        // Update the pointer to the new array and capacity
//        orders = newOrder;
//        capacity = new_capacity;
//    }
//
//    // Add the new order to the end of the array
//    orders[numRates++] = order;
//
//    return &orders[numRates - 1]; // Return a pointer to the added order
//}