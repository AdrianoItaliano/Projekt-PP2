#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

int main()
{
	setlocale(LC_CTYPE, "pl-PL");
	char wybor, lot, dzien;
	
	ifstream file;
	cout << "Witam, Adrian Bednarek 203502, menu:" << endl;
	cout << "o - Wybierz dane z pliku" << endl;
	cout << "q - Zakończ program" << endl;
	cin >> wybor;
	cout << "-----------------------------------" << endl;
	if (wybor == 'o')
	{
		file.open("Metar Gdansk.txt");
		
        

	}
	else if (wybor == 'q')
	{
		cout << "Zamykanie programu...";
		return 0;
	}

}
