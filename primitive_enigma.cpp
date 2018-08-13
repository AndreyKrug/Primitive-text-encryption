#include "Primitive_Enigma.h"



void Primitive_Enigma::del_probel(string & str){
	//удаление лишних пробелов в начале строки, между словами и в конце
	char prob = ' ';
	int i = 0;
	int k = 0;
	while (i < size(str)) {
		if (i == 0 && str[i] == prob) {
			str.erase(i, 1);
			continue;
		}
		if (str[i] == prob) k++;
		else k = 0;
		if (k > 1) {
			str.erase(i, 1);
			continue;
		}
		i++;
	}
}

char Primitive_Enigma::Cezar(char symb, int kol){
	//алгоритм Цезаря, в котором он использовал для шифрования сдвиг алфавита на 
	//определенное количество позиций.
	//данный алгоритм немного усложняю, добавив к стандартному количеству сдвигов (sdvig)
	//определенное количество сдвигов, величину типа int, которую получаю из значения текущего
	//времени (time(NULL))
	//соответственно одинаковый текст в разные моменты времени будет закодирован по разному
	const int sdvig = 3;
	const char prob = ' ';
	char tmp = prob;
	int i = 0;
	while (i < size_alphabet && symb != alphabet[i]) i++;
	if (i == size_alphabet) return tmp;
	else {
		int s = sdvig + kol; //если kol=0, сдвигов будет стандартное количество
		while (s) {
			if (i == size_alphabet) i = 0;
			i++;
			s--;
			
		}
		tmp = alphabet[i];
		return tmp;
	}
}

char Primitive_Enigma::AntiCezar(char symb, int kol){
	const int sdvig = 3;
	
	const char prob = ' ';
	char tmp = prob;
	int i = 0;
	while (i < size_alphabet && symb != alphabet[i]) i++;
	if (i == size_alphabet) return tmp;
	else {
		int s = sdvig + kol;
		while (s) {
			if (i == 0) i = size_alphabet - 1;
			i--;
			s--;
			
		}
		tmp = alphabet[i];
	}
	return tmp;
}

char Primitive_Enigma::random_symb(){
	return (alphabet[rand() % size_alphabet]);
}


Primitive_Enigma::Primitive_Enigma(){
	char prob = ' '; //пробел
	int i = 0;

	for (i = 0; i < 95; i++) {//символы пунктуации, цифры, английский алфавит(больш. и мал.буквы)
		alphabet += (char)(i + 32);
	}

	for (i = 0; i < 48; i++) {//большие буквы русс.алф.+часть малых букв русс.алф.
		alphabet += (char)(i + 128);
	}

	for (i = 0; i < 22; i++) {//малые буквы русс. алф.
		alphabet += (char)(i + 224);
	}

	alphabet += (char)(252);//символ №
}

void Primitive_Enigma::Set_message(string vopr, string &otv, string & message){
	const int sum = 33; //с 33 элемента в таблице ASCII начинаются символы пунктуации
	del_probel(otv);//удаление пробелов с ответа
	del_probel(message);//удаление лишних пробелов с сообщения
	const char prob = ' ';
	string slovo, vopros, otvet;
	string result;
	vopros = vopr;
	otvet = otv;
	int size_otvet = size(otvet);
	otv = "";//удаляю ответ с переменной, в которую вводил пользователь
	long l = time(NULL);
	int size_mas_int = 10; //размер массива int 
	int *mas = new int[size_mas_int];//массив под 10 элементов типа int, в который запишу
									//поциферно l 
	int i = 0, j = 0;
	
	while (i < size_mas_int) {
		mas[i] = l % 10; //запись в обратном порядке значения l (пример: l=1234 - 4321)
		l /= 10;
		i++;
	}
	int pribav = mas[1]; //количество прибавлений к каждой букве (вторая цифра с конца в l
						//или вторая с начала в mas)
	int k = 0;//переменная для движения по mas (который хранит значения времени)
			  //движение происходит с НАЧАЛА МАССИВА
	for (i = 0; i < size(otvet); i++) {//шифрую ответ на секретный вопрос 
		if (k == size_mas_int) k = 0;
		if (i == 0) {//в начале (до шифрования первой буквы), вставляю определенное количество
			//букв (сумма последних трех цифр из l или первых трех из mas)
			int sum = mas[0] + mas[1] + mas[2];
			for (j = 1; j < sum; j++) {
				result += random_symb();
			}
			result += Cezar(otvet[i],mas[k]);
		}
		else {
			for (j = 1; j < pribav; j++) {
				result += random_symb();
			}
			result += Cezar(otvet[i],mas[k]);
		}
		k++;
	}//конец шифрования секретного вопроса

	k = 0; //переменная для движения по mas (который хранит значения времени)
			  //движение происходит с КОНЦА МАССИВА (или с начала l)
	while (size(message) != 0) { //Шифрование непосредственно сообщения
								 //пока сообщение не пустое, вырываю по слову и кодирую
		i = 0;
		slovo = "";
		//переменная k (движение по mas) обнуляется ТОЛЬКО до начала шифрования сообщения (message)
		//каждое следующее слово будет зашифровано относительно длины предыдущего слова
		while (message[i] != prob && i<size(message)) {//Записываю слово, пока не встречу символ пробела
									//или не достигнут конец сообщения
			slovo += message[i];
			message.erase(i, 1); //из сообщения удаляю один символ (который уже записан в слово (slovo)
		}

		if (i < size(message)) {//если после удаления слова сообщение осталось не пустым
								//прибавляю к слову пробел (соотв.пробел в сообщении удаляю)
			slovo += (char)prob;
			message.erase(i, 1);
		}

		pribav = mas[0];//количество прибавлений к каждой букве (первая цифра с конца в l
						//или первая с начала в mas)

		for (i = 0; i < size(slovo); i++) {//шифрую слово 
			if (k == size_mas_int) k = 0; //если k достиг конца массива (mas) обнуляю его
			for (j = 1; j < pribav; j++) {//добавление символов, предшествующих 
										  //закодированной букве
				result += random_symb();
			}
			result += Cezar(slovo[i], mas[k]);//добавление закодированной буквы
			k++;
		}
	}
	
	//полученное время записыавется в шифрованном виде в сам конец сообщения
	//записывается в перевернутом виде относительно полученного времени (или в пямой последовательности
	//элементов mas
	for (i = 0; i < size_mas_int; i++) {//шифрование time (mas)
		//если текущее значение массива равно нулю, подсчитываем сумму всех элементов массива
		//и записываем в виде char
		//иначе, если элемент последний - записываем произведение текущего элемента на предыдущий 
		//иначе, записываем произведение текущего элемента на следующий
		//int sum = 33;// с 33 элемента в таблице ASCII начинаются символы пунктуации
		if (i + 1 == size_mas_int) {
			result += (char)(mas[i] * sum + sum);
		}
		else {
			result += (char)(mas[i] + mas[i + 1] + sum);
		}
	}
	result += (char)(size_otvet + sum);//запись размера ответа в конец сообщения
	FILE *f_vopros, *f_message;
	fopen_s(&f_vopros, "vopros.txt", "w");
	fopen_s(&f_message, "message.txt", "w");
	if (f_vopros != NULL && f_message!=NULL) {
		fputs(vopros.c_str(), f_vopros);
		fputs(result.c_str(), f_message);
		fclose(f_vopros);
		fclose(f_message);
		cout << "Вопрос записан в файл: vopros.txt" << endl;
		cout << "Сообщение записано в файл: message.txt" << endl;
		cout << "Исходные данные удалены" << endl;
	}
	else cout << "Ошибка записи!\n";
	
	delete[]mas;
}

void Primitive_Enigma::Show_message(string otv){
	const int sum = 33;
	string otvet, message;
	FILE *f_message;
	fopen_s(&f_message, "message.txt", "r");
	if (f_message != NULL) {
		int razm = 1000;
		char *buf = new char[razm];
		while (!feof(f_message)) {
			fgets(buf, razm, f_message);
			message += buf;
		}
		delete[]buf;
		fclose(f_message);
		int size_otvet = message[size(message) - 1] - sum;//получение расмера ответа на секретный вопрос
		message.pop_back();//удаление размера ответа
		//расшифровую текст в порядке, обратном шифрованию
		//сначала считываю 10 последних символов для установления даты кодирования
		int size_mas = 10;//размер массива для хранения времени кодирования
		int i = 0;
		int *mas = new int[size_mas];
	
		for (i = 0; i < size_mas; i++) {//считывание 10 символов, отвечающих за время
			mas[i] = message[size(message)-1];
			message.pop_back();//после считывания символ удаляется из сообщения
		}

		//изменение порядка следования цифр на противоположный (т.к. запись шла в одном порядке,
		//а считывание в противоположном)
		i = 0;
		while (i<size_mas/2) {
			mas[i] += mas[size_mas - 1 - i];
			mas[size_mas - 1 - i] = mas[i] - mas[size_mas - 1 - i];
			mas[i] -= mas[size_mas - 1 - i];
			i++;
		}

		
		//собственно процесс расшифровки символов времени
		
		for (i = size_mas-1; i >= 0; i--) {//движение с конца массива
			if (i + 1 == size_mas) {
				mas[i] = (mas[i] - sum) / sum;
			}
			else {
				mas[i] = mas[i] - sum - mas[i + 1];
			}
		}
	

		int pribav = mas[1];//количество прибавлений символов к каждой букве
		int k = 0;//переменная для движения по mas
		int j = 0;//переменная для движения по сообщению (message)
		
		for (i = 0; i < size_otvet; i++) {//считываю символы ответа, пока не считаю количество,
										  //записанное самым последним символом в закодированном сообщении
			j = 0;
			if (k == size_mas) k = 0;
			if (i == 0) {
				j = mas[0] + mas[1] + mas[2];
				otvet += AntiCezar(message[j-1], mas[k]);
				message.erase(0, j);
			}
			else {
				
				if (pribav > 0) {
					otvet += AntiCezar(message[pribav-1], mas[k]);
					message.erase(0, pribav);
				}
			
				else {
					otvet += AntiCezar(message[pribav], mas[k]);
					message.erase(0, pribav + 1);
				}
			}
			k++;
		}

		if (otvet == otv) {
			string result;
			
			k = 0;
			pribav = mas[0];
			while (size(message) != 0) {
				if (k == size_mas) k = 0;
				if (pribav > 0) {
					result += AntiCezar(message[pribav - 1], mas[k]);
					message.erase(0, pribav);
				}
				else {
					result += AntiCezar(message[pribav], mas[k]);
					message.erase(0, pribav + 1);
				}
				k++;
			}

			
			FILE *f;
			fopen_s(&f, "result.txt", "w");
			if (f != NULL) {
				fputs(result.c_str(), f);
				cout << "Расшифрованный текст записан в файл: result.txt" << endl;
				fclose(f);
			}
			else cout << "Ошибка записи!" << endl;
		}
		else {
			cout << "Ответ не верный!" << endl;
		}
		
		delete[]mas;
	}
	else cout << "Ошибка открытия файла!" << endl;
	
	
}


Primitive_Enigma::~Primitive_Enigma(){

}
