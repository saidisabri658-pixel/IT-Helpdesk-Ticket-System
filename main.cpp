#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>

using namespace std;

struct Ticket {
    int id;
    string user;
    string problem;
    string priority;
    string status;
};

vector<Ticket> tickets;
const string FILE_NAME = "tickets.txt";

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void loadTickets() {
    ifstream file(FILE_NAME);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Ticket t;
        string id;

        getline(ss, id, '|');
        getline(ss, t.user, '|');
        getline(ss, t.problem, '|');
        getline(ss, t.priority, '|');
        getline(ss, t.status);

        try {
            t.id = stoi(id);
            tickets.push_back(t);
        } catch (...) {
            // Ungueltige Zeile ignorieren
        }
    }
}

void saveTickets() {
    ofstream file(FILE_NAME);

    for (const Ticket& t : tickets) {
        file << t.id << "|"
             << t.user << "|"
             << t.problem << "|"
             << t.priority << "|"
             << t.status << '\n';
    }
}

int getNextId() {
    int maxId = 0;

    for (const Ticket& t : tickets) {
        if (t.id > maxId)
            maxId = t.id;
    }

    return maxId + 1;
}

void createTicket() {
    Ticket t;
    t.id = getNextId();

    clearInput();

    cout << "\n--- Neues Ticket ---\n";

    cout << "Benutzername: ";
    getline(cin, t.user);

    cout << "Problem: ";
    getline(cin, t.problem);

    int choice;

    cout << "\nPrioritaet:\n";
    cout << "1. Niedrig\n";
    cout << "2. Mittel\n";
    cout << "3. Hoch\n";
    cout << "Auswahl: ";
    cin >> choice;

    switch (choice) {
        case 1:
            t.priority = "Niedrig";
            break;
        case 3:
            t.priority = "Hoch";
            break;
        default:
            t.priority = "Mittel";
    }

    t.status = "Offen";

    tickets.push_back(t);
    saveTickets();

    cout << "\nTicket #" << t.id
         << " wurde erfolgreich erstellt!\n";
}

void showTickets() {
    cout << "\n========== HELPDESK TICKETS ==========\n";

    if (tickets.empty()) {
        cout << "Keine Tickets vorhanden.\n";
        return;
    }

    for (const Ticket& t : tickets) {
        cout << "\n--------------------------------------\n";
        cout << "Ticket ID : " << t.id << '\n';
        cout << "Benutzer  : " << t.user << '\n';
        cout << "Problem   : " << t.problem << '\n';
        cout << "Prioritaet: " << t.priority << '\n';
        cout << "Status    : " << t.status << '\n';
    }

    cout << "--------------------------------------\n";
}

void searchTicket() {
    int id;

    cout << "\nTicket-ID: ";
    cin >> id;

    for (const Ticket& t : tickets) {
        if (t.id == id) {
            cout << "\nTicket gefunden!\n";
            cout << "Benutzer  : " << t.user << '\n';
            cout << "Problem   : " << t.problem << '\n';
            cout << "Prioritaet: " << t.priority << '\n';
            cout << "Status    : " << t.status << '\n';
            return;
        }
    }

    cout << "\nTicket nicht gefunden.\n";
}

void updateTicket() {
    int id;

    cout << "\nTicket-ID: ";
    cin >> id;

    for (Ticket& t : tickets) {
        if (t.id == id) {
            int choice;

            cout << "\nNeuer Status:\n";
            cout << "1. Offen\n";
            cout << "2. In Bearbeitung\n";
            cout << "3. Geschlossen\n";
            cout << "Auswahl: ";
            cin >> choice;

            if (choice == 1)
                t.status = "Offen";
            else if (choice == 2)
                t.status = "In Bearbeitung";
            else if (choice == 3)
                t.status = "Geschlossen";
            else {
                cout << "\nUngueltige Auswahl.\n";
                return;
            }

            saveTickets();

            cout << "\nStatus erfolgreich aktualisiert!\n";
            return;
        }
    }

    cout << "\nTicket nicht gefunden.\n";
}

void deleteTicket() {
    int id;

    cout << "\nTicket-ID zum Loeschen: ";
    cin >> id;

    for (auto it = tickets.begin(); it != tickets.end(); ++it) {
        if (it->id == id) {
            tickets.erase(it);
            saveTickets();

            cout << "\nTicket erfolgreich geloescht!\n";
            return;
        }
    }

    cout << "\nTicket nicht gefunden.\n";
}

int main() {
    loadTickets();

    int choice;

    do {
        cout << "\n======================================\n";
        cout << "       IT HELPDESK TICKET SYSTEM\n";
        cout << "======================================\n";
        cout << "1. Neues Ticket erstellen\n";
        cout << "2. Alle Tickets anzeigen\n";
        cout << "3. Ticket suchen\n";
        cout << "4. Ticket-Status aendern\n";
        cout << "5. Ticket loeschen\n";
        cout << "0. Programm beenden\n";
        cout << "======================================\n";
        cout << "Auswahl: ";

        cin >> choice;

        switch (choice) {
            case 1:
                createTicket();
                break;
            case 2:
                showTickets();
                break;
            case 3:
                searchTicket();
                break;
            case 4:
                updateTicket();
                break;
            case 5:
                deleteTicket();
                break;
            case 0:
                cout << "\nProgramm beendet.\n";
                break;
            default:
                cout << "\nUngueltige Auswahl.\n";
        }

    } while (choice != 0);

    return 0;
}