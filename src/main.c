#include <stdio.h>
#include <stdlib.h>

#include "net.h"
#include "printer.h"

int main( int argc, char** argv ) {
    int rows = argc > 1 ? atoi( argv[1] ) : 5;
    int cols = argc > 2 ? atoi( argv[2] ) : 5;
    int moves = argc > 3 ? atoi( argv[3] ) : 5;
    
    net_t net = net_init( rows, cols, 0 ); // 0 to góra
    net_make_moves( net, moves );

	return 0;
}


