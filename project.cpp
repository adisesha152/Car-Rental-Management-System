#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

#define MAX_USERS 100
#define MAX_CARS 100

struct User {
    string username;
    string password;
    float balance;
};

struct Car {
    string company;
    string model;
    string color;
    string max_speed;
    int price;
};

int login(User users[], int numUsers);
void displayMenu(Car cars[], int numCars, User users[], int currentUserIndex);
void displayCarDetails(Car car);
void rentCar(User users[], Car cars[], int currentUserIndex, int carIndex);
void addCar(Car cars[], int* numCars);
void purchaseCar(User users[], Car cars[], int currentUserIndex, int* numCars);
void removeCar(Car cars[], int* numCars);
void insertBalance(User users[], int currentUserIndex);
int changeCredentials(User users[], int currentUserIndex);
void modifyCar(Car cars[], int numCars);
void readUserData(User users[], int& numUsers);
void writeUserData(User users[], int numUsers);
void readCarData(Car cars[], int& numCars);
void writeCarData(Car cars[], int numCars);
void readCarDetails(Car& car);

int main() {
    User users[MAX_USERS];
    int numUsers;

    Car cars[MAX_CARS];
    int numCars;

    readUserData(users, numUsers);
    readCarData(cars, numCars);

    int currentUserIndex = login(users, numUsers);

    if (currentUserIndex != -1) {
        displayMenu(cars, numCars, users, currentUserIndex);
    }

    return 0;
}

int login(User users[], int numUsers) {
    string username;
    string password;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < numUsers; ++i) {
        if (users[i].username == username && users[i].password == password) {
            cout << "Login successful!\n\n";
            return i;
        }
    }

    cout << "Login failed. Incorrect username or password.\n\n";
    return -1;
}

void displayMenu(Car cars[], int numCars, User users[], int currentUserIndex) {
    int choice;
    int numUsers;

    do {
        cout << "\nCar Rental Management System Menu:\n";
        cout << "1. Add a new car\n";
        cout << "2. Modify a car\n";
        cout << "3. Remove a Car\n";
        cout << "4. Purchase a Car\n";
        cout << "5. Display available cars\n";
        cout << "6. Change username and password\n";
        cout << "7. Insert user balance\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 5:
                if(numCars>0)
                {
                    for (int i = 0; i < numCars; ++i) {
                    cout << "\nCar " << i + 1 << ":\n";
                    displayCarDetails(cars[i]);
                    }
                }
                else
                {
                    cout<<"No Cars available to display.\n";
                }
                break;
            case 1:
                if (currentUserIndex == 0) {
                    addCar(cars, &numCars);
                    writeCarData(cars, numCars);
                } else {
                    cout << "Permission denied. Only admin can add new cars.\n";
                }
                break;
            case 2:
                if (currentUserIndex == 0) {
                    modifyCar(cars, numCars);
                    writeCarData(cars, numCars);
                } else {
                    cout << "Permission denied. Only admin can modify cars.\n";
                }
                break;
            case 6:
                fflush(stdin);
                currentUserIndex = changeCredentials(users, currentUserIndex);
                readUserData(users, numUsers);
                writeUserData(users, numUsers);
                break;
            case 7:
                insertBalance(users, currentUserIndex);
                writeUserData(users, numUsers);
                break;
            case 8:
                cout << "Exiting the program. Goodbye!\n";
                break;
            case 3:
                if (currentUserIndex == 0) {
                    removeCar(cars, &numCars);
                    writeCarData(cars, numCars);
                } else {
                    cout << "Permission denied. Only admin can remove cars.\n";
                }
                break;
            case 4:
                purchaseCar(users, cars, currentUserIndex, &numCars);
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 8);
}

void displayCarDetails(Car car) {
    cout << "Company: " << car.company << "\n";
    cout << "Model: " << car.model << "\n";
    cout << "Color: " << car.color << "\n";
    cout << "Max Speed: " << car.max_speed << "\n";
    cout << "Price: " << car.price << " K\n";
}

void addCar(Car cars[], int* numCars) {
    if (*numCars < MAX_CARS) {
        cout << "Enter car details:\n";
        fflush(stdin);
        readCarDetails(cars[*numCars]);

        (*numCars)++;
        cout << "Car added successfully!\n";
    } else {
        cout << "Cannot add more cars. Maximum limit reached.\n";
    }
}

int changeCredentials(User users[], int currentUserIndex) {
    string newUsername;
    string newPassword;

    cout << "Enter new username: ";
    getline(cin, newUsername);

    cout << "Enter new password: ";
    cin >> newPassword;

    users[currentUserIndex].username = newUsername;
    users[currentUserIndex].password = newPassword;

    cout << "Username and password changed successfully!\n";

    return currentUserIndex;
}

void modifyCar(Car cars[], int numCars) {
    int carIndex;

    cout << "Enter the index of the car to modify (1-" << numCars << "): ";
    cin >> carIndex;

    if (carIndex >= 1 && carIndex <= numCars) {
        cout << "Enter new details for the car:\n";
        fflush(stdin);
        readCarDetails(cars[carIndex - 1]);

        cout << "Car modified successfully!\n";
    } else {
        cout << "Invalid car index. Please enter a valid index.\n";
    }
}

void removeCar(Car cars[], int* numCars) {
    if (*numCars > 0) {
        int carIndex;

        cout << "Enter the index of the car to remove (1-" << *numCars << "): ";
        cin >> carIndex;

        if (carIndex >= 1 && carIndex <= *numCars) {
            cars[carIndex - 1] = cars[*numCars - 1];

            (*numCars)--;
            cout << "Car removed successfully!\n";
        } else {
            cout << "Invalid car index. Please enter a valid index.\n";
        }
    } else {
        cout << "No cars available to remove.\n";
    }
}

void purchaseCar(User users[], Car cars[], int currentUserIndex, int* numCars) {
    if (*numCars > 0) {
        int carIndex;

        cout << "Enter the index of the car to purchase (1-" << *numCars << "): ";
        cin >> carIndex;

        if (carIndex >= 1 && carIndex <= *numCars) {
            cars[carIndex - 1] = cars[*numCars - 1];
            (*numCars)--;
            writeCarData(cars, *numCars);
            users[currentUserIndex].balance -= cars[carIndex - 1].price;
            writeUserData(users, *numCars);
            cout << "Car purchased successfully!\n";
        } else {
            cout << "Invalid car index. Please enter a valid index.\n";
        }
    } else {
        cout << "No cars available to purchase.\n";
    }
}

void insertBalance(User users[], int currentUserIndex) {
    float newBalance;

    cout << "Enter the new balance for the user: ";
    cin >> newBalance;

    users[currentUserIndex].balance = newBalance;

    cout << "Balance inserted successfully!\n";
}

void readUserData(User users[], int& numUsers) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cout << "Error opening file: users.txt\n";
        perror("Error");
        exit(1);
    }

    file >> numUsers;
    for (int i = 0; i < numUsers; ++i) {
        if (!(file >> users[i].username >> users[i].password >> users[i].balance)) {
            cerr << "Error reading user data from file.\n";
            file.close();
            exit(1);
        }
    }

    file.close();
}

void writeUserData(User users[], int numUsers) {
    ofstream file("users.txt");
    if (!file.is_open()) {
        cout << "Error opening file: users.txt\n";
        exit(1);
    }

    file << numUsers << '\n';
    for (int i = 0; i < numUsers; ++i) {
        file << users[i].username << ' ' << users[i].password << ' ' << users[i].balance << '\n';
    }

    file.close();
}

void readCarData(Car cars[], int& numCars) {
    ifstream file("cars.txt");
    if (!file.is_open()) {
        cout << "Error opening file: cars.txt\n";
        exit(1);
    }

    file >> numCars;
    for (int i = 0; i < numCars; ++i) {
        if (!(file >> cars[i].company >> cars[i].model >> cars[i].color >> cars[i].max_speed >> cars[i].price)) {
            cerr << "Error reading car data from file.\n";
            file.close();
            exit(1);
        }
    }

    file.close();
}

void writeCarData(Car cars[], int numCars) {
    ofstream file("cars.txt");
    if (!file.is_open()) {
        cout << "Error opening file: cars.txt\n";
        exit(1);
    }

    file << numCars << '\n';
    for (int i = 0; i < numCars; ++i) {
        file << cars[i].company << ' ' << cars[i].model << ' ' << cars[i].color << ' ' << cars[i].max_speed << ' ' << cars[i].price << ' ' <<'\n';
    }

    file.close();
}

void readCarDetails(Car& car) {
    cout << "Company: ";
    getline(cin, car.company);

    cout << "Model: ";
    getline(cin, car.model);

    cout << "Color: ";
    getline(cin, car.color);

    cout << "Max Speed: ";
    getline(cin, car.max_speed);

    cout << "Price (in K): ";
    cin >> car.price;
}
