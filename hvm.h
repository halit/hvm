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

    void HVM::write_program(int value){
        program[program_write_counter++] = value;
    }

    void HVM::regdump(){
        for(int i=0;i<REGISTER_NUM;i++)
            std::cout << ">> HVM Debugger: Register" << i << " value => " << registers[i] << "\n";
        
        std::cout << ">> HVM Debugger: Last instruction opcode => " << now_instruction.opcode << "\n";
        std::cout << ">> HVM Debugger: Last instruction reg_00 => " << now_instruction.reg_00 << "\n";
        std::cout << ">> HVM Debugger: Last instruction reg_01 => " << now_instruction.reg_01 << "\n";
        std::cout << ">> HVM Debugger: Last instruction reg_02 => " << now_instruction.reg_02 << "\n";
        std::cout << ">> HVM Debugger: Last instruction value  => " << now_instruction.value << "\n";
    }

    int HVM::fetch(){
        int result = registers[REGISTER_PC]++;
        return program[result];
    }

    void HVM::eval(){
        OP_CODES op_code = now_instruction.opcode;
        switch(op_code){
            case NOP:
                break;
            case HLT:
                status = false;
                break;
            case ADD:
                registers[now_instruction.reg_00] = registers[now_instruction.reg_01] + registers[now_instruction.reg_02];
                break;
            case SUB:
                registers[now_instruction.reg_00] = registers[now_instruction.reg_01] - registers[now_instruction.reg_02];
                break;
            case DIV:
                registers[now_instruction.reg_00] = registers[now_instruction.reg_01] / registers[now_instruction.reg_02];
                break;
            case MUL:
                registers[now_instruction.reg_00] = registers[now_instruction.reg_01] * registers[now_instruction.reg_02];
                break;
            case MOV:
                registers[now_instruction.reg_00] = registers[now_instruction.reg_01];
                registers[now_instruction.reg_01] = 0;
                break;
            case LOAD:
                registers[now_instruction.reg_00] = now_instruction.value;
                break;
            case JMP:
                registers[REGISTER_PC] = now_instruction.value;
                break;
            case JNE:
                if(now_instruction.reg_00 != now_instruction.reg_01) registers[REGISTER_PC] = now_instruction.value;
                else registers[REGISTER_PC]++;
                break;
            case JNZ:
                if(now_instruction.reg_00 != now_instruction.reg_01) registers[REGISTER_PC] = now_instruction.value;
                else registers[REGISTER_PC]++;
                break;
               
        }
    }

    void HVM::decode(int value){
        now_instruction.opcode = (OP_CODES)(( value & 0xF000 ) >> 12);
        now_instruction.reg_00 = ( value & 0x0F00 ) >> 8;
        now_instruction.reg_01 = ( value & 0x00F0 ) >> 4;
        now_instruction.reg_02 = ( value & 0x000F );
        now_instruction.value  = ( value & 0x00FF );
    }

    void HVM::clean_instruction(){
        now_instruction.opcode = NOP;
        now_instruction.reg_00 = 0x0;
        now_instruction.reg_01 = 0x0;

        now_instruction.reg_02 = 0x0;
        now_instruction.value  = 0x0;
    }

    void HVM::init(){
        status = true;
        std::cout << ">> HVM: starting\n";

        for(int i=0;i<MAX_PROGRAM;i++)
            program[i] = 0x0;
        std::cout << ">> HVM: program memory cleaned\n";

        for(int i=0;i<REGISTER_NUM;i++)
            registers[i] = 0x0;
        std::cout << ">> HVM: registers cleaned\n";
        
        clean_instruction();
        std::cout << ">> HVM: instruction register cleaned\n";

        program_write_counter = 0x0;
        std::cout << ">> HVM: program write counter cleaned\n";
    }

    void HVM::run(){
        while(status){
            decode(fetch());
            eval();
            //regdump();
        }
    }
       
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
