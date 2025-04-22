#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Deck applicants;

void Deck::ClearDataInApplicant(Applicant& applicant)
	{
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
	start_node = nullptr;
	end_node = nullptr;
	node_count = 0;
}

void Deck::DisplayFrontToBack() {
	Node* head = start_node;

	while (head) {
		Applicant person = head->data;
		cout << person.name << " " << person.addr << " " << person.mark << " " << person.date << endl;
		head = head->prev_ptr;
	}
}

void Deck::DisplayBackToFront() {
	Node* head = end_node;

	while (head) {
		Applicant person = head->data;
		cout << person.name << " " << person.addr << " " << person.mark << " " << person.date << endl;
		head = head->next_ptr;
	}
}

void Deck::push_back(Applicant data) {
	Node* new_node = (Node*)AllocateMemory(sizeof(Node));
	new_node->data = data;

	if (!end_node) {
		new_node->next_ptr = nullptr;
		new_node->prev_ptr = nullptr;
		start_node = end_node = new_node;
	}
	else {
		end_node->prev_ptr = new_node;
		new_node->next_ptr = end_node;
		new_node->prev_ptr = nullptr;
		end_node = new_node;
	}

	node_count++;
}

void Deck::push_front(Applicant data) {
	Node* new_node = (Node*)AllocateMemory(sizeof(Node));
	new_node->data = data;

	if (!start_node) {
		new_node->next_ptr = nullptr;
		new_node->prev_ptr = nullptr;
		start_node = end_node = new_node;
	}
	else {
		start_node->next_ptr = new_node;
		new_node->prev_ptr = start_node;
		new_node->next_ptr = nullptr;
		start_node = new_node;
	}

	node_count++;
}

Applicant* Deck::pop_front() {
	if (!start_node) { return nullptr; }

	int name_length = strlen(start_node->data.name) + 1;
	int addr_length = strlen(start_node->data.addr) + 1;
	int date_length = strlen(start_node->data.date) + 1;

	Applicant* person = (Applicant*)AllocateMemory(sizeof(Applicant));
	(*person).name = (char*)AllocateMemory(sizeof(char) * name_length);
	(*person).addr = (char*)AllocateMemory(sizeof(char) * addr_length);
	(*person).date = (char*)AllocateMemory(sizeof(char) * date_length);

	strcpy_s((*person).name, name_length, start_node->data.name);
	strcpy_s((*person).addr, addr_length, start_node->data.addr);
	strcpy_s((*person).date, date_length, start_node->data.date);
	(*person).mark = start_node->data.mark;

	Node* temp = start_node->prev_ptr;

	ClearDataInApplicant(start_node->data);
	start_node->next_ptr = nullptr;
	start_node->prev_ptr = nullptr;
	free(start_node);

	start_node = temp;
	if (start_node) { start_node->next_ptr = nullptr; }

	node_count--;
	return person;
}

Applicant* Deck::pop_back() {
	if (!end_node) { return nullptr; }

	int name_length = strlen(end_node->data.name) + 1;
	int addr_length = strlen(end_node->data.addr) + 1;
	int date_length = strlen(end_node->data.date) + 1;

	Applicant* person = (Applicant*)AllocateMemory(sizeof(Applicant));
	(*person).name = (char*)AllocateMemory(sizeof(char) * name_length);
	(*person).addr = (char*)AllocateMemory(sizeof(char) * addr_length);
	(*person).date = (char*)AllocateMemory(sizeof(char) * date_length);

	strcpy_s((*person).name, name_length, end_node->data.name);
	strcpy_s((*person).addr, addr_length, end_node->data.addr);
	strcpy_s((*person).date, date_length, end_node->data.date);
	(*person).mark = end_node->data.mark;

	Node* temp = end_node->next_ptr;

	ClearDataInApplicant(end_node->data);
	end_node->next_ptr = nullptr;
	end_node->prev_ptr = nullptr;
	free(end_node);

	end_node = temp;
	if (end_node) { end_node->prev_ptr = nullptr; }

	node_count--;
	return person;
}

int Deck::GetNodeCount() {
	return node_count;
}

bool Deck::isEmpty() {
	return node_count == 0;
}

void Deck::Clear() {
	Node* head = start_node;
	Node* temp = nullptr;

	while (head) {
		ClearDataInApplicant(head->data);
		temp = head->prev_ptr;
		head->next_ptr = nullptr;
		head->prev_ptr = nullptr;
		free(head);
		head = temp;
	}

	start_node = nullptr;
	end_node = nullptr;
	node_count = 0;
}