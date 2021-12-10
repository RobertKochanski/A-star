#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

int** wczytaj_grid(string);
void wypelnij_liczba(float, float[20][20]);
int obliczG(int, int, float[20][20]);
void pokaz_droge(int**, float[20][20], int, int, int, int);

int main()
{
	int** mapa = wczytaj_grid("grid.txt");

	float wartosci[20][20];
	wypelnij_liczba(999, wartosci);
	
	float sprawdzone[20][20];
	wypelnij_liczba(0, sprawdzone);

	float droga[20][20]; // 8 - w górê , 6 - w prawo, 4 - w lewo, 2 - w dó³
	wypelnij_liczba(0, droga);

	int xstart = 19, ystart = 0;
	int xkoniec = 0, ykoniec = 19;
	int xobecne = xstart;
	int yobecne = ystart;

	float wartosc_pola;
	int err = 0;


	for (;;)
	{
		float Fnajmniejsze = 999;
		sprawdzone[xobecne][yobecne] = 1;
		if (mapa[xstart][ystart] == 5 || mapa[xkoniec][ykoniec])
		{
			cout << endl << "Pole startowe lub koncowe jest przeszkoda!" << endl;
			err = 1;
			break;
		}
		int G = obliczG(xobecne, yobecne, droga);
		if (--xobecne >= 0 && mapa[xobecne][yobecne] != 5 && sprawdzone[xobecne][yobecne] != 1) // sprawdzenie pola do góry
		{
			if (xobecne == xkoniec && yobecne == ykoniec)
			{
				mapa[xobecne][yobecne] = 3;
				droga[xobecne][yobecne] = 2;
				break;
			}

			wartosc_pola = G + sqrt(pow((xobecne - xkoniec), 2) + pow((yobecne - ykoniec), 2));
			if (wartosc_pola < wartosci[xobecne][yobecne])
			{
				wartosci[xobecne][yobecne] = wartosc_pola;
				droga[xobecne][yobecne] = 2;
			}
			++xobecne;
		}
		else
		{
			++xobecne;
		}

		if (++xobecne <= 19 && mapa[xobecne][yobecne] != 5 && sprawdzone[xobecne][yobecne] != 1) // sprawdzenie pola do do³u
		{
			if (xobecne == xkoniec && yobecne == ykoniec)
			{
				mapa[xobecne][yobecne] = 3;
				droga[xobecne][yobecne] = 8;
				break;
			}

			wartosc_pola = G + sqrt(pow((xobecne - xkoniec), 2) + pow((yobecne - ykoniec), 2));
			if (wartosc_pola < wartosci[xobecne][yobecne])
			{
				wartosci[xobecne][yobecne] = wartosc_pola;
				droga[xobecne][yobecne] = 8;
			}
			--xobecne;
		}
		else
		{
			--xobecne;
		}

		if (--yobecne >= 0 && mapa[xobecne][yobecne] != 5 && sprawdzone[xobecne][yobecne] != 1) // sprawdzenie pola z lewej
		{
			if (xobecne == xkoniec && yobecne == ykoniec)
			{
				mapa[xobecne][yobecne] = 3;
				droga[xobecne][yobecne] = 6;
				break;
			}

			wartosc_pola = G + sqrt(pow((xobecne - xkoniec), 2) + pow((yobecne - ykoniec), 2));
			if (wartosc_pola < wartosci[xobecne][yobecne])
			{
				wartosci[xobecne][yobecne] = wartosc_pola;
				droga[xobecne][yobecne] = 6;
			}
			++yobecne;
		}
		else
		{
			++yobecne;
		}

		if (++yobecne <= 19 && mapa[xobecne][yobecne] != 5 && sprawdzone[xobecne][yobecne] != 1) // sprawdzenie pola z prawej
		{
			if (xobecne == xkoniec && yobecne == ykoniec)
			{
				mapa[xobecne][yobecne] = 3;
				droga[xobecne][yobecne] = 4;
				break;
			}

			wartosc_pola = G + sqrt(pow((xobecne - xkoniec), 2) + pow((yobecne - ykoniec), 2));
			if (wartosc_pola < wartosci[xobecne][yobecne])
			{
				wartosci[xobecne][yobecne] = wartosc_pola;
				droga[xobecne][yobecne] = 4;
			}
			--yobecne;
		}
		else
		{
			--yobecne;
		}

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				if (sprawdzone[i][j] != 1)
				{
					if (wartosci[i][j] <= Fnajmniejsze)
					{
						Fnajmniejsze = wartosci[i][j];
						xobecne = i;
						yobecne = j;
					}
				}
			}
		}
		if (Fnajmniejsze == 999)
		{
			cout << endl << "Osiagniecie celu jest niemozliwe!" << endl;
			err = 1;
			break;
		}
	}
	if (err == 0)
	{
		pokaz_droge(mapa, droga, xobecne, yobecne, xstart, ystart);
	}
}

int** wczytaj_grid(string nazwa)
{
	int wym1 = 20;
	int wym2 = 20;

	int rows = wym2;
	int** G;

	G = new int* [rows];
	while (rows--) G[rows] = new int[wym1];

	ifstream plik(nazwa);

	if (plik.good() == true)
	{
		cout << "Mapa wczytana z pliku:" << endl;
		for (int i = 0; i < wym2; i++)
		{
			for (int j = 0; j < wym1; j++)
			{
				plik >> G[i][j];
			}
		}

		plik.close();

		for (int i = 0; i < 20; i++)
		{
			for (int j = 0; j < 20; j++)
			{
				cout << G[i][j] << " ";
			}
			cout << endl;
		}
	}
	else
	{
		cout << "Blad przy wczytywaniu pliku!";
	}

	return G;
}
void wypelnij_liczba(float liczba, float tab[20][20])
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			tab[i][j] = liczba;
		}
	}
}
int obliczG(int x, int y, float droga[20][20])
{
	int i = 0;
	while (droga[x][y] > 0)
	{
		if (droga[x][y] == 8) x--;
		else if (droga[x][y] == 2) x++;
		else if (droga[x][y] == 4) y--;
		else if (droga[x][y] == 6) y++;
		i++;
	}
	return i;
}
void pokaz_droge(int** mapa, float droga[20][20], int xobecne, int yobecne, int xstart, int ystart)
{
	cout << endl << "Trasa wyznaczona metoda A* " << endl;
	for (;;)
	{
		if (droga[xobecne][yobecne] == 8)
		{
			--xobecne;
			mapa[xobecne][yobecne] = 3;
		}
		else if (droga[xobecne][yobecne] == 2)
		{
			++xobecne;
			mapa[xobecne][yobecne] = 3;
		}
		else if (droga[xobecne][yobecne] == 4)
		{
			--yobecne;
			mapa[xobecne][yobecne] = 3;
		}
		else if (droga[xobecne][yobecne] == 6)
		{
			++yobecne;
			mapa[xobecne][yobecne] = 3;
		}
		if (xobecne == xstart && yobecne == ystart)
		{
			mapa[xobecne][yobecne] = 3;
			break;
		}
	}

	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			cout << mapa[i][j] << " ";
		}
		cout << endl;
	}
}