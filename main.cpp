#include <iostream>
#include <windows.h>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Kontakt
{
    int id;
    string imie, nazwisko, numerTelefonu, adresEmail, adres;
};

string wczytajLinie()
{
    string linia;
    cin.sync();
    getline(cin, linia);
    return linia;
}

void dopiszKontaktDoPliku (Kontakt kontakt)
{
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik<<kontakt.id<<"|";
        plik<<kontakt.imie<<"|";
        plik<<kontakt.nazwisko<<"|";
        plik<<kontakt.numerTelefonu<<"|";
        plik<<kontakt.adresEmail<<"|";
        plik<<kontakt.adres<<"|";
        plik<<endl;
        plik.close();

        cout << endl << "Zapisano nowy kontakt" << endl;
        system("pause");
    }
    else
    {
        cout << "Nie udalo sie otworzyc pliku i zapisac do niego danych." << endl;
        system("pause");
    }
}

void dodajNowyKontakt (vector <Kontakt> &kontakty)
{
    Kontakt kontakt;

    if (kontakty.empty() == true)
    {
        kontakt.id = 1;
    }
    else
    {
        kontakt.id = kontakty.back().id + 1;
    }

    cout << "Podaj imie nowego kontaktu: ";
    kontakt.imie = wczytajLinie();

    cout << "Podaj nazwisko nowego kontaktu: ";
    kontakt.nazwisko = wczytajLinie();

    cout << "Podaj numer telefonu nowego kontaktu: ";
    kontakt.numerTelefonu = wczytajLinie();

    cout << "Podaj adres e-mail nowego kontaktu: ";
    kontakt.adresEmail = wczytajLinie();

    cout << "Podaj pelny adres nowego kontaktu (i calosc zaakceptuj klawiszem Enter): ";
    kontakt.adres = wczytajLinie();

    kontakty.push_back(kontakt);

    dopiszKontaktDoPliku(kontakt);
}

void wczytajKontaktyZPliku (vector <Kontakt> &kontakty)
{
    Kontakt kontakt;
    string linia= {};

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::app);
    plik.close();

    plik.open("KsiazkaAdresowa.txt", ios::in);

    if (!plik.good())
    {
        cout << "Brak pliku ksiazka adresowa! Zostanie on utworzony automatycznie przy dodaniu pierwszego kontaktu."<<endl;
        system("pause");
    }
    else
    {
        while(getline(plik, linia))
        {
            stringstream ss(linia);
            string pojedynczaDana;
            vector <string> pomocniczy;

            while (getline(ss, pojedynczaDana, '|'))
            {
                pomocniczy.push_back(pojedynczaDana);
            }

            for (unsigned int i = 0; i<pomocniczy.size(); i++)
            {
                switch (i)
                {
                case 0:
                    kontakt.id = atoi(pomocniczy[i].c_str());
                    break;
                case 1:
                    kontakt.imie = pomocniczy[i];
                    break;
                case 2:
                    kontakt.nazwisko = pomocniczy[i];
                    break;
                case 3:
                    kontakt.numerTelefonu = pomocniczy[i];
                    break;
                case 4:
                    kontakt.adresEmail = pomocniczy[i];
                    break;
                case 5:
                    kontakt.adres = pomocniczy[i];
                    break;
                }
            }
            kontakty.push_back(kontakt);
        }
        plik.close();
    }
}

void wyswietlWszystkieKontatky (vector <Kontakt> &kontakty)
{
    if (kontakty.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce adresowej! Dodaj kontakt przed wyswietleniem" << endl;
    }
    else
    {
        for (unsigned int i=0; i< kontakty.size(); i++)
        {
            cout << "Dane kontaktu numer: " << kontakty[i].id << endl;
            cout << "Imie: " << kontakty[i].imie << endl;
            cout << "Nazwisko: " << kontakty[i].nazwisko << endl;
            cout << "Numer telefonu: " << kontakty[i].numerTelefonu << endl;
            cout << "Adres e-mail: " << kontakty[i].adresEmail << endl;
            cout << "Adres: " << kontakty[i].adres << endl;
            cout << endl;
        }
        system("pause");
    }
}

void wyszukajPoImieniu (vector <Kontakt> &kontakty)
{
    bool sprawdzCzyWyszukanoKontakt = false;
    string imieDoWyswietlenia;
    vector <Kontakt>::iterator itr;

    if (kontakty.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce adresowej! Dodaj kontakt przed uzyciem tej funkcji" << endl;
    }
    else
    {
        cout << "Wpisz imie, ktorego szukasz: ";
        imieDoWyswietlenia = wczytajLinie();

        for (itr = kontakty.begin(); itr<=kontakty.end(); itr++)
        {
            if (itr -> imie == imieDoWyswietlenia)
            {
                cout << "Dane kontaktu numer: " << itr -> id << endl;
                cout << "Imie: " << itr -> imie << endl;
                cout << "Nazwisko: " << itr -> nazwisko << endl;
                cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
                cout << "Adres e-mail: " << itr -> adresEmail << endl;
                cout << "Adres: " << itr -> adres << endl;
                cout << endl;
                sprawdzCzyWyszukanoKontakt = true;
            }
        }

        if (sprawdzCzyWyszukanoKontakt == false)
        {
            cout << "Nie znaleziono kontaktow o takim imieniu w ksiazce adresowej." << endl;
            cout << "Sprobuj ponownie, pamietajac, ze wielkosc liter ma znaczenie." << endl;
        }
        system("pause");
    }
}

void wyszukajPoNazwisku (vector <Kontakt> &kontakty)
{
    bool sprawdzCzyWyszukanoKontakt = false;
    string nazwiskoDoWyswietlenia;
    vector <Kontakt>::iterator itr;

    if (kontakty.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce adresowej! Dodaj kontakt przed uzyciem tej funkcji" << endl;
    }
    else
    {
        cout << "Wpisz nazwisko, ktorego szukasz: ";
        nazwiskoDoWyswietlenia = wczytajLinie();

        for (itr = kontakty.begin(); itr<=kontakty.end(); itr++)
        {
            if (itr -> nazwisko == nazwiskoDoWyswietlenia)
            {
                cout << "Dane kontaktu numer: " << itr -> id << endl;
                cout << "Imie: " << itr -> imie << endl;
                cout << "Nazwisko: " << itr -> nazwisko << endl;
                cout << "Numer telefonu: " << itr -> numerTelefonu << endl;
                cout << "Adres e-mail: " << itr -> adresEmail << endl;
                cout << "Adres: " << itr -> adres << endl;
                cout << endl;
                sprawdzCzyWyszukanoKontakt = true;
            }
        }

        if (sprawdzCzyWyszukanoKontakt == false)
        {
            cout << "Nie znaleziono kontaktow o takim nazwisku w ksiazce adresowej." << endl;
            cout << "Sprobuj ponownie, pamietajac, ze wielkosc liter ma znaczenie." << endl;
        }
    }
    system("pause");
}

void zapisWektoraDoPliku (vector <Kontakt> &kontakty)
{
    vector <Kontakt>::iterator itr;
    itr = kontakty.begin();
    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out);

    while (itr != kontakty.end())
    {
        plik<<itr -> id<<"|";
        plik<<itr -> imie<<"|";
        plik<<itr -> nazwisko<<"|";
        plik<<itr -> numerTelefonu<<"|";
        plik<<itr -> adresEmail<<"|";
        plik<<itr -> adres<<"|";
        plik<<endl;
        itr++;
    }
    plik.close();
}

void usunKontakt (vector <Kontakt> &kontakty)
{
    bool sprawdzCzyWyszukanoKontakt = false;
    char potwierdzenie;
    int idKontaktuDoUsuniecia;
    vector <Kontakt>::iterator itr;

    if (kontakty.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce adresowej! Dodaj kontakt przed uzyciem tej funkcji" << endl;
    }
    else
    {
        cout << "Podaj id kontaktu, ktory chcesz usunac: ";
        cin >> idKontaktuDoUsuniecia;

        for (itr = kontakty.begin(); itr<=kontakty.end(); itr++)
        {
            if (itr -> id == idKontaktuDoUsuniecia)
            {
                sprawdzCzyWyszukanoKontakt = true;

                cout << "Potwierdz klawiszem 't' chec usuniecia wyswietlonego wyzej kontaktu" << endl;
                cin >> potwierdzenie;

                if (potwierdzenie == 't' || potwierdzenie == 'T')
                {
                    kontakty.erase(itr);
                    cout<< "Usunieto kontakt" <<endl;
                }
                else
                {
                    cout << "Kontakt nie zostal usuniety. Nie potwierdzono zadania" << endl;
                }
            }
        }

        if (sprawdzCzyWyszukanoKontakt == false)
        {
            cout << "Kontakt o podanym ID nie istnieje. Wprowadz prawidlowe ID." << endl;
        }
    }
    zapisWektoraDoPliku(kontakty);
    system("pause");
}

void edytujKontakt (vector <Kontakt> &kontakty)
{
    bool sprawdzCzyWyszukanoKontakt = false;
    int idKontaktuDoEdycji;
    vector <Kontakt>::iterator itr;

    if (kontakty.size() == 0)
    {
        cout << "Brak kontaktow w ksiazce adresowej! Dodaj kontakt przed uzyciem tej funkcji" << endl;
    }
    else
    {
        cout << "Podaj id kontaktu, ktory chcesz edytowac ";
        cin >> idKontaktuDoEdycji;

        for (itr = kontakty.begin(); itr<=kontakty.end(); itr++)
        {
            if (itr -> id == idKontaktuDoEdycji)
            {
                sprawdzCzyWyszukanoKontakt = true;
                char wybor;

                system("cls");
                cout << "1. Edytuj imie" << endl;
                cout << "2. Edytuj nazwisko" << endl;
                cout << "3. Edytuj numer telefonu" << endl;
                cout << "4. Edytuj adres e-mail" << endl;
                cout << "5. Edytuj adres" << endl;
                cout << "6. Powrot do menu glownego" << endl;
                cout << "Twoj wybor: ";

                cin >> wybor;

                switch (wybor)
                {
                case '1':
                    cout << "Wprowadz nowe imie: " << endl;
                    itr -> imie = wczytajLinie();
                    cout<<"Imie zostalo zmienione" << endl;
                    break;
                case '2':
                    cout << "Wprowadz nowe nazwisko: " << endl;
                    itr -> nazwisko = wczytajLinie();
                    cout<<"Nazwisko zostalo zmienione" << endl;
                    break;
                case '3':
                    cout << "Wprowadz nowy numer telefonu: " << endl;
                    itr -> numerTelefonu = wczytajLinie();
                    cout<<"Numer telefonu zostal zmieniony" << endl;
                    break;
                case '4':
                    cout << "Wprowadz nowy adres e-mail: " << endl;
                    itr -> adresEmail = wczytajLinie();
                    cout << "Adres e-mail zostal zmieniony" << endl;
                    break;
                case '5':
                    cout << "Wprowadz nowy adres: " << endl;
                    itr -> adres = wczytajLinie();
                    cout << "Adres zostal zmieniony" << endl;
                    break;
                case '6':
                    system("cls");
                    break;
                }
            }
        }
    }

    if (sprawdzCzyWyszukanoKontakt == false)
    {
        cout << "Kontakt o podanym ID nie istnieje. Wprowadz prawidlowe ID." << endl;
    }
    zapisWektoraDoPliku(kontakty);
    system("pause");
}

int main()
{
    vector <Kontakt> kontakty;
    char wybor;

    wczytajKontaktyZPliku(kontakty);

    while(true)
    {
        system("cls");
        cout << "KSIAZKA ADRESOWA" << endl;
        cout << "1. Dodaj nowy kontakt" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkie zapisane kontakty" << endl;
        cout << "5. Usun kontakt" << endl;
        cout << "6. Edytuj kontakt" << endl;
        cout << "9. Zakonczenie dzialania programu" << endl;

        cout << "Twoj wybor: ";
        cin>>wybor;

        switch (wybor)
        {
        case '1':
            dodajNowyKontakt(kontakty);
            break;
        case '2':
            wyszukajPoImieniu (kontakty);
            break;
        case '3':
            wyszukajPoNazwisku (kontakty);
            break;
        case '4':
            wyswietlWszystkieKontatky (kontakty);
            break;
        case '5':
            usunKontakt(kontakty);
            break;
        case '6':
            edytujKontakt(kontakty);
            break;
        case '9':
            exit(0);
            break;
        }
    }
    return 0;
}
