#include <fstream>
#include <iostream>
#include <cstring>
#include <locale>
#define MAX_LINI 1500

using namespace std;

struct MetarDane {
    int dzien;
    int godz;
    int minuty;
    int kierunekWiatr;
    int zmienKierWiatr;
    int zmienKierWiatr2;
    int wiatrPre;
    int widocz;
    char chmuryPokr[8];
    int chmuryWys;
    char chmuryPokr2[8];
    int chmuryWys2;
    int temperatura;
    int pktRosy;
    int cisnienie;
    char pogoda[8];
};

void wczytanieDanych(const char* linia, MetarDane& dane) {
    memset(&dane, 0, sizeof(MetarDane));
    if (strlen(linia) == 44) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d %d/%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 59) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d %4d %3s%3d %3s%3d %d/%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr,
            &dane.wiatrPre, &dane.zmienKierWiatr, &dane.zmienKierWiatr2, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.chmuryPokr2, sizeof(dane.chmuryPokr2), &dane.chmuryWys2, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 51) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d %3s%3d %d/%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr,
            &dane.wiatrPre, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.chmuryPokr2, sizeof(dane.chmuryPokr2), &dane.chmuryWys2, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 52) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d %4d %3s%3d %d/%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr,
            &dane.wiatrPre, &dane.zmienKierWiatr, &dane.zmienKierWiatr2, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 47 && strstr(linia, "CAVOK") != nullptr) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d CAVOK %d/M%2d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr,
            &dane.wiatrPre, &dane.zmienKierWiatr, &dane.zmienKierWiatr2, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.chmuryWys = 0;
        dane.chmuryPokr[0] = '\0';
        dane.pktRosy = -dane.pktRosy;
        dane.widocz = 9999;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 39) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT CAVOK %d/M%2d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.chmuryPokr2[0] = '\0';
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryWys2 = 0;
        dane.chmuryWys = 0;
        dane.chmuryPokr[0] = '\0';
        dane.pktRosy = -dane.pktRosy;
        dane.widocz = 9999;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 38) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT CAVOK %d/%2d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.chmuryPokr2[0] = '\0';
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryWys2 = 0;
        dane.chmuryWys = 0;
        dane.chmuryPokr[0] = '\0';
        dane.temperatura = -dane.temperatura;
        dane.widocz = 9999;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 46) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d M%2d/M%2d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.pktRosy = -dane.pktRosy;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 53) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %3dV%3d %4d %3s%3d %d/M%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr,
            &dane.wiatrPre, &dane.zmienKierWiatr, &dane.zmienKierWiatr2, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.pktRosy = -dane.pktRosy;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 45) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s%3d %d/M%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.pogoda[0] = '\0';
    }
    else if (strlen(linia) == 48) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d %d/M%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, dane.pogoda, sizeof(dane.pogoda), &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
    }
    else if (strlen(linia) == 49) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d M%d/M%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, dane.pogoda, sizeof(dane.pogoda), &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
        dane.pktRosy = -dane.pktRosy;
    }
    else if (strlen(linia) == 47) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d %d/%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, dane.pogoda, sizeof(dane.pogoda), &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
        dane.chmuryPokr2[0] = '\0';
        dane.chmuryWys2 = 0;
    }
    else if (strlen(linia) == 55) {
        int ret = sscanf_s(linia, "EPGD %02d%02d%2dZ %3d%2dKT %4d %3s %3s%3d %3s%3d %d/%d Q%d",
            &dane.dzien, &dane.godz, &dane.minuty, &dane.kierunekWiatr, &dane.wiatrPre, &dane.widocz, dane.pogoda, sizeof(dane.pogoda), &dane.chmuryPokr, sizeof(dane.chmuryPokr),
            &dane.chmuryWys, &dane.chmuryPokr2, sizeof(dane.chmuryPokr2), &dane.chmuryWys2, &dane.temperatura, &dane.pktRosy, &dane.cisnienie);
        dane.zmienKierWiatr = 0;
        dane.zmienKierWiatr2 = 0;
    }
}

void wypiszDane(const MetarDane& dane, ostream& output) {
    char czas[6];
    snprintf(czas, sizeof(czas), "%02d:%02d", dane.godz, dane.minuty);
    const char* chmuraOpis = "";
    const char* chmuraOpis2 = "";
    const char* pogodaOpis = "";
    if (strcmp(dane.chmuryPokr, "FEW") == 0) {
        chmuraOpis = "Nieliczne chmury";
    }
    else if (strcmp(dane.chmuryPokr, "SCT") == 0) {
        chmuraOpis = "Rozproszone chmury";
    }
    else if (strcmp(dane.chmuryPokr, "BKN") == 0) {
        chmuraOpis = "Chmury kłębiaste";
    }
    else if (strcmp(dane.chmuryPokr, "OVC") == 0) {
        chmuraOpis = "Zachmurzenie całkowite";
    }
    if (strcmp(dane.chmuryPokr2, "FEW") == 0) {
        chmuraOpis2 = "Nieliczne chmury";
    }
    else if (strcmp(dane.chmuryPokr2, "SCT") == 0) {
        chmuraOpis2 = "Rozproszone chmury";
    }
    else if (strcmp(dane.chmuryPokr2, "BKN") == 0) {
        chmuraOpis2 = "Chmury kłębiaste";
    }
    else if (strcmp(dane.chmuryPokr2, "OVC") == 0) {
        chmuraOpis2 = "Zachmurzenie całkowite";
    }
    else if (dane.chmuryPokr2[0] == '\0') {
        chmuraOpis2 = "Brak";
    }
    if (strcmp(dane.pogoda, "BR") == 0) {
        pogodaOpis = "Zamglenie";
    }
    else if (dane.widocz == 9999 && dane.pogoda[0] == '\0' && dane.chmuryPokr[0] == '\0') {
        pogodaOpis = "CAVOK";
        chmuraOpis = "Brak";
    }
    else if (strcmp(dane.pogoda, "-RA") == 0) {
        pogodaOpis = "Lekki deszcz";
    }
    else if (strcmp(dane.pogoda, "+RA") == 0) {
        pogodaOpis = "Silny deszcz";
    }
    else if (strcmp(dane.pogoda, "RA") == 0) {
        pogodaOpis = "Deszcz";
    }
    else if (strcmp(dane.pogoda, "-SN") == 0) {
        pogodaOpis = "Lekki śnieg";
    }
    else if (strcmp(dane.pogoda, "+SN") == 0) {
        pogodaOpis = "Silny śnieg";
    }
    else if (strcmp(dane.pogoda, "SN") == 0) {
        pogodaOpis = "Śnieg";
    }
    else if (strcmp(dane.pogoda, "-DZ") == 0) {
        pogodaOpis = "Lekka mżawka";
    }
    else if (strcmp(dane.pogoda, "+DZ") == 0) {
        pogodaOpis = "Silna mżawka";
    }
    else if (strcmp(dane.pogoda, "DZ") == 0) {
        pogodaOpis = "Mżawka";
    }
    else if (dane.pogoda[0] == '\0') {
        pogodaOpis = "Brak zmian pogodowych";
    }


    output << "Dzień: " << dane.dzien << ", Czas: " << czas << " UTC\n";
    output << "Kierunek wiatru: " << dane.kierunekWiatr << " stopni, Prędkość wiatru: " << dane.wiatrPre << " KT\n";
    output << "Zmiany kierunku wiatru od: " << dane.zmienKierWiatr << " stopni, do: " << dane.zmienKierWiatr2 << " stopni\n";
    output << "Widoczność: " << dane.widocz << " m\n";
    output << "Pogoda: " << pogodaOpis << " \n";
    output << "Temperatura: " << dane.temperatura << " C, Punkt rosy: " << dane.pktRosy << " C\n";
    output << "Ciśnienie: " << dane.cisnienie << " hPa\n";
    output << "Zachmurzenie: " << chmuraOpis << ", Wysokość chmur: " << dane.chmuryWys * 100 << " ft\n";
    output << "Zachmurzenie2: " << chmuraOpis2 << ", Wysokość chmur2: " << dane.chmuryWys2 * 100 << " ft\n";
    output << "------------------------------------\n";
}


void menu() {
    cout << "Autor: Adrian Bednarek, Indeks: 203502\n";
    cout << "Menu programu:\n";
    cout << "o - Wczytaj dane z pliku Metar Gdansk.txt i zapisz do pogoda_gd.txt\n";
    cout << "k - Wczytaj dane z pliku 1(wpisz nazwe) i zapisz do 2(wpisz nazwe)\n";
    cout << "q - Zakończ program\n";
}

int main() {
    setlocale(LC_CTYPE, "pl-PL");//jezyk polski
    char wyb;
    char nazwaPlikWej[128];
    char nazwaPlikWyj[128];
    do {
        menu();
        cout << "Wybierz opcję: ";
        cin >> wyb;
        cout << "------------------------------------\n";

        if (wyb == 'o') {
            char linie[MAX_LINI][128];
            MetarDane data[MAX_LINI];
            int linieLicz = 0;

            ifstream wczytPlik("Metar Gdansk.txt");
            ofstream zapPlik("pogoda_gd.txt");

            if (!wczytPlik) {
                cerr << "Blad otwarcia pliku Metar Gdansk.txt\n";
                continue;
            }

            while (wczytPlik.getline(linie[linieLicz], 128) && linieLicz < MAX_LINI) {
                wczytanieDanych(linie[linieLicz], data[linieLicz]);
                linieLicz++;
            }

            wczytPlik.close();

            for (int i = 0; i < 3; ++i) {
                wypiszDane(data[i], cout);
            }

            for (int i = 0; i < linieLicz; ++i) {
                wypiszDane(data[i], zapPlik);
            }

            zapPlik.close();
        }
        else if (wyb == 'k') {
            cout << "Wpisz nazwe pliku wczytującego dane: ";
            cin >> nazwaPlikWej;
            cout << "------------------------------------\n";
            cout << "Wpisz nazwe pliku zapisującego dane: ";
            cin >> nazwaPlikWyj;
            cout << "------------------------------------\n";
            char linie[MAX_LINI][128];
            MetarDane data[MAX_LINI];
            int linieLicz = 0;

            ifstream wczytPlik(nazwaPlikWej);
            ofstream zapPlik(nazwaPlikWyj);

            if (!wczytPlik) {
                cerr << "Błąd otwarcia pliku wejściowego\n";
                cout << "------------------------------------\n";
                continue;
            }
            if (!zapPlik) {
                cerr << "Błąd otwarcia pliku wyjściowego\n";
                cout << "------------------------------------\n";
                wczytPlik.close();
                continue;
            }

            while (wczytPlik.getline(linie[linieLicz], 128) && linieLicz < MAX_LINI) {
                wczytanieDanych(linie[linieLicz], data[linieLicz]);
                linieLicz++;
            }

            wczytPlik.close();

            for (int i = 0; i < 3; ++i) {
                wypiszDane(data[i], cout);
            }

            for (int i = 0; i < linieLicz; ++i) {
                wypiszDane(data[i], zapPlik);
            }

            zapPlik.close();
        }
        else if (wyb != 'q') {
            cout << "Nieznana opcja, spróbuj ponownie.\n";
            cout << "------------------------------------\n";
        }
    } while (wyb != 'q');

    return 0;
}
