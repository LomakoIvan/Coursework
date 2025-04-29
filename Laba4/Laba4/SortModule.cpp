#include "Applicants.h"
#include "Memory.h"
#include <iostream>

using namespace std;

Node* GetNodeInDeck(Deck& deck, unsigned int node_number) {
	unsigned int node_count = deck.GetNodeCount();
	if (node_number >= node_count) { return nullptr; }

	Node* node = deck.get_front_node();
	for (int i = 0; i < node_number; i++) {
		node = node->prev_ptr;
	}
	
	return node;
}

void InsertSortMark(Deck& deck) {
	unsigned int node_count = deck.GetNodeCount();
	if (node_count < 2) { return; }

	Node* key_node = deck.get_front_node()->prev_ptr;

	for (int i = 1; key_node != nullptr; i++) {
		Applicant key = key_node->data;
		Node* current_node = key_node;
		Node* this_node = key_node->next_ptr;

		if (!this_node) { return; }

		int j = i - 1;
		for (; j >= 0 && this_node->data.mark > key.mark; j--) {
			current_node->data = this_node->data;
			current_node = this_node;
			this_node = this_node->next_ptr;
		}

		if (j != i - 1) {
			current_node->data = key;
		}

		key_node = key_node->prev_ptr;
	}
}