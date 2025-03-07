#pragma once
using namespace std;
#include <tuple>
#include <stdexcept>
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

class Matrix {

private:
	int nr_lines;
    int nr_cols;
    int dim;//cate elem am la un moment dat
    int capacity;// capacity von array
    tuple<int, int, TElem>* array;//array von tupeln

public:

	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

    void resizeUp();

    void resizeDown();


	// destructor
	~Matrix();

};
