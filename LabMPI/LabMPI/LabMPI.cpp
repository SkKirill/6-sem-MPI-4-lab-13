#include <iostream>
#include <vector>
#include <mpi.h>
#include <string>
#include <random>
#include <iomanip>

using namespace std;

const int rows = 6; // Константы чтобы задавать везде одинаковую матрицу
const int cols = 6;

// Процедура printArray - выводит матрицу в консоль
void printArray(int array[rows][cols], int rows)
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << setw(4) << array[i][j];
		}
		cout << endl;
	}
	cout << endl;
}


int main(int argc, char* argv[]) {
	int rank, size;
	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	/*инициализируем матрицу*/
	int array[rows][cols]{};

	srand(time(NULL) + rank);
	if (rank == 0) {
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				array[i][j] = rand() % 100;
			}
		}
		printArray(array, rows);//вывод матрицы
	}

	/*
	для того чтобы построить свой тип нам нужно описать блоки

	буду рассказывать на примере матрицы 3*3
	1 2 3
	4 5 6
	7 8 9

	кароче есть массив блоков и массив мест начал

	например мы отим оставить только 1 строку. Нам нужно будет blocklengths[0] добавить количество столбцов и написать что начинается с первого символа(displacements[0] = 0;)
	вот так получится
	1 2 3
	0 0 0
	0 0 0

	если мы хотим сделать например квадратик с 0 внутри то нам нужено 2 блока.
	1 -> 1,2,3,4; потом пропускаем 1 символ и второй блок 2 -> 6,7,8,9

	как это реализовать.
	стартовые значения это 0 так как первый блок с самого начала и второе стартовое значение это количество столбцов *2 - 1(тоесть переход на конец 2 строки и на символ назад)
	и два блока длинной в 4. получится:
	1 2 3
	4 0 6
	7 8 9

	матрицы тут раворациваются поэтому лучше визуализировать вот так:

	1 2 3 4 5 6 7 8 9

	c нулевого четыре символа и с cols*2-1 четыре символа, а те элементы что не находятся в блоках трогаться не будут и будут нулями - так создается тип

	1 2 3 4 0 6 7 8 9

	*/


	int blocklengths[rows * 2]{}; // массив с длинами блоков
	for (int i = 0; i < rows * 2; i++)
	{
		blocklengths[i] = 1; // потом все блоки по 3 чтобы мы захватывали 1 элемент с каждой строки с конца и 2 элемента с начала
	}

	int disCh = cols / 2;
	int disNech = 0;
	int displacements[rows * 2]{}; // это унас места начал блоков 
	for (int i = 0; i < rows * 2; i++)
	{
		if (i % 2 == 0) {
			displacements[i] = disCh;
			disCh += cols;
		}
		else {
			displacements[i] = disNech;
			if (i < rows - 1) {
				disNech += cols + 1;
			}
			else {
				disNech += cols - 1;
			}

			if (rows % 2 == 0 && i == rows - 1) {
				disNech += 1;
			}
		}
	}
	MPI_Datatype MyDataType; // создаем свой тип

	//rows - кол-во элементов, blocklengths- массив длин блоков, displacements - массив где каждый блок начинается
	MPI_Type_indexed(rows * 2, blocklengths, displacements, MPI_INT, &MyDataType); //функция-конструктор нашего типа
	MPI_Type_commit(&MyDataType);//регистрирует созданный производный тип.

	if (rank == 0)
	{
		MPI_Send(array, 1, MyDataType, 1, 0, MPI_COMM_WORLD); // первым процессом отправляем нашу матрицу преобразованную в наш тип
	}
	else if (rank == 1) // Процесс с рангом 1 принимает данные, отправленные процессом с рангом 0, используя пользовательский тип данных MyDataType
	{
		printf("init:\n");
		printArray(array, rows);

		MPI_Recv(array, 1, MyDataType, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		
		printf("changes:\n");
		printArray(array, rows); // после чего выводим матрицу
	}

	MPI_Type_free(&MyDataType); //Освобождает ресурсы, связанные с пользовательским типом данных MyDataType.

	MPI_Finalize();
	return 0;
}

