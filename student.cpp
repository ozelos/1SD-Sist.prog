#include "studentas.h"
#include <iomanip>

std::ostream& operator<<(std::ostream& out, const Studentas& studentas) {
    out << studentas.vardas_ << " " << studentas.pavarde_ 
        << " Galutinis: " << std::fixed << std::setprecision(2) 
        << studentas.galutinis_;
    return out;
}
