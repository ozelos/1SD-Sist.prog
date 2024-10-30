#include <iostream>
#include <vector>
#include <list>
#include <deque>
#include <fstream>
#include <chrono>
#include <algorithm>
#include "studentas.h"

// Strategija 1: Skirstymas į du naujus konteinerius
template <typename Container>
void strategija1(const Container& studentai, Container& vargsai, Container& kietiakai) {
    for (const auto& studentas : studentai) {
        if (studentas.getGalutinis() < 5.0) 
            vargsai.push_back(studentas);
        else 
            kietiakai.push_back(studentas);
    }
}

// Strategija 2: Skirstymas naudojant vieną naują konteinerį ir modifikuojant pagrindinį
template <typename Container>
void strategija2(Container& studentai, Container& vargsai) {
    studentai.erase(std::remove_if(studentai.begin(), studentai.end(),
                                    [&vargsai](const Studentas& studentas) {
                                        if (studentas.getGalutinis() < 5.0) {
                                            vargsai.push_back(studentas);
                                            return true;
                                        }
                                        return false;
                                    }),
                    studentai.end());
}

// Algoritmų testavimas: std::partition ir std::stable_partition
void testuotiAlgoritmus(std::vector<Studentas>& studentai) {
    std::vector<Studentas> vargsai, kietiakai;

    // std::partition
    auto start = std::chrono::high_resolution_clock::now();
    auto it = std::partition(studentai.begin(), studentai.end(), [](const Studentas& s) { return s.getGalutinis() < 5.0; });
    vargsai.insert(vargsai.end(), studentai.begin(), it);
    kietiakai.insert(kietiakai.end(), it, studentai.end());
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "std::partition trukmė: " << std::chrono::duration<double>(end - start).count() << " s\n";

    // std::stable_partition
    start = std::chrono::high_resolution_clock::now();
    it = std::stable_partition(studentai.begin(), studentai.end(), [](const Studentas& s) { return s.getGalutinis() < 5.0; });
    vargsai.assign(studentai.begin(), it);
    kietiakai.assign(it, studentai.end());
    end = std::chrono::high_resolution_clock::now();
    std::cout << "std::stable_partition trukmė: " << std::chrono::duration<double>(end - start).count() << " s\n";
}

// Studentų failo nuskaitymas
template <typename Container>
void nuskaitytiStudentus(const std::string& failoVardas, Container& studentai) {
    std::ifstream inFile(failoVardas);
    std::string vardas, pavarde;
    double galutinis;
    while (inFile >> vardas >> pavarde >> galutinis) {
        studentai.emplace_back(vardas, pavarde, galutinis);
    }
}

int main() {
    const std::string failoVardas = "studentai_10000.txt"; // Naudojame pavyzdinį failą
    const int studentuKiekis = 10000;

    // 1 strategija testavimas su skirtingais konteineriais
    std::vector<Studentas> vectorStudentai, vargsaiVector, kietiakaiVector;
    std::list<Studentas> listStudentai, vargsaiList, kietiakaiList;
    std::deque<Studentas> dequeStudentai, vargsaiDeque, kietiakaiDeque;

    // Studentų duomenų nuskaitymas
    nuskaitytiStudentus(failoVardas, vectorStudentai);
    listStudentai.assign(vectorStudentai.begin(), vectorStudentai.end());
    dequeStudentai.assign(vectorStudentai.begin(), vectorStudentai.end());

    // Strategija 1 su std::vector
    auto start = std::chrono::high_resolution_clock::now();
    strategija1(vectorStudentai, vargsaiVector, kietiakaiVector);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Strategija 1 su vector trukmė: " << std::chrono::duration<double>(end - start).count() << " s\n";

    // Strategija 1 su std::list
    start = std::chrono::high_resolution_clock::now();
    strategija1(listStudentai, vargsaiList, kietiakaiList);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Strategija 1 su list trukmė: " << std::chrono::duration<double>(end - start).count() << " s\n";

    // Strategija 1 su std::deque
    start = std::chrono::high_resolution_clock::now();
    strategija1(dequeStudentai, vargsaiDeque, kietiakaiDeque);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Strategija 1 su deque trukmė: " << std::chrono::duration<double>(end - start).count() << " s\n";

    // Strategija 2 su std::vector
    start = std::chrono::high_resolution_clock::now();
    strategija2(vectorStudentai, vargsaiVector);
    end = std::chrono::high_resolution_clock::now();
    std::cout << "Strategija 2 su vector trukmė: " << std::chrono::duration<double>(end - start).count() << " s\n";

    // Testuojame algoritmus
    testuotiAlgoritmus(vectorStudentai);

    return 0;
}
