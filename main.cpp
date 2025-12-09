#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Patient {
    int id;
    string name;
    int level;
};

vector<Patient> patientList;

void addPatient() {
    Patient temp;
    cout<<"\n--- New Patient ---\n";

    cout<<"Enter Patient ID: ";

    cin >> temp.id;
    cin.ignore();
    
    cout <<"Patient Name: ";
    getline(cin, temp.name);

    cout << "Enter triage level (condition) -> 1 = Critical, 2 = Urgent, 3 = Non-urgent. : ";
    cin >> temp.level;

    if (temp.level < 1 || temp.level > 3) {
        cout <<"Invalid level.\n";
        return;
    }

    patientList.push_back(temp);
    cout <<"Patient added to system.\n";
}

void waitingList() {
    cout<< "\n--- Patient List ---\n";

    if(patientList.empty()) {
        cout << "Patient list empty.\n";
        return;
    }
    
    for (int i = 0; i < patientList.size(); i++) {
        cout << i + 1 << ". ";
        cout << "Name: " << patientList[i].name
            << ", ID: " << patientList[i].id
            << ", Triage Level: " << patientList[i].level << endl;
    }
}

void menu() {
    cout<<"\n==============================\n";
    cout<<"  Hospital Triage System !! ";
    cout<<"\n==============================\n";
    cout<<"1. Add a new patient\n";
    cout<<"2. Show patients on waiting list\n";
    cout<<"0. Exit\n";
}

int main() {
    int choice;

    do {
        menu();
        cin >> choice;

        if (choice == 1) {
            addPatient();
        }
        else if (choice == 2) {
            waitingList();
        }
        else if (choice == 0) {
            cout << "System closed.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

