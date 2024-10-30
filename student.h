#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Studentas {
private:
    std::string vardas_;
    std::string pavarde_;
    double galutinis_;

public:
    Studentas(const std::string& vardas, const std::string& pavarde, double galutinis)
        : vardas_(vardas), pavarde_(pavarde), galutinis_(galutinis) {}

    double getGalutinis() const { return galutinis_; }

    friend std::ostream& operator<<(std::ostream& out, const Studentas& studentas);
};

#endif // STUDENTAS_H
