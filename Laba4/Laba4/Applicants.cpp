#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Deck applicants;

void Deck::ClearDataInApplicant(Applicant& applicant) {
	if (applicant.name) {
		free(applicant.name);
		applicant.name = nullptr;
	}
	if (applicant.addr) {
		free(applicant.addr);
		applicant.addr = nullptr;
	}
	if (applicant.date) {
		free(applicant.date);
		applicant.date = nullptr;
	}
}

void Deck::Init() {
	front_node = nullptr;
	back_node = nullptr;
	node_count = 0;
}

void Deck::DisplayFrontToBack() {
	Node* head = front_node;

	while (head) {
		Applicant person = head->data;
		cout << person.name << " " << person.addr << " " << person.mark << " " << person.date << endl;
		head = head->next_ptr;
	}
}

void Deck::DisplayBackToFront() {
	Node* head = back_node;

	while (head) {
		Applicant person = head->data;
		cout << person.name << " " << person.addr << " " << person.mark << " " << person.date << endl;
		head = head->prev_ptr;
	}
}

void Deck::push_back(Applicant data) {
	Node* new_node = (Node*)AllocateMemory(sizeof(Node));
	new_node->data = data;

	if (!back_node) {
		new_node->next_ptr = nullptr;
		new_node->prev_ptr = nullptr;
		front_node = back_node = new_node;
	}
	else {
		back_node->next_ptr = new_node;
		new_node->prev_ptr = back_node;
		new_node->next_ptr = nullptr;
		back_node = new_node;
	}

	node_count++;
}

void Deck::push_front(Applicant data) {
	Node* new_node = (Node*)AllocateMemory(sizeof(Node));
	new_node->data = data;

	if (!front_node) {
		new_node->next_ptr = nullptr;
		new_node->prev_ptr = nullptr;
		front_node = back_node = new_node;
	}
	else {
		front_node->prev_ptr = new_node;
		new_node->next_ptr = front_node;
		new_node->prev_ptr = nullptr;
		front_node = new_node;
	}

	node_count++;
}

Applicant* Deck::pop_front() {
	if (!front_node) { return nullptr; }

	int name_length = strlen(front_node->data.name) + 1;
	int addr_length = strlen(front_node->data.addr) + 1;
	int date_length = strlen(front_node->data.date) + 1;

	Applicant* person = (Applicant*)AllocateMemory(sizeof(Applicant));
	(*person).name = (char*)AllocateMemory(sizeof(char) * name_length);
	(*person).addr = (char*)AllocateMemory(sizeof(char) * addr_length);
	(*person).date = (char*)AllocateMemory(sizeof(char) * date_length);

	strcpy_s((*person).name, name_length, front_node->data.name);
	strcpy_s((*person).addr, addr_length, front_node->data.addr);
	strcpy_s((*person).date, date_length, front_node->data.date);
	(*person).mark = front_node->data.mark;

	Node* temp = front_node->next_ptr;

	ClearDataInApplicant(front_node->data);
	front_node->next_ptr = nullptr;
	front_node->prev_ptr = nullptr;
	free(front_node);

	front_node = temp;
	if (front_node) { front_node->prev_ptr = nullptr; }

	node_count--;
	return person;
}

Applicant* Deck::pop_back() {
	if (!back_node) { return nullptr; }

	int name_length = strlen(back_node->data.name) + 1;
	int addr_length = strlen(back_node->data.addr) + 1;
	int date_length = strlen(back_node->data.date) + 1;

	Applicant* person = (Applicant*)AllocateMemory(sizeof(Applicant));
	(*person).name = (char*)AllocateMemory(sizeof(char) * name_length);
	(*person).addr = (char*)AllocateMemory(sizeof(char) * addr_length);
	(*person).date = (char*)AllocateMemory(sizeof(char) * date_length);

	strcpy_s((*person).name, name_length, back_node->data.name);
	strcpy_s((*person).addr, addr_length, back_node->data.addr);
	strcpy_s((*person).date, date_length, back_node->data.date);
	(*person).mark = back_node->data.mark;

	Node* temp = back_node->prev_ptr;

	ClearDataInApplicant(back_node->data);
	back_node->next_ptr = nullptr;
	back_node->prev_ptr = nullptr;
	free(back_node);

	back_node = temp;
	if (back_node) { back_node->next_ptr = nullptr; }

	node_count--;
	return person;
}

Node* Deck::get_front_node() {
	return front_node;
}

Node* Deck::get_back_node() {
	return back_node;
}

Applicant Deck::get_front_data() {
	return front_node->data;
}

Applicant Deck::get_back_data() {
	return back_node->data;
}

int Deck::GetNodeCount() {
	return node_count;
}

bool Deck::isEmpty() {
	return node_count == 0;
}

void Deck::Clear() {
	Node* head = front_node;
	Node* temp = nullptr;

	while (head) {
		ClearDataInApplicant(head->data);
		temp = head->next_ptr;
		head->next_ptr = nullptr;
		head->prev_ptr = nullptr;
		free(head);
		head = temp;
	}

	front_node = nullptr;
	back_node = nullptr;
	node_count = 0;
}