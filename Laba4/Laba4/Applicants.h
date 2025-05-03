#ifndef APPLICANTS_H
#define APPLICANTS_H

struct Applicant {
	char* name;
	char* addr;
	int mark;
	char* date;
};

struct Queue {
private:
	struct Node {
		Applicant data;
		Node* next_ptr;
	};

	Node* front_node = nullptr;
	Node* back_node = nullptr;
	int node_count = 0;

	void ClearDataInApplicant(Applicant& applicant);

public:
	Queue();
	void Init();
	void Display();
	void push_back(Applicant data);
	Applicant* pop_front();
	void CopyTo(Queue to_queue);
	int GetNodeCount();
	bool isEmpty();
	void Clear();
};

extern Queue applicants;

#endif