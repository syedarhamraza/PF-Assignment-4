#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct hospital
{
    int id;
    string name;
    int age;
    string disease;
    int roomNumber;
};

const int maxPatients = 20;
hospital patients[maxPatients];
int patientCount = 0;

void loadPatients()
{
    ifstream mypatients("hospital.txt");
    if (mypatients.is_open())
    {
        mypatients >> patientCount;
        mypatients.ignore();
        for (int i = 0; i < patientCount; i++)
        {
            mypatients >> patients[i].id;
            mypatients.ignore();
            getline(mypatients, patients[i].name);
            mypatients >> patients[i].age;
            mypatients.ignore();
            getline(mypatients, patients[i].disease);
            mypatients >> patients[i].roomNumber;
        }
    }
    else
    {
        cout << "Error Loading Patients!. Starting fresh.";
    }
    mypatients.close();
}

bool isPatientIdUnique(int userPatientId)
{
    for (int i = 0; i < patientCount; i++)
    {
        if (userPatientId == patients[i].id)
        {
            return false;
        }
    }
    return true;
}

void addPatient()
{
    cout << "**************Hospital Management System**************" << endl;
    if (patientCount >= maxPatients)
    {
        cout << "\nDatabase is full!\n";
    }
    else
    {
        hospital patient;
        cout << endl;
        cout << endl;
        cout << "Enter Patient ID: ";
        cin >> patient.id;
        if (isPatientIdUnique(patient.id) == false)
        {
            for (int i = 0; i < 10; i++)
            {
                cout << endl;
            }
            cout << "\nID Taken!\n";
            return;
        }
        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, patient.name);
        cout << "Enter Patient Age: ";
        cin >> patient.age;
        cout << "Enter Patient Disease: ";
        cin.ignore();
        getline(cin, patient.disease);
        cout << "Enter Patient Room Number: ";
        cin >> patient.roomNumber;

        patients[patientCount] = patient;
        patientCount++;
    }
}

void searchPatient()
{
    int id;
    cout << "Enter Patient ID: ";
    cin >> id;

    for (int i = 0; i < patientCount; i++)
    {
        if (patients[i].id == id)
        {
            cout << "\nPatient Found!\n";
            cout << "\n-------------------------------------------------------------\n";
            cout << "Patient ID: " << patients[i].id << "\n"
                 << "Patient Name: " << patients[i].name << "\n"
                 << "Patient Age: " << patients[i].age << "\n"
                 << "Patient Disease: " << patients[i].disease << "\n"
                 << "Patient Room Number: " << patients[i].roomNumber << "\n";
            cout << "-------------------------------------------------------------\n";
        }
    }
}

void displayPatients()
{
    for (int i = 0; i < patientCount; i++)
    {
        cout << "\n-------------------------------------------------------------\n";
        cout << "Patient ID: " << patients[i].id << "\n"
             << "Patient Name: " << patients[i].name << "\n"
             << "Patient Age: " << patients[i].age << "\n"
             << "Patient Disease: " << patients[i].disease << "\n"
             << "Patient Room Number: " << patients[i].roomNumber << "\n";
        cout << "-------------------------------------------------------------\n";
    }
}

void savePatients()
{
    ofstream mypatient("hospital.txt");
    if (mypatient.is_open())
    {
        cout << endl;
        cout << "Saving Patient!";
        mypatient << patientCount << endl;
        for (int i = 0; i < patientCount; i++)
        {
            mypatient << patients[i].id << endl;
            mypatient << patients[i].name << endl;
            mypatient << patients[i].age << endl;
            mypatient << patients[i].disease << endl;
            mypatient << patients[i].roomNumber << endl;
        }
    }
    else
    {
        cout << "Error Saving Database!";
    }
    mypatient.close();
}

void menu()
{
    int choice;
    do
    {
        cout << "\n1. Add new patients\n";
        cout << "2. Search for a patient by ID\n";
        cout << "3. Display details of all admitted patients\n";
        cout << "4. Exit\n";
        cout << endl;
        cout << "Enter you choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addPatient();
            break;
        case 2:
            searchPatient();
            break;
        case 3:
            displayPatients();
            break;
        case 4:
            cout << "Ending...";
            break;

        default:
            cout << "Please select a valid option!";
            break;
        }

    } while (choice != 4);
}

int main()
{
    loadPatients();
    menu();
    savePatients();
    return 0;
}
