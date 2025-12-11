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
};

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


bool isBetterChoice(const Patient &a, const Patient &b) {
    if (a.level < b.level) return true;
    if (a.level > b.level) return false;
    return a.waitRounds > b.waitRounds;
}

void treatPatient() {
    cout << "\n========== Treat Patient ==========\n";
    cout << "\n ----- Treating Most Severe Patient w/ Highest Wait Time ----- \n";
    int bestIndex = -1;

    for (int i = 0; i < static_cast<int>(patientList.size()); i++) {
        if (patientList[i].status == "Waiting") {
            if (bestIndex == -1 || isBetterChoice(patientList[i], patientList[bestIndex])) {
                bestIndex = i;
        }
    }
}

    if (bestIndex == -1) {
        cout << "No patients to treat.\n";
        return;
    }

    Patient &p = patientList[bestIndex];

    cout << "You have treated: " << p.name << " !!"
         << " (Triage: " << triageLevel(p.level)
         << ", Reason: " << p.reason << ")\n";
    
    patientList.erase(patientList.begin() + bestIndex);
}


void patientConditions() {
    cout << "\n========== Patients' Conditions ==========\n";

    if (patientList.empty()) {
        cout << "\nPatient list empty.\n";
        return;
    }

    bool patientWorsened = false;
    bool patientDied = false;

    for (int i = 0; i < static_cast<int>(patientList.size()); i++) {
        if (patientList[i].status == "Waiting") {
            patientList[i].waitRounds++;

            int worseLimit;
            if (patientList[i].level == 3)
                worseLimit = 3;
            else if (patientList[i].level == 2)
                worseLimit = 2;
            else
                worseLimit = 999;

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

            if (patientList[i].level == 1 && patientList[i].waitRounds >= 3) {
                patientList[i].status = "Deceased";
                patientList[i].waitRounds = 0;
                userLives--;
                patientDied = true;

                cout << "\nPatient " << patientList[i].name
                    << " has died ...\n";
                cout << "Lives remaining: " << userLives << "\n";
            }
        }
    }
    if (!patientWorsened) {
        cout<< "\nNo patient condition worsened.\n";
    }

    for (int i =  static_cast<int>(patientList.size()) - 1; i >= 0; --i) {
        if (patientList[i].status == "Deceased") {
            patientList.erase(patientList.begin() + i);
        }
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
    cout<<"       Total Lives: " << userLives << "\n";
    cout<< "   Patients on waitlist: " << patientList.size() << "\n";
    cout << "-------------------------------\n";
    cout<<"\n 1. Add a new patient\n";
    cout<<"\n 2. Show patients on waiting list\n";
    cout<<"\n 3. Treat Next Patient\n";
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
        else if (choice == 3) {
            treatPatient();
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

        if (userLives <= 0) {
            cout << "\n You're Fired. Too many patients died in your care..\n";
            cout << "\nThe ER could not keep up with the emergencies.\n";
            break;
        }

    } while (choice != 0);

    return 0;
}

