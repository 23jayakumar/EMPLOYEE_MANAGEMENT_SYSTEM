#include <iostream>    
#include <vector>      
#include <iomanip>     
using namespace std;


// Employee class definition

class Employee {
private:
    int employeeID;
    string name;
    float salary;
    string department;

public:
    // Constructor to initialize employee data
    Employee(int id, string n, float s, string dept) {
        employeeID = id;
        name = n;
        salary = s;
        department = dept;
    }

    // Getter methods
    int getID() const { return employeeID; }
    string getName() const { return name; }
    float getSalary() const { return salary; }
    string getDepartment() const { return department; }

    // Setter methods
    void setSalary(float newSalary) { salary = newSalary; }
    void setDepartment(string newDept) { department = newDept; }

    // Calculate net salary after 10% tax
    float calculateNetSalary() const {
        return salary * 0.9;
    }

    // Display employee details
    void display() const {
        cout << fixed << setprecision(2);
        cout << "ID: " << employeeID
             << ", Name: " << name
             << ", Salary: $" << salary
             << ", Department: " << department
             << ", Net Salary: $" << calculateNetSalary() << "\n";
    }
};

// Vector to store list of employees
vector<Employee> employeeList;


// Utility Functions:


// Finds the index of an employee by ID
int findEmployeeIndex(int id) {
    for (int i = 0; i < employeeList.size(); i++) {
        if (employeeList[i].getID() == id) return i;
    }
    return -1; // Not found
}

// Pauses the screen until user presses Enter
void pause() {
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}


// Core Functionalities:


// Add a new employee to the system
void addEmployee() {
    int id;
    string name, department;
    float salary;

    cout << "Enter Employee ID: ";
    cin >> id;

    // Input validation
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. ID must be a number.\n";
        pause();
        return;
    }

    // Check for duplicate ID
    if (findEmployeeIndex(id) != -1) {
        cout << "Employee with this ID already exists.\n";
        pause();
        return;
    }

    cin.ignore(); // Clear buffer
    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Salary: ";
    cin >> salary;

    // Salary input validation
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Salary must be a number.\n";
        pause();
        return;
    }

    cin.ignore(); // Clear buffer
    cout << "Enter Department: ";
    getline(cin, department);

    // Create and add new employee
    Employee emp(id, name, salary, department);
    employeeList.push_back(emp);

    cout << "Employee added successfully!\n";
    pause();
}

// Display all employees
void viewEmployees() {
    if (employeeList.empty()) {
        cout << "No employees to display.\n";
    } else {
        cout << "\n--- Employee List ---\n";
        for (const auto& emp : employeeList) {
            emp.display();
        }
        cout << "----------------------\n";
    }
    pause();
}

// Update an existing employee's data
void updateEmployee() {
    int id;
    cout << "Enter Employee ID to update: ";
    cin >> id;

    // ID input validation
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        pause();
        return;
    }

    int index = findEmployeeIndex(id);
    if (index == -1) {
        cout << "Employee not found.\n";
        pause();
        return;
    }

    // Ask what to update
    int choice;
    cout << "1. Update Salary\n2. Update Department\nChoose option: ";
    cin >> choice;
    cin.ignore(); // Clear buffer

    if (choice == 1) {
        float newSalary;
        cout << "Enter new salary: ";
        cin >> newSalary;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input for salary.\n";
        } else {
            employeeList[index].setSalary(newSalary);
            cout << "Salary updated.\n";
        }

    } else if (choice == 2) {
        string newDept;
        cout << "Enter new department: ";
        getline(cin, newDept);
        employeeList[index].setDepartment(newDept);
        cout << "Department updated.\n";
    } else {
        cout << "Invalid choice.\n";
    }
    pause();
}

// Delete an employee from the system
void deleteEmployee() {
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    // ID input validation
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input.\n";
        pause();
        return;
    }

    int index = findEmployeeIndex(id);
    if (index == -1) {
        cout << "Employee not found.\n";
    } else {
        employeeList.erase(employeeList.begin() + index);
        cout << "Employee deleted successfully.\n";
    }
    pause();
}

// Display the main menu
void showMenu() {
    cout << "\n=== Employee Management System ===\n";
    cout << "1. Add Employee\n";
    cout << "2. View Employees\n";
    cout << "3. Update Employee\n";
    cout << "4. Delete Employee\n";
    cout << "5. Exit\n";
    cout << "Choose an option: ";
}


// Main Program Execution

int main() {
    int choice;

    // Run the menu in a loop until user exits
    do {
        showMenu();
        cin >> choice;

        // Menu input validation
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number between 1-5.\n";
            continue;
        }

        // Perform action based on user choice
        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: updateEmployee(); break;
            case 4: deleteEmployee(); break;
            case 5: cout << "Exiting the program.\n"; break;
            default: cout << "Invalid choice. Try again.\n"; pause();
        }

    } while (choice != 5); // Exit loop if user chooses 5

    return 0;
}

