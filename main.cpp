#include "CGraph.h"
//======================================================================================
int main() {
	
	setlocale(LC_ALL, "");
	
	CGraph gpers;

	gpers.add_person("������");
	gpers.add_person("���");
	gpers.add_person("������");
	gpers.add_person("�����");
	gpers.add_person("����");
	gpers.add_person("���");
	gpers.add_person("�����");
	gpers.add_person("��������");
	gpers.add_person("��������");
	gpers.add_person("���������");
	gpers.add_person("���");


	gpers.set_friend("������", "���");
	gpers.set_friend("���", "������");
	gpers.set_friend("������", "�����");
	gpers.set_friend("��������", "���");
	gpers.set_friend("��������", "���������");
	gpers.set_friend("���", "���������");
	gpers.set_friend("��������", "���");
	gpers.set_friend("�����", "���");
	gpers.set_friend("�����", "����");
	gpers.set_friend("���", "����");
	gpers.set_friend("���", "��������");



	size_t depth{ 3 };
	std::cout << "������� ���������� �����������:\n";
	std::cin >> depth;

	gpers.show_depth(depth);

	return 0;
}