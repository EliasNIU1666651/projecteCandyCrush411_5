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
void Tauler::inicialitza(int size)
{
    m_nColumnes = size;
    m_nFiles = size;
    m_gravityPointer = 0;
    m_gravityArray[0] = VERMELL;
    m_gravityArray[1] = TARONJA;
    m_gravityArray[2] = GROC;
    m_gravityArray[3] = BLAU;
    m_gravityArray[4] = VERD;
    m_gravityArray[5] = LILA;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            m_tauler[i][j] = randomCandy(i, j);
}


//Fa un moviment, retorna true si resulta en una combinacio de caramels i fals si no s'ha fet res.
bool Tauler::move(Posicio from, Posicio to)
{
    bool doable;
    swap(from, to);
    doable = check();
    if (!doable)
        swap(from, to);
    return doable;
}

void Tauler::swap(Posicio from, Posicio to)
{
    Candy temp = m_tauler[from.x][from.y];
    m_tauler[from.x][from.y] = m_tauler[to.x][to.y];
    m_tauler[to.x][to.y] = temp;
}

//Mira si hi han combinacions, si hi han retorna true hi les elimina.
bool Tauler::check()
{
    return false;
}

bool Tauler::checkEmpty(Posicio &emptyPos)
{
    Candy empty = Candy(NO_COLOR, NO_TIPUS);
    int i = 0, j = m_nColumnes-1;
    bool found = false;
    while (i < m_nFiles && !found)
    {
        while(j >= 0 && !found)
        {
            if (m_tauler[i][j] == empty)
            {
                found = true;
                emptyPos.x = i;
                emptyPos.y = j;
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
        for (int i = emptyPos.y; i > 0; i--)
            m_tauler[emptyPos.x][i] = m_tauler[emptyPos.x][i-1];
        m_tauler[emptyPos.x][0] = m_gravityArray[m_gravityPointer];
        m_gravityPointer = (m_gravityPointer + 1) % 6;
    }
}