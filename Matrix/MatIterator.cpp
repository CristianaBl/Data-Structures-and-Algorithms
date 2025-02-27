#include <stdexcept>
#include "MatIterator.h"

int MatrixIteratorByColumn::MatrixIteratorByColumn(const tuple<int, int, TElem> *array): array(array), currentLine(0), currentColumn(0) {}

int MatrixIteratorByRow::MatrixIteratorByRow(tuple<int, int, TElem> *array):array(array), currentIndex(0) {}

TElem MatrixIteratorByRow::next(){
    if (!hasNext()) {
        throw std::out_of_range("err");
    }
    TElem element = std::get<2>(array[currentIndex]);
    currentIndex++;
    return element;
}

bool MatrixIteratorByRow:: hasNext() const {
    return currentIndex < array.dim;
}

    TElem MatrixIteratorByColumn:: next() {
        if (!hasNext()) {
            throw std::out_of_range("err");
        }
        TElem element = std::get<2>(array[currentLine * nrColumns() + currentColumn]);
        currentLine++;
        if (currentLine == .nrLines()) {
            currentColumn++;
            currentLine = 0;
        }
        return element;
    }
    bool MatrixIteratorByColumn:: hasNext() const {
        return currentColumn < nrColumns() && currentLine < matrix.nrLines();
    }
}

