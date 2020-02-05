


#ifndef _A_TP_SCI_H_
#define _A_TP_SCI_H_


#include "sci.h"

void tp_sciInit();
void tp_sciSend(sciBASE_t *sci, uint32 length, uint8 * data);
void tp_sciReceive(sciBASE_t *sci, uint32 length, uint8 * data);








#endif

