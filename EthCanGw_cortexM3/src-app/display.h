/*
 * display.h
 *
 *  Created on: 2014.08.27.
 *      Author: balazs.grill
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

typedef void (*GetValue)(char* buffer);

typedef struct DisplayEntry {
	char* label;
	GetValue getValue;
} DisplayEntry;

extern void display_init();
extern void display_refresh();

extern void display_addEntry(DisplayEntry *entry);

#endif /* DISPLAY_H_ */
