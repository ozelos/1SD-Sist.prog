#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include "student.h"

void nuskaityti(const std::string& fileName, std::vector<Student>& studentai) {
    std::ifstream inFile(fileName);
    if (!inFile) {
        throw std::runtime_error("Nepavyko atidaryti failo");
    }

    std::string vardas, pavarde;
    int egzaminas;
    std::vector<int> namuDarbai(5);

    while (inFile >> vardas >> pavarde >> namuDarbai[0] >> namuDarbai[1] >> namuDarbai[2] >> namuDarbai[3] >> namuDarbai[4] >> egzaminas) {
        studentai.emplace_back(vardas, pavarde, namuDarbai, egzaminas);
    }
    inFile.close();
}

int main() {
    try {
        std::vector<Student> studentai;
        nuskaityti("kursiokai.txt", studentai);

        std::sort(studentai.begin(), studentai.end(), [](const Student& a, const Student& b) {
            return a.vardas_ < b.vardas_;
            });

        std::cout << "Pavardė     Vardas       Galutinis (Vid.)   Galutinis (Med.)\n";
        std::cout << "------------------------------------------------------------\n";
        for (const auto& student : studentai) {
            std::cout << student << std::endl;
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Klaida: " << e.what() << std::endl;
    }
    return 0;
}
