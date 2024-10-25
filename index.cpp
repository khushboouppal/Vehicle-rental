#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <ctime>
#include <algorithm>

using namespace std;

struct Vehicle {
    string numberPlate;
    string name;
    bool isAvailable;
};

struct Customer {
    string customerName;
    int age;
    string gender;
    string rentedVehiclePlate;
    string rentDate;
    string returnDate;
    double rentalAmount;
};

class VehicleRentalSystem {
private:
    vector<Vehicle> vehicles;
    vector<Customer> customers;

public:
    VehicleRentalSystem() {
        vehicles = {
            {"MH12AB1234", "Honda City", true},
            {"DL05MN6789", "Maruti Swift", true},
            {"KA01XY2468", "Hyundai Creta", true},
            {"TN10PQ3579", "Ford Endeavour", true},
            {"WB20RS8426", "Toyota Fortuner", true}
        };
    }

    void rentVehicle() {
        string customerName, gender, vehiclePlate;
        int age;
        cout << "\n--- Rent a Vehicle ---\n";
        cout << "Enter customer's name: ";
        cin.ignore();
        getline(cin, customerName);
        cout << "Enter customer's age: ";
        cin >> age;
        cout << "Enter customer's gender (M/F): ";
        cin >> gender;

        displayAvailableVehicles();
        cout << "Enter the vehicle number plate to rent: ";
        cin >> vehiclePlate;

        auto it = find_if(vehicles.begin(), vehicles.end(), 
                          [&vehiclePlate](const Vehicle& v) { return v.numberPlate == vehiclePlate; });

        if (it != vehicles.end() && it->isAvailable) {
            it->isAvailable = false;
            string rentDate = getCurrentDate();

            Customer customer = {customerName, age, gender, vehiclePlate, rentDate, "", 0.0};
            customers.push_back(customer);
            cout << "Vehicle rented successfully on " << rentDate << ".\n";
        } else {
            cout << "Vehicle not available or invalid plate number!\n";
        }
    }

    void returnVehicle() {
        string vehiclePlate;
        double amount;
        cout << "\n--- Return a Vehicle ---\n";
        cout << "Enter the vehicle number plate to return: ";
        cin >> vehiclePlate;

        auto it = find_if(customers.begin(), customers.end(), 
                          [&vehiclePlate](const Customer& c) { return c.rentedVehiclePlate == vehiclePlate; });

        if (it != customers.end() && it->returnDate.empty()) {
            it->returnDate = getCurrentDate();
            cout << "Enter the rental amount to be paid: ";
            cin >> amount;
            it->rentalAmount = amount;

            auto vehicleIt = find_if(vehicles.begin(), vehicles.end(), 
                                     [&vehiclePlate](const Vehicle& v) { return v.numberPlate == vehiclePlate; });
            if (vehicleIt != vehicles.end()) {
                vehicleIt->isAvailable = true;
                cout << "Vehicle returned successfully on " << it->returnDate << ".\n";
            }
        } else {
            cout << "Invalid vehicle plate or vehicle already returned!\n";
        }
    }

    void displayAvailableVehicles() const {
        cout << "\n--- Available Vehicles ---\n";
        for (const auto& vehicle : vehicles) {
            if (vehicle.isAvailable) {
                cout << "Number Plate: " << vehicle.numberPlate 
                     << " | Name: " << vehicle.name << "\n";
            }
        }
    }

    void displayAllRentals() const {
        cout << "\n--- Rental Records ---\n";
        cout << left << setw(15) << "Name" << setw(5) << "Age" 
             << setw(8) << "Gender" << setw(15) << "Vehicle Plate" 
             << setw(12) << "Rent Date" << setw(12) << "Return Date" 
             << setw(10) << "Amount" << "\n";
        cout << string(80, '-') << "\n";
        
        for (const auto& customer : customers) {
            cout << left << setw(15) << customer.customerName 
                 << setw(5) << customer.age 
                 << setw(8) << customer.gender 
                 << setw(15) << customer.rentedVehiclePlate 
                 << setw(12) << customer.rentDate 
                 << setw(12) << (customer.returnDate.empty() ? "N/A" : customer.returnDate) 
                 << setw(10) << (customer.rentalAmount == 0.0 ? "N/A" : to_string(customer.rentalAmount)) << "\n";
        }
    }

    string getCurrentDate() const {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        char date[11];
        strftime(date, sizeof(date), "%Y-%m-%d", ltm);
        return string(date);
    }
};

int main() {
    VehicleRentalSystem rentalSystem;

    while (true) {
        int choice;
        cout << "\n--- Vehicle Rental Hub ---\n";
        cout << "1. Rent a Vehicle\n";
        cout << "2. Return a Vehicle\n";
        cout << "3. Show Available Vehicles\n";
        cout << "4. Display All Rentals\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                rentalSystem.rentVehicle();
                break;
            case 2:
                rentalSystem.returnVehicle();
                break;
            case 3:
                rentalSystem.displayAvailableVehicles();
                break;
            case 4:
                rentalSystem.displayAllRentals();
                break;
            case 5:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }
}
