// Flood Relief Camp Management System
// Developed for BSCS Semester 4 - IIUI

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// Base class for common person details
class Person
{
protected:
    string name;
    int age;
    string cnic;

public:
    Person(string n = "", int a = 0, string id = "") : name(n), age(a), cnic(id) {}

    void inputBasicInfo()
    {
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter CNIC: ";
        cin >> cnic;
        cin.ignore();
    }

    void displayBasicInfo() const
    {
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "CNIC: " << cnic << endl;
    }
};

// Beneficiary class inherits from Person
class Beneficiary : public Person
{
    string aidType;

public:
    Beneficiary() : Person(), aidType("") {}

    void registerBeneficiary()
    {
        inputBasicInfo();
        cout << "Enter type of aid needed (food/water/medicine/shelter): ";
        getline(cin, aidType);
    }

    void showDetails() const
    {
        displayBasicInfo();
        cout << "Aid Required: " << aidType << endl;
    }

    void saveToFile(ofstream &outfile) const
    {
        outfile << name << "," << age << "," << cnic << "," << aidType << endl;
    }
};

// Camp Management System
class ReliefCamp
{
    vector<Beneficiary> beneficiaries;

public:
    void addBeneficiary()
    {
        Beneficiary b;
        b.registerBeneficiary();
        beneficiaries.push_back(b);
        cout << "Beneficiary registered successfully!\n";
    }

    void viewAllBeneficiaries() const
    {
        if (beneficiaries.empty())
        {
            cout << "No beneficiaries registered yet.\n";
            return;
        }
        for (size_t i = 0; i < beneficiaries.size(); ++i)
        {
            cout << "\n--- Beneficiary " << i + 1 << " ---\n";
            beneficiaries[i].showDetails();
        }
    }

    void saveAllData() const
    {
        ofstream file("beneficiaries.txt", ios::out);
        for (const auto &b : beneficiaries)
        {
            b.saveToFile(file);
        }
        file.close();
        cout << "Data saved to beneficiaries.txt\n";
    }
};

int main()
{
    ReliefCamp camp;
    int choice;

    do
    {
        cout << "\n===== Flood Relief Camp Management =====\n";
        cout << "1. Register Beneficiary\n";
        cout << "2. View All Beneficiaries\n";
        cout << "3. Save Data to File\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // To handle newline after number input

        switch (choice)
        {
        case 1:
            camp.addBeneficiary();
            break;
        case 2:
            camp.viewAllBeneficiaries();
            break;
        case 3:
            camp.saveAllData();
            break;
        case 0:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    return 0;
}