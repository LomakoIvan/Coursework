#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Queue applicants;

Queue::Queue() {
	front_node = nullptr;
	node_count = 0;
}

void Queue::Init() {
	front_node = nullptr;
	node_count = 0;
}

void Queue::Display() {
	Queue temp_queue = applicants;

	while (!isEmpty()) {
		Applicant person = *applicants.pop_front();
		cout << person.name << " " << person.addr << " " << person.mark << " " << person.date << endl;
	}

	applicants = temp_queue;
}

void Queue::push_front(Applicant data) {
	Node* new_node = (Node*)AllocateMemory(sizeof(Node));
	new_node->data = data;
	
	if (!front_node) {
		front_node = new_node;
		new_node->next_ptr = nullptr;
	}
	else {
		new_node->next_ptr = front_node;
		front_node = new_node;
	}

	node_count++;
}

Applicant* Queue::pop_front() {
	if (isEmpty()) { return nullptr; }

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
	free(front_node);

	front_node = temp;

	node_count--;
	return person;
}

int Queue::GetNodeCount() {
	return node_count;
}

bool Queue::isEmpty() {
	return node_count == 0;
}

void Queue::ClearDataInApplicant(Applicant& applicant) {
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
	applicant.mark = 0;
}

void Queue::Clear() {
	while (front_node) {
		ClearDataInApplicant(front_node->data);
		Node* temp = front_node->next_ptr;
		front_node->next_ptr = nullptr;
		free(front_node);
		front_node = temp;
	}

	node_count = 0;
}