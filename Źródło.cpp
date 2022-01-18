#include<iostream>
#include<string.h>
#include<fstream>
#include<ctime>

using namespace std;


class Klient
{
	string Imie;
	string Nazwisko;
	unsigned int Wiek;
	unsigned int NrPesel;
	unsigned int NumerTelefonu;
	bool rabat;

public:
	Klient(string Imie, string Naziwsko, unsigned int Wiek, unsigned int NrPesel, unsigned int NumerTelefonu, bool rabat)
	{
		this-> Imie = Imie;
		this->Nazwisko = Nazwisko;
		this->Wiek = Wiek;
		this->NrPesel = NrPesel;
		this->NumerTelefonu = NumerTelefonu;
		this->rabat = rabat;
	}

	void wypozyczenie()
	{

	}
};

class Samochod
{
	string NumerRejestracyjny;
	unsigned int Rocznik;

public:
	Samochod(string NumerRejestracyjny, unsigned int Rocznik)
	{
		this->NumerRejestracyjny = NumerRejestracyjny;
		this->Rocznik = Rocznik;
	}
};

class Wypozyczenie
{
	float DataPoczatku;
	float DataKonca;
	int MaxWypozyczenie = 30; //30 dni - maksymalne wypożyczenie na taki okres czasu 
	bool Przekroczenie;

public:
	Wypozyczenie(float DataPoczatku, float DataKonca, int MaxWypozyczenie, bool Przekroczenie)
	{
		this->DataPoczatku = DataPoczatku;
		this->DataKonca = DataKonca;
		this->MaxWypozyczenie = MaxWypozyczenie;
		this->Przekroczenie = Przekroczenie;
	}
};

class ModelSamochodu
{
	string Marka;
	string Model;
	float CenaZaDzien;
	bool Dostepnosc;

public:
	ModelSamochodu(string Marka, string Model, float CenaZaDzien, bool Dostepnosc)
	{
		this->Marka = Marka;
		this->Model = Model;
		this->CenaZaDzien = CenaZaDzien;
		this->Dostepnosc = Dostepnosc;
	}
};

class Oplata
{
	int Wartosc;
	string TypPlatnosci;

public:
	Oplata(int Wartosc, string TypPlatnosci)
	{
		this->Wartosc = Wartosc;
		this->TypPlatnosci = TypPlatnosci;
	}
};

class Rejestracja
{
	bool CzyPosiada;

public:
	Rejestracja(bool CzyPosiada)
	{
		this->CzyPosiada = CzyPosiada;
	}
};



int main()
{
	

}








