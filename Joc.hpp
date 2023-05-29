#ifndef Joc_hpp
#define Joc_hpp

#include <stdio.h>
#include <string>
#include "InfoJoc.h"
#include "partida.h"
#include "posicio.h"

using namespace std;

typedef enum
{
    ESTAT_JOC_ESPERA,
    ESTAT_JOC_INTERCANVI,
    ESTAT_JOC_MOVIMENTS,
    ESTAT_FINAL
} EstatJoc;


class Joc 
{
public:
    Joc() : m_temps(0), m_visible(true) {};
    
    void inicialitza(const string& nomFitxerInicial);
    void actualitza(int mousePosX, int mousePosY, bool mouseStatus, double deltaTime);
private:
    double m_temps;
    bool m_visible; 
    Partida m_partida;
    EstatJoc m_estat;
   
};

#endif /* Joc_hpp */
