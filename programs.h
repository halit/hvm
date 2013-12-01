#ifndef PROGRAMS_H
#define PROGRAMS_H

#include "hvm.h"
using namespace VM;

void load_program(HVM&, int, int );
void add_program(HVM&, int, int, int);
void sub_program(HVM&, int, int, int);
void div_program(HVM&, int, int, int);
void mul_program(HVM&, int, int, int);
void mov_program(HVM&, int, int);
void jmp_program(HVM&, int);
void jne_program(HVM&, int, int, int);
void jnz_program(HVM&, int, int);
void hlt_program(HVM&);

#endif
