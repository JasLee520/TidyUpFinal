// Full Name: Jasmine Lee
// Class: ITCS-2530
// GitHub Repo URL: https://github.com/JasLee520/TidyUp-FinalProject
// One-Sentence Summary: Gamified C++ program where users clean different rooms, earn points, and upgrade.
// Your posted hobby or interest: Watching organizing & cleaning videos
// AI Tool(s) Used: ChatGPT

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int MAX_TASKS = 5;
const int MAX_ROOMS = 5;
const int TASK_REWARD = 10;
const int UPGRADE_COST = 50;

// Struct to represent a cleaning task
struct Task {
    string name;
    bool isComplete;
};

// Struct to represent a room with a name and tasks
struct Room {
    string name;
    Task tasks[MAX_TASKS];
};

// Function prototypes
void showMenu(string currentRoom);
void completeTask(Room& room, int& points);
void upgradeRoom(Room rooms[], int& currentRoomIndex, int& points);
void saveProgress(Room rooms[], int currentRoomIndex, int points);
void loadProgress(Room rooms[], int& currentRoomIndex, int& points);

int main() {
    Room rooms[MAX_ROOMS] = {
        {"Living Room", {
            {"Vacuum the carpet", false},
            {"Dust the shelves", false},
            {"Organize books", false},
            {"Wipe windows", false},
            {"Tidy cushions", false}
        }},
        {"Kitchen", {
            {"Wash dishes", false},
            {"Clean refrigerator", false},
            {"Wipe counters", false},
            {"Mop floor", false},
            {"Organize pantry", false}
        }},
        {"Bathroom", {
            {"Scrub toilet", false},
            {"Clean mirror", false},
            {"Wipe sink", false},
            {"Restock toilet paper", false},
            {"Mop tiles", false}
        }},
        {"Bedroom", {
            {"Make the bed", false},
            {"Organize closet", false},
            {"Dust nightstand", false},
            {"Vacuum floor", false},
            {"Change sheets", false}
        }},
        {"Garage", {
            {"Sweep floor", false},
            {"Organize tools", false},
            {"Take out trash", false},
            {"Wipe surfaces", false},
            {"Sort recycling", false}
        }}
    };

    int currentRoomIndex = 0;
    int points = 0;

    loadProgress(rooms, currentRoomIndex, points);

    int choice;
    do {
        showMenu(rooms[currentRoomIndex].name);
        cin >> choice;

        switch (choice) {
        case 1:
            completeTask(rooms[currentRoomIndex], points);
            break;
        case 2:
            upgradeRoom(rooms, currentRoomIndex, points);
            break;
        case 3:
            saveProgress(rooms, currentRoomIndex, points);
            cout << "Progress saved!\n";
            break;
        case 4:
            cout << "Exiting game. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}

void showMenu(string currentRoom) {
    cout << "\n--- TidyUp! Cleaning Game ---\n";
    cout << "Current Room: " << currentRoom << "\n";
    cout << "1. Complete a cleaning task\n";
    cout << "2. Upgrade to next room\n";
    cout << "3. Save progress\n";
    cout << "4. Exit\n";
    cout << "Choose an option: ";
}

void completeTask(Room& room, int& points) {
    cout << "\nAvailable Cleaning Tasks in " << room.name << ":\n";
    for (int i = 0; i < MAX_TASKS; ++i) {
        cout << i + 1 << ". " << room.tasks[i].name;
        if (room.tasks[i].isComplete) cout << " (Completed)";
        cout << endl;
    }

    int selection;
    cout << "Select a task to complete (1-" << MAX_TASKS << "): ";
    cin >> selection;

    if (selection < 1 || selection > MAX_TASKS) {
        cout << "Invalid task number.\n";
    }
    else if (room.tasks[selection - 1].isComplete) {
        cout << "Task already completed.\n";
    }
    else {
        room.tasks[selection - 1].isComplete = true;
        points += TASK_REWARD;
        cout << "Task completed! You've earned " << TASK_REWARD << " points.\n";
        cout << "Total points: " << points << "\n";
    }
}

void upgradeRoom(Room rooms[], int& currentRoomIndex, int& points) {
    if (points >= UPGRADE_COST) {
        if (currentRoomIndex < MAX_ROOMS - 1) {
            points -= UPGRADE_COST;
            currentRoomIndex++;
            cout << "Room upgraded! Welcome to the " << rooms[currentRoomIndex].name << "!\n";
        }
        else {
            cout << "You've already reached the final room!\n";
        }
    }
    else {
        cout << "Not enough points to upgrade. You need " << UPGRADE_COST << " points.\n";
    }
}

void saveProgress(Room rooms[], int currentRoomIndex, int points) {
    ofstream outFile("progress.txt");

    outFile << points << endl;
    outFile << currentRoomIndex << endl;
    for (int i = 0; i < MAX_ROOMS; ++i) {
        for (int j = 0; j < MAX_TASKS; ++j) {
            outFile << rooms[i].tasks[j].isComplete << " ";
        }
        outFile << endl;
    }

    outFile.close();
}

void loadProgress(Room rooms[], int& currentRoomIndex, int& points) {
    ifstream inFile("progress.txt");

    if (!inFile) {
        cout << "No saved progress found. Starting fresh.\n";
        return;
    }

    inFile >> points;
    inFile >> currentRoomIndex;

    for (int i = 0; i < MAX_ROOMS; ++i) {
        for (int j = 0; j < MAX_TASKS; ++j) {
            inFile >> rooms[i].tasks[j].isComplete;
        }
    }

    inFile.close();
}