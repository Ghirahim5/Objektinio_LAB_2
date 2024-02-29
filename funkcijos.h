#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <vector>
#include "studentas.h"

void GeneruotiPazymius(std::vector<Studentas> & Duomenys);
void GeneruotiPazymiusVardus(int m);
double Skaitymas(std::vector<Studentas>& Duomenys);
void RusiuotiSpausdinti(std::vector<Studentas>& Duomenys, double laikas, const std::string& pavadinimas);
void RankinisIvedimas(std::vector<Studentas>& Duomenys);

#endif