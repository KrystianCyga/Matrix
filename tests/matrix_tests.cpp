// tests/matrix_tests.cpp

#include <gtest/gtest.h>
#include "matrix.h"

// Testy konstruktorów
TEST(MatrixConstructorTest, DefaultConstructor) {
    matrix<int> mat;
    EXPECT_EQ(mat.getSize().first, 0);
    EXPECT_EQ(mat.getSize().second, 0);
}

TEST(MatrixConstructorTest, SquareMatrixConstructor) {
    matrix<double> mat(3);
    EXPECT_EQ(mat.getSize().first, 3);
    EXPECT_EQ(mat.getSize().second, 3);
    for (size_t i = 0; i < 3; ++i)
        for (size_t j = 0; j < 3; ++j)
            EXPECT_EQ(mat(i, j), 0.0);
}

TEST(MatrixConstructorTest, RectangularMatrixConstructor) {
    matrix<int> mat(2, 4);
    EXPECT_EQ(mat.getSize().first, 2);
    EXPECT_EQ(mat.getSize().second, 4);
    for (size_t i = 0; i < 2; ++i)
        for (size_t j = 0; j < 4; ++j)
            EXPECT_EQ(mat(i, j), 0);
}

TEST(MatrixConstructorTest, PairConstructor) {
    std::pair<std::size_t, std::size_t> size = {5, 6};
    matrix<double> mat(size);
    EXPECT_EQ(mat.getSize().first, 5);
    EXPECT_EQ(mat.getSize().second, 6);
    for (size_t i = 0; i < 5; ++i)
        for (size_t j = 0; j < 6; ++j)
            EXPECT_EQ(mat(i, j), 0.0);
}

// Testy dostępu i modyfikacji elementów
TEST(MatrixAccessTest, SetAndGetElements) {
    matrix<int> mat(3, 3);
    mat(0, 0) = 1;
    mat(1, 1) = 5;
    mat(2, 2) = 9;
    EXPECT_EQ(mat(0, 0), 1);
    EXPECT_EQ(mat(1, 1), 5);
    EXPECT_EQ(mat(2, 2), 9);
}

TEST(MatrixAccessTest, OutOfRangeAccess) {
    matrix<int> mat(3, 3);
    EXPECT_THROW(mat(3, 0), std::out_of_range);
    EXPECT_THROW(mat(0, 3), std::out_of_range);
    EXPECT_THROW(mat(static_cast<size_t>(-1), 0), std::out_of_range); // Uciekający konwersja na size_t
    EXPECT_THROW(mat(0, static_cast<size_t>(-1)), std::out_of_range);
}

// Testy operatora równości
TEST(MatrixEqualityTest, EqualMatrices) {
    matrix<int> mat1(2, 2);
    matrix<int> mat2(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;
    mat2(0, 0) = 1; mat2(0, 1) = 2;
    mat2(1, 0) = 3; mat2(1, 1) = 4;
    EXPECT_TRUE(mat1 == mat2);
}

TEST(MatrixEqualityTest, DifferentMatrices) {
    matrix<int> mat1(2, 2);
    matrix<int> mat2(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;
    mat2(0, 0) = 5; mat2(0, 1) = 6;
    mat2(1, 0) = 7; mat2(1, 1) = 8;
    EXPECT_FALSE(mat1 == mat2);
}

TEST(MatrixEqualityTest, DifferentSizes) {
    matrix<int> mat1(2, 2);
    matrix<int> mat2(3, 3);
    EXPECT_FALSE(mat1 == mat2);
}

// Testy operatora dodawania
TEST(MatrixAdditionTest, ValidAddition) {
    matrix<int> mat1(2, 2);
    matrix<int> mat2(2, 2);
    mat1(0, 0) = 1; mat1(0, 1) = 2;
    mat1(1, 0) = 3; mat1(1, 1) = 4;
    mat2(0, 0) = 5; mat2(0, 1) = 6;
    mat2(1, 0) = 7; mat2(1, 1) = 8;
    matrix<int> result = mat1 + mat2;
    EXPECT_EQ(result(0, 0), 6);
    EXPECT_EQ(result(0, 1), 8);
    EXPECT_EQ(result(1, 0), 10);
    EXPECT_EQ(result(1, 1), 12);
}

TEST(MatrixAdditionTest, AdditionWithDifferentSizes) {
    matrix<int> mat1(2, 2);
    matrix<int> mat3(3, 3);
    EXPECT_THROW(mat1 + mat3, std::invalid_argument);
}

TEST(MatrixAdditionTest, AdditionWithEmptyMatrix) {
    matrix<int> mat1(2, 2);
    matrix<int> empty;
    EXPECT_THROW(mat1 + empty, std::invalid_argument);
}

// Testy operatora odejmowania
TEST(MatrixSubtractionTest, ValidSubtraction) {
    matrix<int> mat1(2, 2);
    matrix<int> mat2(2, 2);
    mat1(0, 0) = 5; mat1(0, 1) = 6;
    mat1(1, 0) = 7; mat1(1, 1) = 8;
    mat2(0, 0) = 1; mat2(0, 1) = 2;
    mat2(1, 0) = 3; mat2(1, 1) = 4;
    matrix<int> result = mat1 - mat2;
    EXPECT_EQ(result(0, 0), 4);
    EXPECT_EQ(result(0, 1), 4);
    EXPECT_EQ(result(1, 0), 4);
    EXPECT_EQ(result(1, 1), 4);
}

TEST(MatrixSubtractionTest, SubtractionWithDifferentSizes) {
    matrix<int> mat1(2, 2);
    matrix<int> mat3(2, 3);
    EXPECT_THROW(mat1 - mat3, std::invalid_argument);
}

TEST(MatrixSubtractionTest, SubtractionWithEmptyMatrix) {
    matrix<int> mat1(2, 2);
    matrix<int> empty;
    EXPECT_THROW(mat1 - empty, std::invalid_argument);
}

// Testy transpozycji
TEST(MatrixTransposeTest, Transpose) {
    matrix<int> mat(2, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;
    matrix<int> transposed = mat.getTranspose(); 
    EXPECT_EQ(transposed.getSize().first, 3);
    EXPECT_EQ(transposed.getSize().second, 2);
    EXPECT_EQ(transposed(0, 0), 1);
    EXPECT_EQ(transposed(0, 1), 4);
    EXPECT_EQ(transposed(1, 0), 2);
    EXPECT_EQ(transposed(1, 1), 5);
    EXPECT_EQ(transposed(2, 0), 3);
    EXPECT_EQ(transposed(2, 1), 6);
}

// Testy wyznacznika
TEST(MatrixDeterminantTest, Determinant1x1) {
    matrix<int> mat(1, 1);
    mat(0, 0) = 5;
    EXPECT_EQ(mat.getDeterminant(), 5);
}

TEST(MatrixDeterminantTest, Determinant2x2) {
    matrix<int> mat(2, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;
    EXPECT_EQ(mat.getDeterminant(), -2);
}

TEST(MatrixDeterminantTest, Determinant3x3) {
    matrix<int> mat(3, 3);
    mat(0, 0) = 6; mat(0, 1) = 1; mat(0, 2) = 1;
    mat(1, 0) = 4; mat(1, 1) = -2; mat(1, 2) = 5;
    mat(2, 0) = 2; mat(2, 1) = 8; mat(2, 2) = 7;
    EXPECT_EQ(mat.getDeterminant(), -306);
}

TEST(MatrixDeterminantTest, DeterminantNonSquare) {
    matrix<int> mat(2, 3);
    EXPECT_THROW(mat.getDeterminant(), std::invalid_argument);
}

// Testy inwersji
TEST(MatrixTransposeTest, Transpose2x2) {
    matrix<double> mat(2, 2);
    mat(0, 0) = 4; mat(0, 1) = 7;
    mat(1, 0) = 2; mat(1, 1) = 6;

    double det = mat.getDeterminant();
    EXPECT_NE(det, 0);

    matrix<double> Transpose = mat.getTranspose(); 

    // Oczekujemy transpozycji, więc wynik powinien być transponowaną macierzą mat
    EXPECT_EQ(Transpose.getSize().first, 2);
    EXPECT_EQ(Transpose.getSize().second, 2);
    EXPECT_EQ(Transpose(0, 0), 4.0);
    EXPECT_EQ(Transpose(0, 1), 2.0);
    EXPECT_EQ(Transpose(1, 0), 7.0);
    EXPECT_EQ(Transpose(1, 1), 6.0);
}

// Testy transpozycji
TEST(MatrixTransposeTest, TransposeNonSquareMatrix) {
    matrix<int> mat(2, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;

    matrix<int> transposed = mat.getTranspose();

    EXPECT_EQ(transposed.getSize().first, 3);
    EXPECT_EQ(transposed.getSize().second, 2);

    EXPECT_EQ(transposed(0, 0), 1);
    EXPECT_EQ(transposed(0, 1), 4);
    EXPECT_EQ(transposed(1, 0), 2);
    EXPECT_EQ(transposed(1, 1), 5);
    EXPECT_EQ(transposed(2, 0), 3);
    EXPECT_EQ(transposed(2, 1), 6);
}

TEST(MatrixTransposeTest, TransposeSquareMatrix) {
    matrix<int> mat(3, 3);
    mat(0, 0) = 1; mat(0, 1) = 2; mat(0, 2) = 3;
    mat(1, 0) = 4; mat(1, 1) = 5; mat(1, 2) = 6;
    mat(2, 0) = 7; mat(2, 1) = 8; mat(2, 2) = 9;

    matrix<int> transposed = mat.getTranspose();

    EXPECT_EQ(transposed.getSize().first, 3);
    EXPECT_EQ(transposed.getSize().second, 3);

    EXPECT_EQ(transposed(0, 0), 1);
    EXPECT_EQ(transposed(0, 1), 4);
    EXPECT_EQ(transposed(0, 2), 7);
    EXPECT_EQ(transposed(1, 0), 2);
    EXPECT_EQ(transposed(1, 1), 5);
    EXPECT_EQ(transposed(1, 2), 8);
    EXPECT_EQ(transposed(2, 0), 3);
    EXPECT_EQ(transposed(2, 1), 6);
    EXPECT_EQ(transposed(2, 2), 9);
}

TEST(MatrixTransposeTest, TransposeOfTransposeEqualsOriginal) {
    matrix<int> mat(3, 2);
    mat(0, 0) = 1; mat(0, 1) = 2;
    mat(1, 0) = 3; mat(1, 1) = 4;
    mat(2, 0) = 5; mat(2, 1) = 6;

    matrix<int> transposed = mat.getTranspose();
    matrix<int> doubleTransposed = transposed.getTranspose();

    EXPECT_EQ(doubleTransposed.getSize().first, mat.getSize().first);
    EXPECT_EQ(doubleTransposed.getSize().second, mat.getSize().second);

    for (size_t i = 0; i < mat.getSize().first; ++i)
        for (size_t j = 0; j < mat.getSize().second; ++j)
            EXPECT_EQ(doubleTransposed(i, j), mat(i, j));
}

TEST(MatrixTransposeTest, TransposeEmptyMatrix) {
    matrix<int> mat;
    matrix<int> transposed = mat.getTranspose();

    EXPECT_EQ(transposed.getSize().first, 0);
    EXPECT_EQ(transposed.getSize().second, 0);
}