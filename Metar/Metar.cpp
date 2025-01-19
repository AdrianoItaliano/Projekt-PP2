#include <fstream>
#include <iostream>
#include <cstring>
#include <locale>

using namespace std;

#define MAX_LINES 200

struct MetarData {
    int day;
    int hour;
    int minute;
    char windDirection[4];
    int varWindDirection1;
    int varWindDirection2;
    int windSpeed;
    int visibility;
    char cloudCoverage[8];
    int cloudBase;
    char cloudCoverage2[8];
    int cloudBase2;
    int temperature;
    int dewPoint;
    int pressure;
};

// Modify parseLine function to handle cloud types:
void parseLine(const char* line, MetarData& data) {

	if (strlen(line) == 44) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %4d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
	}
    if (strlen(line) == 59) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %3dV%3d %4d %3s%3d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.cloudCoverage2, sizeof(data.cloudCoverage2), &data.cloudBase2, &data.temperature, &data.dewPoint, &data.pressure);
    }
    if (strlen(line) == 51) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %4d %3s%3d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.cloudCoverage2, sizeof(data.cloudCoverage2), &data.cloudBase2, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
    }
    if (strlen(line) == 52) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %3dV%3d %4d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
		data.cloudCoverage2[0] = '\0';  
        data.cloudBase2 = 0;
    }
    if (strlen(line) == 47) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %3dV%3d CAVOK %d/M%2d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
		data.cloudBase = 0;
		data.cloudCoverage[0] = '\0';
		data.dewPoint = -data.dewPoint;
        data.visibility = 9999;
    }
    if (strlen(line) == 39) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT CAVOK %d/M%2d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
		data.varWindDirection1 = 0; 
		data.varWindDirection2 = 0;
        data.cloudBase2 = 0;
        data.cloudBase = 0;
        data.cloudCoverage[0] = '\0';
        data.dewPoint = -data.dewPoint;
        data.visibility = 9999;
    }
    if (strlen(line) == 38) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT CAVOK %d/%2d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudBase2 = 0;
        data.cloudBase = 0;
        data.cloudCoverage[0] = '\0';
        data.temperature = -data.temperature;
        data.visibility = 9999;
    }
    if (strlen(line) == 46) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %4d %3s%3d %d/M%2d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
        data.dewPoint = -data.dewPoint;
    }
    if (strlen(line) == 53) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %3dV%3d %4d %3s%3d %d/M%d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
		data.dewPoint = -data.dewPoint;
    }
    if (strlen(line) == 45) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3s%2dKT %4d %3s%3d %d/M%d Q%d",
            &data.day, &data.hour, &data.minute, data.windDirection, sizeof(data.windDirection),
            &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
    }

}

// Modify the printMetarData function to display different cloud coverage
void printMetarData(const MetarData& data, ostream& output) {
    // Format the time to display as "gg:mm" (2 digits for hour and minute)
    char timeFormatted[6];  // For "gg:mm" format
    snprintf(timeFormatted, sizeof(timeFormatted), "%02d:%02d", data.hour, data.minute);

    output << "Dzień: " << data.day << ", Czas: " << timeFormatted << " UTC\n";
    output << "Kierunek wiatru: " << data.windDirection << ", Prędkość wiatru: " << data.windSpeed << " KT\n";
    output << "Kierunek wiatru zmienny od: " << data.varWindDirection1 << " stopni, do: " << data.varWindDirection2 << " stopni\n";
    output << "Widzialność: " << data.visibility << " m\n";
    output << "Temperatura: " << data.temperature << " C, Punkt rosy: " << data.dewPoint << " C\n";
    output << "Ciśnienie: " << data.pressure << " hPa\n";
    output << "Zachmurzenie: " << data.cloudCoverage << ", Podstawa chmur: " << data.cloudBase * 100 << " ft\n";
    output << "Zachmurzenie2: " << data.cloudCoverage2 << ", Podstawa chmur2: " << data.cloudBase2 * 100 << " ft\n";
    output << "------------------------------------\n";
}


void displayMenu() {
    cout << "Autor: Adrian Bednarek, Indeks: 203502\n";
    cout << "Menu programu:\n";
    cout << "o - Wczytaj dane z pliku Metar Gdansk.txt i zapisz do pogoda_gd.txt\n";
    cout << "q - Zakończ program\n";
}

int main() {
    setlocale(LC_CTYPE, "pl-PL");
    char option;
    do {
        displayMenu();
        cout << "Wybierz opcję: ";
        cin >> option;
        cout << "------------------------------------\n";

        if (option == 'o') {
            char lines[MAX_LINES][128];
            MetarData data[MAX_LINES];
            int lineCount = 0;

            ifstream inputFile("Metar Gdansk.txt");
            ofstream outputFile("pogoda_gd.txt");

            if (!inputFile) {
                cerr << "Blad otwarcia pliku Metar Gdansk.txt\n";
                continue;
            }

            while (inputFile.getline(lines[lineCount], 128) && lineCount < MAX_LINES) {
                parseLine(lines[lineCount], data[lineCount]);
                lineCount++;
            }

            inputFile.close();

            for (int i = 0; i < 3; ++i) {
                printMetarData(data[i], cout);
            }

            for (int i = 0; i < lineCount; ++i) {
                printMetarData(data[i], outputFile);
            }

            outputFile.close();
            break; // Exit after displaying and saving data
        }
        else if (option != 'q') {
            cout << "Nieznana opcja, spróbuj ponownie.\n";
        }
    } while (option != 'q');

    return 0;
}
