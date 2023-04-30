#include "CGraph.h"
//======================================================================================
int main() {
	
	setlocale(LC_ALL, "");
	
	CGraph gpers;

	gpers.add_person("Наташа");
	gpers.add_person("Юра");
	gpers.add_person("Андрей");
	gpers.add_person("Настя");
	gpers.add_person("Вера");
	gpers.add_person("Оля");
	gpers.add_person("Артем");
	gpers.add_person("Геннадий");
	gpers.add_person("Кристина");
	gpers.add_person("Маргарита");
	gpers.add_person("Юля");


	gpers.set_friend("Наташа", "Юра");
	gpers.set_friend("Юра", "Андрей");
	gpers.set_friend("Андрей", "Артем");
	gpers.set_friend("Кристина", "Юра");
	gpers.set_friend("Кристина", "Маргарита");
	gpers.set_friend("Юра", "Маргарита");
	gpers.set_friend("Геннадий", "Оля");
	gpers.set_friend("Настя", "Оля");
	gpers.set_friend("Настя", "Вера");
	gpers.set_friend("Юля", "Вера");
	gpers.set_friend("Юра", "Геннадий");



	size_t depth{ 3 };
	std::cout << "Введите количество рукопожатий:\n";
	std::cin >> depth;

	gpers.show_depth(depth);

	return 0;
}