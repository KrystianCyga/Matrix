// src/main.cpp

#include <iostream>
#include "matrix.h"

int main() {
    try {
        // Tworzenie macierzy 3x3
        matrix<int> mat1(3, 3);

        // Ustawianie elementow macierzy
        mat1(0, 0) = 1;
        mat1(0, 1) = 2;
        mat1(0, 2) = 3;
        mat1(1, 0) = 4;
        mat1(1, 1) = 5;
        mat1(1, 2) = 6;
        mat1(2, 0) = 7;
        mat1(2, 1) = 8;
        mat1(2, 2) = 9;

        // Wyświetlenie macierzy
        std::cout << "Macierz mat1:" << std::endl;
        std::cout << mat1 << std::endl;

        // Tworzenie kopii macierzy (przypisanie kopiujace)
        matrix<int> mat2 = mat1;

        // Modyfikacja kopii
        mat2(0, 0) = 10;

        std::cout << "Macierz mat2 po modyfikacji:" << std::endl;
        std::cout << mat2 << std::endl;

        // Sprawdzenie rowności macierzy
        if (mat1 == mat2) {
            std::cout << "mat1 i mat2 sa rowne." << std::endl;
        } else {
            std::cout << "mat1 i mat2 NIE sa rowne." << std::endl;
        }

        // Dodawanie macierzy
        matrix<int> mat3 = mat1 + mat2;
        std::cout << "Macierz mat3 (mat1 + mat2):" << std::endl;
        std::cout << mat3 << std::endl;

        // Obliczanie wyznacznika macierzy 2x2
        matrix<int> mat4(2, 2);
        mat4(0, 0) = 4;
        mat4(0, 1) = 7;
        mat4(1, 0) = 2;
        mat4(1, 1) = 6;
        std::cout << "Macierz mat4:" << std::endl;
        std::cout << mat4 << std::endl;
        std::cout << "Wyznacznik mat4: " << mat4.getDeterminant() << std::endl;

        // Obliczanie transpozycji macierzy
        matrix<int> transposed = mat1.getTranspose(); // Zakładajac, że getInverse() zwraca transpozycję
        std::cout << "Transponowana macierz mat1:" << std::endl;
        std::cout << transposed << std::endl;

        //std::cout << mat4(5,5) << std::endl;

    } catch (const std::exception &e) {
        std::cerr << "Wystapil blad: " << e.what() << std::endl;
    }

    return 0;
}