#ifndef INKJET_NOZZLE_H
#define INKJET_NOZZLE_H

#include <inttypes.h>

extern uint16_t strip_buffer;

void hpc6602_init();
void nozzle_trigger(const uint16_t &strip_code);

#endif /* INKJET_NOZZLE_H */