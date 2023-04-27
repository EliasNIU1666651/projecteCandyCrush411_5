#ifndef TAULER_H
#define TAULER_H
#include "candy.h"
#include "posicio.h"
#include "definicions.h"
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

class Tauler
{

public:
    Tauler() : m_nColumnes(0), m_nFiles(0) {};

    //GETTERS
    int getNColumnes() const { return m_nColumnes; };
    int getNFiles() const { return m_nFiles; };
    int getCandiesDestroyed(ColorCandy c) const { return candiesDestroyed[c]; }
    Candy getTauler(int fila, int columna) const { return m_tauler[fila][columna]; };


    //SETTERS
    void setTauler(Candy& Caramel, int fila, int columna) { m_tauler[fila][columna] = Caramel; };

    void inicialitza(int size);
    bool move(Posicio from, Posicio to);


private:
    Candy m_tauler[MAX_COLUMNES][MAX_FILES];
    Candy m_gravityArray[NUM_COLOR_CANDIES];
    int candiesDestroyed[NUM_COLOR_CANDIES];
    int m_nColumnes;
    int m_nFiles;
    int m_gravityPointer;


    bool check();
    bool checkEmpty(Posicio& emptyPos);
    bool checkForCross(Posicio pos, Posicio posArr[]);
    bool checkForRowVertical(Posicio pos, Posicio posArr[], int candiesInARow);
    bool checkForRow(Posicio pos, Posicio posArr[], int candiesInARow);
    bool checkForRowHoritzontal(Posicio pos, Posicio posArr[], int candiesInARow);

    void swap(Posicio from, Posicio to);
    void removeCombination(Posicio posArr[], int size, Candy c);
    void removeLinia(Posicio p, TipusCandy t);
    void removeAllColors(ColorCandy color);
    void popCandy(Candy c, Posicio p);
    void gravity();
};

#endif

