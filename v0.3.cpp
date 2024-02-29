#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

double bendras_laikas = 0;
int vykdymu_skaicius = 0;

struct Studentas {
    string v;
    string p;
    int n;
    double egz_rez;
    vector<double> nd_rez;
    double nd_sum = 0;
    double nd_vid;
    double rez;
    double mediana;
};

void RankinisIvedimas(vector<Studentas>& Duomenys);
void GeneruotiPazymius(vector<Studentas>& Duomenys);
void GeneruotiPazymiusVardus(int m);
double Skaitymas(const string& pavadinimas, vector<Studentas>& Duomenys);
void RusiuotiSpausdinti(vector<Studentas>& Duomenys, double laikas, const string& pavadinimas);

int main() {

    vector<Studentas> Duomenys;  // Vektorius skirtas saugoti studentu duomenims
    srand(time(NULL));
    int veiksmas;
    string pavadinimas;

    while (true) {
        cout << "1 - Vesti duomenis rankiniu budu" << endl;
        cout << "2 - Generuoti pazymius" << endl;
        cout << "3 - Generuoti ir pazymius ir studentu vardus" << endl;
        cout << "4 - Nuskaityti duomenis is failo" << endl;
        cout << "5 - Baigti darba" << endl;
        cout << endl;
        cout << "Pasirinkite veiksma ivesdami skaiciu: ";
        cin >> veiksmas;
        cout << endl;

        switch (veiksmas) {
        case 1:

            RankinisIvedimas(Duomenys);
            break;

        case 2:
            GeneruotiPazymius(Duomenys);
            break;

        case 3:
            int m3;
            while (true) {
                try {
                    cout << "Iveskite studentu skaiciu: "; cin >> m3;
                    cout << endl;
                    if (cin.fail() || m3 <= 0) {
                        throw runtime_error("Neteisinga ivestis, prasome ivesti skaiciu");
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    GeneruotiPazymiusVardus(m3);
                    break;
                }
                catch (const exception& e) {
                    cout << e.what() << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
            break;

        case 4: {
            try {
                int pasirinkimas;
                cout << "Is kurio failo norit nuskaityti duomenis?" << endl;
                cout << endl;
                cout << "1 - 'kursiokai.txt'" << endl;
                cout << "2 - 'studentai10000.txt'" << endl;
                cout << "3 - 'studentai100000.txt'" << endl;
                cout << "4 - 'studentai1000000.txt'" << endl;
                cout << endl;
                cout << "Iveskite pasirinkima: "; cin >> pasirinkimas;
                cout << endl;
                while (cin.fail() || pasirinkimas <= 0 || pasirinkimas > 4) {
                    cout << "Neteisinga ivestis, prasome ivesti skaiciu nuo 1 iki 4" << endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cin >> pasirinkimas;
                }
                switch (pasirinkimas) {
                case 1:
                    pavadinimas = "kursiokai.txt";
                    break;
                case 2:
                    pavadinimas = "studentai10000.txt";
                    break;
                case 3:
                    pavadinimas = "studentai100000.txt";
                    break;
                case 4:
                    pavadinimas = "studentai1000000.txt";
                    break;
                }

                double laikas = Skaitymas(pavadinimas, Duomenys);
                RusiuotiSpausdinti(Duomenys, laikas, pavadinimas);

                bendras_laikas += laikas;
                vykdymu_skaicius++;

                cout << "Vidutinis vykdymo laikas: " << bendras_laikas / vykdymu_skaicius << " sekundes" << endl;
                cout << endl;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
            }
        } break;

        case 5:
            cout << "Programa baigia darba." << endl;
            return 0;

        default:
            cout << "Neteisinga ivestis, prasome ivesti viena is pateiktu pasirinkimo variantu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
    }
}

void RankinisIvedimas(vector<Studentas>& Duomenys) {
    Studentas studentas;
    double pazymys;

    cout << "Jei norite baigti iveskite zodi BAIGTI kaip studento varda arba pavarde" << endl;
    cout << endl;

    while (true) {
        try {
            cout << "Iveskite studento varda: ";
            cin >> studentas.v;
            cout << endl;
            if (studentas.v == "BAIGTI" || studentas.v == "Baigti" || studentas.v == "baigti") break;
            if (cin.fail() || any_of(studentas.v.begin(), studentas.v.end(), [](char c) { return !isalpha(c); })) {
                throw runtime_error("Neteisinga ivestis, prasome ivesti varda sudaryta is raidziu");
            }
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        while (true) {
            try {
                cout << "Iveskite studento pavarde: ";
                cin >> studentas.p;
                cout << endl;
                if (studentas.p == "BAIGTI" || studentas.p == "Baigti" || studentas.p == "baigti") break;
                if (cin.fail() || any_of(studentas.p.begin(), studentas.p.end(), [](char c) { return !isalpha(c); })) {
                    throw runtime_error("Neteisinga ivestis, prasome ivesti pavarde sudaryta is raidziu");
                }
                break;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }

        while (true) {
            try {
                cout << "Iveskite studento namu darbu pazymi (jei norite baigti iveskite -1): " << endl;
                cin >> pazymys;
                cout << endl;
                if (cin.fail() || pazymys < -1 || pazymys > 10) {
                    throw runtime_error("Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje");
                }
                if (pazymys == -1) break;
                studentas.nd_rez.push_back(pazymys);
            }
            catch (const exception& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }

        // Egzamino rezultato ivestis
        while (true) {
            try {
                cout << "Koks buvo studento egzamino rezultatas?" << endl;
                cin >> studentas.egz_rez;
                cout << endl;
                if (cin.fail() || studentas.egz_rez < 0 || studentas.egz_rez > 10) {
                    throw runtime_error("Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje");
                }
                break;
            }
            catch (const exception& e) {
                cout << e.what() << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        }

        // Namu darbu sumos skaiciavimas

        studentas.nd_sum = accumulate(studentas.nd_rez.begin(), studentas.nd_rez.end(), 0.0);

        // Namu darbu masyvo rusiavimas

        sort(studentas.nd_rez.begin(), studentas.nd_rez.end());

        // Medianos skaiciavimas

        if (studentas.nd_rez.size() % 2 == 0) {
            studentas.mediana = (studentas.nd_rez[studentas.nd_rez.size() / 2 - 1] + studentas.nd_rez[studentas.nd_rez.size() / 2]) / 2.0;
        }
        else {
            studentas.mediana = studentas.nd_rez[studentas.nd_rez.size() / 2];
        }

        Duomenys.push_back(studentas);

    }

    // Rezultatu spausdinimas pasirenkant Vid. arba Med.

    string pasirinkimas;
    cout << "Kaip norite matyti savo galutini bala?"<<endl;
    cout << "1 - Vid." << endl;
    cout << "2 - Med." << endl;
    cout << endl;
    try {
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas;
        cout << endl;

        while (pasirinkimas != "1" && pasirinkimas != "2") {
            cout << "Pasirinkite arba '1' arba '2'" << endl;
            cin >> pasirinkimas;
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (pasirinkimas == "1") {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
        for (auto& studentas : Duomenys) {
            studentas.nd_vid = studentas.nd_sum / studentas.nd_rez.size();
            studentas.rez = 0.4 * studentas.nd_vid + 0.6 * studentas.egz_rez;
            cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
        }
    }
    else {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
        for (auto& studentas : Duomenys) {
            studentas.rez = 0.4 * studentas.mediana + 0.6 * studentas.egz_rez;
            cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
        }
    }
    cout << endl;
    }

void GeneruotiPazymius(vector<Studentas>& Duomenys) {
    Studentas studentas;

    cout << "Jei norite baigti iveskite zodi BAIGTI kaip studento varda arba pavarde" << endl;
    cout << endl;

    while (true) {
        try {
            cout << "Iveskite studento varda: ";
            cin >> studentas.v;
            cout << endl;
            if (studentas.v == "BAIGTI" || studentas.v == "Baigti" || studentas.v == "baigti") break;
            if (cin.fail() || any_of(studentas.v.begin(), studentas.v.end(), [](char c) { return !isalpha(c); })) {
                throw runtime_error("Neteisinga ivestis, prasome ivesti varda sudaryta is raidziu");
            }
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        try {
            cout << "Iveskite studento pavarde: ";
            cin >> studentas.p;
            cout << endl;
            if (studentas.p == "BAIGTI" || studentas.p == "Baigti" || studentas.p == "baigti") break;
            if (cin.fail() || any_of(studentas.p.begin(), studentas.p.end(), [](char c) { return !isalpha(c); })) {
                throw runtime_error("Neteisinga ivestis, prasome ivesti pavarde sudaryta is raidziu");
            }
        }
        catch (const exception& e) {
            cout << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    }

    // Egzamino rezultato generavimas

    studentas.egz_rez = (rand() % 10) + 1;

    // Namu darbu skaiciaus generavimas

    int n = (rand() % 10) + 1;

    studentas.nd_rez.resize(n);

    // Namu darbu rezultatu generavimas ir sumos skaiciavimas

    for (int j = 0; j < n; j++) {
        studentas.nd_rez[j] = (rand() % 10) + 1;
        studentas.nd_sum += studentas.nd_rez[j];
    }

    // Namu darbu masyvo rusiavimas

    sort(studentas.nd_rez.begin(), studentas.nd_rez.end());

    // Medianos skaiciavimas

    if (studentas.nd_rez.size() % 2 == 0) {
        studentas.mediana = (studentas.nd_rez[studentas.nd_rez.size() / 2 - 1] + studentas.nd_rez[studentas.nd_rez.size() / 2]) / 2.0;
    }
    else {
        studentas.mediana = studentas.nd_rez[studentas.nd_rez.size() / 2];
    }

    Duomenys.push_back(studentas);

    // Rezultatu spausdinimas pasirenkant Vid. arba Med.

    string pasirinkimas;
    cout << endl;
    cout << "Kaip norite matyti savo galutini bala?" << endl;
    cout << "1 - Vid." << endl;
    cout << "2 - Med." << endl;
    cout << endl;
    try {
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas;
        cout << endl;

        while (pasirinkimas != "1" && pasirinkimas != "2") {
            cout << "Pasirinkite arba '1' arba '2'" << endl;
            cin >> pasirinkimas;
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (pasirinkimas == "1") {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
        for (auto& studentas : Duomenys) {
            studentas.nd_vid = studentas.nd_sum / studentas.nd_rez.size();
            studentas.rez = 0.4 * studentas.nd_vid + 0.6 * studentas.egz_rez;
            cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
        }
        cout << endl;
    }
    else {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
        for (auto& studentas : Duomenys) {
            studentas.rez = 0.4 * studentas.mediana + 0.6 * studentas.egz_rez;
            cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
        }
        cout << endl;
    }
    }

void GeneruotiPazymiusVardus(int m3) {
    vector<Studentas> Duomenys(m3);

    for (int i = 0; i < m3; i++) {
        // Masyvai saugantys visus variantus vardu ir pavardziu

        vector<string> VyriskiVardai = { "Arvydas", "Robertas", "Deivydas", "Marius", "Matas", "Jokubas", "Nojus", "Augustas", "Tomas", "Arnas" };
        vector<string> MoteriskiVardai = { "Gija", "Patricija", "Ieva", "Karolina", "Sandra", "Vita", "Aleksandra", "Liepa", "Smilte", "Guoste" };
        vector<string> VyriskosPavardes = { "Petrauskas", "Jankauskas", "Butkus", "Navickas", "Kazlauskas", "Urbanavicius", "Sadauskas", "Mazeika", "Kavaliauskas", "Adomaitis" };
        vector<string> MoteriskosPavardes = { "Kazlauskaite", "Petrauskaite", "Kavaliauskaite", "Jankauskaite", "Pociute", "Balciunaite", "Lukoseviciute", "Vasiliauskaite", "Butkute", "Leonaviciute" };

        // Vardo ir Pavardes generavimas

        if (rand() % 2 == 0) {
            Duomenys[i].v = VyriskiVardai[rand() % VyriskiVardai.size()];
            Duomenys[i].p = VyriskosPavardes[rand() % VyriskosPavardes.size()];
        }
        else {
            Duomenys[i].v = MoteriskiVardai[rand() % MoteriskiVardai.size()];
            Duomenys[i].p = MoteriskosPavardes[rand() % MoteriskosPavardes.size()];
        }

        // Namu darbu skaiciaus generavimas

        Duomenys[i].n = (rand() % 10) + 1;

        Duomenys[i].nd_rez.resize(Duomenys[i].n);

        // Namu darbu rezultatu generavimas

        for (int j = 0; j < Duomenys[i].n; j++) {
            Duomenys[i].nd_rez[j] = (rand() % 10) + 1;
            Duomenys[i].nd_sum += Duomenys[i].nd_rez[j];
        }
        Duomenys[i].egz_rez = (rand() % 10) + 1;  // Egzamino rezultato generavimas

        // Namu darbu masyvo rusiavimas

        sort(Duomenys[i].nd_rez.begin(), Duomenys[i].nd_rez.end());

        // Medianos skaiciavimas

        if (Duomenys[i].n % 2 == 0) {
            Duomenys[i].mediana = (Duomenys[i].nd_rez[Duomenys[i].n / 2 - 1] + Duomenys[i].nd_rez[Duomenys[i].n / 2]) / 2.0;
        }
        else {
            Duomenys[i].mediana = Duomenys[i].nd_rez[Duomenys[i].n / 2];
        }
    }

    // Rezultatu spausdinimas pasirenkant Vid. arba Med.

    string pasirinkimas;
    cout << "Kaip norite matyti savo galutini bala?" << endl;
    cout << "1 - Vid." << endl;
    cout << "2 - Med." << endl;
    cout << endl;
    try {
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas;
        cout << endl;

        while (pasirinkimas != "1" && pasirinkimas != "2") {
            cout << "Pasirinkite arba '1' arba '2'" << endl;
            cin >> pasirinkimas;
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (pasirinkimas == "1") {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }
    else {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }

    for (int i = 0; i < m3; i++) {
        if (pasirinkimas == "1") {
            Duomenys[i].nd_vid = Duomenys[i].nd_sum / Duomenys[i].n;
            Duomenys[i].rez = 0.4 * Duomenys[i].nd_vid + 0.6 * Duomenys[i].egz_rez;
            cout << left << setw(15) << Duomenys[i].v << setw(15) << Duomenys[i].p << fixed << setprecision(2) << setw(15) << Duomenys[i].rez << endl;
        }
        else {
            Duomenys[i].rez = 0.4 * Duomenys[i].mediana + 0.6 * Duomenys[i].egz_rez;
            cout << left << setw(15) << Duomenys[i].v << setw(15) << Duomenys[i].p << fixed << setprecision(2) << setw(15) << Duomenys[i].rez << endl;
        }
    }
    cout << endl;
    }
double Skaitymas(const string& pavadinimas, vector<Studentas>& Duomenys) {
    Studentas studentas;
    string line;

    auto pradzia = high_resolution_clock::now();

    try {
        ifstream infile("kursiokai.txt");
        if (!infile) {
            throw runtime_error("Nepavyko atidaryti failo.");
        }

        // Nuskaitoma ir ignoruojama pirmoji eilute
        getline(infile, line);

        while (getline(infile, line)) {
            studentas.nd_rez.clear();
            studentas.nd_sum = 0;
            stringstream ss(line);

            // Nuskaitomi studentu vardai ir pavardes
            ss >> studentas.v >> studentas.p;

            // Nuskaitomi pazymiai
            int grade;
            while (ss >> grade) {
                studentas.nd_rez.push_back(grade);
                studentas.nd_sum += grade;
            }
            if (studentas.nd_rez.empty()) {
                throw runtime_error("Nerasta namu darbu ivertinimu.");
            }

            studentas.nd_sum = studentas.nd_sum - studentas.nd_rez.back();

            // Nuskaitomas egzamino rezultatas (paskutinis skaicius eiluteje)
            studentas.egz_rez = studentas.nd_rez.back();

            studentas.nd_rez.pop_back();  // Pasalinamas egzamino rezultata is namu darbu rezultatu saraso

            // Pazymiu rusiavimas ir medianos skaiciavimas
            sort(studentas.nd_rez.begin(), studentas.nd_rez.end());

            if (studentas.nd_rez.size() % 2 == 0) {
                studentas.mediana = (studentas.nd_rez[studentas.nd_rez.size() / 2 - 1] + studentas.nd_rez[studentas.nd_rez.size() / 2]) / 2.0;
            }
            else {
                studentas.mediana = studentas.nd_rez[studentas.nd_rez.size() / 2];
            }

            Duomenys.push_back(studentas);
        }

        infile.close();
    }
    catch (const exception& e) {
        cerr << e.what() << endl;
        return -1;
    }

    auto pabaiga = high_resolution_clock::now();
    duration<double> trukme = pabaiga - pradzia;
    double laikas = trukme.count();

    return laikas;
}

void RusiuotiSpausdinti(vector<Studentas>& Duomenys, double laikas, const string& pavadinimas) {
    string pasirinkimas, pasirinkimas1, pasirinkimas2, pasirinkimas3;
    try {
        cout << "Kaip norite matyti savo galutini bala?" << endl;
        cout << "1 - Vid." << endl;
        cout << "2 - Med." << endl;
        cout << endl;
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas;
        while (pasirinkimas != "1" && pasirinkimas != "2") {
            cout << "Pasirinkite arba '1' arba '2'" << endl;
            cin >> pasirinkimas;
        }
        cout << endl;

        cout << "Pagal ka norite rusiuoti rezultatus?" << endl;
        cout << "1 - Varda" << endl;
        cout << "2 - Pavarde" << endl;
        cout << "3 - Bala" << endl;
        cout << endl;
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas3;
        while (pasirinkimas3 != "1" && pasirinkimas3 != "2" && pasirinkimas3 != "3") {
            cout << "Pasirinkite arba '1' arba '2' arba '3'" << endl;
            cin >> pasirinkimas3;
        }
        cout << endl;

        cout << "Kokia tvarka norite rusiuoti rezultatus?" << endl;
        cout << "1 - Didejancia" << endl;
        cout << "2 - Mazejancia" << endl;
        cout << endl;
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas1;
        while (pasirinkimas1 != "1" && pasirinkimas1 != "2") {
            cout << "Pasirinkite arba '1' arba '2'" << endl;
            cin >> pasirinkimas1;
        }
        cout << endl;

        cout << "Kaip norite matyti rezultatus?" << endl;
        cout << "1 - Ekrane" << endl;
        cout << "2 - Faile" << endl; 
        cout << endl;
        cout << "Iveskite pasirinkima: "; cin >> pasirinkimas2;
        while (pasirinkimas2 != "1" && pasirinkimas2 != "2") {
            cout << "Pasirinkite arba '1' arba '2'" << endl;
            cin >> pasirinkimas2;
        }
        cout << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Skaiciuojami galutiniai rezultatai
    for (auto& studentas : Duomenys) {
        if (pasirinkimas == "1") {
            studentas.nd_vid = studentas.nd_sum / studentas.nd_rez.size();
            studentas.rez = 0.4 * studentas.nd_vid + 0.6 * studentas.egz_rez;
        }
        else {
            studentas.rez = 0.4 * studentas.mediana + 0.6 * studentas.egz_rez;
        }
    }

    // Rusiuojama pagal pasirinkta kriteriju
    if (pasirinkimas3 == "1") {
        if (pasirinkimas1 == "1")
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.v > b.v; });
        else
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.v < b.v; });
    }
    else if (pasirinkimas3 == "2") {
        if (pasirinkimas1 == "1")
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.p > b.p; });
        else
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.p < b.p; });
    }
    else if (pasirinkimas3 == "3") {
        if (pasirinkimas1 == "1")
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.rez > b.rez; });
        else
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.rez < b.rez; });
    }

    // Pasirenkamas spausdinimas i konsole arba faila
    if (pasirinkimas2 == "1") {
        if (pasirinkimas == "1") {
            cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Vid.)" << endl;
            cout << "-----------------------------------------------" << endl;
            for (const auto& studentas : Duomenys) {
                cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
            }
            cout << endl;
        }
        else {
            cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Med.)" << endl;
            cout << "-----------------------------------------------" << endl;
            for (const auto& studentas : Duomenys) {
                cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
            }
            cout << endl;
        }
    }
    else {
        // Rezultatu irasymas i faila
        ofstream outfile("rezultatai.txt");
        if (!outfile) {
            cerr << "Nepavyko sukurti rezultatu failo.";
            return;
        }
        if (pasirinkimas == "1") {
            outfile << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Vid.)" << endl;
            outfile << "-----------------------------------------------" << endl;
            for (const auto& studentas : Duomenys) {
                outfile << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
            }
        }
        else {
            outfile << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Med.)" << endl;
            outfile << "-----------------------------------------------" << endl;
            for (const auto& studentas : Duomenys) {
                outfile << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
            }
        }
        outfile.close();
        cout << "Rezultatai irasyti i faila rezultatai.txt" << endl;
    }
}