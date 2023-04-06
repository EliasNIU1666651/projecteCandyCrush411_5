#include "Tauler.h"


//Selecciona un Caramel aleatori, utilitzada per generar el tauler.
Candy randomCandy(int i, int j)
{
    srand(time(NULL)+i-j);
    ColorCandy c = static_cast<ColorCandy>(rand() % 6);
    TipusCandy t = static_cast<TipusCandy>(rand() % NUM_TYPE_CANDIES);
    return Candy(c, t);
}

//Inicialitza el tauler amb una mida quadrada.
void Tauler::inicialitza(int tamany)
{
    m_nColumnes = tamany;
    m_nFiles = tamany;
    m_gravityPointer = 0;
    m_gravityArray[0].setColor(VERMELL);    
    m_gravityArray[1].setColor(TARONJA);
    m_gravityArray[2].setColor(GROC);
    m_gravityArray[3].setColor(BLAU);
    m_gravityArray[4].setColor(VERD);
    m_gravityArray[5].setColor(LILA);
    for (int i = 0; i < tamany; i++)
        for (int j = 0; j < tamany; j++)
            m_tauler[i][j] = randomCandy(i, j);
}


//Fa un moviment, retorna true si resulta en una combinacio de caramels i fals si no s'ha fet res.
bool Tauler::move(Posicio from, Posicio to)
{
    bool doable;
    swap(from, to);
    doable = check(from, to);
    if (!doable)
        swap(from, to);
    return doable;
}

void Tauler::swap(Posicio from, Posicio to)
{
    Candy temp = m_tauler[from.getFila()][from.getColumna()];
    m_tauler[from.getFila()][from.getColumna()] = m_tauler[to.getFila()][to.getColumna()];
    m_tauler[to.getFila()][to.getColumna()] = temp;
}

//Mira si hi han combinacions, si hi han retorna true.
bool Tauler::check(Posicio& from, Posicio& to)
{
    bool valid = false;

    if (true) //theres a combination
    {
        //vols fer una funció amb booleà per mirar si els veíns son compatibles? (i dintre utilitzar el operator==)
        valid = true;
        removeCombination(from, to);
        gravity();
        check(from, to);
    }

    return valid;
}

void Tauler::removeCombination(Posicio from, Posicio to)
{
    for (int i = from.getFila(); i <= to.getFila(); i++)
        for (int j = from.getColumna(); j <= to.getColumna(); j++)
            m_tauler[i][j] = emptyCandy;
}

bool Tauler::checkEmpty(Posicio &emptyPos)
{
    int i = 0, j = m_nColumnes-1;
    bool found = false;
    while (i < m_nFiles && !found)
    {
        while(j >= 0 && !found)
        {
            if (m_tauler[i][j] == emptyCandy)
            {
                found = true;
                emptyPos.setFila(i);
                emptyPos.setColumna(j);
            }
            else j--;
        }
        i++;
    }
    return found;
}

void Tauler::gravity()
{
    Posicio emptyPos;
    while(checkEmpty(emptyPos))
    {
        for (int i = emptyPos.getColumna(); i > 0; i--)
            m_tauler[emptyPos.getFila()][i] = m_tauler[emptyPos.getFila()][i - 1];
        m_tauler[emptyPos.getFila()][0] = m_gravityArray[m_gravityPointer];
        m_gravityPointer = (m_gravityPointer + 1) % 6;
    }
}