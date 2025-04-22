#include "Memory.h"
#include <iostream>

using namespace std;

//Allocate memory and return ptr on this memory
void* AllocateMemory(size_t size) {
	void* ptr = malloc(size);
	if (!ptr) {
		cout << "\nОшибка выделения памяти\n";
		exit(1);
	}
	return ptr;
}

//Allocate memory on text and return this text(char*)
char* AllocateMemoryToStr(char* text) {
	int length = strlen(text);
	char* newStr = (char*)AllocateMemory((length + 1) * sizeof(char));

	int i = 0;
	for (; i < length; i++) {
		newStr[i] = text[i];
	}
	newStr[i] = '\0';

	return newStr;
}

//Resize allocate memory in "ptr" on "size"
void ResizeAllocatedMemory(void*& ptr, size_t size) {
	void* temp = realloc(ptr, size);
	if (!temp) {
		cout << "\nОшибка выделения памяти\n";
		exit(1);
	}
	ptr = temp;
}