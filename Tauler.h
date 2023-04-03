#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "Definicions.h"
#include "Candy.h"


class Tauler
{

public:
    Tauler() : m_nColumnes(0), m_nFiles(0) {};

    int getNColumnes() const { return m_nColumnes; }
    int getNFiles() const { return m_nFiles; }

    void inicialitza(int size);
    bool move(Posicio from, Posicio to);

private:
    Candy m_tauler[MAX_COLUMNES][MAX_FILES];
    int m_nColumnes;
    int m_nFiles;
    Candy m_gravityArray[NUM_COLOR_CANDIES];
    int m_gravityPointer;
    
    void swap(Posicio from, Posicio to);
    bool check();
    bool checkEmpty(Posicio& emptyPos);
    void gravity();
};