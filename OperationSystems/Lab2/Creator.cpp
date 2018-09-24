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
	if (argc < 2)
	{
		cout << "Error: there must be a command argument"<<endl;
		getchar();
		return 0;
	}

	ofstream fout(argv[1], ios::binary | ios::out);
	int notes;
	cout << "Enter the number of notes: ";
	cin >> notes;
		for (int i = 0; i < notes; i++)
		{
			mystruct ord;
			cout << "Enter the code: ";
			cin >> ord.code;
			cout << "Enter the name: ";
			cin.ignore();
			ord.name = new char[10];
			cin.getline(ord.name, 10);
			cout << "Enter the price: ";
			cin >> ord.price;
			cout << "How many goods were sold? ";
			cin >> ord.sold;
			cout << "How many goods left? ";
			cin >> ord.left;
			cout << endl;
			fout.write((char*)&ord, sizeof(ord));
			//delete ord;
		}
	fout.close();
}