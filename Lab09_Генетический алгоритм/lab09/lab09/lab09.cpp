#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>
#include <Windows.h>

using namespace std;

#define V 8
#define GENES ABCDE
#define START 0

int child = 0;
int populationSize = 0;
int evoCount = 0;



 
int cities[V][V] = { { INT_MAX, 25, 40, 31, 27, 10, 5, 9},
				{ 25, INT_MAX, 17, 30, 25, 15, 20, 10},
				{ 40, 17, INT_MAX, 6, 1, 20, 30, 25},
				{ 31, 30, 6, INT_MAX, 6, 10, 5, 9 },
				{ 27, 25, 1, 6, INT_MAX, 15, 20, 10 },
				{ 10, 15, 20, 10, 15, INT_MAX, 17, 30 },
				{ 5, 20, 30, 5, 20, 17, INT_MAX, 6 },
				{ 9, 10, 25, 9, 10, 30, 6, INT_MAX } };

struct individual {
	string gnome;
	int fitness;
};

int rand_num(int start, int end) // просто алгоритм вычисления рандомного числа
{
	int r = end - start;
	int rnum = start + rand() % r;
	return rnum;
}

bool repeat(string s, char ch)
{
	for (int i = 0; i < s.size(); i++) {
		if (s[i] == ch)
			return true;
	}
	return false;
}

string mutatedGene(string gnome) // мутация - генерируются рандомные числа, сравниваются, меняются местами
{
	while (true) {
		int r = rand_num(1, V);
		int r1 = rand_num(1, V);
		if (r1 != r) {
			char temp = gnome[r];
			gnome[r] = gnome[r1];
			gnome[r1] = temp;
			break;
		}
	}
	return gnome;
}

string create_gnome()
{
	string gnome = "0";
	while (true) {
		if (gnome.size() == V) { //добавляется начальный город, чтобы зациклить
			gnome += gnome[0];
			break;
		}
		int temp = rand_num(1, V);
		if (!repeat(gnome, (char)(temp + 48))) // проверка есть ли уже этот символ в геноме
			gnome += (char)(temp + 48); // добавляеттся, если нет (ASCII)
	}
	return gnome;
}

int cal_fitness(string gnome) // вычисление веса 
{

	int f = 0;
	for (int i = 0; i < gnome.size() - 1; i++) {
		if (cities[gnome[i] - 48][gnome[i + 1] - 48] == INT_MAX)
			return INT_MAX;
		f += cities[gnome[i] - 48][gnome[i + 1] - 48];
	}
	return f;
}

int cooldown(int temp)
{
	return (90 * temp) / 100;
}

bool lessthan(struct individual t1,
	struct individual t2)
{
	return t1.fitness < t2.fitness;
}

void Genetic_algo(int cities[V][V])
{
	int gen = 1; //текущеее положение в ген алг
	int gen_thres = evoCount; //представляет пороговое значение для количества поколений, после которого алгоритм остановит свою работу.

	vector<struct individual> population; //создается вектор population, который будет хранить популяцию индивидуумов. Каждый индивидуум представлен структурой individual
	struct individual temp; //создается временная переменная temp типа individual, которая будет использоваться для создания и инициализации новых индивидуумов.

	for (int i = 0; i < populationSize; i++) { // создание начальной популяции
		temp.gnome = create_gnome();
		temp.fitness = cal_fitness(temp.gnome);
		population.push_back(temp);
	}

	cout << "\nСтартовая популяция: " << endl;
	cout << "Геном популяции \t||вес генома\n";
	for (int i = 0; i < populationSize; i++)
		cout << population[i].gnome << "\t\t\t"
		<< population[i].fitness << endl;
	cout << "\n";

	int temperature = 10000;

	sort(population.begin(), population.end(), lessthan); // сортировка в порядке возрастания, используя lessthan

	while (temperature > 100 && gen <= gen_thres) { //пока температура (temperature) больше 100 и текущее поколение (gen) не превысит пороговое значение поколений.
		cout << endl << "Лучший геном: " << population[0].gnome; // первый из отсортир
		cout << " его вес: " << population[0].fitness << "\n\n";

		vector<struct individual> new_population; //для хранения новой популяции индивидуумов после операции скрещивания и мутации.

		for (int i = 0; i < child; i++) { // меньше количества потомков в популяции

			struct individual p1 = population[i]; //получает значение индивидуума из текущей популяции population для скрещивания и мутации.

			while (true)
			{
				string new_g = mutatedGene(p1.gnome);
				struct individual new_gnome; // нового индивидуума в новой популяции.
				new_gnome.gnome = new_g; //Значение нового генома new_g присваивается полю gnome переменной new_gnome.
				new_gnome.fitness = cal_fitness(new_gnome.gnome);

				if (new_gnome.fitness <= population[i].fitness) {
					new_population.push_back(new_gnome);
					break;
				}
				else {
					new_gnome.fitness = INT_MAX;
					new_population.push_back(new_gnome);
					break;
				}
			}
		}

		temperature = cooldown(temperature);
		for (int i = 0; i < child; i++)
		{
			population.push_back(new_population[i]); // добавление в конец
		}
		sort(population.begin(), population.end(), lessthan); // сортировка возрастания

		for (int i = 0; i < child; i++) // убираем колво детей
		{
			population.pop_back();
		}

		cout << "Поколение " << gen << " \n";
		cout << "Геном популяции \t||вес генома\n";

		for (int i = 0; i < populationSize; i++)
			cout << population[i].gnome << "\t\t\t"
			<< population[i].fitness << endl;
		gen++;
	}
	cout << "\n\nнаиболее оптимальный маршрут, найденный генетическим алгоритмом с текущими параметрами: ";
	cout << population[0].gnome;
	cout << "\n\n";
}

int main()
{
	setlocale(LC_ALL, "ru");
	do
	{
		cout << "Введите размер популяций: ";
		cin >> populationSize;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (populationSize <= 0);

	do
	{
		cout << "Введите количество потомков в одной популяции: ";
		cin >> child;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (child <= 0);

	do
	{
		cout << "Введите количество эволюций: ";
		cin >> evoCount;
		cin.clear();
		cin.ignore(32767, '\n');
	} while (evoCount <= 0);

	Genetic_algo(cities);
}
