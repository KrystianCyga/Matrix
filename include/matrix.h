#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <stdexcept>
#include <utility>
#include <math.h>
#include <type_traits> 



template <typename T>
class matrix
{
    static_assert(std::is_same<T, int>::value || std::is_same<T, double>::value,
                  "matrix can only be used with int or double");

private:
    std::vector<std::vector<T>> _data;
    std::pair<int, int> _size;

public:
    matrix() : _data(), _size(0, 0) {}
    matrix(int n);
    matrix(int n, int m);
    matrix(std::pair<int, int>);
    matrix(const matrix<T> &other);
    matrix(matrix<T>&& other) noexcept;
    ~matrix() {}

    void setMatrixElem(int n, int m, T value);
    T getMatrixElem(int n, int m) const;
    std::pair<int, int> getSize() const;
    bool ifSameSize(const matrix<T> &matrix1, const matrix<T> &matrix2);
    void swap(matrix<T> &other) noexcept;

    matrix<T> &operator=(const matrix<T> &other);
    matrix<T> operator+(const matrix<T> &other);
    matrix<T> operator-(const matrix<T> &other);
    matrix<T> &operator=(matrix<T> &&other) noexcept;
    bool operator==(const matrix<T> &other);
    T& operator()(int row, int col);
    const T& operator()(int row, int col) const;

    matrix<T> getPartCopy(int remx, int remy);

    T getDeterminant();

    matrix<T> getTranspose();
};

// Definicje metod

template <typename T>
matrix<T>::matrix(int n)
{
    _data.resize(n, std::vector<T>(n, 0));
    _size = std::make_pair(n, n);
}

template <typename T>
matrix<T>::matrix(int n, int m) 
    : _data(n, std::vector<T>(m, 0)), _size(n, m) {}

template <typename T>
matrix<T>::matrix(std::pair<int, int> nSize)
{
    _data.resize(nSize.first, std::vector<T>(nSize.second, 0));
    _size = nSize;
}

template <typename T>
matrix<T>::matrix(const matrix<T> &other) : _data(other._data), _size(other._size) {}

template <typename T>
matrix<T>::matrix(matrix<T>&& other) noexcept{

    _data = std::move(other._data);
    _size = other._size;
    other._size = {0, 0};

}

template <typename T>
void matrix<T>::setMatrixElem(int n, int m, T value)
{
    if (n < 0 || n >= _data.size() || m < 0 || m >= _data[n].size())
    {
        throw std::out_of_range("Index out of range");
    }
    _data[n][m] = value;
}

template <typename T>
T matrix<T>::getMatrixElem(int n, int m) const
{
    if (n < 0 || n >= _data.size() || m < 0 || m >= _data[n].size())
    {
        throw std::out_of_range("Index out of range");
    }
    return _data[n][m];
}

template <typename T>
void matrix<T>::swap(matrix<T> &other) noexcept
{
    using std::swap;
    swap(this->_data, other._data);
    swap(this->_size, other._size);
}

template <typename T>
bool matrix<T>::operator==(const matrix<T> &other)
{
    if (_data.size() != other._data.size())
    {
        return false; // Rozmiary są różne
    }

    for (size_t i = 0; i < _data.size(); i++)
    {
        if (_data[i].size() != other._data[i].size())
        {
            return false; // Rozmiary są różne
        }

        for (size_t j = 0; j < other._data[i].size(); j++)
        {
            if (_data[i][j] != other._data[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
matrix<T> &matrix<T>::operator=(const matrix<T> &other)
{
    if (this != &other)
    {
        matrix<T> temp(other); 
        swap(temp);           

    }
    return *this;
}

template <typename T>
std::pair<int, int> matrix<T>::getSize() const
{
    return _size;
}

template <typename T>
matrix<T> matrix<T>::operator+(const matrix<T> &other)
{
    if (this->_data.empty() || other._data.empty()) {
        throw std::invalid_argument("Cannot add empty matrices.");
    }

    if (this->_size != other._size)
    {
        throw std::invalid_argument("Matrices must be of the same size for addition");
    }

    matrix<T> result(this->_data.size(), this->_data[0].size());

    for (size_t i = 0; i < this->_data.size(); ++i)
    {
        for (size_t j = 0; j < this->_data[i].size(); ++j)
        {
            result.setMatrixElem(i, j, this->_data[i][j] + other._data[i][j]);
        }
    }

    return result;
}

template <typename T>
T& matrix<T>::operator()(int row, int col)
{
    if (row < 0 || row >= _size.first || col < 0 || col >= _size.second) {
        throw std::out_of_range("Matrix indices out of range.");
    }
    return _data[row][col];
}

template <typename T>
matrix<T> matrix<T>::operator-(const matrix<T> &other)
{
    if (this->_data.empty() || other._data.empty()) {
        throw std::invalid_argument("Cannot subtract empty matrices.");
    }

    if (this->_size != other._size)
    {
        throw std::invalid_argument("Matrices must be of the same size for subtraction");
    }

    matrix<T> result(this->_data.size(), this->_data[0].size());

    for (size_t i = 0; i < this->_data.size(); ++i)
    {
        for (size_t j = 0; j < this->_data[i].size(); ++j)
        {
            result.setMatrixElem(i, j, this->_data[i][j] - other._data[i][j]);
        }
    }

    return result;
}

template <typename T>
const T& matrix<T>::operator()(int row, int col) const
{
    if (row < 0 || row >= _size.first || col < 0 || col >= _size.second) {
        throw std::out_of_range("Matrix indices out of range.");
    }
    return _data[row][col];
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const matrix<T> &m)
{

    for (size_t i = 0; i < m.getSize().first; ++i)
    {
        for (size_t j = 0; j < m.getSize().second; ++j)
        {
            os << m(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T>
matrix<T> &matrix<T>::operator=(matrix<T> &&other) noexcept
{
    if (this != &other)
    {
        swap(other);

    }
    return *this;
}

template <typename T>
bool matrix<T>::ifSameSize(const matrix<T> &matrix1, const matrix<T> &matrix2)
{
    return matrix1.getSize() == matrix2.getSize();
}

template <typename T>
matrix<T> matrix<T>::getPartCopy(int remRow, int remCol)
{
    // Sprawdzenie poprawności indeksów
    if (remRow < 0 || remRow >= _size.first || remCol < 0 || remCol >= _size.second) {
        throw std::out_of_range("Row or column to remove is out of range.");
    }

    matrix<T> minor(_size.first - 1, _size.second - 1);
    size_t minorRow = 0;

    for (size_t i = 0; i < _size.first; ++i) {
        if (i == remRow) continue; // Pomija wiersz do usunięcia
        size_t minorCol = 0;
        for (size_t j = 0; j < _size.second; ++j) {
            if (j == remCol) continue; // Pomija kolumnę do usunięcia
            minor(minorRow, minorCol) = _data[i][j];
            ++minorCol;
        }
        ++minorRow;
    }

    return minor;
}

template <typename T>
T matrix<T>::getDeterminant()
{
    // Sprawdzenie, czy macierz jest kwadratowa
    if (_size.first != _size.second) {
        throw std::invalid_argument("Matrix must be square to calculate determinant.");
    }

    size_t n = _size.first;

    if (n == 0) {
        throw std::invalid_argument("Cannot calculate determinant of a 0x0 matrix.");
    }

    if (n == 1) {
        return _data[0][0];
    }

    if (n == 2) {
        return (_data[0][0] * _data[1][1]) - (_data[0][1] * _data[1][0]);
    }

    T det = 0;
    for (size_t col = 0; col < n; ++col) {
        // Tworzenie minoru poprzez usunięcie pierwszego wiersza i bieżącej kolumny
        matrix<T> minor = getPartCopy(0, col);
        // Wzór Laplace'a: det = suma ( (-1)^(i+j) * a_ij * det(minor) )
        det += ((col % 2 == 0) ? 1 : -1) * _data[0][col] * minor.getDeterminant();
    }

    return det;
}

template <typename T>
matrix<T> matrix<T>::getTranspose()
{

    matrix<T> rev(this->getSize().second, this->getSize().first);

    for (size_t i = 0; i < this->getSize().first; i++)
    { 
        for (size_t j = 0; j < this->getSize().second; j++)
        {                                                      
            rev.setMatrixElem(j, i, this->getMatrixElem(i, j)); 
        }
    }

    return rev;
}

#endif // MATRIX_H
