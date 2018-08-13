#pragma once
#include<iostream>
#include<ctime>
#include<string>
#include<io.h>
using namespace std;



class Primitive_Enigma{
	string message;
	string alphabet;
	const int size_alphabet = 166;
	void del_probel(string &str);
	char Cezar(char symb, int kol);
	char AntiCezar(char symb, int kol);
	char random_symb();
public:
	
	Primitive_Enigma();
	void Set_message(string vopr, string &otv, string &message);
	void Show_message(string otv);
	~Primitive_Enigma();
};
