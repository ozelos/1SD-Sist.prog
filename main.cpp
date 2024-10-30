#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <deque>
#include <chrono>
#include <random>
#include "studentas.h"

// Atsitiktinių skaičių generavimui
std::mt19937 rng(std::random_device{}());
std::uniform_int_distribution<int> dist(1, 10);

// Atsitiktinių studentų generavimas
void generuotiStudentuFaila(const std::string& failoVardas, int studentuKiekis) {
    std::ofstream outFile(failoVardas);
    if (!outFile) throw std::runtime_error("Nepavyko sukurti failo!");

    for (int i = 1; i <= studentuKiekis; ++i) {
        outFile << "Vardas" << i << " Pavarde" << i;
        for (int j = 0; j < 5; ++j) outFile << " " << dist(rng);
        outFile << " " << dist(rng) << "\n";
    }
}

// Duomenų nuskaitymas iš failo
template <typename Container>
void nuskaitytiStudentus(const std::string& failoVardas, Container& studentai) {
    std::ifstream inFile(failoVardas);
    if (!inFile) throw std::runtime_error("Nepavyko atidaryti failo!");

    std::string vardas, pavarde;
    std::vector<int> namuDarbai(5);
    int egzaminas;

    while (inFile >> vardas >> pavarde >> namuDarbai[0] >> namuDarbai[1] >> namuDarbai[2] >> namuDarbai[3] >> namuDarbai[4] >> egzaminas) {
        studentai.emplace_back(vardas, pavarde, namuDarbai, egzaminas);
    }
}

// Studentų padalijimas į dvi kategorijas
template <typename Container>
void padalintiStudentus(const Container& studentai, Container& vargsai, Container& kietiakai) {
    for (const auto& studentas : studentai) {
        if (studentas.getGalutinis() < 5.0)
            vargsai.push_back(studentas);
        else
            kietiakai.push_back(studentas);
    }
}

// Rezultatų išvedimas į failus
template <typename Container>
void isvestiStudentusIFaila(const std::string& failoVardas, const Container& studentai) {
    std::ofstream outFile(failoVardas);
    for (const auto& studentas : studentai) {
        outFile << studentas << "\n";
    }
}

int main() {
    const std::vector<int> studentuKiekiai = { 1000, 10000, 100000, 1000000, 10000000 };
    const std::string failuPriedas = "studentai_";

    // Generuojame failus su studentų įrašais
    for (int kiekis : studentuKiekiai) {
        std::string failoVardas = failuPriedas + std::to_string(kiekis) + ".txt";
        auto start = std::chrono::high_resolution_clock::now();
        generuotiStudentuFaila(failoVardas, kiekis);
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Failo " << failoVardas << " generavimas užtruko: " 
                  << std::chrono::duration<double>(end - start).count() << " s\n";
    }

    // Konteinerių testavimas
    for (int kiekis : studentuKiekiai) {
        std::string failoVardas = failuPriedas + std::to_string(kiekis) + ".txt";
        
        // Tikriname su vector
        {
            std::vector<Studentas> studentai, vargsai, kietiakai;
            auto start = std::chrono::high_resolution_clock::now();
            nuskaitytiStudentus(failoVardas, studentai);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Nuskaitymas į vector užtruko: " 
                      << std::chrono::duration<double>(end - start).count() << " s\n";

            start = std::chrono::high_resolution_clock::now();
            padalintiStudentus(studentai, vargsai, kietiakai);
            end = std::chrono::high_resolution_clock::now();
            std::cout << "Padalijimas į vector užtruko: " 
                      << std::chrono::duration<double>(end - start).count() << " s\n";

            isvestiStudentusIFaila("vargsai_vector_" + std::to_string(kiekis) + ".txt", vargsai);
            isvestiStudentusIFaila("kietiakai_vector_" + std::to_string(kiekis) + ".txt", kietiakai);
        }

        // Tikriname su list
        {
            std::list<Studentas> studentai, vargsai, kietiakai;
            auto start = std::chrono::high_resolution_clock::now();
            nuskaitytiStudentus(failoVardas, studentai);
            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Nuskaitymas į list užtruko: " 
                      << std::chrono::duration<double>(end - start).count() << " s\n";

            start = std::chrono::high_resolution_clock::
