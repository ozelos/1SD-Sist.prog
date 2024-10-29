#include "student.h"
#include <iostream>
#include <algorithm>
#include <numeric>
#include <iomanip>

// Numatytasis konstruktorius
Student::Student() : vardas_(""), pavarde_(""), egzaminas_(0), galutinisVid_(0), galutinisMed_(0) {}

// Parametrų konstruktorius
Student::Student(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas)
    : vardas_(vardas), pavarde_(pavarde), namuDarbai_(namuDarbai), egzaminas_(egzaminas) {
    skaiciuotiGalutini();
}

// Kopijavimo konstruktorius
Student::Student(const Student& other) : vardas_(other.vardas_), pavarde_(other.pavarde_), namuDarbai_(other.namuDarbai_), egzaminas_(other.egzaminas_), galutinisVid_(other.galutinisVid_), galutinisMed_(other.galutinisMed_) {}

// Priskyrimo operatorius
Student& Student::operator=(const Student& other) {
    if (this != &other) {
        vardas_ = other.vardas_;
        pavarde_ = other.pavarde_;
        namuDarbai_ = other.namuDarbai_;
        egzaminas_ = other.egzaminas_;
        galutinisVid_ = other.galutinisVid_;
        galutinisMed_ = other.galutinisMed_;
    }
    return *this;
}

// Destruktorius
Student::~Student() {}

// Duomenų įvedimas
void Student::ivestiDuomenis() {
    std::cout << "Įveskite vardą: ";
    std::cin >> vardas_;
    std::cout << "Įveskite pavardę: ";
    std::cin >> pavarde_;

    int nd;
    std::cout << "Įveskite namų darbų rezultatus (įveskite -1, kai baigsite): ";
    while (true) {
        std::cin >> nd;
        if (nd == -1) break;
        namuDarbai_.push_back(nd);
    }

    std::cout << "Įveskite egzamino rezultatą: ";
    std::cin >> egzaminas_;

    skaiciuotiGalutini();
}

// Galutinio pažymio skaičiavimas
void Student::skaiciuotiGalutini() {
    galutinisVid_ = 0.4 * skaiciuotiVidurki() + 0.6 * egzaminas_;
    galutinisMed_ = 0.4 * skaiciuotiMediana() + 0.6 * egzaminas_;
}

double Student::skaiciuotiVidurki() const {
    return std::accumulate(namuDarbai_.begin(), namuDarbai_.end(), 0.0) / namuDarbai_.size();
}

double Student::skaiciuotiMediana() const {
    std::vector<int> temp = namuDarbai_;
    std::sort(temp.begin(), temp.end());
    size_t size = temp.size();
    return (size % 2 == 0) ? (temp[size / 2 - 1] + temp[size / 2]) / 2.0 : temp[size / 2];
}

// Duomenų įvedimo operatorius
std::istream& operator>>(std::istream& in, Student& student) {
    student.ivestiDuomenis();
    return in;
}

// Duomenų išvedimo operatorius
std::ostream& operator<<(std::ostream& out, const Student& student) {
    out << std::setw(12) << student.pavarde_ << std::setw(12) << student.vardas_
        << std::setw(20) << std::fixed << std::setprecision(2) << student.galutinisVid_
        << std::setw(20) << std::fixed << std::setprecision(2) << student.galutinisMed_;
    return out;
}
