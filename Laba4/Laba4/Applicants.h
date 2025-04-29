#ifndef APPLICANTS_H
#define APPLICANTS_H

struct Applicant {
	char* name;
	char* addr;
	int mark;
	char* date;
};

struct Node {
	Applicant data;
	Node* next_ptr;
	Node* prev_ptr;
};

struct Deck {
private:
	Node* front_node = nullptr;
	Node* back_node = nullptr;
	int node_count = 0;

	void ClearDataInApplicant(Applicant& applicant);

public:
	void Init();
	void DisplayFrontToBack();
	void DisplayBackToFront();
	void push_back(Applicant data);
	void push_front(Applicant data);
	Applicant* pop_front();
	Applicant* pop_back();
	Node* get_back_node();
	Node* get_front_node();
	Applicant get_front_data();
	Applicant get_back_data();
	int GetNodeCount();
	bool isEmpty();
	void Clear();
};

extern Deck applicants;

#endif