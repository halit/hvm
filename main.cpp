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
#include "programs.h"

using namespace std;
using namespace VM;

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

