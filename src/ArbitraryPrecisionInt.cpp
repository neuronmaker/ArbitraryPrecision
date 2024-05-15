//
// File: ArbitraryPrecisionInt.cpp
// Project: Arbitrary Precision
// Created by Dalton Herrewynen on Feb 6 2023.
//

#include "ArbitraryPrecisionInt.h"

APint::APint(){
	APint(DEFAULT_INT_SIZE);//set it to the default integer size
}

APint::APint(APint::precisionType newSize){//size is in bits, round up to next byte
	if(newSize%APInt_VAL_SIZE==0) newSize=newSize/APInt_VAL_SIZE;//if divisible (usually by 8 bits per byte)
	else newSize=newSize/APInt_VAL_SIZE+1;//add another byte if between two byte sizes... bad ceiling rounding
	overflow=false;//no overflows on a new instance
	sizeInBytes=newSize;//store the total size
	value=new valueType[sizeInBytes];//ask for memory
	for(precisionType i=0; i<sizeInBytes; ++i){//0 out the bits
		value[i]=0;
	}
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
	}else if(givenInt.sizeInBytes>
			 this->sizeInBytes){//if the new integer is larger, then set our precision to match it
		this->sizeInBytes=givenInt.sizeInBytes;//set to the largest of the sizes
		delete[] this->value;//free memory up
		this->value=new unsigned char[this->sizeInBytes];//get the new chunk of memory
		for(precisionType i=0; i<this->sizeInBytes; ++i){//copy one chunk at a time
			this->value[i]=givenInt.value[i];
		}
	}else{//Otherwise we have the larger size and precision, use ours
		bool negative=APIntSignBit & givenInt.value[givenInt.sizeInBytes-
													1];//like doing 0b10000000 but easier to change, extracts the left most bit in left most byte
		for(precisionType i=0; i<givenInt.sizeInBytes; ++i){//copy all bits from provided APint
			this->value[i]=givenInt.value[i];
		}
		for(precisionType i=givenInt.sizeInBytes; i<this->sizeInBytes; ++i){//zero out the rest of the array
			this->value[i]=0;//this may not be required
		}
		if(negative) this->value[this->sizeInBytes-1]=APIntSignBit;//copy the negative sign bit
	}
	return *this;
}

APint operator+(const APint &left, const APint &right){
	if(left.sizeInBytes!=right.sizeInBytes){
		//convert
	}
	APint result=APint(left.sizeInBytes);//create the result holder
	APint::valueType carry=0;//holder for carry
	for(APint::precisionType i=0; i<left.sizeInBytes; ++i){//special case for the last value which holds sign bit
		if(APIntValMax-(left.value[i]+carry)>
		   right.value[i]){//if max value is lower than the total value, but without writing the max value directly
			//Overflow has undefined behavior, so add total value subtract max value, carry the 1, but split the max value so that we never write a value bigger than the max value
			result.value[i]=(left.value[i]-APIntValMax)+(right.value[i]-1)+carry;
			carry=1;//carry the 1
		}else{//if no overflow happens here, no need to carry next round
			result.value[i]=left.value[i]+right.value[i]+carry;//if no overflow will occur, no need to carry
			carry=0;//if carry happened, make sure it does not happen again
		}
	}
	if(carry!=0) result.overflow=true;//flag an overflow happened if we are carrying out a number at the end.
	return result;
}

APint operator-(const APint &left, const APint &right){
	return APint();
}

/** Makes the entire internal structure full of zeros */
void APint::zeroOut(){
	for(precisionType i=0; i<this->sizeInBytes; ++i){
		this->value[i]=0;
	}
}

/**
 * Dumps a printable string showing the internal state
 * @return Human readable string from internal state
 */
std::string APint::dumpString(){
	std::string buffer="";
	for(precisionType i=0; i<sizeInBytes; ++i){
		buffer+=this->value[i];
	}
	return buffer;
}

/**
 * Generates a printable string from the internal state
 * @return Printable string
 */
std::string APint::dumpBinString(){
	std::string buffer="";
	APint::valueType holder;
	for(precisionType i=0; i<sizeInBytes; ++i){
		holder=this->value[i];
		for(unsigned int j=0; j<APInt_VAL_SIZE; ++j){//extract each bit
			if(0!=(holder & (1<<j))){//figure out if this bit is a 1 or a 0
				buffer+='1';
			}else{
				buffer+='0';
			}
		}
		buffer+=' ';//space for readability
	}
	return buffer;
}

void APint::loadVal(APint::valueType newValue[], APint::precisionType len){
	for(precisionType i=0; i<len && i<sizeInBytes; ++i){
		this->value[i]=newValue[i];
	}
}

void APint::insertByte(APint::valueType val, APint::precisionType index){
	value[index]=val;
}

APint::valueType APint::recallByte(APint::precisionType index){
	return value[index];
}