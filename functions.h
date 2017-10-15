#pragma once

size_t levenshtein_distance(const char* s, size_t n, const char* t, size_t m);
int get_line_count();
void read_file(char** cluster, int* strCount, int n);
void sort_cluster(char** cluster, int* strCount, int* sort_strCount, int n);
void printCL(char* str, int* count);
void FindLocations(Point* point, int* distance, int n, int m);
int CalcDistance(int x, int y, int x1, int y1);
double random(double min, double max);