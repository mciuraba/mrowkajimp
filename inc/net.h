#ifndef NET_H_IS_INCLUDED
#define NET_H_IS_INCLUDED

#include <stdbool.h>

#include "ant.h"


typedef struct {
    unsigned rows;
    unsigned cols;
    bool** map; /// [x][y]

}* net_t;

net_t net_init( unsigned rows, unsigned cols, direction_t ant_direction );
void net_free( net_t* );

void net_make_moves( net_t, int amount );
void net_switch_tile( net_t, unsigned x, unsigned y );

#endif /// NET_H_IS_INCLUDED
