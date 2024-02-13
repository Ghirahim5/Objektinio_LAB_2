#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

struct {
    string v;
    string p;
    double egz_rez;
    int nd_sk;
    double nd_rez[10];
} Duomenys;

int main() {

    double rez;
    string pasirinkimas;

    cout << "Koks jusu vardas?" << endl;
    cin >> Duomenys.v;
    cout << "Kokia jusu pavarde?" << endl;
    cin >> Duomenys.p;
    cout << "Koks buvo jusu egzamino rezultatas?" << endl;
    while (!(cin >> Duomenys.egz_rez) || Duomenys.egz_rez < 0 || Duomenys.egz_rez > 10) {
        cout << "Neteisinga ivestis, prasome ivesti skaiciu 10-baleje sistemoje" << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "Kiek namu darbu atlikote?" << endl;
    cin >> Duomenys.nd_sk;

    // Namu darbu rezultatu ivedimas ir sumos skaiciavimas

    double nd_sum = 0;
    for (int i = 0; i < Duomenys.nd_sk; i++) {
        cout << "Koks buvo " << i + 1 << "-o namu darbo vertinimas?" << endl;
        cin >> Duomenys.nd_rez[i];
        nd_sum += Duomenys.nd_rez[i];
    }

    // Namu darbu masyvo rusiavimas

    sort(Duomenys.nd_rez, Duomenys.nd_rez + Duomenys.nd_sk);

    // Medianos skaiciavimas

    double mediana;
    if (Duomenys.nd_sk % 2 == 0) {
        mediana = (Duomenys.nd_rez[Duomenys.nd_sk / 2 - 1] + Duomenys.nd_rez[Duomenys.nd_sk / 2]) / 2.0;
    }
    else {
        mediana = Duomenys.nd_rez[Duomenys.nd_sk / 2];
    }

    cout << "Kaip norite matyti savo galutini bala? Irasykite viena is dvieju pasirinkimu: (Vid. / Med.)" << endl;
    cin >> pasirinkimas;
    cout << endl;

    if (pasirinkimas == "Vid.") {
        double nd_avg = nd_sum / Duomenys.nd_sk;
        rez = 0.4 * nd_avg + 0.6 * Duomenys.egz_rez;

        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Vid.)" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << left << setw(15) << Duomenys.v << setw(15) << Duomenys.p << fixed << setprecision(2) << setw(15) << rez << endl;

    }
    else if (pasirinkimas == "Med.") {

        rez = 0.4 * mediana + 0.6 * Duomenys.egz_rez;

        cout << left << setw(15) << "Pavarde" << setw(15) << "Vardas" << setw(15) << "Galutinis (Med.)" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << left << setw(15) << Duomenys.v << setw(15) << Duomenys.p << fixed << setprecision(2) << setw(15) << rez << endl;
    }
    return 0;
}
