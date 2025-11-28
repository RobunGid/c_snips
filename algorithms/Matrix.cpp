#include <iostream>
#include <iomanip>

class matrix {
	int **values;
	int rows, cols;
	public:
		matrix(int rows_arg = 0, int cols_arg = 0) {
			values = new int*[rows_arg];
			rows = rows_arg;
			cols = cols_arg;
			for (int i = 0; i < rows; i++) {
				values[i] = new int[cols];
				for (int j = 0; j < cols; j++) {
					values[i][j] = 0;
				}
			}
		}
		void in(void) {
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					std::cout << this << ": matrix[" << i+1 << "][" << j+1 << "] = ";
					std::cin >> values[i][j];
				}
			}
		}
		void out(void) {
			std::cout << this << ": " << std::endl;
			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					std::cout << std::right << std::setw(3) << values[i][j] << " ";
				}
				std::cout << std::endl;
			}
		}
		~matrix() {
			for (int i = 0; i < rows; i++) {
				delete[] values[i];
			}
			delete[] values;
		}
		friend matrix operator*(const matrix&, const matrix&);
};

matrix operator *(const matrix& matrix_first_arg, const matrix& matrix_second_arg) {
	matrix res(matrix_first_arg.rows, matrix_second_arg.cols);
	if (matrix_first_arg.cols != matrix_second_arg.rows) {
		std::cout << "No result" << std::endl;
		return res;
	}
	for (int i = 0; i < matrix_first_arg.rows; i++) {
		for (int j = 0; j < matrix_second_arg.cols; j++) {
			res.values[i][j] = 0;
			for (int k = 0; k < matrix_first_arg.cols; k++) {
				res.values[i][j] += matrix_first_arg.values[i][k] * matrix_second_arg.values[k][j];
			}
		}
	}
	return res;
}