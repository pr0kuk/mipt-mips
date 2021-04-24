#include "ooo_window.h"

template <typename FuncInstr> 
OOOWindow<FuncInstr>::OOOWindow(unsigned long number) {
    size = number;
    number_of_independent_instructions = 0;
    number_of_updates = 0;
}


template <typename FuncInstr> 
OOOWindow<FuncInstr>::~OOOWindow() {
    std::cout << this->get_avg_independent_instruction() << std::endl;
}

template <typename FuncInstr> 
void OOOWindow<FuncInstr>::write_instruction(FuncInstr instruction) {
    if (OOOQueue.size() == size)
        OOOQueue.pop_back();
    OOOQueue.insert(OOOQueue.begin(), instruction);
    if (OOOQueue.size() != size)
        return;
    int count = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < i; j++) {
            int temp = 0;
            if (is_zero(OOOQueue[i]) && is_zero(OOOQueue[j])) {
                count += 2;
                break;
            }
            for (int k = 0; k < 3; k++)
                if (OOOQueue[i].get_src_num(k) != OOOQueue[i].get_src_dst())
                    temp++;
            if (temp == 3)
                count += 2;
        }
    }
    number_of_independent_instructions += count;
    number_of_updates++;
}

template <typename FuncInstr> 
double OOOWindow<FuncInstr>::get_avg_independent_instruction() {
    return static_cast<double>(number_of_independent_instructions/number_of_updates);
}



/*int main()
{
    OOOWindow <int> mywindow{4};
    for(int i = 0; i < 20; i++) {
        mywindow.write_instruction(i);
    }
    mywindow.write_instruction(19);
    return 0;
}*/