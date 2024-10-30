#include "studentas.h"
#include <numeric>
#include <iomanip>

Studentas::Studentas(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), namuDarbai_(namuDarbai), egzaminas_(egzaminas) {
    skaiciuotiGalutini();
}

void Studentas::skaiciuotiGalutini() {
    double vidurkis = std::accumulate(namuDarbai_.begin(), namuDarbai_.end(), 0.0) / namuDarbai_.size();
    galutinis_ = 0.4 * vidurkis + 0.6 * egzaminas_;
}

std::ostream& operator<<(std::ostream& out, const Studentas& studentas) {
    out << std::setw(12) << studentas.pavarde_ << std::setw(12) << studentas.vardas_
        << std::setw(10) << std::fixed << std::setprecision(2) << studentas.galutinis_;
    return out;
}
