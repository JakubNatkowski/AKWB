// graf_4.cpp : Ten plik zawiera funkcjê „main”. W nim rozpoczyna siê i koñczy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <list>
#include <fstream>

using namespace std;

vector< vector <int> > lista_nast;
vector< vector <int> > lista_krawedzi;

bool sprzezony = true;
bool liniowy = true;
bool onegraf = true;

unsigned i, j, k, l, m, a, h;

int cmp = 0;  //zmienna pomocnicza do porownywania wartosci wierzcholkow


void odczyt_lista_nast()
{
	string wiersz;
	string liczba;
	int wierzcholek;
	int iter = -1;

	fstream plik;
	plik.open("C:\\Users\\Agata\\Desktop\\graf.txt", ios::in);

	while (!plik.eof())
	{
		//cout<<"wszedlem"<<endl;
		getline(plik, wiersz);
		if (wiersz == ";")
		{
			// cout<<"if"<<endl;
			lista_nast.push_back(vector<int>());
			iter++;

		}

		else
		{
			wierzcholek = atoi(wiersz.c_str());
			lista_nast[iter].push_back(wierzcholek);
		}
	}

	plik.close();
}

void wyswietl_lista_nast()
{
	cout << endl << "Lista nastepnikow: " << endl;
	for (i = 0; i < lista_nast.size(); i++)
	{
		for (j = 0; j < lista_nast[i].size(); j++)
		{
			cout << lista_nast[i][j] << " ";
		}
		cout << endl;
	}
}

int czy_onegraf()
{
	for (i = 0; i < lista_nast.size(); i++)
	{
		for (k = 1; k < lista_nast[i].size(); k++)
		{
			if (lista_nast[i].size() > 2)
			{
				cmp = lista_nast[i][k]; //ustawiamy cmp na wartosc piwerwszego nastepnika
				for (a = 2; a < lista_nast[i].size(); a++) //for, ktory nam leci od drugiego nastepnika z kolei
				{
					if (a != k)
					{
						if (cmp == lista_nast[i][a])
						{
							onegraf = false;
							cout << endl << "MULTIGRAF! PRZERYWAMY ZABAWE :c " << endl;
							exit(0);
						}
						
					}
				}
				
				

			}
		}
	}
	if (onegraf == true)
		cout << endl << "ONEGRAF!" << endl;

}

int czy_sprzezony()
{

	int wspolne = 0;
	int rozmiar = 0;

	for (i = 0; i < lista_nast.size(); i++)
	{
		if (lista_nast[i].size() > 1)
		{
			for (j = (i + 1); j < lista_nast.size(); j++)
			{
				wspolne = 0;

				for (k = 1; k < lista_nast[i].size(); k++)
				{
					for (m = 1; m < lista_nast[j].size(); m++)
					{
						if (lista_nast[i].size() >= lista_nast[j].size())
						{
							rozmiar = lista_nast[i].size() - 1;
						}

						else if (lista_nast[i].size() < lista_nast[j].size())
						{
							rozmiar = lista_nast[j].size() - 1;
						}

						if (lista_nast[i][k] == lista_nast[j][m])
						{

							wspolne++;
						}
					}
				}
				if ((wspolne != rozmiar) && (wspolne != 0))
				{
					// cout<<"AKWB"<<endl;
					sprzezony = false;
					break;
				}

				if (sprzezony == false)
					break;
			}
			if (sprzezony == false)
				break;
		}
		if (sprzezony == false)
			break;

	}
	if (sprzezony == true)
		cout << endl << "SPRZEZONY" << endl;
	else
	{
		cout << endl << "NIESPRZEZONY" << endl;
		exit(0);
	}
}

void czy_liniowy()
{
	bool struktura_12 = false;
//	bool str_1, str_2 = false;
	bool pierwszy = false;
	bool drugi = false;
	bool trzeci = false;
	int tmp1, tmp2, heh = 0;



	/*  SPRAWDZENIE CZY JEST 1 i 2 STRUKTURA */
	/*  --------------------------------------- */

	for (i = 0; i < lista_nast.size(); i++)
	{
		if (lista_nast[i].size() > 2) //tutaj szukam pierwszego wierzcholka ze struktury, ktory ma 2 nastepniki
		{
			for (k = 1; k < 2; k++) //zeby sprawdzal tylko pierwszy nastepnik
			{
				for (j = 1; j < lista_nast.size(); j++)
				{
					if (i != j)  //zeby nei porownal sam ze soba
					{
						if (lista_nast[i][k] == lista_nast[j][0])
						{
							pierwszy = true;
							tmp1 = j; // tu zapisuje wiersz w ktorym jest pierwszy nastepnik
						}
						if (pierwszy == true)
						{
							for (h = 2; h < lista_nast[i].size(); h++)  //zeby porowywal od drugiego
							{
								for (m = 0; m < lista_nast.size(); m++)
								{
									if (m != j && m != i)  //zeby szukal w jakims trzecim innym wierszu
									{
										if (lista_nast[i][h] == lista_nast[m][0])
										{
											drugi = true;
											tmp2 = m;  // tu zapisuje wiersz, w ktorym jets drugi nastepnik

										}
									}
									if (drugi == true)
										break;

								}
								if (drugi == true)
									break;
							}
						}

					}

				}
				if (pierwszy && drugi)
					break;

			}
			if (pierwszy && drugi)
				break;
		}
	}


	if (pierwszy && drugi)
	{
		for (i = 0; i < lista_nast[tmp1].size(); i++)
		{
			for (j = 1; j < lista_nast[tmp2].size(); j++)
			{
				if ((lista_nast[tmp1][i] == lista_nast[tmp2][j]))
				{
					trzeci = true;
				}
			}
		}

	}

	if (pierwszy&&drugi&&trzeci)
	{
		struktura_12 = true;
		cout << endl << "Znaleziono 1 lub 2 strukture!" << endl;

	}
	
	/*SPRAWDZENIE CZY JEST  3 STRUKTURA*/
	/* --------------------------------*/

	bool struktura_3 = false;
	bool nast_1 = false;
	bool nast_2 = false;
	bool petla_1 = false;
	bool petla_2 = false;


	for (i = 0; i < lista_nast.size(); i++)  //petla glowna
	{
		int cmp = lista_nast[i][0];

		if (lista_nast[i].size() > 2)
		{
			for (l = 1; l < lista_nast[i].size(); l++)  //tu znajduje petle
			{
				if (cmp == lista_nast[i][l])
					petla_1 = true;
			
			}
			for (j = 1; j < lista_nast.size(); j++)
			{
				for (h = 1; l < lista_nast[i].size(); h++)
				{
					if (lista_nast[i][h] == lista_nast[j][0])
						nast_1 = true;

					if (lista_nast[j][0] == lista_nast[j][h])
						petla_2 = true;

					if (cmp == lista_nast[j][h])
						nast_2 = true;
				}
				if (nast_1 && nast_2 && petla_2)
					break;
			}
			if (nast_1 && nast_2 && petla_2)
				break;
		}
		if (nast_1 && nast_2 && petla_2)
			break;
	}


	if (nast_1 && nast_2 && petla_1 && petla_2)
	{
		struktura_3 = true;
		cout << endl << "Znaleziono 3 strukture!" << endl;
	}

	if (struktura_12 || struktura_3)
	{
		liniowy = false;
	}

	if (liniowy == false)
	{
		cout << "NIE-LINIOWY" << endl << endl;
	}
	else
		cout << endl << "LINIOWY!" << endl << endl;

}

void transformacja()
{
	int nowy_wierzch = 1;
	int l_wierzcholkow = lista_nast.size();

	for (int i = 0; i < l_wierzcholkow; i++)
	{
		lista_krawedzi.push_back(vector<int>());

		for (int j = 0; j < 2; j++)
		{
			lista_krawedzi[i].push_back(nowy_wierzch);
			nowy_wierzch++;
		}
	}
	//wyswietl nadmiarowy graf
	cout << "lista krawedzi: " << endl;
	for (int i = 0; i < lista_krawedzi.size(); i++)
	{
		for (int j = 0; j < lista_krawedzi[i].size(); j++)
		{
			cout << lista_krawedzi[i][j] << " ";
		}
		cout << endl;
	}
;

	for (int i = 0; i < lista_nast.size(); i++)
	{
		for (int j = 1; j < lista_nast[i].size(); j++)
		{
			int krawedz = lista_nast[i][j] - 1;  // zmienna w ktorej przechowuje wartosc krawedzi do ktorej bede szla przy porownaniu
			
			if (lista_krawedzi[i][1] < lista_krawedzi[krawedz][0])
				lista_krawedzi[krawedz][0] = lista_krawedzi[i][1];

			else
				lista_krawedzi[i][1] = lista_krawedzi[krawedz][0];

		}

	}
	cout << endl;

	cout << "lista krawedzi po transformacji: " << endl;
	for (int i = 0; i < lista_krawedzi.size(); i++)
	{
		for (int j = 0; j < lista_krawedzi[i].size(); j++)
		{
			cout << lista_krawedzi[i][j] << " ";
		}
		cout << endl;
	}

	cout << endl;

}

void Uporzadkuj()
{
	int n = 1, k = 0;
	while (n)
	{
		k = 0;
		for (int i = 0; i < lista_krawedzi.size(); i++)
		{
			if (k) { break; }
			for (int j = 0; j < lista_krawedzi.size(); j++)
			{
				if (i == j) { continue; }
				if (lista_krawedzi[i][0] == lista_krawedzi[j][0])
				{
					lista_krawedzi[i].push_back(lista_krawedzi[j][1]);
					lista_krawedzi.erase(lista_krawedzi.begin() + j);

					k = 1;
					break;
				}
			}
			if (k) { break; }
			if (i == (lista_krawedzi.size() - 1)) { n = 0; }
		}
	}


	cout << " wyswietlanie listy krawedzi po transformacji i scisnieciu : " << endl;

	for (int i = 0; i < lista_krawedzi.size(); i++)
	{
		for (int j = 0; j < lista_krawedzi[i].size(); j++)
		{
			cout << lista_krawedzi[i][j] << " ";
		}
		cout << endl;
	}
}

void zapis_graf_oryginalny()
{
	fstream pliczek;

	pliczek.open("C:\\Users\\Agata\\Desktop\\lista_krawedzi.txt", ios::out | ios::trunc);
	if (pliczek.good() == true)
	{
		pliczek << ";" << endl;

		for (i = 0; i < lista_krawedzi.size(); i++)
		{
			for (k = 0; k < lista_krawedzi[i].size(); k++)
			{
				pliczek << lista_krawedzi[i][k] << endl;
				if (k == (lista_krawedzi[i].size() - 1) && i != (lista_krawedzi.size() - 1))
					pliczek << ";" << endl;
				if (lista_krawedzi[i].size() == 0)
					pliczek << "" << endl;

			}
		}
	}
	pliczek.close();
}

void odczyt_lista_krawedzi()
{
	string wiersz;
	string liczba;
	int wierzcholek;
	int iter = -1;

	fstream plik;
	plik.open("C:\\Users\\Agata\\Desktop\\lista_krawedzi.txt", ios::in);

	while (!plik.eof())
	{
		//cout<<"wszedlem"<<endl;
		getline(plik, wiersz);
		if (wiersz == ";")
		{
			// cout<<"if"<<endl;
			lista_nast.push_back(vector<int>());
			iter++;

		}

		else
		{
			wierzcholek = atoi(wiersz.c_str());
			lista_nast[iter].push_back(wierzcholek);
		}
	}

	plik.close();
}

void wyswietl_lista_krawedzi()
{
	cout << endl << "Lista nastepnikow grafu oryginalnego: " << endl;
	for (i = 0; i < lista_krawedzi.size(); i++)
	{
		for (j = 0; j < lista_krawedzi[i].size(); j++)
		{
			cout << lista_krawedzi[i][j] << " ";
		}
		cout << endl;
	}
}

int czy_oryginal_onegraf()
{
	for (i = 0; i < lista_krawedzi.size(); i++)
	{
		for (k = 1; k < lista_krawedzi[i].size(); k++)
		{
			if (lista_krawedzi[i].size() > 2)
			{
				cmp = lista_krawedzi[i][k]; //ustawiamy cmp na wartosc piwerwszego nastepnika
				for (a = 2; a < lista_krawedzi[i].size(); a++) //for, ktory nam leci od drugiego nastepnika z kolei
				{
					if (a != k)
					{
						if (cmp == lista_krawedzi[i][a])
						{
							onegraf = false;
							cout << endl << "MULTIGRAF! PRZERYWAMY ZABAWE :c " << endl;
							exit(0);

						}
						
					}
				}
//
			}
		}
	}
	if (onegraf == true)
		cout << endl << "ONEGRAF!" << endl;

}

int czy_oryginal_sprzezony()
{
	int wspolne = 0;
	int rozmiar = 0;

	for (i = 0; i < lista_krawedzi.size(); i++)
	{
		if (lista_krawedzi[i].size() > 1)
		{
			for (j = (i + 1); j < lista_krawedzi.size(); j++)
			{
				wspolne = 0;

				for (k = 1; k < lista_krawedzi[i].size(); k++)
				{
					for (m = 1; m < lista_krawedzi[j].size(); m++)
					{
						if (lista_krawedzi[i].size() >= lista_krawedzi[j].size())
						{
							rozmiar = lista_krawedzi[i].size() - 1;
						}

						else if (lista_krawedzi[i].size() < lista_krawedzi[j].size())
						{
							rozmiar = lista_krawedzi[j].size() - 1;
						}

						if (lista_krawedzi[i][k] == lista_krawedzi[j][m])
						{
							wspolne++;
						}
					}
				}
				if ((wspolne != rozmiar) && (wspolne != 0))
				{
					sprzezony = false;
					break;
				}

				if (sprzezony == false)
					break;
			}
			if (sprzezony == false)
				break;
		}
		if (sprzezony == false)
			break;

	}
	if (sprzezony == true)
		cout << endl << "SPRZEZONY" << endl;
	else
	{
		cout << endl << "NIESPRZEZONY" << endl;
		exit (0);
	}
}

void czy_oryginal_liniowy()
{
	bool struktura_12 = false;
//	bool str_1, str_2 = false;
	bool pierwszy = false;
	bool drugi = false;
	bool trzeci = false;
	int tmp1, tmp2 = 0;



	/*  SPRAWDZENIE CZY JEST 1 i 2 STRUKTURA */
	/*  --------------------------------------- */

	for (i = 0; i < lista_krawedzi.size(); i++)
	{
		if (lista_krawedzi[i].size() > 2)
		{
			for (k = 1; k < 2; k++) //zeby sprawdzal tylko pierwszy nastepnik
			{
				for (j = 1; j < lista_krawedzi.size(); j++)
				{
					// cout<<"j: "<<j<<endl;
					if (i != j)  //zeby nei porownal sam ze soba
					{
						if (lista_krawedzi[i][k] == lista_krawedzi[j][0])
						{
							// cout<<"i: "<<i<<"  k: "<<k<<"  j: "<<j<<endl;
							//  cout<<"PIERWSZY     "<< lista_nast[i][k] << "  " << lista_nast[j][0]<<endl;
							pierwszy = true;/**<  */
							tmp1 = j;
						}
						if (pierwszy == true)
						{
							for (h = 2; h <= lista_krawedzi[i].size(); h++) //zeby porowywal od drugiego
							{
								for (m = 0; m < lista_krawedzi.size(); m++)
								{

									if (m != j && m != i)  //zeby szukal w jakims trzcim innym wierszu
									{
										if (lista_krawedzi[i][h] == lista_krawedzi[m][0])
										{
											//cout<<"i: "<<i<<"  h: "<<h<<"  m: "<<m<<"  k: "<<k<<"  j: "<<j<<endl;
											// cout<<"DRUGI   "<< lista_nast[i][h] << "  " << lista_nast[m][0]<<endl;
											drugi = true;
											tmp2 = m;

										}
									}
									if (drugi == true)
										break;

								}
								if (drugi == true)
									break;
							}

						}

					}
					if (pierwszy && drugi)
						break;
				}
				
			}
			if (pierwszy && drugi)
				break;
		}
	}

	//cout<<"tmp1: "<<tmp1<<"  tmp2: "<<tmp2<<endl;

	if (pierwszy && drugi)
	{
		for (i = 1; i < lista_krawedzi[tmp1].size(); i++)
		{
			for (j = 1; j < lista_krawedzi[tmp2].size(); j++)
			{
				if ((lista_krawedzi[tmp1][i] == lista_krawedzi[tmp2][j]))
				{
					trzeci = true;
					// str_1 = true;
				}
				// if( lista_nast[tmp1][i] == lista_nast[i][0])
				// str_2 = true;
			}
		}

	}

	if (pierwszy&&drugi&&trzeci)
	{
		struktura_12 = true;
		cout << endl << "Znaleziono 1 lub 2 strukture!" << endl;

	}

	/*    if(str_1 == true)
			cout<<"znaleziono 1 strukture!"<<endl;

		  if(str_2 == true)
			cout<<"znaleziono 2 strukture!"<<endl;
	*/


	/*SPRAWDZENIE CZY JEST  3 STRUKTURA*/
	/* --------------------------------*/

	bool struktura_3 = false;
	bool nast_1 = false;
	bool nast_2 = false;
	bool petla_1 = false;
	bool petla_2 = false;

	//bool petla_1, petla_2 = false; 


	for (i = 0; i < lista_krawedzi.size(); i++)  //petla glowna
	{
		int cmp = lista_krawedzi[i][0];

		if (lista_krawedzi[i].size() > 2)
		{
			//for(k=0; k<lista_nast[i].size(); k++)
			{
				for (h = 1; h < lista_krawedzi[i].size(); h++)  //tu znajduje petle
				{
					if (cmp == lista_krawedzi[i][h])
						petla_1 = true;

				}

			}
			for (j = 1; j < lista_krawedzi.size(); j++)
			{
				if (lista_krawedzi[j].size() > 2)
				{
					if (i != j)
					{
						for (h = 1; l < lista_krawedzi[h].size(); h++)
						{
							if (lista_krawedzi[i][h] == lista_krawedzi[j][0])
								nast_1 = true;

							if (lista_krawedzi[j][0] == lista_krawedzi[j][h])
								petla_2 = true;

							if (cmp == lista_krawedzi[j][h])
								nast_2 = true;
						}
						if (nast_1 && nast_2 && petla_2)
							break;
					}
					if (nast_1 && nast_2 && petla_2)
						break;
				}
				if (nast_1 && nast_2 && petla_2)
					break;
			}
		}
	}


	if (nast_1 && nast_2 && petla_1 && petla_2)
	{
		struktura_3 = true;
		cout << endl << "Znaleziono 3 strukture!" << endl;
	}

	if (struktura_12 || struktura_3)
	{
		liniowy = false;
	}

	if (liniowy == false)
	{
		cout << "NIE-LINIOWY" << endl << endl;
	}
	else
		cout << endl << "LINIOWY!" << endl << endl;
}

int main()
{

	odczyt_lista_nast();
	wyswietl_lista_nast();
	czy_onegraf();
	czy_sprzezony();
	if (sprzezony == true)
	{
		czy_liniowy();
		transformacja();
		Uporzadkuj();
		zapis_graf_oryginalny();
		odczyt_lista_krawedzi();
		wyswietl_lista_krawedzi();
		czy_oryginal_onegraf();
		if (onegraf == true)
		{
			czy_oryginal_sprzezony();
			czy_oryginal_liniowy();
		}


	}

	return 0;
}





