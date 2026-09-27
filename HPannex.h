#pragma once
#ifndef HP_ANNEX_H
#define HP_ANNEX_H
#include"HPmath.h"
inline HP_dec HPI_to_HPD(const HP_int& to){
	HP_dec num;
	num.integer=to;
	return num;
}
inline HP_int HPD_to_HPI(const HP_dec& to){
	return to.integer;
}
#endif
