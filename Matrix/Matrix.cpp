#include "Matrix.h"
#include <exception>
#include <tuple>



Matrix::Matrix(int nrLines, int nrCols) {
	  nr_lines=nrLines;
      nr_cols=nrCols;
      capacity=10;
      dim=0;
      array=new tuple<int,int,TElem >[capacity];
}

//tetha(1)
int Matrix::nrLines() const {
	return nr_lines;

}

//tetha(1)
int Matrix::nrColumns() const {
	return nr_cols;

}
//WORST CASE: tetha(n), BEST CASE: tetha(1), AVERAGE CASE:o(n)
TElem Matrix::element(int i, int j) const
{
    if (i < 0 || i >= nr_lines || j < 0 || j >= nr_cols)
    {
        throw out_of_range("not a valid position");
    }
    for (int k = 0; k < dim; k++)
    {
        if (get<0>(array[k]) == i && get<1>(array[k]) == j)
        {
            return get<2>(array[k]);
        }
    }
    return NULL_TELEM;
}

void Matrix::resizeUp() {
    int newCapacity = capacity * 2;
    tuple<int, int, TElem> *newArray = new tuple<int, int, TElem>[newCapacity];
    for (int i = 0; i < dim; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}

void Matrix::resizeDown() {
    int newCapacity = capacity / 2;
    tuple<int, int, TElem> *newArray = new tuple<int, int, TElem>[newCapacity];
    for (int i = 0; i < dim; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
    capacity = newCapacity;
}


//WORST CASE: tetha(n), BEST CASE: tetha(1), AVERAGE CASE:o(n)
TElem Matrix::modify(int i, int j, TElem e)
{
    if (i < 0 || i >= nr_lines || j < 0 || j >= nr_cols) {
        throw invalid_argument("Invalid indices");
    }

    int indexEl = 0;
    while (indexEl < dim && (get<0>(array[indexEl]) < i || (get<0>(array[indexEl]) == i && get<1>(array[indexEl]) < j))) {
        ++indexEl;
    }

    TElem prevalue = NULL_TELEM;
    if (e == 0) {
        if (indexEl < dim && get<0>(array[indexEl]) == i && get<1>(array[indexEl]) == j) {
            prevalue = get<2>(array[indexEl]);
            for (int k = indexEl; k < dim - 1; ++k) {
                array[k] = array[k + 1];
            }
            --dim;
            //we verify if we need to resize down
            if (dim < capacity / 4) {
                resizeDown();
            }
        }
    } else {
        if (indexEl < dim && get<0>(array[indexEl]) == i && get<1>(array[indexEl]) == j) {
            prevalue = get<2>(array[indexEl]);
            get<2>(array[indexEl]) = e;
        } else {
            if (dim == capacity) {
                resizeUp();
            }

            if (indexEl < dim) {
                for (int k = dim; k > indexEl; --k) {
                    array[k] = array[k - 1];
                }
            }
            get<0>(array[indexEl]) = i;
            get<1>(array[indexEl]) = j;
            get<2>(array[indexEl]) = e;
            ++dim;
        }
    }

    return prevalue;
}


Matrix::~Matrix()
{
    delete[] array;
}


