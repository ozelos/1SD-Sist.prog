#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <algorithm>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> namuDarbai_;
    int egzaminas_;
    double galutinis_;

public:
    // Konstruktorius
    Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas);

    // Galutinio balo skaičiavimas
    void skaiciuotiGalutini();
    double getGalutinis() const { return galutinis_; }

    // Išvedimo operatorius
    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);
};

#endif // STUDENTAS_H
