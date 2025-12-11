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
int userLives = 3;
int nextId = 1;

void addPatient() {
    Patient temp;
    cout<<"\n========== New Patient ==========\n";

    cout<<"\nEnter Patient ID: ";

    if(!(cin >>  temp.id)) {
        cout << "\nInvalid input .\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

    cin.ignore(1000, '\n');
    
    cout <<"\nPatient Name: ";
    getline(cin, temp.name);

    cout << "\nEnter patient's condition -> 1 = Critical, 2 = Urgent, 3 = Non-urgent. : ";
        if(!(cin >> temp.level)) {
        cout << "Invalid input .\n";
        cin.clear();
        cin.ignore(1000, '\n');
        return;
    }

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

void spawnPatient() {
    static int nameIndexCount = 0;

    Patient temp;
    temp.id = nextId++;

    string patientNames[] = {"Joe", "Rob", "Riley", "CoCo", "Taylor", "RoRo", "Bob", "Martha"};
    int nameIndex = nameIndexCount % 8;
    nameIndexCount++;
    temp.name = patientNames[nameIndex] + " #" + to_string(temp.id);

    temp.level = (rand() % 3) + 1;

    string reasons[] = {"missing arm", "head injury", "headache", "stomach ache", "paper cut",};
    int reasonIndex = rand() % 5;
    temp.reason = reasons[reasonIndex];

    temp.status = "Waiting";
    temp.waitRounds = 0;

    patientList.push_back(temp);

    cout <<"\n[NEW ARRIVAL] " << temp.name
        << " entered the ER. \nCondition: " << triageLevel(temp.level)
        << " (" << temp.reason << ")\n";
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
                    cout << "\n[ALERT] Patient " << patientList[i].name
                        << "'s condition got worse !! : "
                        << triageLevel(previousLevel) << " -> "
                        << triageLevel(patientList[i].level) << endl;
                }
        }
    }
    if (!patientWorsened) {
        cout<< "\nNo patient condition worsened.\n";
    }
 }

void waitingList() {
    cout<< "\n========== Patient List ==========\n\n";

    if(patientList.empty()) {
        cout << "\nPatient list empty.\n";
        return;
    }
    
    for (int i = 0; i < patientList.size(); i++) {
        cout << i + 1 << ". ";
        cout << "Name: " << patientList[i].name
            << ", ID: " << patientList[i].id
            << ", Triage: " << triageLevel(patientList[i].level)
            << ", Status: " << patientList[i].status
            << ", Waiting Rounds: " << patientList[i].waitRounds
            << ", Reason: " << patientList[i].reason
            << "\n\n";
    }
}

void menu() {
    cout<<"\n==============================\n";
    cout<<"  ✙ Hospital Triage System ✙ ";
    cout<<"\n==============================\n";
    cout<< "   Patients on waitlist: " << patientList.size() << "\n";
    cout << "-------------------------------\n";
    cout<<"\n 1. Add a new patient\n";
    cout<<"\n 2. Show patients on waiting list\n";
    cout<<"\n 0. Exit\n";
}

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));
    int choice;

    do {
        int chance = rand() % 100;
        if (chance < 40) {
            spawnPatient();
        }

        menu();
        if (!(cin >> choice)) {
            cout << "Invalid input. Try again.\n";
            break;
        }

        if (choice == 1) {
            addPatient();
        }
        else if (choice == 2) {
            waitingList();
        }
        else if (choice == 0) {
            cout << "\nSystem closed.\n";
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

