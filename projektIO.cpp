//
//Kod źródłowy projektu Wypożyczalnia Samochodów
//Przygotowane przez - Damian Błażowski, Bartłomiej Burda, Dawid Chmielowiec
//
#include <iostream>
#include <string.h>
#include <ctime>
#include <unistd.h>

using namespace std;

string loginKier = "DBBBDC2115"; //login i hasło dla kierownika, właściciela
string hasloKier = "DBD123";
float cenaZaWszystko = 0.0;
int dodane = 0;
int wybrane = 0;
int nrKlienta = 0;

void fun();
//Klasy wykorzystane w naszym projekcie:
class Klient
{
    string imie;
    string nazwisko;
    int nrPesel;
    int numerTelefonu;
    string login;
    string haslo;
    bool rabat;

public:
    Klient(string imie, string nazwisko, int nrPesel, int numerTelefonu, string login, string haslo, bool rabat)
    {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->nrPesel = nrPesel;
        this->numerTelefonu = numerTelefonu;
        this->login = login;
        this->haslo = haslo;
        this->rabat = rabat;
    }

    Klient()
    {
    }

    ~Klient()
    {
    }

    void zmianaDanych(string nImie, string nNaziwsko, int nNrPesel, int nNumerTelefonu, string nLogin, string nHaslo)
    {
        imie = nImie;
        nazwisko = nNaziwsko;
        nrPesel = nNrPesel;
        numerTelefonu = nNumerTelefonu;
        login = nLogin;
        haslo = nHaslo;
    }

    string getHaslo() const
    {
        return haslo;
    }

    string getLogin() const
    {
        return login;
    }
};

class Samochod
{
    string numerRejestracyjny;
    unsigned int rocznik;

public:
    Samochod(string numerRejestracyjny, unsigned int rocznik)
    {
        this->numerRejestracyjny = numerRejestracyjny;
        this->rocznik = rocznik;
    }
};

class Wypozyczenie
{
    float dataPoczatku;
    float dataKonca;
    int maxWypozyczenie = 30; //30 dni - maksymalne wypożyczenie na taki okres czasu
    bool przekroczenie;

public:
    Wypozyczenie(float dataPoczatku, float dataKonca, int maxWypozyczenie, bool przekroczenie)
    {
        this->dataPoczatku = dataPoczatku;
        this->dataKonca = dataKonca;
        this->maxWypozyczenie = maxWypozyczenie;
        this->przekroczenie = przekroczenie;
    }
};

class modelSamochodu
{
    string marka;
    string model;
    int rocznik;
    int iloscDni;
    float cenaZaDzien = 0.0;
    bool dostepnosc = true;

public:
    modelSamochodu(string marka, string model, int rocznik, float cenaZaDzien, bool dostepnosc)
    {
        this->marka = marka;
        this->model = model;
        this->rocznik = rocznik;
        this->cenaZaDzien = cenaZaDzien;
        this->dostepnosc = dostepnosc;
    }

    modelSamochodu()
    {
    }

    ~modelSamochodu()
    {
    }

    void Wypisz()
    {
        cout << " Marka: " << marka << " Model: " << model << " Rocznik: " << rocznik << " CenaZaDzien: " << cenaZaDzien << " Dostepnosc: " << dostepnosc << endl;
    }

    void Zamiana(string nMarka, string nModel, int nRocznik, float nCenazadzien)
    {
        marka = nMarka;
        model = nModel;
        rocznik = nRocznik;
        cenaZaDzien = nCenazadzien;
    }

    float getCena() const
    {
        return cenaZaDzien;
    }

    void setIloscDni(int nIloscdni)
    {
        iloscDni = nIloscdni;
    }

    int getIloscDni() const
    {
        return iloscDni;
    }
};

class Oplata
{
    int wartosc;
    string typPlatnosci;

public:
    Oplata(int wartosc, string typPlatnosci)
    {
        this->wartosc = wartosc;
        this->typPlatnosci = typPlatnosci;
    }
};

class Rejestracja
{
    bool czyPosiada;

public:
    Rejestracja(bool czyPosiada)
    {
        this->czyPosiada = czyPosiada;
    }
};

int getInput() //funkcja wykorzystywana wczytywanie z klawiatury w switch casach
{
    int wybor;
    cin >> wybor;
    return wybor;
}

void menuGlowne()
{
    cout << "----------------------------" << endl;
    cout << "| Wypozyczalnia samochodow |" << endl;
    cout << "----------------------------" << endl;
    cout << "1 - Rejestracja\n";
    cout << "2 - Logowanie\n";
    cout << "3 - Wyjdz\n";
    cout << "Wybor: ";
}

void menuLogowanie()
{
    cout << "--------------------" << endl;
    cout << "| Zaloguj sie jako |" << endl;
    cout << "--------------------" << endl;
    cout << "1 - Klient\n";
    cout << "2 - Kierownik\n";
    cout << "3 - Wyjdz\n";
    cout << "Wybor: ";
}

void menuMenadzera()
{
    cout << "------------------" << endl;
    cout << "| Menu Menadzera |" << endl;
    cout << "------------------" << endl;
    cout << "1 - Dopisanie nowego samochodu" << endl;
    cout << "2 - Usuniecie samochodu" << endl;
    cout << "3 - Wymiana samochodu" << endl;
    cout << "4 - Wyjdz" << endl;
    cout << "Wybor: ";
}

void menuKlienta()
{
    cout << "----------------" << endl;
    cout << "| Menu Klienta |" << endl;
    cout << "----------------" << endl;
    cout << "1 - Wypozyczenie samochodu" << endl;
    cout << "2 - Zwrot samochodu" << endl;
    cout << "3 - Stan wypozyczenia" << endl;
    cout << "4 - Usuniecie konta" << endl;
    cout << "5 - Wyjdz" << endl;
    cout << "Wybor: ";
}

Klient klienci[] = {Klient(), Klient(), Klient(), Klient(), Klient()};

modelSamochodu tablicaSamochodow[] = {
    modelSamochodu("Ford-Mustang", "GT", 2021, 2000.0, true), //tablica dostępnych samochodów
    modelSamochodu("Mercedes", "C", 2018, 1500.0, true),
    modelSamochodu("Mercedes", "E", 2018, 1000.0, true),
    modelSamochodu("Mazda", "MX-5", 2019, 1670.0, true),
    modelSamochodu("BMW", "8", 2020, 2450.0, true),
    modelSamochodu("BMW", "2", 2020, 1930.0, true),
    modelSamochodu("Mercedes", "S", 2019, 2100.0, true),
    modelSamochodu("Porsche", "911", 2020, 2750.0, true),
    modelSamochodu("BMW", "4", 2019, 1870.0, true),
    modelSamochodu("Porsche", "718", 2020, 1600.0, true),
    modelSamochodu(),
    modelSamochodu(),
    modelSamochodu()};

void wypisanieAut() //funkcja wpisująca samochody do tablicy modeli samochodów
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

void wymianaSamochodu() // funkcja, która umożliwia kierownikowi wymianę samochodów
{
    int wybor = 0;
    string zamiana1, zamiana2;
    int zamiana3;
    float zamiana4;
    do
    {

        system("cls");
        wypisanieAut();
        cout << "Ktore auto chcesz wymienic?" << endl;
        wybor = getInput();
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
        cout << "Podaj cene za dzien: " << endl;
        cin >> zamiana4;
        tablicaSamochodow[wybor - 1].Zamiana(zamiana1, zamiana2, zamiana3, zamiana4);
        cout << "Wymieniono samochod!" << endl;
        sleep(1);
    } while (wybor != 0);
    system("pause");
}

void dopisanieSamochodu()
{
    string zamiana1, zamiana2; //funkcja, która umożliwia kierownikowi dopisanie/dodanie nowego samochodu do listy
    int zamiana3;
    float zamiana4;
    do
    {
        wypisanieAut();
        cout << "Dodaj samochod:" << endl;
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
        cout << "Podaj cene za dzien: " << endl;
        cin >> zamiana4;
        tablicaSamochodow[10 + dodane].Zamiana(zamiana1, zamiana2, zamiana3, zamiana4);
        dodane++;
        cout << "Dodano samochod!" << endl;
        sleep(1);
    } while (zamiana1 != "0");
    system("pause");
}

void usunAuto(modelSamochodu a[], int ktory) //funkcja, która usuwa usunięty elemnt z tablicy samochodów
{
    for (int i = ktory - 1; i < 9 + dodane; i++)
        a[i] = a[i + 1];
    a[9 + dodane].Zamiana("0", "0", 0, 0.0);
    system("PAUSE");
}

void usunAutoWybrany(modelSamochodu a[], int ktory)
{
    for (int i = ktory - 1; i < wybrane; i++)
        a[i] = a[i + 1];
    a[wybrane].Zamiana("0", "0", 0, 0.0);
    system("PAUSE");
}

void usuniecieSamochodu() //funkcja, która umożliwia kierownikowi usunięcie samochodu z listy
{
    int wybor = 0;
    string zamiana1, zamiana2;
    int usun;
    do
    {
        wypisanieAut();
        cout << "Usun samochod:" << endl;
        cin >> usun;
        if (usun == 0)
        {
            break;
        }
        usunAuto(tablicaSamochodow, usun);
        dodane--;
        cout << "Usunieto samochod!" << endl;
        sleep(1);
    } while (usun != 0);
    system("pause");
}

modelSamochodu wybraneSamochody[10] = {modelSamochodu()};

void wyborSamochodu() //funkcja, która umożliwia klientowi wybranie samochodu do wypożyczenia oraz
{                     //możliwość dni na ile chce je wypożyczyć
    int wybor = 0;
    int usun;
    int wybierz;
    int iloscDni;
    do
    {
        system("cls");
        wypisanieAut();
        cout << "Ktory samochod chcesz wypozyczyc?" << endl;
        cin >> wybierz;
        if (wybierz == 0)
        {
            break;
        }
        cout << "Wybrales: ";
        wybraneSamochody[wybrane] = tablicaSamochodow[wybierz - 1];
        tablicaSamochodow[wybierz - 1].Wypisz();
        cout << "Na ile dni chcesz wypozyczyc?" << endl;
        cin >> iloscDni;
        wybraneSamochody[wybrane].setIloscDni(iloscDni);
        cenaZaWszystko += wybraneSamochody[wybrane].getCena() * wybraneSamochody[wybrane].getIloscDni();
        wybrane++;
        cout << "Gotowe!" << endl;
        sleep(1);
    } while (wybierz != 0);
    system("pause");
}

void zwrotSamochodu() //funkcja, która umożliwia klientowi zwrot samochodu
{
    int usun;
    do
    {
        system("cls");
        cout << "Wypozyczone samochody:      0 - wyjdz" << endl;
        for (int i = 0; i < wybrane; i++)
        {
            wybraneSamochody[i].Wypisz();
        }
        cout << "Ktory samochod chcesz zwrocic: " << endl;
        cin >> usun;
        if (usun == 0)
        {
            break;
        }
        cenaZaWszystko -= wybraneSamochody[usun - 1].getCena() * wybraneSamochody[usun - 1].getIloscDni();
        usunAutoWybrany(wybraneSamochody, usun);
        wybrane--;
        cout << "Gotowe!" << endl;
    } while (usun != 0);
    system("pause");
}

void stanWypozyczenia() //funkcja, która umożliwia klientowi sprawdzenie stanu aktualnego wypożyczenia samochodu
{
    int wybor = 0;
    do
    {
        system("cls");
        cout << "Wypozyczone samochody:      0 - wyjdz" << endl;
        for (int i = 0; i < wybrane; i++)
        {
            wybraneSamochody[i].Wypisz();
            cout << " Ilosc dni: " << wybraneSamochody[i].getIloscDni() << ", czyli ogolem: " << wybraneSamochody[i].getCena() * wybraneSamochody[i].getIloscDni() << " zl" << endl;
        }
        cout << "Cena za wszystko: " << cenaZaWszystko << " zl" << endl;
        wybor = getInput();
        if (wybor == 0)
        {
            break;
        }

    } while (wybor != 0);
    system("pause");
}

void dokanajOplaty()
{
    /*
    string wpisywanieNrPesel;
    int wpisywanieNrK;
    cout << "Podaj numer PESEL" << endl;
    cin >> wpisywanieNrPesel;
    cout << "Podaj numer klienta" << endl;
    cin >> wpisywanieNrK;
    Oplata();
    */
}

void usuwanieKonta() //funkcja, która umożliwia klientowi usunięcie wcześniej stworzonego konta
{
    string wLogin, wHaslo;
    int nr;
    cout << "Podaj login" << endl;
    cin >> wLogin;
    cout << "Podaj haslo" << endl;
    cin >> wHaslo;
    cout << "Podaj numer klienta" << endl;
    cin >> nr;
    if (wLogin == klienci[nr].getLogin() && wHaslo == klienci[nr].getHaslo())
    {
        sleep(1);
        cout << "Usunieto konto" << endl;
        klienci[nr].zmianaDanych("", "", 0, 0, "", "");
        fun();
    }
    else
    {
        cout << "Bledne dane" << endl;
        usuwanieKonta();
    }
}

void logowanieKlientWybor() //funkcja, która umożliwia klientowi wybranie opcji z menu
{
    int wybor = 0;

    do
    {
        system("cls");
        menuKlienta();
        wybor = getInput();
        switch (wybor)
        {
        case 1:
            wyborSamochodu();
            break;
        case 2:
            zwrotSamochodu();
            break;
        case 3:
            stanWypozyczenia();
            break;
        case 4:
            usuwanieKonta();
            break;
        case 5:
            break;
        default:
            break;
        }
    } while (wybor != 6);
    system("PAUSE");
}

void Rejestracja() //funkcja, która umożliwia klientowi rejestrację, czyli założenie konta
{
    string wpisywanie1, wpisywanie2, wpisywanie5, wpisywanie6;
    int wpisywanie3, wpisywanie4;
    cout << "Tworzenie konta" << endl;
    cout << "Imie" << endl;
    cin >> wpisywanie1;
    cout << "Nazwisko" << endl;
    cin >> wpisywanie2;
    cout << "NR Pesel" << endl;
    cin >> wpisywanie3;
    cout << "NR Telefonu" << endl;
    cin >> wpisywanie4;
    cout << "Podaj login" << endl;
    cin >> wpisywanie5;
    cout << "Podaj haslo" << endl;
    cin >> wpisywanie6;
    cout << "Twoj numer klienta to: " << nrKlienta << endl;
    klienci[nrKlienta].zmianaDanych(wpisywanie1, wpisywanie2, wpisywanie3, wpisywanie4, wpisywanie5, wpisywanie6);
    sleep(1);
    nrKlienta++;
}

void logowanieMenadzerWybor() //funkcja, która umożliwia menadżerowi wybieranie opcji z menu
{
    int wybor = 0;

    do
    {
        system("cls");
        menuMenadzera();
        wybor = getInput();
        switch (wybor)
        {
        case 1:
            dopisanieSamochodu();
            break;
        case 2:
            usuniecieSamochodu();
            break;
        case 3:
            wymianaSamochodu();
            break;
        case 4:
            break;

        default:
            break;
        }
    } while (wybor != 4);
    system("PAUSE");
}

void Logowanie() //funckja, która umożliwia zalogowanie się na swoje konto
{
    string wpisywanieL, wpisywanieH;
    int wpisywanieNrK;
    cout << "Podaj login" << endl;
    cin >> wpisywanieL;
    cout << "Podaj haslo" << endl;
    cin >> wpisywanieH;
    cout << "Podaj numer klienta" << endl;
    cin >> wpisywanieNrK;
    if (wpisywanieH != klienci[wpisywanieNrK].getHaslo() || wpisywanieL != klienci[wpisywanieNrK].getLogin())
    {
        cout << "Bledny login lub haslo" << endl;
        Logowanie();
    }
    else
    {
        cout << "Zalogowano Klienta" << endl;
        logowanieKlientWybor();
    }
}

void logowanieKier() //funkcja, która umożliwia kierownikowi zalogowanie się na swoje konto
{
    string wpisywanieL, wpisywanieH;
    int wpisywanieNrK;
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
    else
    {
        cout << "Bledny login lub haslo" << endl;
        logowanieKier();
    }
}

void logowanieWybor() //funkcja, która umożliwia wybór opcji z opcji z menu głownego
{
    int wybor = 0;

    do
    {
        system("cls");
        menuLogowanie();
        wybor = getInput();
        switch (wybor)
        {
        case 1:
            Logowanie();
            break;
        case 2:
            logowanieKier();
            break;
        case 3:
            break;

        default:
            break;
        }
    } while (wybor != 3);
    system("PAUSE");
}

void fun()
{
    int wybor = 0;

    do
    {
        system("cls");
        menuGlowne();
        wybor = getInput();
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
}

int main()
{
    fun();
    return EXIT_SUCCESS;
}
