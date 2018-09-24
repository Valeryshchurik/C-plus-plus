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
	fout << "����� �� " << (code == 1 ? "�������������" : "�����������") << " �������\n\n";
	mystruct ord;
	while (fin.read((char*)&ord, sizeof(ord)))
	{
		fout << "��� ������: " << ord.code << endl;
		fout << "��� ������: " << ord.name << endl;
		fout << "���� ������: " << ord.price << endl;
		fout << "���������� ������: " << (code == 1 ? ord.sold : ord.left) << endl;
		fout << "����� ��������� ������: " << ord.price * (code == 1 ? ord.sold : ord.left) << endl << endl;
	}
}