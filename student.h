#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class Student {
private:
    std::string vardas_;
    std::string pavarde_;
    std::vector<int> namuDarbai_;
    int egzaminas_;
    double galutinisVid_;
    double galutinisMed_;

public:
    // Konstruktoriai ir destruktorius
    Student();
    Student(const std::string& vardas, const std::string& pavarde, const std::vector<int>& namuDarbai, int egzaminas);
    Student(const Student& other); // Kopijavimo konstruktorius
    Student& operator=(const Student& other); // Priskyrimo operatorius
    ~Student(); // Destruktorius

    // Metodai
    void ivestiDuomenis();
    void skaiciuotiGalutini();
    double skaiciuotiVidurki() const;
    double skaiciuotiMediana() const;

    // Operatoriai
    friend std::istream& operator>>(std::istream& in, Student& student);
    friend std::ostream& operator<<(std::ostream& out, const Student& student);
};

#endif // STUDENT_H
