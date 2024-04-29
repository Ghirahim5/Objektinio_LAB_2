#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <string>
#include <list>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <iomanip>
#include <limits>
#include <random>
#include <fstream>
#include <sstream>

class Studentas {

private:

    std::string v;
	std::string p; 
	double egz_rez; 
	double mediana;
	std::list<double> nd_rez; 
    double nd_sum = 0;
    double rez;

    void UpdateNdSum() { nd_sum = std::accumulate(nd_rez.begin(), nd_rez.end(), 0.0); }

public:

    // konstruktoriai
    Studentas();
    Studentas(const std::string& v_, const std::string& p_, double mediana, double egz_rez_, double rez_, const std::list<double>& nd_rez_);

    // destruktorius
    ~Studentas() { 
      v.clear();
      p.clear();
      nd_rez.clear();
    }

    // get'eriai
    inline std::string getV() const { return v; }
    inline std::string getP() const { return p; }
    const std::list<double>& getNd_rez() const { return nd_rez; }
    double getEgz_rez() const { return egz_rez; }
    double getNd_sum() const { return nd_sum; }
    double getRez() const { return rez; }

    // set'eriai
    void setV(const std::string& v) { this->v = v; }
    void setP(const std::string& p) { this->p = p; }
    void setRez(double rez) { this->rez = rez; }
    void setMediana(double mediana) { this->mediana = mediana; }
    void setEgz_rez(double egz_rez) { this->egz_rez = egz_rez; }
    void setNd_rez(const std::list<double>& nd_rez) { this->nd_rez = nd_rez; UpdateNdSum(); }
    void setNd_sum(double nd_sum) { this->nd_sum = nd_sum; }

    // funkcijos
    double ApskaiciuotiMediana() const;
    double ApskaiciuotiVidurki() const;
    double ApskaiciuotiGalutini(bool mediana);
    void addNd_rez(double result) { nd_rez.push_back(result); }
    void resizeNd_rez(int n) { nd_rez.resize(n); }
    void popNd_rez() { nd_rez.pop_back(); }
    void clearNdRez() { nd_rez.clear(); }

};


#endif
