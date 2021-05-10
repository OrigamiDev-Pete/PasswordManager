/*******************************************************************************
* Author: Peter de Vroom
* 
* The header file for the In/Out functionality of the program.
*******************************************************************************/

#ifndef IO_H
#define IO_H

#include "util.h"

enum compression { huffman, runLength };

bool saveData(boolean encrypt, boolean compress, enum compression cmp_type);

bool loadData(boolean decrypt, boolean decompress, enum compresion cmp_type);


#endif /* IO_H */