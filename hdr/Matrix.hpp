/**
 * @file    Matrix.hpp
 * @brief   Matrix class header
 *
 * @author  Tiago Pereira Vidigal
 * @version 1.3
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
 * 1.3      2016/11/21  TVIDIGAL     Added Doxygen comments
 *
 *----------------------------------------------------------------------------*/

#ifndef MATRIX_H_
#define MATRIX_H_

#include "PID_constants.hpp"
#include <stdlib.h>

using namespace std;

///Model a matrix and operations
class Matrix {

	public:

		///Copy constructor
		Matrix(const Matrix& matrix);

		/**
		 * @brief  Constructor of a zero matrix
		 * @param  numRow  The number of rows
		 * @param  numCol  The number of columns
		 */
		Matrix(int numRow, int numCol);

		/**
		 * @brief  Constructor of a initialized matrix
		 * @param  numRow  The number of rows
		 * @param  numCol  The number of columns
		 * @param  init    Initial values
		 */
		Matrix(int numRow, int numCol, float_pid* init);

		///Default desctructor
		~Matrix();

		/**
		 * @brief  Fill the matrix with values
		 * @param  values  The values
		 */
		void fill(float_pid *values);

		/**
		 * @brief  Fill the matrix with values
		 * @param  values  The values
		 */
		void fill(const Matrix *values);

		/**
		 * @brief   Read a value
		 * @param   x  Number of the row
		 * @param   y  Number of the column
		 * @return  Value read
		 */
		float_pid read(int x, int y) const;

		/**
		 * @brief   Write a value
		 * @param   x  Number of the row
		 * @param   y  Number of the column
		 * @param   value Value to write
		 */
		void write(int x, int y, float_pid value);

		/**
		 * @brief   Gets the number of columns.
		 * @return  The number of columns.
		 */
		int getNumCols() const ;

		/**
		 * @brief   Gets the number of rows.
		 * @return  The number of rows.
		 */
		int getNumRows() const ;

		/**
		 * @brief  Make a matrix product
		 * @param  mult Matrix to multiply
		 * @return Return resulting matrix or the original matrix if error
		 */
		Matrix product(Matrix mult);

		/**
		 * @brief  Make a matrix sum
		 * @param  sum Matrix to add
		 * @return Return resulting matrix or the original matrix if error
		 */
		Matrix sum(Matrix sum);

		/**
		 * @brief  Multiply each element of the matrix
		 * @param  mult Value to multiply
		 * @return Return resulting matrix
		 */
		Matrix productElem(float_pid mult);

		///Assignment operator for Matrix
		Matrix& operator=(const Matrix& arg);

	private:

		///Pointer to the values of the Matrix
		float_pid** values;

		///Number of rows
		int numRows;

		///Number of columns
		int numColumns;

		///Allocate space at memory for the Matrix
		void allocate(int numRow, int numCol);

		///Deallocate space at memory
		void deallocate();
};

#endif /* MATRIX_H_ */