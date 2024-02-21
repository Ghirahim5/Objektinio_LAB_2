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

using namespace std;

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

void RankinisIvedimas(int m);
void GeneruotiPazymius(int m2);
void GeneruotiPazymiusVardus(int m3);
void Skaitymas(vector<Studentas>& Duomenys);
void RusiuotiSpausdinti(vector<Studentas>& Duomenys, string pasirinkimas, string pasirinkimas1, string pasirinkimas2, string pasirinkimas3);

int main() {
    vector<Studentas> Duomenys;  // Vektorius skirtas saugoti studentu duomenims

    srand(time(NULL));
    int veiksmas;
    string pasirinkimas, pasirinkimas1, pasirinkimas2, pasirinkimas3;

    while (true) {
        cout << "1 - Vesti duomenis rankiniu budu" << endl;
        cout << "2 - Generuoti pazymius" << endl;
        cout << "3 - Generuoti ir pazymius ir studentu vardus" << endl;
        cout << "4 - Baigti darba" << endl;
        cout << "5 - Nuskaityti duomenis is failo" << endl;
        cout << endl;
        cout << "Pasirinkite veiksma ivesdami skaiciu: ";
        cin >> veiksmas;
        cout << endl;

        switch (veiksmas) {
        case 1:
            cout << "Iveskite studentu skaiciu" << endl;
            int m;
            while (!(cin >> m) || cin.peek() != '\n' || m <= 0) {
                cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            RankinisIvedimas(m);
            break;

        case 2:
            cout << "Iveskite studentu skaiciu" << endl;
            int m2;
            while (!(cin >> m2) || cin.peek() != '\n' || m2 <= 0) {
                cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            GeneruotiPazymius(m2);
            break;

        case 3:
            cout << "Iveskite studentu skaiciu" << endl;
            int m3;
            while (!(cin >> m3) || cin.peek() != '\n' || m3 <= 0) {
                cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            GeneruotiPazymiusVardus(m3);
            break;

        case 4:
            cout << "Programa baigia darba." << endl;
            return 0;

        case 5: {
            Skaitymas(Duomenys);

            cout << "Kaip norite matyti savo galutini bala? Irasykite viena is dvieju pasirinkimu: (V - Vid. / M - Med.)" << endl;
            cin >> pasirinkimas;
            while (pasirinkimas != "V" && pasirinkimas != "M") {
                cout << "Pasirinkite arba 'V' arba 'M'" << endl;
                cin >> pasirinkimas;
            }
            cout << endl;

            cout << "Pagal ka norite rusiuoti rezultatus?" << endl;
            cout << "V - Varda" << endl;
            cout << "P - Pavarde" << endl;
            cout << "B - Bala" << endl;
            cin >> pasirinkimas3;
            while (pasirinkimas3 != "V" && pasirinkimas3 != "P" && pasirinkimas3 != "B") {
                cout << "Pasirinkite arba 'V' arba 'P' arba 'B'" << endl;
                cin >> pasirinkimas3;
            }
            cout << endl;

            cout << "Kokia tvarka norite rusiuoti rezultatus: (D - Didejancia, M - Mazejancia)" << endl;
            cin >> pasirinkimas1;
            while (pasirinkimas1 != "D" && pasirinkimas1 != "M") {
                cout << "Pasirinkite arba 'D' arba 'M'" << endl;
                cin >> pasirinkimas1;
            }
            cout << endl;

            cout << "Kaip norite matyti rezultatus? (E - Ekrane, F - Faile) " << endl;
            cin >> pasirinkimas2;
            while (pasirinkimas2 != "E" && pasirinkimas2 != "F") {
                cout << "Pasirinkite arba 'E' arba 'F'" << endl;
                cin >> pasirinkimas2;
            }
            cout << endl;

            RusiuotiSpausdinti(Duomenys, pasirinkimas, pasirinkimas1, pasirinkimas2, pasirinkimas3);

        } break;

        default:
            cout << "Neteisinga ivestis, prasome ivesti viena is pateiktu pasirinkimo variantu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << endl;
        }
    }
}

void RankinisIvedimas(int m) {
    vector<Studentas> Duomenys(m);

    for (int i = 0; i < m; i++) {
        cout << "Koks jusu vardas?" << endl;
        bool valid_v = true;
        do {
            if (!(cin >> Duomenys[i].v)) {
                valid_v = false;
            }
            else {
                valid_v = true;
                for (char c : Duomenys[i].v) {
                    if (!isalpha(c)) {
                        valid_v = false;
                        break;
                    }
                }
            }
            if (!valid_v) {
                cout << "Neteisinga ivestis, prasome ivesti savo varda sudaryta tik is raidziu " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid_v);

        // Pavardes ivestis

        cout << "Kokia jusu pavarde?" << endl;
        bool valid_p = true;
        do {
            if (!(cin >> Duomenys[i].p)) {
                valid_p = false;
            }
            else {
                valid_p = true;
                for (char c : Duomenys[i].p) {
                    if (!isalpha(c)) {
                        valid_p = false;
                        break;
                    }
                }
            }
            if (!valid_p) {
                cout << "Neteisinga ivestis, prasome ivesti savo pavarde sudaryta tik is raidziu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid_p);

        // Egzamino rezultato ivestis

        cout << "Koks buvo jusu egzamino rezultatas?" << endl;
        while (!(cin >> Duomenys[i].egz_rez) || Duomenys[i].egz_rez < 0 || Duomenys[i].egz_rez > 10) {
            cout << "Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // Namu darbu skaiciaus ivestis

        cout << "Kiek namu darbu atlikote?" << endl;
        while (!(cin >> Duomenys[i].n) || Duomenys[i].n < 0) {
            cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        Duomenys[i].nd_rez.resize(Duomenys[i].n);

        // Namu darbu rezultatu ivedimas ir sumos skaiciavimas

        for (int j = 0; j < Duomenys[i].n; j++) {
            cout << "Koks buvo " << j + 1 << "-o namu darbo vertinimas?" << endl;
            while (!(cin >> Duomenys[i].nd_rez[j]) || Duomenys[i].nd_rez[j] <= 0 || Duomenys[i].nd_rez[j] > 10 || cin.peek() != '\n') {
                cout << "Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Koks buvo " << i + 1 << "-o namu darbo vertinimas?" << endl;
            }
            Duomenys[i].nd_sum += Duomenys[i].nd_rez[j];
        }

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
    cout << "Kaip norite matyti savo galutini bala? Irasykite viena is dvieju pasirinkimu: (V - Vid. / M - Med.)" << endl;
    cin >> pasirinkimas;
    cout << endl;

    while (pasirinkimas != "V" && pasirinkimas != "M") {
        cout << "Pasirinkite arba 'V' arba 'M'" << endl;
        cin >> pasirinkimas;
    }

    if (pasirinkimas == "V") {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }
    else {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }

    for (int i = 0; i < m; i++) {
        if (pasirinkimas == "V") {
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

void GeneruotiPazymius(int m2) {
    vector<Studentas> Duomenys(m2);

    for (int i = 0; i < m2; i++) {
        cout << "Koks jusu vardas?" << endl;
        bool valid_v = true;
        do {
            if (!(cin >> Duomenys[i].v)) {
                valid_v = false;
            }
            else {
                valid_v = true;
                for (char c : Duomenys[i].v) {
                    if (!isalpha(c)) {
                        valid_v = false;
                        break;
                    }
                }
            }
            if (!valid_v) {
                cout << "Neteisinga ivestis, prasome ivesti savo varda sudaryta tik is raidziu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid_v);

        // Pavardes ivestis

        cout << "Kokia jusu pavarde?" << endl;
        bool valid_p = true;
        do {
            if (!(cin >> Duomenys[i].p)) {
                valid_p = false;
            }
            else {
                valid_p = true;
                for (char c : Duomenys[i].p) {
                    if (!isalpha(c)) {
                        valid_p = false;
                        break;
                    }
                }
            }
            if (!valid_p) {
                cout << "Neteisinga ivestis, prasome ivesti savo pavarde sudaryta tik is raidziu" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        } while (!valid_p);

        // Egzamino rezultato generavimas

        Duomenys[i].egz_rez = (rand() % 10) + 1;

        // Namu darbu skaiciaus generavimas

        Duomenys[i].n = (rand() % 10) + 1;

        Duomenys[i].nd_rez.resize(Duomenys[i].n);

        // Namu darbu rezultatu generavimas ir sumos skaiciavimas

        for (int j = 0; j < Duomenys[i].n; j++) {
            Duomenys[i].nd_rez[j] = (rand() % 10) + 1;
            Duomenys[i].nd_sum += Duomenys[i].nd_rez[j];
        }

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
    cout << "Kaip norite matyti savo galutini bala? Irasykite viena is dvieju pasirinkimu: (V - Vid. / M - Med.)" << endl;
    cin >> pasirinkimas;
    cout << endl;

    while (pasirinkimas != "V" && pasirinkimas != "M") {
        cout << "Pasirinkite arba 'V' arba 'M'" << endl;
        cin >> pasirinkimas;
    }

    if (pasirinkimas == "V") {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }
    else {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }

    for (int i = 0; i < m2; i++) {
        if (pasirinkimas == "V") {
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

        // Namu darbu skaiciaus ivestis

        cout << "Kiek namu darbu atliko " << i + 1 << "-asis studentas" << endl;
        while (!(cin >> Duomenys[i].n) || Duomenys[i].n < 0) {
            cout << "Neteisinga ivestis, prasome ivesti skaiciu" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

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
    cout << "Kaip norite matyti savo galutini bala? Irasykite viena is dvieju pasirinkimu: (V - Vid. / M - Med.)" << endl;
    cin >> pasirinkimas;
    cout << endl;

    while (pasirinkimas != "V" && pasirinkimas != "M") {
        cout << "Pasirinkite arba 'V' arba 'M'" << endl;
        cin >> pasirinkimas;
    }

    if (pasirinkimas == "V") {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }
    else {
        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
    }

    for (int i = 0; i < m3; i++) {
        if (pasirinkimas == "V") {
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
void Skaitymas(vector<Studentas>& Duomenys) {
    Studentas studentas;
    string line;

    ifstream infile("kursiokai.txt");
    if (!infile) {
        cerr << "Nepavyko atidaryti failo.";
        return;
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
            cerr << "Nerasta namu darbu ivertinimu.";
            return;
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

void RusiuotiSpausdinti(vector<Studentas>& Duomenys, string pasirinkimas, string pasirinkimas1, string pasirinkimas2, string pasirinkimas3) {
    // Skaiciuojami galutiniai rezultatai
    for (auto& studentas : Duomenys) {
        if (pasirinkimas == "V") {
            studentas.nd_vid = studentas.nd_sum / studentas.nd_rez.size();
            studentas.rez = 0.4 * studentas.nd_vid + 0.6 * studentas.egz_rez;
        }
        else {
            studentas.rez = 0.4 * studentas.mediana + 0.6 * studentas.egz_rez;
        }
    }

    // Rusiuojama pagal pasirinkta kriteriju
    if (pasirinkimas3 == "V") {
        if (pasirinkimas1 == "D")
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.v > b.v; });
        else
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.v < b.v; });
    }
    else if (pasirinkimas3 == "P") {
        if (pasirinkimas1 == "D")
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.p > b.p; });
        else
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.p < b.p; });
    }
    else if (pasirinkimas3 == "B") {
        if (pasirinkimas1 == "D")
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.rez > b.rez; });
        else
            sort(Duomenys.begin(), Duomenys.end(), [](const Studentas& a, const Studentas& b) { return a.rez < b.rez; });
    }

    // Pasirenkamas spausdinimas i konsole arba faila
    if (pasirinkimas2 == "E") {
        if (pasirinkimas == "V") {
            cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Vid.)" << endl;
            cout << "-----------------------------------------------" << endl;
            for (const auto& studentas : Duomenys) {
                cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
            }
        }
        else {
            cout << left << setw(15) << "Vardas" << setw(15) << "Pavarde" << setw(15) << "Galutinis (Med.)" << endl;
            cout << "-----------------------------------------------" << endl;
            for (const auto& studentas : Duomenys) {
                cout << left << setw(15) << studentas.v << setw(15) << studentas.p << fixed << setprecision(2) << setw(15) << studentas.rez << endl;
            }
        }
    }
    else {
        // Rezultatu irasymas i faila
        ofstream outfile("rezultatai.txt");
        if (!outfile) {
            cerr << "Nepavyko sukurti rezultatu failo.";
            return;
        }
        if (pasirinkimas == "V") {
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