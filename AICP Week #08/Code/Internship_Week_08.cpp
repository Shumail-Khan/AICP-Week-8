#include <iostream>
#include <algorithm>
using namespace std;

const int BOAT_COUNT = 10;
const int OPENING_HOUR = 10;
const int CLOSING_HOUR = 17;
const int FULL_HOUR_RATE = 20;
const int HALF_HOUR_RATE = 12;

struct Boat {
    int number;
    float totalHours;
    float moneyTaken;
    int returnTime;
};

void calculatePayment(Boat &boat) {
    float duration;
    cout << "Enter the duration (in hours) for Boat " << boat.number << ": ";
    cin >> duration;

    if (duration < 0 || duration != static_cast<int>(duration) && duration - static_cast<int>(duration) != 0.5) {
        cout << "Invalid duration entered. Please enter a valid duration (whole or half hours)." << endl;
        return;
    }

    int currentTime;
    cout << "Enter the current time (in 24-hour format): ";
    cin >> currentTime;

    if (currentTime < OPENING_HOUR || currentTime >= CLOSING_HOUR) {
        cout << "Boat cannot be hired at this time." << endl;
        return;
    }

    if (currentTime + duration > CLOSING_HOUR) {
        cout << "Boat cannot be hired for that duration as it exceeds operating hours." << endl;
        return;
    }

    float fullHours = static_cast<int>(duration);
    float remaining = duration - fullHours;

    float cost = fullHours * FULL_HOUR_RATE + remaining * HALF_HOUR_RATE * 2; // Calculate cost for full and remaining hours
    boat.totalHours += duration;
    boat.moneyTaken += cost;
    boat.returnTime = currentTime + static_cast<int>(duration);

    cout << "Payment for Boat " << boat.number << " updated. Total hours: " << boat.totalHours<< ", Money taken: $" << boat.moneyTaken << endl;
}

void findNextAvailable(const Boat boats[], int currentTime) {
    int availableCount = 0;
    int nextAvailableTime = CLOSING_HOUR + 1;

    for (int i = 0; i < BOAT_COUNT; ++i) {
        if (boats[i].returnTime <= currentTime) {
            availableCount++;
        } else {
            nextAvailableTime = min(nextAvailableTime, boats[i].returnTime);
        }
    }

    if (availableCount > 0) {
        cout << "Number of available boats at current time: " << availableCount << endl;
    } else {
        cout << "No boats available. Next available time: " << nextAvailableTime << endl;
    }
}

void endOfDayReport(const Boat boats[]) {
    float totalMoney = 0;
    int totalHours = 0;
    int boatsNotUsed = 0;
    Boat mostUsedBoat = boats[0];

    for (int i = 0; i < BOAT_COUNT; ++i) {
        totalMoney += boats[i].moneyTaken;
        totalHours += boats[i].totalHours;
        if (boats[i].totalHours == 0) {
            boatsNotUsed++;
        }
        if (boats[i].totalHours > mostUsedBoat.totalHours) {
            mostUsedBoat = boats[i];
        }
    }

    cout << "End-of-day Report:" << endl;
    cout << "Total money taken: $" << totalMoney << endl;
    cout << "Total hours boats were hired: " << totalHours << " hours" << endl;
    cout << "Boats not used today: " << boatsNotUsed << endl;
    cout << "Boat used the most: Boat " << mostUsedBoat.number << " (Total hours: " << mostUsedBoat.totalHours << " hours)" << endl;
}

int main() {
    Boat boats[BOAT_COUNT];

    for (int i = 0; i < BOAT_COUNT; ++i) {
        boats[i].number = i + 1;
        boats[i].totalHours = 0;
        boats[i].moneyTaken = 0;
        boats[i].returnTime = 0;
    }

    for (int i = 0; i < 3; ++i) {
        calculatePayment(boats[i]);
    }

    int currentTime;
    cout << "Enter the current time (in 24-hour format): ";
    cin >> currentTime;
    findNextAvailable(boats, currentTime);

    endOfDayReport(boats);

    return false;
}

