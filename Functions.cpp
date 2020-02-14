#include "Functions.h"

void flush()
{
	cin.clear();
	while (cin.get() != '\n');
}

int menu()
{
	int key = 0;
	int code;

	do {
		system("cls");

		key = (key + 5) % 5;

		if (key == 0) cout << "-> Add the word" << endl;
		else  cout << "   Add the word" << endl;
		if (key == 1) cout << "-> Find the word" << endl;
		else  cout << "   Find the word" << endl;
		if (key == 2) cout << "-> Change the word" << endl;
		else  cout << "   Change the word" << endl;
		if (key == 3) cout << "-> Delete the word" << endl;
		else  cout << "   Delete the word" << endl;
		if (key == 4) cout << "-> Exit" << endl;
		else cout << "   Exit" << endl;

		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}

	} while (code != 13);
	system("cls");
	return key;
}





int menuchange()
{
	int key = 0;
	int code;

	do {
		system("cls");

		cout << "What do u want to change ?" << endl;

		key = (key + 3) % 3;

		if (key == 0) cout << "-> English word" << endl;
		else  cout << "   English word" << endl;
		if (key == 1) cout << "-> Ukrainian translate" << endl;
		else  cout << "   Ukrainian translate" << endl;
		if (key == 2) cout << "-> Nothing" << endl;
		else  cout << "   Nothing" << endl;

		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}

	} while (code != 13);
	system("cls");
	return key;
}





int menudelete()
{
	int key = 0;
	int code;

	do {
		system("cls");

		cout << "What do u want to delete ?" << endl;

		key = (key + 3) % 3;

		if (key == 0) cout << "-> All translates" << endl;
		else  cout << "   All translates" << endl;
		if (key == 1) cout << "-> One translate" << endl;
		else  cout << "   One translate" << endl;
		if (key == 2) cout << "-> Nothing" << endl;
		else  cout << "   Nothing" << endl;

		code = _getch();
		if (code == 224)
		{
			code = _getch();
			if (code == 80) key++;
			if (code == 72) key--;
		}

	} while (code != 13);
	system("cls");
	return key;
}





char* newword(const char* text, char* word)
{
	while (true)
	{
		cout << text << endl;

		cin.getline(word, 15);
		if (cin.fail())
		{
			flush();
			system("cls");
			cout << "Incorrect input" << endl;
			continue;
		}

		bool ret = false;

		for (int i = 1; i < 16; i++)
		{
			if (word[i] != ' ' && word[i - 1] == ' ')
			{
				ret = true;
				break;
			}
		}
		for (int i = 0; i < 16; i++)
		{
			if (!isalpha(word[i]) && word[i] != '\0' && (word[i] < 'À' || word[i] > 'ÿ') && word[i] != '¿' && word[i] != 'º' && word[i] != '³' && word[i] != '¯' && word[i] != 'ª' && word[i] != '²')
			{
				ret = true;
				break;
			}
		}
		if (word[0] == '\0')
		{
			system("cls");
			continue;
		}
		if (ret == true)
		{
			system("cls");
			cout << "Incorrect input" << endl;
			continue;
		}

		break;
	}

	return word;
}





void Add()
{
	Word word = {};

	newword("Enter the english word (Up to 15 leters) to add it in the base", word.eng);

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	newword("Enter the ukrainian translate (Up to 15 leters) to add it in the base", word.ukr);

	FILE* file = fopen("Words.bin", "ab");

	fwrite(&word, sizeof(Word), 1, file);

	fclose(file);

	cout << "Successfully added" << endl;
}




void Find()
{
	while (true)
	{
		cout << "Enter the word to find" << endl;

		Word word;

		cin.getline(word.eng, 15);
		if (cin.fail())
		{
			flush();
			system("cls");
			continue;
		}

		if (word.eng[0] == '\0')
		{
			system("cls");
			continue;
		}

		bool ret = false;

		for (int i = 1; i < 16; i++)
		{
			if (word.eng[i] != ' ' && word.eng[i - 1] == ' ')
			{
				ret = true;
				break;
			}
		}

		if (ret == true)
		{
			cout << "There is no such a word" << endl;
			break;
		}

		try
		{
			FILE* file = fopen("Words.bin", "rb");

			int temp = 0;

			while (feof(file) == 0)
			{
				Word findword;

				fread(&findword, sizeof(Word), 1, file);
				if (feof(file) != 0)
				{
					break;
				}
				if (strcmp(word.eng, findword.eng) == 0)
				{
					temp++;
				}
			}

			if (temp == 0)
			{
				cout << "There is no such a word" << endl;
				break;
			}

			fclose(file);

			Word* words = new Word[temp];

			file = fopen("Words.bin", "rb");

			int i = 0;

			while (feof(file) == 0)
			{
				Word findword;

				fread(&findword, sizeof(Word), 1, file);
				if (feof(file) != 0)
				{
					break;
				}
				if (strcmp(word.eng, findword.eng) == 0)
				{
					strcpy(words[i].ukr , findword.ukr);
					i++;
				}
			}

			fclose(file);

			for (int j = 0; j < temp; j++)
			{
				cout << words[j].ukr << '\t';
			}
			cout << endl;
		}
		catch (const std::exception& ex)
		{
			system("cls");
			cout << ex.what() << endl;
			cout << "Something wrong , try again" << endl;
			continue;
		}

		break;
	}
}





void Change()
{
	while (true)
	{
		cout << "Enter the word to change" << endl;

		Word word;

		cin.getline(word.eng, 15);
		if (cin.fail())
		{
			flush();
			system("cls");
			continue;
		}

		if (word.eng[0] == '\0')
		{
			system("cls");
			continue;
		}

		bool ret = false;

		for (int i = 1; i < 16; i++)
		{
			if (word.eng[i] != ' ' && word.eng[i - 1] == ' ')
			{
				ret = true;
				break;
			}
		}

		if (ret == true)
		{
			cout << "There is no such a word" << endl;
			break;
		}

		try
		{
			FILE* file = fopen("Words.bin", "rb");

			int temp = 0, all = 0;

			while (feof(file) == 0)
			{
				Word findword;

				fread(&findword, sizeof(Word), 1, file);
				if (feof(file) != 0)
				{
					break;
				}
				if (strcmp(word.eng, findword.eng) == 0)
				{
					temp++;
				}
				all++;
			}

			if (temp == 0)
			{
				cout << "There is no such a word" << endl;
				break;
			}

			fclose(file);

			Word* words = new Word[temp];
			Word* allwords = new Word[all];

			file = fopen("Words.bin", "rb");

			int i = 0;
			int k = 0;

			while (feof(file) == 0)
			{
				Word findword;

				fread(&findword, sizeof(Word), 1, file);
				if (feof(file) != 0)
				{
					break;
				}

				strcpy(allwords[k].eng, findword.eng);
				strcpy(allwords[k].ukr, findword.ukr);
				k++;

				if (strcmp(word.eng, findword.eng) == 0)
				{
					strcpy(words[i].eng, findword.eng);
					strcpy(words[i].ukr, findword.ukr);
					i++;
				}
			}

			fclose(file);

			for (int j = 0; j < temp; j++)
			{
				cout << words[j].ukr << '\t';
			}
			cout << endl;

			cout << "Type anything..." << endl;
			flush();

			int answer = menuchange();

			char wordnew[16] = {};
			char wordold[16] = {};
			i = 0;
			bool exist = false;

			switch (answer)
			{
			case 0:
				system("cls");

				newword("Enter the changed english word", wordnew);

				file = fopen("Words.bin", "wb");

				for (int j = 0; j < all; j++)
				{
					if (strcmp(word.eng, allwords[j].eng) == 0)
					{
						strcpy(allwords[j].eng, wordnew);
					}
					fwrite(&allwords[j], sizeof(Word), 1, file);
				}

				fclose(file);

				cout << "Changed" << endl;

				break;
			case 1:
				system("cls");

				SetConsoleCP(1251);
				SetConsoleOutputCP(1251);

				newword("Enter ukrainian translate u want to change", wordold);

				for (int j = 0; j < temp; j++)
				{
					if (strcmp(wordold, words[j].ukr) == 0)
					{
						i = j;
						exist = true;
						break;
					}
				}

				if (exist == true)
				{
					newword("Enter the new translate of a word", words[i].ukr);

					file = fopen("Words.bin", "wb");

					for (int j = 0; j < all; j++)
					{
						if (strcmp(words[i].eng, allwords[j].eng) == 0 && strcmp(wordold, allwords[j].ukr) == 0)
						{
							strcpy(allwords[j].ukr, words[i].ukr);
						}
						fwrite(&allwords[j], sizeof(Word), 1, file);
					}

					fclose(file);
					cout << "Successfully changed" << endl;
				}
				else
				{
					system("cls");
					cout << "There is no such a translate" << endl;
				}

				break;
			case 2:
				system("cls");
				cout << "Tap to continue" << endl;
				break;
			default :
				break;
			}

			if (answer == 2)
			{
				break;
			}
		}
		catch (const std::exception& ex)
		{
			system("cls");
			cout << ex.what() << endl;
			cout << "Something wrong , try again" << endl;
			continue;
		}

		break;
	}
}





void Delete()
{
	while (true)
	{
		cout << "Enter the word to delete" << endl;

		Word word;

		cin.getline(word.eng, 15);
		if (cin.fail())
		{
			flush();
			system("cls");
			continue;
		}

		if (word.eng[0] == '\0')
		{
			system("cls");
			continue;
		}

		bool ret = false;

		for (int i = 1; i < 16; i++)
		{
			if (word.eng[i] != ' ' && word.eng[i - 1] == ' ')
			{
				ret = true;
				break;
			}
		}

		if (ret == true)
		{
			cout << "There is no such a word" << endl;
			break;
		}

		try
		{
			FILE* file = fopen("Words.bin", "rb");

			int temp = 0, all = 0;

			while (feof(file) == 0)
			{
				Word findword;

				fread(&findword, sizeof(Word), 1, file);
				if (feof(file) != 0)
				{
					break;
				}
				if (strcmp(word.eng, findword.eng) == 0)
				{
					temp++;
				}
				all++;
			}

			if (temp == 0)
			{
				cout << "There is no such a word" << endl;
				break;
			}

			fclose(file);

			Word* words = new Word[temp];
			Word* allwords = new Word[all];

			file = fopen("Words.bin", "rb");

			int i = 0;
			int k = 0;

			while (feof(file) == 0)
			{
				Word findword;

				fread(&findword, sizeof(Word), 1, file);
				if (feof(file) != 0)
				{
					break;
				}

				strcpy(allwords[k].eng, findword.eng);
				strcpy(allwords[k].ukr, findword.ukr);
				k++;

				if (strcmp(word.eng, findword.eng) == 0)
				{
					strcpy(words[i].eng, findword.eng);
					strcpy(words[i].ukr, findword.ukr);
					i++;
				}
			}

			fclose(file);

			for (int j = 0; j < temp; j++)
			{
				cout << words[j].ukr << '\t';
			}
			cout << endl;

			cout << "Type anything..." << endl;
			flush();

			int answer = menudelete();
			char worddel[16] = {};
			bool exist = false;

			switch (answer)
			{
			case 0:
				file = fopen("Words.bin", "wb");

				for (int i = 0; i < all; i++)
				{
					if (strcmp(allwords[i].eng, word.eng) != 0)
					{
						fwrite(&allwords[i], sizeof(Word), 1, file);
					}
				}

				cout << "Deleted" << endl;

				fclose(file);

				break;
			case 1:
				system("cls");

				SetConsoleCP(1251);
				SetConsoleOutputCP(1251);

				newword("Enter ukrainian translate u want to delete", worddel);

				for (int i = 0; i < temp; i++)
				{
					if (strcmp(worddel, words[i].ukr) == 0)
					{
						exist = true;
						break;
					}
				}

				if (exist == false)
				{
					system("cls");
					cout << "There is no such a translate" << endl;
				}
				else
				{
					file = fopen("Words.bin", "wb");

					for (int i = 0; i < all; i++)
					{
						if (strcmp(allwords[i].eng, word.eng) == 0 && strcmp(allwords[i].ukr, worddel) == 0)
						{
							continue;
						}
						fwrite(&allwords[i], sizeof(Word), 1, file);
					}
					cout << "Deleted" << endl;

					fclose(file);
				}
				
				break;
			case 2:
				system("cls");
				cout << "Tap to continue" << endl;
				break;
			default:
				break;
			}
		}
		catch (const exception& ex)
		{
			cout << ex.what() << endl;
			cout << "Something wrong" << endl;
		}

		break;
	}
}