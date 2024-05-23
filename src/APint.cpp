//
// File: ArbitraryPrecisionInt.cpp
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

#include "APint.h"

APint::APint():APint(DEFAULT_INT_SIZE){//delegated constructor call
}
/**
 * Construct an integer with a given size
 * @param newSize How many bits of precision
 */
APint::APint(APint::precisionType newSize){//size is in bits, round up to next byte
	if(newSize%APint_VAL_SIZE==0) newSize=newSize/APint_VAL_SIZE;//if divisible (usually by 8 bits per byte)
	else newSize=newSize/APint_VAL_SIZE+1;//add another byte if between two byte sizes... bad ceiling rounding
	overflow=false;//no overflows on a new instance
	sizeInBytes=newSize;//store the total size
	value=new valueType[sizeInBytes];//ask for memory
	zeroOut();//0 out the bits for newly created integers
}

APint::~APint(){
	delete[] value;//delete to avoid memory leaks (ensure memory can be re-used when finished with it)
	value=nullptr;//set to null pointer to avoid dangling references
}

APint &APint::operator=(APint &givenInt){
	if(givenInt.sizeInBytes==this->sizeInBytes){//if precision is the same
		for(precisionType i=0; i<this->sizeInBytes; ++i){//copy one chunk at a time
			this->value[i]=givenInt.value[i];
		}
	//if the new integer is larger, then set our precision to match it
	}else if(givenInt.sizeInBytes>this->sizeInBytes){
		this->sizeInBytes=givenInt.sizeInBytes;//set to the largest of the sizes
		delete[] this->value;//free memory up
		this->value=new unsigned char[this->sizeInBytes];//get the new chunk of memory
		for(precisionType i=0; i<this->sizeInBytes; ++i){//copy one chunk at a time
			this->value[i]=givenInt.value[i];
		}
	}else{//Otherwise we have the larger size and precision, use ours
		bool negative=APintSignBit & givenInt.value[givenInt.sizeInBytes-1];//like doing 0b10000000 but easier to change, extracts the left most bit in left most byte
		for(precisionType i=0; i<givenInt.sizeInBytes; ++i){//copy all bits from provided APint
			this->value[i]=givenInt.value[i];
		}
		for(precisionType i=givenInt.sizeInBytes; i<this->sizeInBytes; ++i){//zero out the rest of the array
			this->value[i]=0;//this may not be required
		}
		if(negative) this->value[this->sizeInBytes-1]=APintSignBit;//copy the negative sign bit
	}
	return *this;
}

APint operator+(const APint &left, const APint &right){
	if(left.sizeInBytes!=right.sizeInBytes){
		//todo convert
	}
	APint result=APint(left.sizeInBytes);//create the result holder
	APint::valueType carry=0;//holder for carry
	for(APint::precisionType i=0; i<left.sizeInBytes; ++i){//special case for the last value which holds sign bit
		//if max value is lower than the total value, but without writing the max value directly
		if(APintValMax-(left.value[i]+carry)>right.value[i]){
			//Overflow has undefined behavior, so add total value subtract max value, carry the 1, but split the max value so that we never write a value bigger than the max value
			result.value[i]=(left.value[i]-APintValMax)+(right.value[i]-1)+carry;
			carry=1;//carry the 1
		}else{//if no overflow happens here, no need to carry next round
			result.value[i]=left.value[i]+right.value[i]+carry;//if no overflow will occur, no need to carry
			carry=0;//if carry happened, make sure it does not happen again
		}
	}//todo handle signed math
	if(carry!=0) result.overflow=true;//flag an overflow happened if we are carrying out a number at the end.
	return result;
}

APint operator-(const APint &left, const APint &right){
	return APint();
}

/** Makes the entire internal structure full of zeros */
void APint::zeroOut(){
	for(precisionType i=0; i<this->sizeInBytes; ++i)
		this->value[i]=0;
	overflow=false;//a blank integer cannot be overflown
}

/**
 * Prints the human-readable number which is represented by the internal state
 * @return a number in a string, or "OVERFLOW" if there was an overflow or underflow
 */
std::string APint::to_string(){
	if(overflow) return "OVERFLOW";
	std::string number;
	//todo finish this when I have division working
	return number;
}

/**
 * Generates a printable string showing the internal 1's and 0's
 * @return Printable string
 */
std::string APint::dumpBinString(){
	std::string buffer="";
	APint::valueType holder;
	for(precisionType i=sizeInBytes; i>0; --i){//Go backwards since we read right to left and print left to right
		holder=this->value[(i-1)];//offset by 1 since we are running from max to 1 instead of max-1 to 0
		for(int j=APint_VAL_SIZE-1; j>=0; --j){//extract each bit
			if(0!=(holder & (1 << j))){//figure out if this bit is a 1 or a 0
				buffer+='1';
			}else{
				buffer+='0';
			}
		}
		buffer+=' ';//space for readability
	}
	return buffer;
}

/**
 * Returns the current size of the integer
 * @return Current number of bytes the integer holds
 */
APint::precisionType APint::getSize() const{
	return sizeInBytes;
}

/**
 * Returns whether the integer has overflown
 * @return True of overflow has occurred.
 */
bool APint::isOverflow() const{
	return overflow;
}

/**
 * Directly loads the values of an array into the integer
 * @param newValue The array to load
 * @param len      How many elements make up the array
 */
void APint::loadVal(APint::valueType newValue[], APint::precisionType len){
	for(precisionType i=0; i<len && i<sizeInBytes; ++i){
		this->value[i]=newValue[i];
	}
}

/**
 * Directly writes a single byte into the integer structure
 * @param val   The value to set
 * @param index Which address to place this value
 */
void APint::insertByte(unsigned char val, APint::precisionType index){
	value[index]=val;//todo check if the index in in range and prevent segmentation faults
}

/**
 * Directly reads a single byte from the integer structure
 * @param index Which address to place this value
 * @return The byte at that address
 */
unsigned char APint::recallByte(APint::precisionType index){
	return value[index];
}

/**
 * Loads a C++ long into the integer structure
 * @param val the C++ long to load in
 * @return true if the value was set successfully, false if something went wrong
 */
bool APint::load(long val){
	if(sizeInBytes<LongBytes) return false;//return an error if the structure is too small for a long
	overflow=false;//successfully loaded integers cannot be overflown
	precisionType i;
	for(i=0; i<LongBytes; ++i){//copy each byte, one at a time using bit masks and shifting
		value[i]=APintValMask & (val>>(i*APint_VAL_SIZE));//shift the int by the predefined number of bits per data element
	}
	for(; i<sizeInBytes; ++i)//for the remaining bytes
		value[i]=0;//zero out the rest of the integer

	if(val<0){//if less than 0, toggle our sign bit, val is already in 2's compliment (usually)
		value[LongBytes-1]&=0b01111111;//toggle off the sign bit of the last byte since we move that bit to our sign bit
		value[sizeInBytes-1]|=APintSignBit;//toggle the sign bit on the final byte of this integer structure
	}
	return true;
}
