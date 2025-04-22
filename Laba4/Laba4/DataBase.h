#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>

std::ofstream new_DB(char* file_name);
bool remove_DB(char* file_name);
bool save_DB(char* file_name);
bool load_DB(char* file_name);

#endif