#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Patient {
    int id;
    string name;
    int level;
    string status;
    string reason;
    int waitRounds;
};

vector<Patient> patientList;

void addPatient() {
    Patient temp;
    cout<<"\n========== New Patient ==========\n";

    cout<<"\nEnter Patient ID: ";

    cin >> temp.id;
    cin.ignore();
    
    cout <<"\nPatient Name: ";
    getline(cin, temp.name);

    cout << "\nEnter patient's condition -> 1 = Critical, 2 = Urgent, 3 = Non-urgent. : ";
    cin >> temp.level;

    if (temp.level < 1 || temp.level > 3) {
        cout <<"Invalid level.\n";
        return;
    }

    temp.status = "Waiting";
    temp.waitRounds = 0;

    patientList.push_back(temp);
    cout <<"\nThe Patient is added to the system.\n";
}

string triageLevel(int level) {
    if (level == 1)
        return "Critical";
    else if (level == 2)
        return "Urgent";
    else if (level == 3)
        return "Non-urgent";
    else
        return "Unspecified";
}

void patientConditions() {
    cout << "\n========== Patients' Conditions ==========\n";

    if (patientList.empty()) {
        cout << "\nPatient list empty.\n";
        return;
    }

    bool patientWorsened = false;

    for (int i = 0; i < patientList.size(); i++) {
        if (patientList[i].status == "Waiting") {
            patientList[i].waitRounds++;
                if (patientList[i].waitRounds >= 2 && patientList[i].level > 1) {
                    int previousLevel = patientList[i].level;
                    patientList[i].level--;
                    patientList[i].waitRounds = 0;

                    patientWorsened = true;
                    cout << "[ALERT] Patient " << patientList[i].name
                        << "'s condition got worse: "
                        << triageLevel(previousLevel) << " -> "
                        << triageLevel(patientList[i].level) << endl;
                }
        }
    }
    if (!patientWorsened) {
        cout<< "No patient condition worsened.\n";
    }
 }

void waitingList() {
    cout<< "\n========== Patient List ==========\n";

    if(patientList.empty()) {
        cout << "\nPatient list empty.\n";
        return;
    }
    
    for (int i = 0; i < patientList.size(); i++) {
        cout << i + 1 << ". ";
        cout << "Name: " << patientList[i].name
            << ", ID: " << patientList[i].id
            << ", Triage Level: " << triageLevel(patientList[i].level) << endl;
    }
}

void menu() {
    cout<<"\n==============================\n";
    cout<<"  ✙ Hospital Triage System ✙ ";
    cout<<"\n==============================\n";
    cout<<"\n 1. Add a new patient\n";
    cout<<"\n 2. Show patients on waiting list\n";
    cout<<"\n 0. Exit\n";
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

        if (choice != 0) {
            patientConditions();
        }

    } while (choice != 0);

    return 0;
}

