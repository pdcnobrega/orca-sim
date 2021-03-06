/** 
 * This file is part of project URSA. More information on the project
 * can be found at 
 *
 * URSA's repository at GitHub: http://https://github.com/andersondomingues/ursa
 *
 * Copyright (C) 2018 Anderson Domingues, <ti.andersondomingues@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA. **/
//lib dependent includes
#include <iostream>
//#include <queue>
#include <vector>
#include <algorithm>
#include <stdint.h>

//api includes
#include <UntimedModel.h>
#include <USignal.h>
#include <USignalSet.h>
#include <UMemory.h> //includes MemoryAddr and MemoryType

//ctor. 
template <typename T>
USignalSet<T>::USignalSet(std::string name, uint32_t nsig) : UntimedModel(name){
	
    //set internal variables
    _num_signals = nsig;
    _signals = new USignal<T>*[_num_signals];

    //create a new vector of signals. Signals are no mapped yep, use MapTo.
    for(uint32_t i = 0; i < _num_signals; i++)
        _signals[i] = new USignal<T>(this->GetName() + "." + to_string(i));

}

//dtor.
template <typename T>
USignalSet<T>::~USignalSet(){
    delete[] _signals;
}


//mapping function
template <typename T>
void USignalSet<T>::MapTo(MemoryType* memptr, MemoryAddr addr){

    MemoryAddr address = addr;
    MemoryType* memtype = memptr;

    //set the proper address to each signal and map
    for(uint32_t i = 0; i < _num_signals; i++){

        _signals[i]->SetAddress(address);
        _signals[i]->MapTo(memtype, address, false);

        address += sizeof(T);

        //caution, pointer arithmetic here
        for(uint32_t j = 0; j < sizeof(T) / sizeof(MemoryType); j++)
            memtype++;
    }
}

//getters
template <typename T>
USignal<T>* USignalSet<T>::GetSignal(uint32_t index){

    if(index > _num_signals - 1 || index < 0){
        std::cout << "warn: requested signals is out of the bounds of the set" << std::endl;
        return nullptr;
    }

    return _signals[index];
}
