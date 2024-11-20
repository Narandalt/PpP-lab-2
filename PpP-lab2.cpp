#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <locale>

using namespace std;

int defense(string str, void text(), int min, int max);

#define ADD_USER 1
#define ADD_TARIFF 2
#define SET_EXPENSE_FOR_USER 3
#define SHOW_TOTAL_USER_EXPENSE 4
#define SHOW_MAX_USER_EXPENSE 5
#define SET_TARIFF_FOR_USER 6
#define DISPLAY_ALL_USERS 7
#define DISPLAY_ALL_TARIFFS 8
#define EXIT 9

// перечисление гендеров
enum Gender
{
	MALE = 'm',
	FEMALE = 'f'
};

class Tariff
{
private:
	string name; // название тарифа
	int price; // цена за 1 мб
public:
	Tariff() : name(""), price(0) {}
	Tariff(string name, int price) : name(name), price(price) {}

	~Tariff() {}

	// задаем значения объектам
	void set_name(string str) { name = str; }
	void set_price(int value) { price = value; }

	// возвращаем значения объектив
	string get_name() { return name; }
	int get_price() { return price; }

	// выделяем место под тариф
	Tariff* selectPlace(Tariff* old_tariff, int size)
	{
		Tariff* new_tariff = new Tariff[size + 1];

		for (int i = 0; i < size; i++)
		{
			new_tariff[i] = old_tariff[i];
		}

		return new_tariff;
	}
};

class User
{
private:
	string name; // имя
	string surname; // фамилия
	int age; // возраст
	int expense; // сколько потратил мБайт тарифа
	Gender gender; // гендер 
	Tariff tariff; // тарифф, выбранный пользователем

public:
	User() : name(""), surname(""), age(0), expense(0), gender(MALE), tariff("", 0) {}
	User(string name, string surname, int age, int mbSpent, Gender gender, Tariff tariff) : name(name), surname(surname), age(age), expense(mbSpent), gender(gender), tariff(tariff) {}

	// задаем значения объектов
	void set_name(string str) { name = str; }
	void set_surname(string str) { surname = str; }
	void set_age(int value) { age = value; }
	void set_expense(int value) { expense = value; }
	void set_gender(char c) { c == 'm' ? gender = MALE : gender = FEMALE; }
	void set_tariff(Tariff t) { tariff = t; }

	~User() {}

	// возвращаем значения объектов
	string get_name() { return name; }
	string get_surname() { return surname; }
	string get_tariff() { return tariff.get_name(); }
	int get_age() { return age; }
	int get_expense() { return expense; }
	Gender get_gender() { return gender; }

	// выделяем место под пользователя
	User* selectPlace(User* old_user, int size)
	{
		User* new_user = new User[size + 1];

		for (int i = 0; i < size; i++)
		{
			new_user[i] = old_user[i];
		}

		return new_user;
	}
};

class Operator
{
private:
	int user_quantity = 1; // количество пользователей (на деле на 1 меньше)
	int tariff_quantity = 1; // количество тарифов (на деле на 1 меньше)
	User* user = new User[user_quantity]; // массив пользователей
	Tariff* tariff = new Tariff[tariff_quantity]; // массив тариффов

	Operator() {}

	Operator(const Operator&) = delete;
	Operator& operator=(const Operator&) = delete;

public:
	static Operator& getInstance()
	{
		static Operator instance;
		return instance;
	}

	~Operator() {}

	// задаем значения объектов
	void set_user_name(string str, int index) { user[index].set_name(str); }
	void set_user_surname(string str, int index) { user[index].set_surname(str); }
	void set_user_age(int value, int index) { user[index].set_age(value); }
	void set_user_expense(int value, int index) { user[index].set_expense(value); }
	void set_user_gender(char c, int index) { user[index].set_gender(c); }
	void set_tariff_name(string str, int index) { tariff[index].set_name(str); }
	void set_tariff_price(int value, int index) { tariff[index].set_price(value); }

	// возвращаем количества пользователей и тарифов
	int get_tariff_quantity() { return tariff_quantity - 1; }
	int get_user_quantity() { return user_quantity - 1; }

	// добавляем нового пользователя
	void add_user()
	{
		string input;

		system("cls");

		user = user->selectPlace(user, user_quantity);
		user_quantity++;

		cout << "Введите имя пользователя: ";
		cin >> input;
		set_user_name(input, get_user_quantity() - 1);

		system("cls");
		cout << "Введите фамилию пользователя: ";
		cin >> input;
		set_user_surname(input, get_user_quantity() - 1);

		system("cls");
		set_user_age(defense("Введите возраст пользователя: ", nullptr, 0, INT_MAX), get_user_quantity() - 1);
		system("cls");
		set_user_expense(0, get_user_quantity() - 1); // изначально пользователь только зарегистрирован, так что нет трат трафика

		do
		{
			system("cls");
			cout << "Введите гендер пользователя: ";
			cin >> input;
		} while (input != "f" && input != "m");

		set_user_gender(input[0], get_user_quantity() - 1);
	}

	// добавляем новый тариф
	void add_tariff()
	{
		system("cls");
		string input;

		tariff = tariff->selectPlace(tariff, tariff_quantity);
		tariff_quantity++;

		cout << "Введите название тарифа: ";
		cin >> input;

		set_tariff_name(input, get_tariff_quantity() - 1);
		set_tariff_price(defense("Введите цену за 1мб тарифа: ", nullptr, 0, INT_MAX), get_tariff_quantity() - 1);
	}

	// вывод конкретного пользователя
	string display_user(int index)
	{
		string str = "";

		str += "Name: ";
		str += user[index].get_name();

		str += "\nSurname: ";
		str += user[index].get_surname();

		str += "\nAge: ";
		str += to_string(user[index].get_age());

		str += "\nTariff spent: ";
		str += to_string(user[index].get_expense());

		str += "\nGender: ";
		str += user[index].get_gender();

		str += "\nTariff name: ";

		user[index].get_tariff() == "" ? str += "no tariff" : str += user[index].get_tariff();

		return str;
	}

	// вывод всех пользователей
	string display_all_user()
	{
		string str;

		for (int i = 0; i < get_user_quantity(); i++)
		{
			str = str + to_string(i + 1) + " пользователь\n";

			str += "Name: ";
			str += user[i].get_name();

			str += "\nSurname: ";
			str += user[i].get_surname();

			str += "\nAge: ";
			str += to_string(user[i].get_age());

			str += "\nTariff spent: ";
			str += to_string(user[i].get_expense());

			str += "\nGender: ";
			user[i].get_gender() == MALE ? str += "male" : str += "female";

			str += "\nTariff name: ";

			user[i].get_tariff() == "" ? str += "no tariff" : str += user[i].get_tariff();

			str += "\n\n";
		}

		return str;
	}

	string display_tariff_info()
	{
		string str;

		for (int i = 0; i < get_tariff_quantity(); i++)
		{
			str = str + to_string(i + 1) + " тариф\n";

			str += "Tariff name: ";
			str += tariff[i].get_name();

			str += "\nPrice: ";
			str += to_string(tariff[i].get_price());

			str += "\n\n";
		}

		return str;
	}

	// задать траты по тарифу
	void set_expense()
	{
		system("cls");
		int index = 0;
		string str = "";

		str = display_all_user();

		str += "Выберите пользователя: ";

		index = defense(str, nullptr, 1, get_user_quantity()) - 1;
		str += to_string(index + 1);
		str += "\nВведите значение потраченного трафика: ";

		system("cls");
		set_user_expense(defense(str, nullptr, 0, INT_MAX), index);
	}

	long long get_total_expense(int index)
	{
		for (int i = 0; i < tariff_quantity; i++)
		{
			if (user[index - 1].get_tariff() == tariff[i].get_name())
			{
				return (long long)user[index - 1].get_expense() * (long long)tariff[i].get_price();
			}
		}
	}

	// траты одного пользователя
	void user_total_expense()
	{
		system("cls");
		string str;
		int index;

		str = display_all_user();
		str += "Выберите пользователя: ";

		index = defense(str, nullptr, 1, get_user_quantity());

		cout << "Пользователь потратил: " << get_total_expense(index);

		cin.get();
		cin.ignore();
	}

	// выводим данные пользователя, потратившего больше всего на тариф
	void max_expense_user()
	{
		system("cls");

		int index = 1;
		string usr = "";

		for (int i = 2; i <= get_user_quantity(); i++)
		{
			if (get_total_expense(i) > get_total_expense(index))
			{
				index = i;
			}
		}

		usr = display_user(index - 1);

		cout << "Пользователь, потративший больше всего на услуги оператора: \n";
		cout << usr;

		cin.get();
		cin.ignore();
	}

	// задать тарифный план для пользователя
	void set_user_tariff()
	{
		system("cls");
		int index = 0;
		string str = "";
		str += display_all_user();

		str += "Выберите пользователя: ";

		index = defense(str, nullptr, 1, get_user_quantity()) - 1;
		str += to_string(index + 1);

		system("cls");

		str = display_tariff_info();
		str += "Выберите тариффный план для пользователя ";

		user[index].set_tariff(tariff[defense(str, nullptr, 1, get_tariff_quantity()) - 1]);
	}
};

void uncorrectNumError()
{
	cout << "\nОшибка! Введите корректное значение";
	cin.ignore();
	cin.get();
	system("cls");
}

// защита от неверного ввода
int defense(string str, void text(), int min, int max)
{
	string value;
	const string INT_MAX_VALUE = to_string(INT_MAX);

again:

	if (str != "")
	{
		cout << str;
	}
	else if (text != NULL)
	{
		text();
	}

	cin >> value;

	if (value.length() > INT_MAX_VALUE.length())
	{
		uncorrectNumError();
		goto again;
	}

	for (int i = 0; i < value.length(); i++)
	{
		if (!('0' <= value[i] && value[i] <= '9'))
		{
			uncorrectNumError();
			goto again;
		}
	}

	if (value.length() > INT_MAX_VALUE.length())
	{
		uncorrectNumError();
		goto again;
	}
	else if (value.length() == INT_MAX_VALUE.length())
	{
		for (int i = 0; i < value.length(); i++)
		{
			if (value[i] > INT_MAX_VALUE[i])
			{
				uncorrectNumError();
				goto again;
			}
		}
	}

	// проверка допустимых пределов
	if (!(stoi(value) >= min && stoi(value) <= max))
	{
		uncorrectNumError();
		goto again;
	}

	return stoi(value);
}

void menu()
{
	cout << "\n	1. Зарегистрировать нового пользователя\n\n";
	cout << "	2. Добавить новый тариффный план\n\n";
	cout << "	3. Ввод данных о потребленном траффике для конкретного пользователя\n\n";
	cout << "	4. Подсчет общей стоимости потребленного траффика\n\n";
	cout << "	5. Данные клиента, заплатившего наибольшую сумму за услуги\n\n";
	cout << "	6. Задать пользователю тариффный план\n\n";
	cout << "	7. Вывести всех пользователей\n\n";
	cout << "	8. Вывести все тарифные планы\n\n";
	cout << "	9. Выход\n\n";
	cout << "-> ";
}

int main()
{
	setlocale(LC_ALL, "Russian");

	Operator& provider = Operator::getInstance();
	string usrInput;

	do
	{
	again:

		system("cls");

		switch (defense("", menu, ADD_USER, EXIT))
		{
		case ADD_USER:
			system("cls");
			provider.add_user();
			break;
		case ADD_TARIFF:
			system("cls");
			provider.add_tariff();
			break;
		case SET_EXPENSE_FOR_USER:
			if (provider.get_user_quantity() == 0)
				goto again;

			system("cls");
			provider.set_expense();
			break;
		case SHOW_TOTAL_USER_EXPENSE:
			if (provider.get_user_quantity() == 0)
				goto again;

			system("cls");
			provider.user_total_expense();
			break;
		case SHOW_MAX_USER_EXPENSE:
			if (provider.get_user_quantity() == 0)
				goto again;

			system("cls");
			provider.max_expense_user();
			break;
		case SET_TARIFF_FOR_USER:
			if (provider.get_user_quantity() == 0 || provider.get_tariff_quantity() == 0)
				goto again;

			system("cls");
			provider.set_user_tariff();
			break;
		case DISPLAY_ALL_USERS:
			system("cls");
			cout << provider.display_all_user();
			cin.get();
			cin.ignore();
			break;
		case DISPLAY_ALL_TARIFFS:
			system("cls");
			cout << provider.display_tariff_info();
			cin.get();
			cin.ignore();
			break;
		case EXIT:
			goto closeMenu;
			break;
		}

	} while (1);

closeMenu:

	return 0;
}