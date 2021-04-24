#include <iostream>
#include <queue>
template <typename FuncInstr> 
class OOOWindow {
    private:
        int size;
        int number_of_independent_instructions;
        int number_of_updates;
        std::vector <FuncInstr> OOOQueue;
    public:
        OOOWindow(unsigned long number);
        void write_instruction(FuncInstr instruction);
        double get_avg_independent_instruction();
        ~OOOWindow();
};