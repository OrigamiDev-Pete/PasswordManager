/*******************************************************************************
* Author: Peter de Vroom
* 
* The header file for the In/Out functionality of the program.
*******************************************************************************/

#ifndef IO_H
#define IO_H

#include "util.h"

enum compression { huffman, runLength };

boolean saveData(boolean encrypt, boolean compress, enum compression cmp_type);

boolean loadData(boolean decrypt, boolean decompress, enum compression cmp_type);


#endif /* IO_H */