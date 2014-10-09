/*
 * strutils.h
 *
 *  Created on: 2014 okt. 8
 *      Author: balazs.grill
 */

#ifndef UTILS_STRUTILS_H_
#define UTILS_STRUTILS_H_

int count_chars(char* buffer, int max);

char* itoa (int value, char* buffer, int base);

int strcopy(char* from, char* to, int target);

#endif /* UTILS_STRUTILS_H_ */
