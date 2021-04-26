#include <iostream>
#include <list>
template <typename FuncInstr> 
class OOOWindow {
    private:
        unsigned long size;
        unsigned long long number_of_independent_instructions;
        unsigned long long number_of_updates;
        std::list <FuncInstr> OOOQueue;
    public:
        OOOWindow(unsigned long number): size(number), number_of_independent_instructions(0), number_of_updates(0) {}

        void write_instruction(FuncInstr instruction) {
            if (size == 0)
                return;
            if (static_cast<unsigned long>(OOOQueue.size()) == size) {
                OOOQueue.pop_front();
                OOOQueue.push_back(instruction);
                this->update_number_of_independent_instructions();
                return;
            }
            OOOQueue.push_back(instruction);
        }

        void update_number_of_independent_instructions() {
            int count = 0, instruction_independent = 1;
            for (auto it1 = OOOQueue.begin(), end = OOOQueue.end(); it1 != end; ++it1, instruction_independent = 1) {
                for (auto it3 = OOOQueue.begin(); it3 != it1 && instruction_independent; ++it3)
                    for (int k = 0; k < 3 && instruction_independent; k++)
                        if (((*it1).get_src_num(k) == (*it3).get_dst_num()) && !((*it3).get_dst_num().is_zero()))
                            instruction_independent = 0;
                if (instruction_independent)
                    count++;
            }
            number_of_independent_instructions += count;
            number_of_updates++;
        }

        double get_avg_independent_instructions() {
            if (number_of_updates == 0)
                return 0;
            return (static_cast<double>(number_of_independent_instructions))/(static_cast<double>(number_of_updates));
        }

        ~OOOWindow() { std::cout << this->get_avg_independent_instructions() << std::endl; }
};