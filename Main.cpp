#include "Functions.h"

int main()
{
	setlocale(LC_ALL, "");

	cout << "It's a universal eng-to-ukr translator! U can find here all english words that are in base." << endl;
	cin.get();
	system("cls");

	while (true)
	{
		bool exit = false;

		int choice = menu();

		switch (choice)
		{
		case 0:
			Add();
			flush();
			break;
		case 1:
			Find();
			flush();
			break;
		case 2:
			Change();
			flush();
			break;
		case 3:
			Delete();
			flush();
			break;
		case 4:
			exit = true;
			break;
		default:
			break;
		}

		if (exit == true)
		{
			break;
		}
	}
}

