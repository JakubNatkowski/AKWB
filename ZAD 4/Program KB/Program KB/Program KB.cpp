#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

vector<int> zbiorek;
vector<int>mapka;
bool *sumy;
int najwieksza = 0;
int iloscelem = 0;
int zaglebienie = 0;
bool znalezione = false;
bool *tab;

void odczyt() {

	ifstream plik;
	int liczba;

	plik.open("C:\\Users\\Agata\\Desktop\\mapa.txt", std::ios::in);
	if (plik.good() == false)
		cout << "Nie mozna otworzyc pliku!" << endl;
	else {
		while (plik.good()) {
			plik >> liczba;
			zbiorek.push_back(liczba);
		}
		cout << "Udalo sie wczytac plik!" << endl;
		plik.close();
	}
}

int Zaglebienie() {
	int i = 1;
	while (iloscelem * 2 != i * (i + 1)) {
		i++;
		if (i*(i + 1) > iloscelem * 2) {
			cout << "Bledny zbior!" << endl;
			return 0;
		}
	}
	return i;
}

bool SumaZgodna() {
	int suma = 0;
	bool a = 1;
	for (int i = 0; i < iloscelem; i++) {
		sumy[i] = false;
	}
	for (int i = 0; i < mapka.size(); i++) {
		suma = 0;
		for (int j = i; j < mapka.size(); j++) {
			a = 0;
			suma += mapka[j];
			if (suma > najwieksza) {
				return 0;
			}
			if (find(zbiorek.begin(), zbiorek.end(), suma) == zbiorek.end()) {
				return 0;
			}
			for (int i = 0; i < iloscelem; i++) {
				if (zbiorek[i] == suma && sumy[i] == false) {
					sumy[i] = true;
					a = 1;
					break;

				}
			}
			if (a == 0)
				return 0;
		}
	}
	return 1;
}

bool SumyWszystkie() {
	int sum = 0;
	for (int i = 0; i < mapka.size(); i++)
		sum += mapka[i];
	if (sum == najwieksza)
		return 1;
	else return 0;
}
void Nemo(int dodaj, int *jest, int poziom_zaglebienia) {

	int temp;
	vector<int>probowane;
	int item;

	mapka.push_back(dodaj);
	//for (int i = 0; i < mapka.size(); i++)
	//	cout << mapka[i] << " ";
	//cout << endl;

	for (int i = 0; i < iloscelem; i++) {
		if (zbiorek[i] == dodaj && tab[i] == 0) {
			tab[i] = true;
			break;
		}
	}
	if (poziom_zaglebienia == 0)
		probowane.push_back(dodaj);

	if (SumaZgodna()) {
		if (poziom_zaglebienia < zaglebienie - 1) {
			for (int i = 0; i < iloscelem; i++) {
				if (tab[i] == false) {
					probowane.push_back(zbiorek[i]);
					Nemo(zbiorek[i], jest, (poziom_zaglebienia + 1));
					break;
				}
			}
		}
		else if (SumyWszystkie()) {
			*jest = true;
		}
		else {
			for (int i = 0; i < iloscelem; i++) {
				int c = mapka[mapka.size() - 1];
				if (zbiorek[i] == c && tab[i] == true) {
					tab[i] = false; break;
				}
			}
			mapka.pop_back();
			return;
		}
	}
	else {
		for (int i = 0; i < iloscelem; i++) {
			int c = mapka[mapka.size() - 1];
			if (zbiorek[i] == c && tab[i] == true) {
				tab[i] = false; break;
			}
		}
		mapka.pop_back();
		return;

	}
	if (*jest == true) {
		return;
	}
	else {
		for (int i = 0; i < iloscelem; i++) {
			item = zbiorek[i];
			if (find(probowane.begin(), probowane.end(), item) == probowane.end() && tab[i] == false) {
				probowane.push_back(zbiorek[i]);
				Nemo(zbiorek[i], jest, (poziom_zaglebienia + 1));
				if (*jest == true) return;
			}
		}
		for (int i = 0; i < iloscelem; i++) {
			int c = mapka[mapka.size() - 1];
			if (zbiorek[i] == c && tab[i] == true) {
				tab[i] = false; break;
			}
		}
		mapka.pop_back();
		return;

	}
}
int main() {
	std::cout << "Hello World!\n";

	odczyt();

	for (int i = 0; i < zbiorek.size(); i++) {
		cout << zbiorek[i] << " ";
	}

	int jest = false;
	double stoper;
	clock_t start, stop;
	sort(zbiorek.begin(), zbiorek.end());
	najwieksza = zbiorek[zbiorek.size() - 1];
	iloscelem = zbiorek.size();
	zaglebienie = Zaglebienie();
	if (zaglebienie != 0) {
		tab = new bool[iloscelem];
		sumy = new bool[iloscelem];


		for (int i = 0; i < iloscelem; i++) {
			tab[i] = false;
			sumy[i] = false;
		}



		cout << endl;
		start = clock();
		for (int i = 0; i < zbiorek.size(); i++) {
			//	tab[i] = 1;
			Nemo(zbiorek[i], &jest, 0);
			if (jest == true) break;
		}
		stop = clock();
		long czas = (long)(stop - start);
		if (jest == false)
			cout << "Brak rozwiazania. " << endl;
		else {
			cout << "Mapa to: " << endl;
			for (int i = 0; i < mapka.size(); i++)
				cout << mapka[i] << " ";
			cout << "Czas dzialania: " << czas << "ms" << endl;
		}
	}

	system("pause");
}

