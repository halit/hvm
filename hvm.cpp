// =====================================================================================
//
//
//       Filename:  hvm.cpp
//
//    Description:  My toy virtual machine implentation
//
//        Version:  0.1
//        Created:  10/17/2013 04:33:55 PM
//       Revision:  none
//       Compiler:  gcc
//
//         Author:  Halit Alptekin (), info@halitalptekin.com
//   Organization:  
//
// =====================================================================================
#include "hvm.h"

using namespace std;
using namespace VM;

void test_add(HVM& virtual_machine){

    int instruction = 0x0000;

    instruction |= LOAD << 12; // binding value
    instruction |= 0x3 << 8; // register[3]
    instruction |= 0x7; // register[3] = 7

    virtual_machine.write_program(instruction); // write instruction
    instruction  = 0x000; // reset value

    instruction |= LOAD << 12; // binding value
    instruction |= 0x2 << 8; // register[2]
    instruction |= 0x3; // register[2] = 3
    
    virtual_machine.write_program(instruction); // write instruction
    instruction  = 0x000; // reset value

    instruction |= ADD << 12; // sum values
    instruction |= 0x4 << 8;  // contains sum value to register[4]
    instruction |= 0x2 << 4;  // register[2]
    instruction |= 0x3;       // register[3]
    
    virtual_machine.write_program(instruction); 
    instruction  = 0x000; // reset value

    instruction |= HLT << 12; // halt system
    virtual_machine.write_program(instruction); // write program
}

void load_program(HVM& virtual_machine, int reg, int value ){
    int instruction = 0x000;
    instruction |= LOAD << 12;
    instruction |= reg << 8;
    instruction |= value;

    virtual_machine.write_program(instruction);
}

void add_program(HVM& virtual_machine, int reg, int r1, int r2 ){
    int instruction = 0x000;
    instruction |= ADD << 12;
    instruction |= reg << 8;
    instruction |= r1  << 4;
    instruction |= r2;

    virtual_machine.write_program(instruction);
}

void sub_program(HVM& virtual_machine, int reg, int r1, int r2){
    int instruction = 0x000;
    instruction |= SUB << 12;
    instruction |= reg << 8;
    instruction |= r1  << 4;
    instruction |= r2;

    virtual_machine.write_program(instruction);
   
}

void div_program(HVM& virtual_machine, int reg, int r1, int r2){
    int instruction = 0x000;
    instruction |= DIV << 12;
    instruction |= reg << 8;
    instruction |= r1  << 4;
    instruction |= r2;

    virtual_machine.write_program(instruction);
   
}

void mul_program(HVM& virtual_machine, int reg, int r1, int r2){
    int instruction = 0x000;
    instruction |= MUL << 12;
    instruction |= reg << 8;
    instruction |= r1  << 4;
    instruction |= r2;

    virtual_machine.write_program(instruction);
   
}

void mov_program(HVM& virtual_machine, int reg, int r1){
    int instruction = 0x000;
    instruction |= MOV << 12;
    instruction |= reg << 8;
    instruction |= r1  << 4;

    virtual_machine.write_program(instruction);

}

void jmp_program(HVM& virtual_machine, int value){
    int instruction = 0x000;
    instruction |= JMP << 12;
    instruction |= value;

    virtual_machine.write_program(instruction);

}

void jne_program(HVM& virtual_machine, int r1, int r2, int value){
    int instruction = 0x000;
    instruction |= JNE << 12;
    instruction |= r1  << 8;
    instruction |= r2  << 4;
    instruction |= value;

    virtual_machine.write_program(instruction);

}

void jnz_program(HVM& virtual_machine, int r1, int value){
    int instruction = 0x000;
    instruction |= JNZ << 12;
    instruction |= r1  << 8;
    instruction |= value;

    virtual_machine.write_program(instruction);

}

void hlt_program(HVM& virtual_machine){
    int instruction = 0x000;
    instruction |= HLT << 12;

    virtual_machine.write_program(instruction);
}


int main(){
    HVM my_vm; // init virtual machine
    //test_add(my_vm); // test add program write to virtual machine program register
    
    load_program(my_vm, 2, 15); // 15 -> reg2
    load_program(my_vm, 3, 18); // 18 -> reg3
    add_program(my_vm, 4, 2, 3); // reg4 -> reg2 + reg3
    load_program(my_vm, 2, 30); // 30 -> reg2
    sub_program(my_vm, 4, 4, 2); // reg4 -> reg4 - reg2
    load_program(my_vm, 2, 10); // 10 -> reg2
    mul_program(my_vm, 4, 4, 2); // reg4 -> reg4 * reg2
    load_program(my_vm, 2, 3); // 3 -> reg2
    div_program(my_vm, 4, 4, 2); // reg4 -> reg4 / reg2
    mov_program(my_vm, 2, 4); // reg2 -> reg4
    mov_program(my_vm, 1, 2); // reg1 -> reg2
    //jmp_program(my_vm, 0);
    hlt_program(my_vm); // stop program

    my_vm.run(); // run the machine
    my_vm.regdump(); // register dump

    return 0;
}

