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
        OOOWindow(unsigned long number) {
            size = number;
            number_of_independent_instructions = 0;
            number_of_updates = 0;
        }
        void write_instruction(FuncInstr instruction) {
            if (size == 0)
                return;
            if (static_cast<unsigned long>(OOOQueue.size()) == size) {
                OOOQueue.pop_back();
                OOOQueue.push_front(instruction);
                std::list <FuncInstr> templist = OOOQueue;
                for (auto it1 = templist.begin(); it1 != templist.end(); ++it1) {
                    for (auto it3 = it1; it3 != templist.end(); ++it3) {
                        if (it3 == it1)
                            continue;
                        for (int k = 0; k < 3; k++) {
                            if (((*it3).get_src_num(k) == (*it1).get_dst_num()) && !((*it3).get_src_num(k).is_zero()) && !((*it1).get_dst_num().is_zero())) {
                                it3 = templist.erase(it3);
                                it3--;
                            }   
                        }
                    }
                }
                number_of_independent_instructions += templist.size();
                number_of_updates++;
                return;
            }
            OOOQueue.push_front(instruction);
        }
        double get_avg_independent_instructions() {
            if (number_of_updates == 0)
                return 0;
            return (static_cast<double>(number_of_independent_instructions))/(static_cast<double>(number_of_updates));
        }
        ~OOOWindow() {
            std::cout << this->get_avg_independent_instructions() << std::endl;
        }
};