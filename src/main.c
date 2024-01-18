#include "net.h"
#include "repository.h"
#include "arguments.h"

/** wiersze, kolumny, liczba iteracji, przedrostek (str), początkowy kierunek mrówki, +opcjonalne wczytanie mapy,
  * +opcjonalne wygenerowanie mapy (na podstawie % zapełnienia) , +opcjonalne rysowanie mapy w czasie rzeczywistym    */
int main( int argc, char** argv ) {

    init_rep( argv[0] );
    init_arguments( argc, argv );

// Program
    net_t net = net_init( arguments.rows, arguments.cols, arguments.direction );

    // implementowanie opcjonalnych parametrów wywołania
    if( arguments.perc_flag ) {
        net_gen_by_perc( net, arguments.percentage );
    }

    // wykonywanie ruchów mrówki
    net_make_moves( net, arguments.iterations );

// Kończenie programu
    net_free( &net );

    return 0; /// sukces
}
