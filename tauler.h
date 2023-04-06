#ifndef TAULER_H
#define TAULER_H
#include "candy.h"
#include "posicio.h"
#include "definicions.h"
#include <string>
#include <iostream>
#include<fstream>
#include <bits.h>
#include <cstdlib>
#include <vector>

using namespace std;

class Tauler
{

public:
    Tauler() : m_nColumnes(0), m_nFiles(0) {};

    //GETTERS
    int getNColumnes() const { return m_nColumnes; }
    int getNFiles() const { return m_nFiles; }
    int getNColumnesUtilitzades() const { return m_nColumnesUtilitzades; }
    int getNFilesUtilitzades() const { return m_nFilesUtilitzades; }
    Candy getTauler() const { return m_tauler[getNFilesUtilitzades()][getNColumnesUtilitzades()]; }


    //SETTERS
    void setNColumnesUtilitzades(int& Columna) { m_nColumnesUtilitzades = Columna; }
    void setNFilesUtilitzades(int& Fila) { m_nFilesUtilitzades = Fila; }
    void setTauler(Candy& Caramel) { m_tauler[getNFilesUtilitzades()][getNColumnesUtilitzades()] = Caramel; }

    void inicialitza(int size);
    bool move(Posicio from, Posicio to);

private:
    Candy m_tauler[MAX_COLUMNES][MAX_FILES];
    int m_nColumnes;
    int m_nFiles;
    Candy m_gravityArray[NUM_COLOR_CANDIES];
    int m_gravityPointer;

    
    bool check(Posicio& from, Posicio& to);
    bool checkEmpty(Posicio& emptyPos);

    void swap(Posicio from, Posicio to);
    void removeCombination(Posicio from, Posicio to);
    void gravity();

    //PER INICIALITZAR A PARTIDA.H
    int m_nColumnesUtilitzades;
    int m_nFilesUtilitzades;
};

#endif

