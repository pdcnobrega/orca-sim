#ifndef __PROCESSOR_STATE_H
#define __PROCESSOR_STATE_H

#define NUMBER_OF_REGISTERS 32

/** Defines a generic state model 
  * for use within processor models. */
template <typename T>
struct ProcessorState{

	//please note that register to from 0 to NUM_REGS, and
	//the next reg (which would overflow the array size)
	//falls in the PC instead. For example, for an arch with
	//32 register, the register number 33 is PC.
	T regs[NUMBER_OF_REGISTERS]; //general purpose registers
	T pc_prev;  //value of pc in the last cycle (zero if 1st)
	T pc;       //the value of pc in the current cycle
	T pc_next;  //value of pc in the next cycle
	T bp;       //flag's risen if breakpoint has being reached

	//#ifdef ORCA_ENABLE_GDBRSP
	T pause;
	T steps;
	//#endif
};

//Some of the most used instances. More can be added later.
template struct ProcessorState<uint8_t>;
template struct ProcessorState<uint16_t>;
template struct ProcessorState<uint32_t>;
template struct ProcessorState<uint64_t>;

//Some of the most used instances. More can be added later.
template struct ProcessorState<int8_t>;
template struct ProcessorState<int16_t>;
template struct ProcessorState<int32_t>;
template struct ProcessorState<int64_t>;

#endif /** __PROCESSOR_STATE_H **/
