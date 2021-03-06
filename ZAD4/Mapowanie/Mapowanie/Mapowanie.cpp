// ostatni program.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <conio.h>
#include <sstream>

using namespace std;


/************************************************************* globalne *********************************************************/

vector <int> A;
vector <int> elem;
clock_t start, koniec;
double czas;

void Read_map_Generate();
void wczytaj_multizbior(vector<int>);
void ile_elemntow(vector<int>);
void szukaj(int *tab_rozw, int ind, int *jest);

int l_frag;
int p_el;
int id_p;
int maxind;


int main()
{
	//Read_map_Generate();
	wczytaj_multizbior(A);
	ile_elemntow(A);

	maxind = l_frag - 1;

	int * tab_rozw = new int[l_frag];
	for (int i = 0; i < l_frag; i++)
		tab_rozw[i] = 0;
	tab_rozw[0] = p_el;

	int jest = 0;

	start = clock();
	szukaj(tab_rozw, 0, &jest);
	koniec = clock();


	czas = (double)(koniec - start) / (double)(CLOCKS_PER_SEC);
	cout << "\n czas trwania to: " << czas << endl;

	if (jest == 0)
	{
		cout << endl << " BRAK ROZWIAZANIA " << endl;
	}
}


void Read_map_Generate()
{
	int i, j;
	vector<int> map_pom;
	vector<int> sorted_map;

	fstream file;
	string line;
	file.open("C:\\Users\\Agata\\Desktop\\mapa.txt", ios::in);

	if (file.is_open())
	{
		//cout << "Wczytano plik mapa!" << endl;

		getline(file, line);
		istringstream ss(line);
		int num;

		// WCZYTYWANIE MAPY 

		while (ss >> num)
			map_pom.push_back(num);


		cout << endl << "wczytana mapa: ";
		for (i = 0; i < map_pom.size(); i++)
			cout << map_pom[i] << " ";

		int size = map_pom.size();
		int liczba = 0;

		for (i = 0; i < size - 1; i++) //tu robie sume wszystkich kombinacji sasiednich liczb
		{
			liczba = 0;
			for (j = i + 1; j < size; j++)
			{
				if (liczba > 1)
				{
					liczba += map_pom[j];
					map_pom.push_back(liczba);
				}
				if (liczba == 0)
				{
					liczba = map_pom[j] + map_pom[i];
					map_pom.push_back(liczba);
				}
			}
		}

		cout << endl << endl << "Dodanie wartosci mapy: ";
		for (i = 0; i < map_pom.size(); i++)
			cout << map_pom[i] << " ";

		sorted_map = map_pom;
		sort(sorted_map.begin(), sorted_map.end());

		cout << endl << endl << "Posortowany multizbior: ";
		for (i = 0; i < sorted_map.size(); i++)
			cout << sorted_map[i] << " ";

		cout << endl;
	}
	else
	{
		cout << "BLAD ODCZYTU" << endl;
		exit(0);
	}
}

void wczytaj_multizbior(vector<int> $A)
{
	fstream plik;
	string sciezka = "C:\\Users\\Agata\\Desktop\\multizbior.txt";
	plik.open(sciezka, std::ios::in);

	int cos = 0;

	if (plik.good())
	{
		while (!plik.eof())
		{
			plik >> cos;
			A.push_back(cos);
		}
	}
	plik.close();

	cout << "A: ";
	for (int i = 0; i < A.size(); i++)
		cout << A[i] << " ";

	int max = A[0];


	for (int i = 1; i < A.size(); i++)
	{
		if (A[i] > max)
		{
			max = A[i];
		}
	}

	int max_2 = A[0];
	if (max_2 == max)
	{
		max_2 = A[1];
		for (int j = 2; j < A.size(); j++)
		{
			if (A[j] > max_2)
				max_2 = A[j];
		}
	}
	else
	{
		for (int j = 1; j < A.size(); j++)
		{
			if (A[j] != max)
				if (A[j] > max_2)
					max_2 = A[j];
		}

	}

	/*el_1 = A[0];
	el_2 = A[1];*/
	p_el = max - max_2;
	//cout << endl << "max : " << max << endl;
	//cout << endl << "max_2 : " << max_2 << endl;
	//cout << endl<<"p_el = " << p_el << endl;

	

	for (int i = 0; i < A.size(); i++)
	{
		if (A[i] == p_el)
		{
			id_p = i;
			break;
		}

	}
	sort(A.begin(), A.end());
}

void ile_elemntow(vector<int> $A)
{

	int size = A.size();
	int delta = 0;
	size *= 2;
	delta = 1 + 4 * size;
	delta = sqrt(delta);

	l_frag = ((1 + delta) / 2);

	if ((l_frag * (l_frag - 1)) / 2 == A.size())
		cout<<endl << "Licznosc odpowiednia! Podano prawidlowe dane" << endl << endl;
	else
	{
		cout << endl<<" Podane zle dane! :(" << endl;
		exit(0);
	}

	l_frag = l_frag - 1;
	//cout << endl << "l_frag: " << l_frag << endl;
}

void szukaj( int *tab_rozw, int ind, int *jest)
{
	int element;
	bool suma_jest = false;

	int * tab_zuzyte = new int[A.size()];  // dynamiczna tablica zuzytych elementow A
	for (int i = 0; i < A.size(); i++) //zaeruje ja przy kazdym wywolaniu funkcji
		tab_zuzyte[i] = 0;
	

	for (int i = 0; i < l_frag; i++) //zeby tutaj ja uzupelnic odpowidnimi wartosciami z obecnego rozwiazania
	{
		for (int j = 0; j < A.size(); j++)
		{
			if (A[j] == tab_rozw[i])
			{
				if (tab_zuzyte[j] == 0)
				{
					tab_zuzyte[j] = 1;
					break;
				}
			}
		}

	}

	if (ind == maxind)
	{
		bool rozwiazanie = true;
		vector < int > sumy;

		//jak jest rozwiazanie to sprawdzam je na zasadzie:
		//z mojego rozwiazania tworze multizbior

		for (int i = 0; i < l_frag; i++)
		{
			int cos = tab_rozw[i];
			sumy.push_back(cos);
			for (int j = i + 1; j < l_frag; j++)
			{
				
				int suma = cos + tab_rozw[j];
				cos += tab_rozw[j];
				sumy.push_back(suma);
			}
		}

		//sortuje oba multizbiory - ten z wejscia i ten z rozwiazania 
		sort(sumy.begin(), sumy.end()); 		
		sort(A.begin(), A.end());


		if (sumy.size() != A.size())   //jezeli rozmiary multizbiorow sa rozne to rozwiazanie jest bledne
			rozwiazanie = false;

		else if (sumy.size() == A.size())	// jezeli rozmiary sa takie same
			for (int k = 0; k < sumy.size(); k++) //to sprawdzamy czy elementy sa takie same
			{
				if (sumy[k] != A[k]) //jezeli jakas para z porownnaia sie rozni
				{
					rozwiazanie = false;  //to rozwiazanie jest niepoprawne
					break;
				}
			}

		if (rozwiazanie)
		{
			cout << endl << "  rozwiazanie : ";		//jezeli rozwiaznie jest prawidlowe to je wyswietlam
			for (int r = 0; r < l_frag; r++)
				cout << tab_rozw[r] << " ";
			*jest = 1;
		}
		else  //jezeli nie to usuwam osttani element z rozwiazania i
		{
			int zla_liczba = tab_rozw[ind];
			for (int i = 0; i < A.size(); i++)
			{
				if (zla_liczba == A[i])  //jak znajdziemy zla liczba w zbiorze
				{
					tab_rozw[ind] = 0;
					tab_zuzyte[i] = 0; //to w tablicy zuzytych zmieniamy jej wartosc na zero
					break;
				}
			}
		}

	}
	else for (int a = 0; a < A.size(); a++)  //przechodzimy przez multizbior  
	{
		bool warto = true;

		if (tab_zuzyte[a] == 0) //jezeli element nie byl uzyty
		{
			element = A[a];  
			tab_rozw[ind + 1] = element;  //element niezuzyty jest teraz koljenym elementem mojego rozwiazania - dodaje go do rozwiazania

			/*cout << "tab_rozw [z]  ";
			for(int z = 0; z < l_frag; z++)
				cout  << tab_rozw[z] << " ";
			cout << endl;*/

			for (int i = 0; i < l_frag - 1; i++)									//sprawdzamy czy sumy elementow sa w A
			{				
				int sklad = tab_rozw[i];
				for (int j = i + 1; j < l_frag; j++)
				{
					
					int suma = sklad + tab_rozw[j]; //dodajemy elementy do siebie
					sklad += tab_rozw[j];
					suma_jest = false;

					if (suma == 0)
						suma_jest = true;
					else 
						for (int k = 0; k < A.size(); k++)   //sprawdzamy czy suma elementow z rozwiazania jest w multizbiorze
						{
							if (suma == A[k]) //
								suma_jest = true;

						}
					if (!suma_jest) //jezzeli nie ma sumy w zbiorze 
					{
						warto = false; 
						tab_rozw[ind + 1] = 0; //to obecnie rozpatrywany element wyrzucamy z rozwiazania
						break;
					}
					else
						warto = true;
				}
				if (!suma_jest)
					break;
			}
			if (warto) //jezeli po sprawdzeniu calego rozwiazania, czyli wszystkie sumy sa w multizbiiorze i zmienna warto ma dalej wartosc 'true' to akceptujemy je i rekrencyjnie 
						//wyszukujemy kolejnego elementu rozwiazania
			{
				szukaj(tab_rozw, ind + 1, jest);

			}
		}
		if (*jest == 1)
			break;
	}
}


