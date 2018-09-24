#include <iostream>
#include <fstream>
struct mystruct
{
	int code;
	char* name;
	double price;
	int sold;
	int left;
};
using namespace std;

int main(int argc, char *argv[])
{
	if (argc < 4)
	{
		cout << "Error: there must be 3 command arguments\n";
		getchar();
		return 0;
	}
	int code = atoi(argv[3]);
	if (code != 1 && code != 2)
	{
		cout << "Error: illegal report code\n";
		getchar();
		return 0;
	}

	ifstream fin(argv[1], ios::binary | ios::in);
	ofstream fout(argv[2], ios::out);
	fout << "Отчёт по " << (code == 1 ? "реализованным" : "непроданным") << " товарам\n\n";
	mystruct ord;
	while (fin.read((char*)&ord, sizeof(ord)))
	{
		fout << "Код товара: " << ord.code << endl;
		fout << "Имя товара: " << ord.name << endl;
		fout << "Цена товара: " << ord.price << endl;
		fout << "Количество товара: " << (code == 1 ? ord.sold : ord.left) << endl;
		fout << "Общая стоимость товара: " << ord.price * (code == 1 ? ord.sold : ord.left) << endl << endl;
	}
}