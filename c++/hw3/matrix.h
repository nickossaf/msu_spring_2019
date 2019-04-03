#include<iostream>
#include<cstdlib>
#include<vector>
#include<stdexcept>

class Row{
public:
    unsigned const int len;
    int* data;

    Row(unsigned int l = 1, int* beginP = nullptr):
        len(l),
        data(beginP){}

    const int& operator[](unsigned int i) const{
        if(i >= len) throw std::out_of_range("");
        return data[i];
    }

    int& operator[](unsigned int i){
        if(i >= len) throw std::out_of_range("");
        return data[i];
    }
};

class Matrix{
public:
    unsigned const int rows;
    unsigned const int columns;
    int* data;

    Matrix(unsigned int rw = 1, unsigned clmn = 1):
        rows(rw),
        columns(clmn),
        data(new int[rows * columns]){}

    ~Matrix(){
        delete[] data;
    }

    unsigned int getRows(){
        return rows;
    }

    unsigned int getColumns(){
        return columns;
    }

    bool operator==(const Matrix& matrix) const{
        if(this == &matrix)
            return true;

        if(rows != matrix.rows || columns != matrix.columns)
			return false;

        for(int i = 0; i < rows; i++)
            for(int j = 0; j < columns; j++)
                if (data[i * columns + j] != matrix[i][j])
                    return false;

        return true;
    }

    bool operator!=(Matrix& matrix) const{
        return !(*this == matrix);
    }

    const Matrix& operator*=(int number){
        for(int i = 0; i < rows; i++)
            for(int j = 0; j < columns; j++)
                data[i * columns + j] *= number;

        return *this;
    }

    const Row operator[](unsigned int i) const{
        if(i >= rows) throw std::out_of_range("");
        Row r(columns, data + i * columns);
        return r;
    }

    Row operator[](unsigned int i){
        if(i >= rows) throw std::out_of_range("");
        Row r(columns, data + i * columns);
        return r;
    }
};

