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
    int windDirection;
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
	char weather[8];
};

void parseLine(const char* line, MetarData& data) {
    memset(&data, 0, sizeof(MetarData));
	if (strlen(line) == 44) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d %d/%d Q%d", 
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
        data.weather[0] = '\0';
	}
    else if (strlen(line) == 59) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d %4d %3s%3d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection,
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.cloudCoverage2, sizeof(data.cloudCoverage2), &data.cloudBase2, &data.temperature, &data.dewPoint, &data.pressure);
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 51) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection,
            &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.cloudCoverage2, sizeof(data.cloudCoverage2), &data.cloudBase2, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 52) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d %4d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection,
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
		data.cloudCoverage2[0] = '\0';  
        data.cloudBase2 = 0;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 47 && strstr(line, "CAVOK") != nullptr) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d CAVOK %d/M%2d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection,
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
		data.cloudBase = 0;
		data.cloudCoverage[0] = '\0';
		data.dewPoint = -data.dewPoint;
        data.visibility = 9999;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 39) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT CAVOK %d/M%2d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
		data.varWindDirection1 = 0; 
		data.varWindDirection2 = 0;
        data.cloudBase2 = 0;
        data.cloudBase = 0;
        data.cloudCoverage[0] = '\0';
        data.dewPoint = -data.dewPoint;
        data.visibility = 9999;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 38) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT CAVOK %d/%2d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudBase2 = 0;
        data.cloudBase = 0;
        data.cloudCoverage[0] = '\0';
        data.temperature = -data.temperature;
        data.visibility = 9999;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 46) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d M%2d/M%2d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
        data.dewPoint = -data.dewPoint;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 53) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d %4d %3s%3d %d/M%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection,
            &data.windSpeed, &data.varWindDirection1, &data.varWindDirection2, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
		data.dewPoint = -data.dewPoint;
        data.weather[0] = '\0';
    }
    else if (strlen(line) == 45) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d %d/M%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
		data.weather[0] = '\0';
    }
    else if (strlen(line) == 48) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d %d/M%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, data.weather, sizeof(data.weather), &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
    }
    else if (strlen(line) == 49) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d M%d/M%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, data.weather, sizeof(data.weather), &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
		data.dewPoint = -data.dewPoint;
    }
    else if (strlen(line) == 47) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, data.weather, sizeof(data.weather), &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
        data.cloudCoverage2[0] = '\0';
        data.cloudBase2 = 0;
    }
    else if (strlen(line) == 55) {
        int ret = sscanf_s(line, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d %3s%3d %d/%d Q%d",
            &data.day, &data.hour, &data.minute, &data.windDirection, &data.windSpeed, &data.visibility, data.weather, sizeof(data.weather), &data.cloudCoverage, sizeof(data.cloudCoverage),
            &data.cloudBase, &data.cloudCoverage2, sizeof(data.cloudCoverage2), &data.cloudBase2, &data.temperature, &data.dewPoint, &data.pressure);
        data.varWindDirection1 = 0;
        data.varWindDirection2 = 0;
    }
}

void printMetarData(const MetarData& data, ostream& output) {
    char timeFormatted[6];  
    snprintf(timeFormatted, sizeof(timeFormatted), "%02d:%02d", data.hour, data.minute);
    const char* chmuraOpis = "";
    const char* chmuraOpis2 = "";
    const char* pogodaOpis = "";
    if (strcmp(data.cloudCoverage, "FEW") == 0) {
        chmuraOpis = "Nieliczne chmury";
    }
    else if (strcmp(data.cloudCoverage, "SCT") == 0) {
        chmuraOpis = "Rozproszone chmury";
    }
    else if (strcmp(data.cloudCoverage, "BKN") == 0) {
        chmuraOpis = "Chmury kłębiaste";
    }
    else if (strcmp(data.cloudCoverage, "OVC") == 0) {
        chmuraOpis = "Zachmurzenie całkowite";
    }
    if (strcmp(data.cloudCoverage2, "FEW") == 0) {
        chmuraOpis2 = "Nieliczne chmury";
    }
    else if (strcmp(data.cloudCoverage2, "SCT") == 0) {
        chmuraOpis2 = "Rozproszone chmury";
    }
    else if (strcmp(data.cloudCoverage2, "BKN") == 0) {
        chmuraOpis2 = "Chmury kłębiaste";
    }
    else if (strcmp(data.cloudCoverage2, "OVC") == 0) {
        chmuraOpis2 = "Zachmurzenie całkowite";
    }
    else if (data.cloudCoverage2[0] == '\0') {
        chmuraOpis2 = "Brak";
    }
    if (strcmp(data.weather, "BR") == 0) {
        pogodaOpis = "Zamglenie";
    }
    else if (data.visibility == 9999 && data.weather[0] == '\0' && data.cloudCoverage[0] == '\0') {
        pogodaOpis = "CAVOK";
		chmuraOpis = "Brak";
    }
    else if (strcmp(data.weather, "-RA") == 0) {
        pogodaOpis = "Lekki deszcz";
    }
    else if (data.weather[0] == '\0') {
        pogodaOpis = "Brak zmian pogodowych";
    }
	

    output << "Dzień: " << data.day << ", Czas: " << timeFormatted << " UTC\n";
    output << "Kierunek wiatru: " << data.windDirection << " stopni, Prędkość wiatru: " << data.windSpeed << " KT\n";
    output << "Kierunek wiatru zmienny od: " << data.varWindDirection1 << " stopni, do: " << data.varWindDirection2 << " stopni\n";
    output << "Widzialność: " << data.visibility << " m\n";
    output << "Pogoda: " << pogodaOpis << " \n";
    output << "Temperatura: " << data.temperature << " C, Punkt rosy: " << data.dewPoint << " C\n";
    output << "Ciśnienie: " << data.pressure << " hPa\n";
    output << "Zachmurzenie: " << chmuraOpis << ", Podstawa chmur: " << data.cloudBase * 100 << " ft\n";
    output << "Zachmurzenie2: " << chmuraOpis2 << ", Podstawa chmur2: " << data.cloudBase2 * 100 << " ft\n";
    output << "------------------------------------\n";
}


void displayMenu() {
    cout << "Autor: Adrian Bednarek, Indeks: 203502\n";
    cout << "Menu programu:\n";
    cout << "o - Wczytaj dane z pliku Metar Gdansk.txt i zapisz do pogoda_gd.txt\n";
    cout << "k - Wczytaj dane z pliku 1(wpisz nazwe) i zapisz do 2(wpisz nazwe)\n";
    cout << "q - Zakończ program\n";
}

int main() {
    setlocale(LC_CTYPE, "pl-PL");
    char option;
	char inputFileName[128];
	char outputFileName[128];
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
        }
        else if (option == 'k') {
            cout << "Wpisz nazwe pliku wczytującego dane: ";
            cin >> inputFileName;
            cout << "------------------------------------\n";
            cout << "Wpisz nazwe pliku zapisującego dane: ";
            cin >> outputFileName;
            cout << "------------------------------------\n";
            char lines[MAX_LINES][128];
            MetarData data[MAX_LINES];
            int lineCount = 0;

            ifstream inputFile(inputFileName);
            ofstream outputFile(outputFileName);

            if (!inputFile) {
                cerr << "Błąd otwarcia pliku wejściowego\n";
                continue;
            }
            if (!outputFile) {
                cerr << "Błąd otwarcia pliku wyjściowego\n";
                inputFile.close();
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
        }
        else if (option != 'q') {
            cout << "Nieznana opcja, spróbuj ponownie.\n";
        }
    } while (option != 'q');

    return 0;
}
