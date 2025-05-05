#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Queue applicants;

Queue::Queue() {
	front_node = nullptr;
	back_node = nullptr;
	node_count = 0;
}

void Queue::Init() {
	front_node = nullptr;
	back_node = nullptr;
	node_count = 0;
}

void Queue::Display() {
	Queue temp_queue;

	while (!isEmpty()) {
		Applicant person = *applicants.pop_front();
		temp_queue.push_back(person);
		cout << person.name << " " << person.addr << " " << person.mark << " " << person.date << endl;
	}

	while (!temp_queue.isEmpty()) {
		applicants.push_back(*temp_queue.pop_front());
	}
}

void Queue::push_back(Applicant data) {
	Node* new_node = (Node*)AllocateMemory(sizeof(Node));
	new_node->data = data;
	new_node->next_ptr = nullptr;
	
	if (!back_node) {
		back_node = front_node = new_node;
	}
	else {
		back_node->next_ptr = new_node;
		back_node = new_node;
	}

	node_count++;
}

Applicant* Queue::pop_front() {
	if (isEmpty()) { return nullptr; }

	int name_length = strlen(front_node->data.name) + 1;
	int addr_length = strlen(front_node->data.addr) + 1;
	int date_length = strlen(front_node->data.date) + 1;

	Applicant* person = (Applicant*)AllocateMemory(sizeof(Applicant));
	person->name = front_node->data.name;
	person->addr = front_node->data.addr;
	person->mark = front_node->data.mark;
	person->date = front_node->data.date;

	Node* temp = front_node->next_ptr;
	front_node->next_ptr = nullptr;
	free(front_node);

	front_node = temp;
	if (!temp) { back_node = temp; }

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

	back_node = nullptr;

	node_count = 0;
}