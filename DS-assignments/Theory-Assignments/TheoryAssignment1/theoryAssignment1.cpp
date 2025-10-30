#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// A simple structure to store one weather record
struct WeatherRecord {
    string date;
    string city;
    double temperature;
};

// A class to store and manage all weather data
class WeatherDataSystem {
private:
    static const int YEARS = 3;
    static const int CITIES = 3;
    double temperatureData[YEARS][CITIES];
    string cityNames[CITIES];
    int years[YEARS];

public:
    WeatherDataSystem() {
        cityNames[0] = "Delhi";
        cityNames[1] = "Mumbai";
        cityNames[2] = "Chennai";

        years[0] = 2022;
        years[1] = 2023;
        years[2] = 2024;

        // initialize all values to -1 (sentinel for missing data)
        for (int i = 0; i < YEARS; i++) {
            for (int j = 0; j < CITIES; j++) {
                temperatureData[i][j] = -1;
            }
        }
    }

    // Fills the 2D array with sample temperature values
    void populateArray() {
        temperatureData[0][0] = 32.5;
        temperatureData[0][1] = 30.1;
        temperatureData[0][2] = 33.0;

        temperatureData[1][0] = 34.2;
        temperatureData[1][1] = 29.4;
        temperatureData[1][2] = 35.5;

        temperatureData[2][0] = 31.7;
        temperatureData[2][1] = 30.9;
        temperatureData[2][2] = 34.1;
    }

    // Displays values row by row (year-wise)
    void rowMajorAccess() {
        cout << "\nRow Major Access (Year-wise):\n";
        for (int i = 0; i < YEARS; i++) {
            for (int j = 0; j < CITIES; j++) {
                cout << "Year " << years[i] << ", " << cityNames[j]
                     << " = " << temperatureData[i][j] << "°C" << endl;
            }
        }
    }

    // Displays values column by column (city-wise)
    void columnMajorAccess() {
        cout << "\nColumn Major Access (City-wise):\n";
        for (int j = 0; j < CITIES; j++) {
            for (int i = 0; i < YEARS; i++) {
                cout << "City " << cityNames[j] << ", Year " << years[i]
                     << " = " << temperatureData[i][j] << "°C" << endl;
            }
        }
    }

    // Shows how missing values (sparse data) are handled
    void handleSparseData() {
        cout << "\nSparse Data Representation (-1 = no record):\n";
        for (int i = 0; i < YEARS; i++) {
            for (int j = 0; j < CITIES; j++) {
                cout << setw(6) << temperatureData[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Simple time and space complexity info
    void analyzeComplexity() {
        cout << "\nTime and Space Complexity Analysis:\n";
        cout << "Insert Operation: O(1)\n";
        cout << "Delete Operation: O(1)\n";
        cout << "Retrieve Operation: O(1)\n";
        cout << "Space Complexity: O(n*m) where n = years, m = cities\n";
    }
};

// Main function to test all features
int main() {
    WeatherDataSystem system;

    system.populateArray();
    system.rowMajorAccess();
    system.columnMajorAccess();
    system.handleSparseData();
    system.analyzeComplexity();

    return 0;
}
