#ifndef DEFINICIONS_H
#define DEFINICIONS_H

typedef struct
{
    int x;
    int y;
} Posicio;

typedef enum
{
    VERD,
    LILA,
    BLAU,
    TARONJA,
    VERMELL,
    GROC,
    NO_COLOR
} ColorCandy;

typedef enum
{
    NORMAL,
    RATLLAT,
    //RATLLAT_VERTICAL,
    NO_TIPUS
} TipusCandy;

typedef enum
{
    MATCHING_PRIMARI,
    MATCHING_SECUNDARI
} TipusMatch;

typedef enum
{
    HORIZONTAL,
    VERTICAL,
    DESCONEGUDA
} Direccio; 

const Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
const int MAX_FILES = 10;
const int MAX_COLUMNES = 10;
const int MIN_MATCHING = 3;
const int MIN_CARAMEL_ESPECIAL = 4;
const int NUM_COLOR_CANDIES = 6;
const int NUM_TYPE_CANDIES = 4;

#endif
