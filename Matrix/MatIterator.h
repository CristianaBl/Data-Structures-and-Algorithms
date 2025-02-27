#include <tuple>
typedef int TElem;
#ifndef MATRIX_MATITERATOR_H
#define MATRIX_MATITERATOR_H
class MatrixIteratorByRow {
private:
    int currentIndex;
    tuple<int, int, TElem>* array;

public:
    MatrixIteratorByRow(tuple<int, int, TElem>* array) ;
    TElem next();
    bool hasNext() const;
};

class MatrixIteratorByColumn {
private:
    tuple<int, int, TElem>* array;
    int currentLine;
    int currentColumn;
public:
    MatrixIteratorByColumn(const tuple<int, int, TElem> *array);
    TElem next();
    bool hasNext() const;
};