#include <iostream>

using namespace std;

class DoubleIntClass {
private:
	int **double_matrix;
	int matrix_length;
	int matrix_width;
public:
	DoubleIntClass();
	DoubleIntClass(int, int);
	~DoubleIntClass();
	void ShowMatrix();

	operator int() { return (matrix_length * matrix_width); } // оператор преобразования типа

	int *operator[](int i) { return double_matrix[i]; } //Перегрузка индексации элемента

	DoubleIntClass& operator=(DoubleIntClass &arrInt2) { //перегрузка оператора присваивания
		delete[] double_matrix;

		matrix_length = arrInt2.matrix_length;
		matrix_width = arrInt2.matrix_width;

		double_matrix = new int*[matrix_length];
		for (int i = 0; i < matrix_width; i++) {
			double_matrix[i] = new int[matrix_width];
		}
		for (int i = 0; i < matrix_length; i++) {
			for (int j = 0; j < matrix_width; j++) {
				double_matrix[i][j] = arrInt2.double_matrix[i][j];
			}
		}
		return *this;
	}
	
	friend bool operator ==(DoubleIntClass &arrInt, DoubleIntClass &arrInt2); //перегрузка ==

	friend ostream& operator<<(ostream&, const DoubleIntClass&); //перегрузка оператора вывода в поток

	void *operator new(size_t size){ //перегрузка new
		DoubleIntClass* res = (DoubleIntClass*)malloc(sizeof(DoubleIntClass)*size);
		return res;
	}

	void operator delete(void *p) { free(p); } // перегрузка оператора delete


	DoubleIntClass operator+(DoubleIntClass &arrInt){
		int s;
		s = arrInt[0][0] + arrInt[0][1] + arrInt[1][0] + arrInt[1][1];
		cout << s << "\n\n";
		return DoubleIntClass();
	}
	DoubleIntClass operator-(DoubleIntClass &arrInt) {
		int s;
		s = arrInt[0][0] - arrInt[0][1] - arrInt[1][0] - arrInt[1][1];
		cout << s << "\n\n";
		return DoubleIntClass();
	}

	int operator++(int) {
		if (matrix_width < matrix_length - 1)
			++matrix_length;
		return matrix_length;
	}
	int operator--(int) {
		if (matrix_width > 0)
			--matrix_width;
		return matrix_width;
	}

	int operator>(const DoubleIntClass&) {
		if (matrix_length > matrix_width) {
			return matrix_length;
		}
		else {
			return matrix_width;
		}
	}
	int operator<(const DoubleIntClass&) {
		if (matrix_length < matrix_width) {
			return matrix_width;
		}
		else {
			return matrix_length;
		}
	}
};


ostream& operator<<(ostream& os, const DoubleIntClass& arr) {
	if (arr.double_matrix) {
		for (int i = 0; i<arr.matrix_length; ++i) {
			cout << arr.double_matrix[i] << " ";
		}
	}
	return os;
}


bool operator == (DoubleIntClass &arrInt, DoubleIntClass &arrInt2)
{
	if (arrInt.matrix_length != arrInt2.matrix_length){ //сравниваем размеры массивов объектов
		cout << "The number of rows are not the same\n";
		return 0;
	}
	if (arrInt.matrix_width != arrInt2.matrix_width) { //сравниваем размеры массивов объектов
		cout << "The number of columns are not the same\n";
		return 0;
	}
	else { //проверяем равны ли данныев в ячейках массивов
		for (int i = 0; i < arrInt.matrix_length; i++) {
			for (int j = 0; j < arrInt.matrix_width; j++) {
				if (arrInt.double_matrix[i][j] != arrInt2.double_matrix[i][j]) {
					cout << "Values are not equal\n";
					return 0;
				}
			}
		}
	}
	return 1;
}


DoubleIntClass::DoubleIntClass() {
	double_matrix = 0;
	matrix_length = 0;
	matrix_width = 0;
}


DoubleIntClass::DoubleIntClass(int l, int w) {
	matrix_length = l;
	matrix_width = w;
	double_matrix = new int*[l];
	if (double_matrix == nullptr) {
		std::cout << "No free memory!";
		return;
	}
	for (int i = 0; i < w; i++) {
		double_matrix[i] = new int[w];
		if (double_matrix[i] == nullptr) {
			for (int z = i - 1; z >= 0; z--) {
				delete double_matrix[z];
			}
			delete[] double_matrix;
			std::cout << "No free memory!";
			return;
		}
	}
}


DoubleIntClass::~DoubleIntClass() {
	for (int i = 0; i < matrix_width; i++) {
		delete[] double_matrix[i];
	}
	delete[] double_matrix;
}


void DoubleIntClass::ShowMatrix() {
	std::cout << '\n';
	for (int i = 0; i < matrix_length; i++) {
		for (int j = 0; j < matrix_width; j++) {
			std::cout << " " << double_matrix[i][j];
		}
		std::cout << endl;
	}
	std::cout << endl;
}


int main() {
	DoubleIntClass ArrayInt(2,2);    //создаем объект класса и записываем в него данные
	ArrayInt[0][0] = 1; //перегруженный []
	ArrayInt[0][1] = 2;
	ArrayInt[1][0] = 3;
	ArrayInt[1][1] = 4;
	cout << "ArrayInt:  ";
	ArrayInt.ShowMatrix();    //вывод данных массива на экран

	DoubleIntClass ArrayInt2(2,2); //создаем второй объект класса
	ArrayInt2[0][0] = 11; //перегруженный []
	ArrayInt2[0][1] = 22;
	ArrayInt2[1][0] = 33;
	ArrayInt2[1][1] = 44;
	cout << "ArrayInt2: ";
	ArrayInt2.ShowMatrix();   //вывод данных массива на экран

	if (ArrayInt == ArrayInt2) { //сравнение двух объектов класса (перегруженный ==)
		cout << "ArrayInt and ArrayInt2 are the same\n";
	}
	else {
		ArrayInt = ArrayInt2;
	}

	cout << "ArrayInt after copying:  ";
	ArrayInt.ShowMatrix();

	DoubleIntClass ArrayInt3(2,2); // третий объект класса с массивом из 4 элементов
	cout << "ArrayInt3: ";
	ArrayInt3.ShowMatrix();
	ArrayInt3 = ArrayInt2; // копируем массив из ArrayInt2 в ArrayInt3
	cout << "ArrayInt3 after copying: \n";
	ArrayInt3.ShowMatrix();

	cout << "Sum : ";
	cout << ArrayInt + ArrayInt;
	
	cout << "Difference : ";
	cout << ArrayInt - ArrayInt;

	cout << "Analysis : ";
	cout << ArrayInt++ << " ";
	cout << ArrayInt-- << "\n";

	cout << "Comparison between lines and columns : ";
	cout << (ArrayInt > ArrayInt);
	cout << " - ";
	cout << (ArrayInt < ArrayInt);
	cout << "\n";

	int A = ArrayInt; // преобразование типа
	cout << "Type conversion: " << A << "\n";

	system("pause");
	return 0;
}
