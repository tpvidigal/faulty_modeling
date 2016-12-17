/**
 * @file    Matrix.cpp
 * @brief   Matrix class source
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.2
 *
 */
/*------------------------------------------------------------------------------
 *
 * History
 *
 * Version  Date        Author       Note
 * 1.0      2016/09/17  TVIDIGAL     Document created.
 * 1.1      2016/09/21  TVIDIGAL     Changed parameter of methods from
 *                                   float_pid** to float_pid for some strange
 *                                   error (invalid address accesses with []).
 * 1.2      2016/10/02  TVIDIGAL     Create a constructor that uses a Matrix
 *                                   and making other corrections
 *
 *----------------------------------------------------------------------------*/

#include "../hdr/Matrix.hpp"


/* Public ********************************************************************/

Matrix::Matrix(const Matrix& matrix) {
	this->numRows = matrix.getNumRows();
	this->numColumns = matrix.getNumCols();
	this->allocate(this->numRows, this->numColumns);
	this->fill(&matrix);
}

Matrix::Matrix(int numRow, int numCol) {
	this->allocate(numRow, numCol);
}

Matrix::Matrix(int numRow, int numCol, float_pid* init) {
	allocate(numRow, numCol);
	this->fill(init);
}

Matrix::~Matrix() {
	deallocate();
}

void Matrix::fill(float_pid* values) {
	for(int i=0; i<numRows; i++)
		for(int j=0; j<numColumns; j++) 
			this->values[i][j] = values[i*numColumns+j];
}

void Matrix::fill(const Matrix *values) {
	for(int i=0; i<numRows; i++)
		for(int j=0; j<numColumns; j++) 
			this->values[i][j] = values->read(i,j);
}

float_pid Matrix::read(int x, int y) const {
	return this->values[x][y];
}

void Matrix::write(int x, int y, float_pid value) {
	this->values[x][y] = value;
}

int Matrix::getNumCols() const {
	return this->numColumns;
}

int Matrix::getNumRows() const {
	return this->numRows;
}

Matrix Matrix::product(Matrix mult) {

	//Check if it's a valid multiplication
	if( numColumns != mult.getNumRows() )
		return *this;

	//Initializations
	Matrix result(numRows, mult.getNumCols());

	//Multiplication
	for(int i=0; i<numRows; i++) {
		for(int j=0; j<mult.getNumCols(); j++)
			for(int x=0; x<mult.getNumRows(); x++)
				result.write(i, j, result.read(i,j) + (this->read(i,x) * mult.read(x,j)));
	}

	return result;
}

Matrix Matrix::sum(Matrix sum) {

	//Check if it's a valid sum
	if( numColumns != sum.getNumCols() &&
		numRows    != sum.getNumRows()    )
		return *this;

	Matrix result(numRows, numColumns);

	//Sum
	for(int i=0; i<numRows; i++)
		for(int j=0; j<numColumns; j++) 
			result.write(i, j, this->read(i,j) + sum.read(i,j));

	return result;
}

Matrix Matrix::productElem(float_pid mult){

	Matrix result(numRows, numColumns);

	//Multiplication
	for(int i=0; i<numRows; i++)
		for(int j=0; j<numColumns; j++)
			result.write(i, j, this->read(i,j) * mult);

	return result;
}


/* Private ********************************************************************/

void Matrix::allocate(int numRow, int numCol) {

	this->values = (float_pid**) calloc(numRow, sizeof(float_pid*));
	for(int i=0; i<numRow; i++)
		this->values[i] = (float_pid*) calloc(numCol, sizeof(float_pid));

	this->numRows = numRow;
	this->numColumns = numCol;
}

void Matrix::deallocate() {
	for(int i=0; i<numRows; i++)
		delete[] values[i];
	delete[] values;
}
