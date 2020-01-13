//
// Created by MK on 13.01.2020.
//

#ifndef N_QUEENS_SOLVER_H
#define N_QUEENS_SOLVER_H

#include <stdint.h>
#include <stdbool.h>

#ifndef AREA_SIZE_BYTES
    #define AREA_SIZE_T uint8_t
    #define AREA_MAX_SIZE UINT8_MAX
#elif AREA_SIZE_BYTES == 2              //If 255 is not enough for melting computer - Beware
    #define AREA_SIZE_T uint16_t
    #define AREA_MAX_SIZE UINT16_MAX
#else
    #define AREA_SIZE_T uint8_t
    #define AREA_MAX_SIZE UINT8_MAX
#endif


void solution(int32_t area_size, bool draw);

#endif //N_QUEENS_SOLVER_H
