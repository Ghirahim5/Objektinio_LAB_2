#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <vector>

struct Studentas {
    std::string v;
    std::string p;
    int n;
    double egz_rez;
    std::vector<double> nd_rez;
    double nd_sum = 0;
    double nd_vid;
    double rez;
    double mediana;
};

#endif
