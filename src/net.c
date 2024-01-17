#include "net.h"
#include "repository.h"

#include <stdlib.h>
#include <string.h>
#include <time.h>


net_t net_init( unsigned rows, unsigned cols, direction_t ant_direction ) {
// ALOKACJA PAMIĘCI
    net_t net = (net_t) malloc( sizeof *net );
    if( net == NULL ) {
        push_crit_error( "nie udało się zainicjować siatki - błąd pamięci" );
        return NULL;
    }

    // Mapa
    net->map = (bool**) malloc( cols * sizeof(bool*) );
    if( net->map == NULL ) { // zabezpieczenie
        free( net );

        push_crit_error( "nie udało się zainicjować mapy w siatce - błąd pamięci [1]" );
        return NULL;
    }
    for( unsigned i=0; i < cols; ++i ) {
        net->map[i] = (bool*) calloc( rows, sizeof(bool) ); // wypełnia mapę białymi polami
        if( net->map[i] == NULL ) { // zabezpieczenie
            // zwalnianie dotychczasowo zajętej pamięci
            for( unsigned j=0; j < i; ++j) {
                free( net->map[j] );
            }
            free( net->map );

            free( net );

            push_crit_error( "nie udało się zainicjować mapy w siatce - błąd pamięci [2]" );
            return NULL;
        }
    }
    
    // GUI
    net->gui = net_gui_init( rows, cols );
    if( net->gui == NULL ) { // wystąpił jakiś błąd przy inicjalizacji gui
        // zwalnianie dotychczasowo zajętej pamięci
        for( unsigned i=0; i < net->cols; ++i ) {
            free( net->map[i] );
        }
        free( net->map );

        free( net );

        push_crit_error( "nie udało się zainicjować odwzorowanie graficznego siatki - błąd pamięci" );
        return NULL;
    }

    // Mrówka
    net->ant = ant_init( rows, cols, -1, -1, ant_direction );
    if( net->ant == NULL ) { // błąd alokacji pamięci
        // zwalnianie dotychczasowo zajętej pamięci
        for( unsigned i=0; i < net->cols; ++i ) {
            free( net->map[i] );
        }
        free( net->map );

        net_gui_free( &(net->gui) );
        free( net );

        push_crit_error( "nie udało się zainicjować mrówki w siatce - błąd pamięci" );
        return NULL;
    }

// WARTOŚCI POCZĄTKOWE
    net->rows = rows;
    net->cols = cols;

    return net;
}

void net_free( net_t* net_ptr ) {
    if( *net_ptr == NULL ) { // zabezpieczenie
        push_error( "nie udało się zwolnić pamięci siatki - nie ma przydzielonej pamięci" );
        return;
    }

// Zwalnianie pamięci
    net_t net = *net_ptr;

    for( unsigned i=0; i < net->cols; ++i ) {
        free( net->map[i] );
    }
    free( net->map );

    net_gui_free( &(net->gui) );
    ant_free( &(net->ant) );
    free( net );

    *net_ptr = NULL;
}



void net_make_moves( net_t net, int amount ) {
    unsigned last_x = 0;
    unsigned last_y = 0;

    for( int i=0; i < amount; ++i ) {
        last_x = net->ant->x;
        last_y = net->ant->y;

        // wykonywanie ruchu
        ant_move( net->ant, net->map[ net->ant->x ][ net->ant->y ] );
        net_switch_tile( net, last_x, last_y );
    }
}

void net_switch_tile( net_t net, unsigned x, unsigned y ) {
    // zabezpieczenie
    if( net->cols <= x || net->rows <= y ) {
        push_error( "nie udało się zmienić pola - podane pole wychodzi poza granice siatki" );
        return;
    }

    // zamiana pola
    if( net->map[x][y] == WHITE ) {
        net->map[x][y] = BLACK;
    }
    else { // czarne
        net->map[x][y] = WHITE;
    }
}
