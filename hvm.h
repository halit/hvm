#ifndef HVM_H
#define HVM_H

#include <iostream>
namespace VM{
    
    /* Virtual machine features  */
    const int MAX_PROGRAM  = 255;
    const int REGISTER_NUM = 6;
    const int REGISTER_PC  = 0;
    
    /* Op-Codes */
    enum OP_CODES {
        NOP = 0, HLT, ADD, SUB, DIV, MUL, MOV, LOAD, JMP, JNZ, JNE
    };
    
    /* Instruction struct */
    struct instruction{
        OP_CODES opcode;
        int reg_00;
        int reg_01;
        int reg_02;
        int value;
    };
    
    /* Virtual Machine Class */
    class HVM {
    public:
        HVM (){
            init();
        };
        void run(); // Start machine
        void regdump(); // Debug register status
        void write_program(int value); // Write program to program register
        
    private:
        int registers[REGISTER_NUM]; // VM register
        int program[MAX_PROGRAM]; // Program container
        int program_write_counter; // Program write counter
        bool status; // VM status
        instruction now_instruction; // Last command instruction

        /* VM Functions */
        int fetch(); // Fetch intstruction command from program
        void eval(); // Execute command
        void decode(int); // Decode value to command
        void init(); // Init virtual machine
        void clean_instruction(); // Clean now_instruction register
    };

      
}

/*
 *    now_instruction.opcode = LOAD; // binding value
 *    now_instruction.reg_00 = 0x2;  // register[2]
 *    now_instruction.value  = 0x3;  // register[2] = 3
 *    eval(); // eval load value
 *    regdump(); // see register[2] => 3
 *    
 *    now_instruction.opcode = LOAD; // binding value
 *    now_instruction.reg_00 = 0x3;  // register[3]
 *    now_instruction.value  = 0x7;  // register[3] = 7
 *    eval(); // eval load value
 *    regdump(); // see register[3] => 7
 *
 *
 *    now_instruction.opcode = ADD; // sum two register value
 *    now_instruction.reg_00 = 0x4; // contains sum value to register[4]
 *    now_instruction.reg_01 = 0x2; // register[2]
 *    now_instruction.reg_02 = 0x3; // register[3]
 *    eval(); // register[4] = register[2] + register[3];
 *    regdump(); // see register[4] => 10
 *
 *    now_instruction.opcode = HLT;
 *    eval();
 *
 *
 */

#endif
