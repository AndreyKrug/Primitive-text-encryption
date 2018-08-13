#include"Primitive_Enigma.h"
#include<conio.h>
#include<Windows.h>
void main() {
	srand(time(NULL));
	setlocale(LC_ALL, "rus");	
	Primitive_Enigma enigma;
	string vopros, otvet, message;
	char *buf = new char[1000];
	char action;
	do {
		system("cls");
		cout << "Выберите необходимое действие и нажмите соответствующую кнопку\n";
		cout << "1. Зашифровать сообщение\n";
		cout << "2. Расшифровать сообщение\n";
		cout << "Esc - выход из программы\n";
		action = _getch();
		switch (action) {
		case '1':
			system("cls");
			cout << "Вопрос и ответ задается на одно сообщение!\n";
			cout << "Введите секретный вопрос, ответ на который будет знать только ваш собеседник\n";
			cout << "Например: девичья фамилия матери и т.д.\n";
			getline(cin, vopros);
			cout << "Введите ответ на секретный вопрос: ";
			getline(cin, otvet);
			cout << "А теперь введите текст послания (для завершения ввода нажмите Enter:\n";
			getline(cin, message);
			enigma.Set_message(vopros, otvet, message);
			system("pause");
			break;
		case '2':
			system("cls");
			cout << "Поместите файлы message.txt и vopros.txt в директорию с программой\n";
			FILE *f_vopros;
			fopen_s(&f_vopros, "vopros.txt", "r");
			if (f_vopros != NULL) {
				fgets(buf, 1000, f_vopros);
				fclose(f_vopros);
				cout << buf << endl;
				cout << "Введите ответ на заданный выше вопрос: ";
				getline(cin, otvet);
				enigma.Show_message(otvet);
			}
			else cout << "Ошибка открытия файла с вопросом! Дальнейшая работа невозможна\n";
			Sleep(3000);
			break;
		}

	} while (action != 27);
	delete[]buf;
	system("pause");
}
