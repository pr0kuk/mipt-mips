#include <iostream>
#include <list>
#include <func_sim/operation.h>
template <typename FuncInstr> 
class OOOWindow {
    private:
        unsigned long size;
        int number_of_independent_instructions;
        int number_of_updates;
        std::list <FuncInstr> OOOQueue;
    public:
        OOOWindow(unsigned long number) {
            size = number;
            number_of_independent_instructions = 0;
            number_of_updates = 0;
        }
        void write_instruction(FuncInstr instruction) {
            if (static_cast<unsigned long>(OOOQueue.size()) == size) {
                OOOQueue.pop_back();
                OOOQueue.push_front(instruction);
                int count = 0;
                for (auto it1 = OOOQueue.begin(), it2 = OOOQueue.end(); it1 != it2; ++it1) {
                    for (auto it3 = OOOQueue.begin(); it3 != it1; ++it3) {
                        int temp = 0;
                        for (int k = 0; k < 3; k++)
                            if (!((*it3).get_src_num(k) == (*it1).get_dst_num()) || ((*it3).get_src_num(k).is_zero() && (*it1).get_dst_num().is_zero()))
                                temp++;
                        if (temp == 3)
                            count += 2;
                    }
                }
                number_of_independent_instructions += count;
                number_of_updates++;
                return;
            }
            OOOQueue.push_front(instruction);
        }
        double get_avg_independent_instructions() {
            return static_cast<double>(number_of_independent_instructions/number_of_updates);
        }
        ~OOOWindow() {
            std::cout << static_cast<double>(number_of_independent_instructions/number_of_updates) << std::endl;
        }
};