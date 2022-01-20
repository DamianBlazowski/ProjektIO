#include<iostream>
#include<string.h>
#include<ctime>
#include<locale.h>

using namespace std;

string login, haslo, imie, nazwisko, nrPesel;
string loginKier = "abc";
string hasloKier = "qwe";
int dodane = 0;

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
    int Rocznik;
    float CenaZaDzien = 0.0;
    bool Dostepnosc = true;

public:
    ModelSamochodu(string Marka, string Model, int Rocznik, float CenaZaDzien, bool Dostepnosc)
    {
        this->Marka = Marka;
        this->Model = Model;
        this->Rocznik = Rocznik;
        this->CenaZaDzien = CenaZaDzien;
        this->Dostepnosc = Dostepnosc;
    }

    ModelSamochodu()
    {

    }

    ~ModelSamochodu()
    {

    }

    void Wypisz()
    {
        cout << " Marka: " << Marka << " Model: " << Model << " Rocznik: " << Rocznik << " CenaZaDzien: " << CenaZaDzien << " Dostepnosc: " << Dostepnosc << endl;
    }

    void Zamiana(string nMarka, string nModel, int nRocznik)
    {
        Marka = nMarka;
        Model = nModel;
        Rocznik = nRocznik;
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

int GetInput()
{
    int wybor;
    cin >> wybor;
    return wybor;
}

void MenuGlowne()
{
    cout << "----------------------------" << endl;
    cout << "| Wypożyczalnia samochodów |" << endl;
    cout << "----------------------------" << endl;
    cout << "1 - Rejestracja\n";
    cout << "2 - Logowanie\n";
    cout << "3 - Wyjdź\n";
    cout << "Wybór: ";
}

void MenuLogowanie()
{
    cout << "--------------------" << endl;
    cout << "| Zaloguj się jako |" << endl;
    cout << "--------------------" << endl;
    cout << "1 - Klient\n";
    cout << "2 - Kierownik\n";
    cout << "3 - Wyjdź\n";
    cout << "Wybór: ";
}

    void MenuMenadzera()
{
    cout << "------------------" << endl;
    cout << "| Menu Menadzera |" << endl;
    cout << "------------------" << endl;
    cout << "1 - Dopisanie nowego samochodu" << endl;
    cout << "2 - Usunięcie Samochodu" << endl;
    cout << "3 - Wymiana Samochodu" << endl;
    cout << "4 - Wyjdź" << endl;
    cout << "Wybór: ";
}

void MenuKlienta()
{
    cout << "----------------" << endl;
    cout << "| Menu Klienta |" << endl;
    cout << "----------------" << endl;
    cout << "1 - Wypożyczenie Samochodu" << endl;
    cout << "2 - Zwrot Samochodu" << endl;
    cout << "3 - Stan Wypożyczenia" << endl;
    cout << "4 - Dokonanie Opłaty" << endl;
    cout << "5 - Usunięcie konta" << endl;
    cout << "6 - Wyjdź" << endl;
    cout << "Wybór: ";
}

ModelSamochodu tablicaSamochodow[] = {
    ModelSamochodu("Ford-Mustang", "GT", 2020, 0.0, true), //dostępne samochody
    ModelSamochodu("Mercedes", "C", 2020, 0.0, true),
    ModelSamochodu("Mercedes", "E", 2020, 0.0, true),
    ModelSamochodu("Mazda", "MX-5", 2020, 0.0, true),
    ModelSamochodu("BMW", "8", 2020, 0.0, true),
    ModelSamochodu("BMW", "2", 2020, 0.0, true),
    ModelSamochodu("Mercedes", "S", 2020, 0.0, true),
    ModelSamochodu("Porsche", "911", 2020, 0.0, true),
    ModelSamochodu("BMW", "4", 2020, 0.0, true),
    ModelSamochodu("Porsche", "718", 2020, 0.0, true),
    ModelSamochodu(),
    ModelSamochodu(),
    ModelSamochodu() };

void WypisanieAut()
{

    cout << endl
        << "Dostepne samochody: " << endl;
    for (int i = 0; i < 10 + dodane; i++)
    {
        cout << "Nr. " << i + 1;
        tablicaSamochodow[i].Wypisz();
    }
    cout << "0 - wyjdz" << endl;
}

void WymianaSamochodu()
{
    int wybor = 0;
    string zamiana1, zamiana2;
    int zamiana3;
    do
    {

        system("cls");
        WypisanieAut();
        cout << "Które auto chcesz wymienić?" << endl;
        wybor = GetInput();
        if (wybor == 0)
        {
            break;
        }
        cout << "Podaj marke: " << endl;
        cin >> zamiana1;
        cout << "Podaj model: " << endl;
        cin >> zamiana2;
        cout << "Podaj rocznik: " << endl;
        cin >> zamiana3;
        tablicaSamochodow[wybor - 1].Zamiana(zamiana1, zamiana2, zamiana3);
        cout << "Wymieniono samochód!" << endl;
    } while (wybor != 0);
    system("pause");
}

void DopisanieSamochodu()
{
    string zamiana1, zamiana2;
    int zamiana3;
    do
    {
        WypisanieAut();
        cout << "Dodaj samochód:" << endl;
        cout << "Podaj marke: " << endl;
        cin >> zamiana1;
        if (zamiana1 == "0")
        {
            break;
        }
        cout << "Podaj model: " << endl;
        cin >> zamiana2;
        cout << "Podaj rocznik: " << endl;
        cin >> zamiana3;
        tablicaSamochodow[10 + dodane].Zamiana(zamiana1, zamiana2, zamiana3);
        dodane++;
        cout << "Dodano samochód!" << endl;
    } while (zamiana1 != "0");
    system("pause");
}

void UsunAuto(ModelSamochodu a[], int ktory)
{
    for (int i = ktory - 1; i < 9 + dodane; i++)
        a[i] = a[i + 1];
    a[9 + dodane].Zamiana("0", "0", 0);
    system("PAUSE");
}

void UsuniecieSamochodu()
{
    int wybor = 0;
    string zamiana1, zamiana2;
    int usun;
    do
    {
        WypisanieAut();
        cout << "Usuń samochód:" << endl;
        cin >> usun;
        if (usun == 0)
        {
            break;
        }
        UsunAuto(tablicaSamochodow, usun);
        dodane--;
        cout << "Usunięto samochód!" << endl;
    } while (usun != 0);
    system("pause");
}

void Oplata()
{
    int wybor = 0;
    string wypisz;
    do
    {
        system("cls");
        cout << "Podaj okres trwania wypożyczenia (w miesiącach): " << endl;
        wybor = GetInput();
        switch (wybor)
        {
        case 1:
            cout << "Opłata wynosi 10000zł " << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 2:
            cout << "Opłata wynosi 19000zł " << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 3:
            cout << "Opłata wynosi 27000zł " << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 4:
            cout << "Opłata wynosi 34000zł " << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 5:
            cout << "Opłata wynosi 40000zł " << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 6:
            cout << "Opłata wynosi 45000zł " << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 7:
            break;
        default:
            break;
        }
    } while (wybor != 7);
    system("PAUSE");
}

void wyborSamochodu()
{
    int wybor = 0;
    string wypisz;
    do
    {
        system("cls");
        WypisanieAut();
        wybor = GetInput();
        switch (wybor)
        {
        case 1:
            cout << "Wybrałeś:  Ford Mustang 	GT 	2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 2:
            cout << "Wybrałeś:  Mercedes	 C	2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 3:
            cout << "Wybrałeś:   Mercedes E	2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 4:
            cout << "Wybrałeś:   Mazda MX-5	2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 5:
            cout << "Wybrałeś:  BMW 8 2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 6:
            cout << "Wybrałeś:   BMW 2 2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 7:
            cout << "Wybrałeś:  Mercedes S 2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 8:
            cout << "Wybrałeś:   Porsche 911 2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 9:
            cout << "Wybrałeś:  BMW 4 2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 10:
            cout << "Wybrałeś:   Porsche 718	2020" << endl;
            cin >> wypisz;
            if (wypisz == "0")
            {
                break;
            }
            break;
        case 0:
            break;

        default:
            break;
        }
    } while (wybor != 0);
    system("pause");
}
  
void wypozyczenieSamochodu()
{
    string wpisywanie1, wpisywanie2, wpisywanie3;
    cout << "Podaj imie" << endl;
    cin >> wpisywanie1;
    cout << "Podaj nazwisko" << endl;
    cin >> wpisywanie2;
    cout << "Podaj numer PESEL" << endl;
    cin >> wpisywanie3;
    if (wpisywanie1 != imie || wpisywanie2 != nazwisko || wpisywanie3 != nrPesel)
    {
        cout << "Błędne dane logowania" << endl;
       wypozyczenieSamochodu();
    }
    else 
    {
        wyborSamochodu();
    }
}

void ZwrotSamochodu()
{

}

void StanWypozyczenia()
{
    cout << "aktualnie wypozyczone przez ";
}

void DokanajOplaty()
{
    string wpisywanieImie, wpisywanieNazwisko, wpisywanieNrPesel;
    int wybor;
    cout << "Podaj imie" << endl;
    cin >> wpisywanieImie;
    cout << "Podaj nazwisko" << endl;
    cin >> wpisywanieNazwisko;
    cout << "Podaj numer PESEL" << endl;
    cin >> wpisywanieNrPesel;
    if (wpisywanieImie != imie || wpisywanieNazwisko != nazwisko || wpisywanieNrPesel != nrPesel)
    {
        cout << "Błędne dane logowania" << endl;
        MenuLogowanie();
    }
        Oplata();
    
}

void UsuwanieKonta()
{
    string wpisywanie;
    cout << "Podaj imie" << endl;
    cin >> wpisywanie;
    cout << "Podaj nazwisko" << endl;
    cin >> wpisywanie;
    cout << "Podaj numer PESEL" << endl;
    cin >> wpisywanie;
    if (wpisywanie != imie || wpisywanie != nazwisko || wpisywanie != nrPesel)
    {
        cout << "Błędne dane logowania" << endl;
        MenuLogowanie();
    }
    else
    {
        cout << "Usunieto konto" << endl;
        MenuGlowne();
    }
}

void Rejestracja()
{
    string wpisywanie;
    cout << "Tworzenie konta" << endl;
    cout << "Imie" << endl;
    cin >> wpisywanie;
    imie = wpisywanie;
    cout << "Nazwisko" << endl;
    cin >> wpisywanie;
    nazwisko = wpisywanie;
    cout << "NR Pesel" << endl;
    cin >> wpisywanie;
    nrPesel = wpisywanie;
    cout << "Podaj login" << endl;
    cin >> wpisywanie;
    login = wpisywanie;
    cout << "Podaj hasło" << endl;
    cin >> wpisywanie;
    haslo = wpisywanie;
    MenuGlowne();
}

void logowanieKlientWybor()
{
    int wybor = 0;

    do
    {
        system("cls");
        MenuKlienta();
        wybor = GetInput();
        switch (wybor)
        {
        case 1:
            wypozyczenieSamochodu();
            break;
        case 2:
            ZwrotSamochodu();
            break;
        case 3:
            StanWypozyczenia();
            break;
        case 4:
            DokanajOplaty();

            break;
        case 5:
            UsuwanieKonta();
            break;
        case 6:
            break;

        default:
            break;
        }
    } while (wybor != 6);
    system("PAUSE");
}

void logowanieMenadzerWybor()
{
    int wybor = 0;

    do
    {
        system("cls");
        MenuMenadzera();
        wybor = GetInput();
        switch (wybor)
        {
        case 1:
            DopisanieSamochodu();
            break;
        case 2:
            UsuniecieSamochodu();
            break;
        case 3:
            WymianaSamochodu();
            break;
        case 4:
            break;

        default:
            break;
        }
    } while (wybor != 4);
    system("PAUSE");
}

void Logowanie()
{
    string wpisywanieL, wpisywanieH;
    cout << "Podaj login" << endl;
    cin >> wpisywanieL;
    cout << "Podaj haslo" << endl;
    cin >> wpisywanieH;
    if (wpisywanieH == hasloKier && wpisywanieL == loginKier)
    {
        cout << "Zalogowano Kierownika" << endl;
        logowanieMenadzerWybor();
        system("PAUSE");
    }
    else if (wpisywanieH != haslo || wpisywanieL != login)
    {
        cout << "Błędny login lub hasło" << endl;
        Logowanie();
    }
    else
    {
        cout << "Zalogowano Klienta" << endl;
        logowanieKlientWybor();
        //główny kod klienta
    }
}

void logowanieWybor()
{
    int wybor = 0;

    do
    {
        system("cls");
        MenuLogowanie();
        wybor = GetInput();
        switch (wybor)
        {
        case 1:
            Logowanie();
            break;
        case 2:
            Logowanie();
            break;
        case 3:
            break;

        default:
            break;
        }
    } while (wybor != 3);
    system("PAUSE");
}


int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "polish");

    int wybor = 0;

    do
    {
        system("cls");
        MenuGlowne();
        wybor = GetInput();
        switch (wybor)
        {
        case 1:
            Rejestracja();
            break;
        case 2:
            logowanieWybor();
            break;
        case 3:
            break;

        default:
            break;
        }
    } while (wybor != 3);
    system("pause");
    return EXIT_SUCCESS;
    
}
    










