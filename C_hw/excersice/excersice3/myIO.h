#ifndef myIO_H
#define myIO_H
#include <stdio.h>
#include "basic.h"
#define MAX_algorithm 2
extern char algo_name[MAX_algorithm][10];
extern int relation_map[MAX_person][MAX_person];
void _build_map();
void _print_relation();
void _check_argument(int argc, char **argv);
void _err_message(int condition);
#define _print(states) {printf(#states": "); _print_relation();}
#endif