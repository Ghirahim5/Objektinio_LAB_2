#include <iostream>
#include <vector>
#include "funkcijos.h"

using namespace std;

double bendras_laikas = 0;
int vykdymu_skaicius = 0;

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
            double laikas = Skaitymas(Duomenys);
            RusiuotiSpausdinti(Duomenys, laikas, pavadinimas);

            bendras_laikas += laikas;
            vykdymu_skaicius++;

            cout << "Keliu testu laiku vidurkis: " << bendras_laikas / vykdymu_skaicius << " sekundes" << endl;
            cout << endl;

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