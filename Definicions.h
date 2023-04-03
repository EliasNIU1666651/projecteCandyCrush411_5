#include "Candy.h"

//Definicions en el seu propi fitxer per poder cambiar-los per lo que sigui.
int const MAX_FILES = 20, MAX_COLUMNES = 20;
int const NUM_TYPE_CANDIES = 4, NUM_COLOR_CANDIES = 6;
Candy const emptyCandy = Candy(NO_COLOR, NO_TIPUS);

typedef struct
{
    int x;
    int y;
} Posicio;

typedef enum
{
    
    NO_COLOR
} ColorCandy;

typedef enum
{

    NO_TIPUS
} TipusCandy;
