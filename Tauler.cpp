#include "tauler.h"

//Selecciona un Caramel aleatori, utilitzada per generar el tauler.
Candy randomCandy(int i, int j)
{
    srand(time(NULL) + i - j);
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
    m_gravityArray[0].setColor(VERMELL); m_gravityArray[0].setTipus(NORMAL);
    m_gravityArray[1].setColor(TARONJA); m_gravityArray[1].setTipus(NORMAL);
    m_gravityArray[2].setColor(GROC); m_gravityArray[2].setTipus(NORMAL);
    m_gravityArray[3].setColor(BLAU); m_gravityArray[3].setTipus(NORMAL);
    m_gravityArray[4].setColor(VERD); m_gravityArray[4].setTipus(NORMAL);
    m_gravityArray[5].setColor(LILA); m_gravityArray[5].setTipus(NORMAL);
    for (int i = 0; i < tamany; i++)
        for (int j = 0; j < tamany; j++)
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
    Candy cFrom = m_tauler[from.getFila()][from.getColumna()];
    Candy cTo = m_tauler[to.getFila()][to.getColumna()];
    m_tauler[from.getFila()][from.getColumna()] = m_tauler[to.getFila()][to.getColumna()];
    m_tauler[to.getFila()][to.getColumna()] = cFrom;
    if (cFrom.getTipus() == BOMBA_DE_CARAMEL)
        removeAllColors(cTo.getColor());
    else if (cTo.getTipus() == BOMBA_DE_CARAMEL)
        removeAllColors(cFrom.getColor());

}

//Mira si hi han combinacions, si hi han retorna true.
bool Tauler::check()
{
    bool valid = false;

    for (int i = m_nFiles - 1; i >= 0; i--)
    {
        for (int j = m_nColumnes - 1; j >= 0; j--)
        {
            Posicio pos(i, j);
            Posicio posArr[4]; // [pos1.1, pos1.2, pos2.1, pos2.2] --->  v;
            if (checkForRowVertical(pos, posArr, 4))
            {
                valid = true;
                Candy c(m_tauler[i][j].getColor(), RATLLAT_HORITZONTAL);
                removeCombination(posArr, 2, c);
                if (check())
                {
                    gravity();
                }
                else
                {
                    gravity();
                }
                check();
            }
            else if (checkForRowHoritzontal(pos, posArr, 4))
            {
                valid = true;
                if ((i == 1) && (j == 4))
                {
                    Candy c(m_tauler[i][j].getColor(), RATLLAT_HORITZONTAL);
                    removeCombination(posArr, 2, c);
                }
                else
                {
                    Candy c(m_tauler[i][j].getColor(), RATLLAT_VERTICAL);
                    removeCombination(posArr, 2, c);
                }

                if (check())
                {
                    gravity();
                }
                else
                {
                    gravity();
                }
                check();
            }
            else if (checkForRow(pos, posArr, 3)) //Check if its just 3 in a row, lowest priority
            {
                valid = true;
                Candy c(NO_COLOR, NO_TIPUS);
                removeCombination(posArr, 2, c);
                if (check())
                {
                    gravity();
                }
                else
                {
                    gravity();
                }

                check();
            }
        }
    }
    return valid;
}

void Tauler::removeLinia(Posicio p, TipusCandy t)
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    if (t == RATLLAT_HORITZONTAL)
        for (int i = 0; i < m_nColumnes; i++)
            if (m_tauler[p.getFila()][i].getTipus() != RATLLAT_HORITZONTAL)
            {
                popCandy(m_tauler[p.getFila()][i], Posicio(p.getFila(), i));
            }
            else
            {
                m_tauler[p.getFila()][i] = emptyCandy;
            }

    else if (t == RATLLAT_VERTICAL)
        for (int i = 0; i < m_nFiles; i++)
            if (m_tauler[i][p.getColumna()].getTipus() != RATLLAT_VERTICAL)
            {
                popCandy(m_tauler[i][p.getColumna()], Posicio(i, p.getColumna()));

            }
            else
            {
                m_tauler[i][p.getColumna()] = emptyCandy;
            }

}

void Tauler::removeAllColors(ColorCandy color)
{
    for (int i = 0; i < m_nFiles; i++)
        for (int j = 0; j < m_nColumnes; j++)
            if (m_tauler[i][j].getColor() == color)
                popCandy(m_tauler[i][j], Posicio(i, j));
}

void Tauler::popCandy(Candy c, Posicio p)
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    switch (c.getTipus())
    {
    case RATLLAT_HORITZONTAL:
    case RATLLAT_VERTICAL:
        removeLinia(p, c.getTipus());
        break;

    case ENVOLTORI:
        for (int i = -1; i <= 1; i++)
            for (int j = -1; j <= 1; j++)
                if (!(i == 0 && j == 0))
                    popCandy(m_tauler[p.getFila() + i][p.getColumna() + j], Posicio(p.getFila() + i, p.getColumna() + j));
        m_tauler[p.getFila()][p.getColumna()] = emptyCandy;
        break;

    case BOMBA_DE_CARAMEL:

        break;

    case NORMAL:
    default:
        m_tauler[p.getFila()][p.getColumna()] = emptyCandy;
        break;
    }
    candiesDestroyed[c.getColor()]++;
}

void Tauler::removeCombination(Posicio posArr[], int size, Candy c)
{
    for (int s = 0; s < size / 2; s++)
        for (int i = 0; i <= abs(posArr[1 + s * 2].getFila() - posArr[s * 2].getFila()); i++)
            for (int j = 0; j <= abs(posArr[1 + s * 2].getColumna() - posArr[s * 2].getColumna()); j++)
            {
                Posicio pos(posArr[s * 2].getFila() + i, posArr[s * 2].getColumna() + j);
                popCandy(m_tauler[pos.getFila()][pos.getColumna()], pos);
            }
    if (c.getTipus() == RATLLAT_VERTICAL)
    {
        m_tauler[posArr[0].getFila()][posArr[0].getColumna() + 1] = c;
    }
    else
    {
        m_tauler[posArr[0].getFila()][posArr[0].getColumna()] = c;
    }

}

bool Tauler::checkEmpty(Posicio& emptyPos)
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    int i = m_nFiles - 1, j = 0;
    bool found = false;
    while (i >= 0 && !found)
    {
        j = 0;
        while (j <= m_nColumnes - 1 && !found)
        {
            if (m_tauler[i][j] == emptyCandy)
            {
                found = true;
                emptyPos.setFila(i);
                emptyPos.setColumna(j);
            }
            else j++;
        }
        i--;
    }
    return found;
}

void Tauler::gravity()
{
    Candy emptyCandy = Candy(NO_COLOR, NO_TIPUS);
    Posicio emptyPos;

    while (checkEmpty(emptyPos))
    {

        if ((emptyPos.getFila() - 1 >= 0) && (m_tauler[emptyPos.getFila() - 1][emptyPos.getColumna()].getColor() != NO_COLOR))
        {
            m_tauler[emptyPos.getFila()][emptyPos.getColumna()] = m_tauler[emptyPos.getFila() - 1][emptyPos.getColumna()];
            m_tauler[emptyPos.getFila() - 1][emptyPos.getColumna()] = emptyCandy;

        }
        else
        {
            if ((emptyPos.getFila() - 2 >= 0) && (m_tauler[emptyPos.getFila() - 2][emptyPos.getColumna()].getColor() != NO_COLOR))
            {
                m_tauler[emptyPos.getFila()][emptyPos.getColumna()] = m_tauler[emptyPos.getFila() - 2][emptyPos.getColumna()];
                m_tauler[emptyPos.getFila() - 2][emptyPos.getColumna()] = emptyCandy;
            }
            else
            {
                if ((emptyPos.getFila() - 3 >= 0) && (m_tauler[emptyPos.getFila() - 3][emptyPos.getColumna()].getColor() != NO_COLOR))
                {
                    m_tauler[emptyPos.getFila()][emptyPos.getColumna()] = m_tauler[emptyPos.getFila() - 3][emptyPos.getColumna()];
                    m_tauler[emptyPos.getFila() - 3][emptyPos.getColumna()] = emptyCandy;
                }
                else
                {
                    if ((emptyPos.getFila() - 4 >= 0) && (m_tauler[emptyPos.getFila() - 4][emptyPos.getColumna()].getColor() != NO_COLOR))
                    {
                        m_tauler[emptyPos.getFila()][emptyPos.getColumna()] = m_tauler[emptyPos.getFila() - 4][emptyPos.getColumna()];
                        m_tauler[emptyPos.getFila() - 4][emptyPos.getColumna()] = emptyCandy;
                    }
                    else
                    {
                        if ((emptyPos.getFila() - 5 >= 0) && (m_tauler[emptyPos.getFila() - 5][emptyPos.getColumna()].getColor() != NO_COLOR))
                        {
                            m_tauler[emptyPos.getFila()][emptyPos.getColumna()] = m_tauler[emptyPos.getFila() - 5][emptyPos.getColumna()];
                            m_tauler[emptyPos.getFila() - 5][emptyPos.getColumna()] = emptyCandy;
                        }
                        else
                        {
                            if (m_gravityPointer == 6)
                            {
                                m_gravityPointer = 0;
                            }
                            m_tauler[emptyPos.getFila()][emptyPos.getColumna()] = m_gravityArray[m_gravityPointer];
                            if (m_gravityPointer != 6)
                            {
                                m_gravityPointer++;
                            }
                            else
                            {
                                m_gravityPointer = 0;
                            }
                        }
                    }
                }
            }
        }

    }

}

bool Tauler::checkForRowHoritzontal(Posicio pos, Posicio posArr[], int candiesInARow)
{
    Candy c = m_tauler[pos.getFila()][pos.getColumna()];
    bool valid = false;

    if ((pos.getColumna() + 1 < 10) && (m_tauler[pos.getFila()][pos.getColumna()].getColor() != NO_COLOR))
    {
        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 2]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 3]))
        {
            valid = true;
            posArr[0] = Posicio(pos.getFila(), pos.getColumna());
            posArr[1] = Posicio(pos.getFila(), pos.getColumna() + 3);
        }
        else
        {
            if ((pos.getColumna() - 1 > 0) && (pos.getColumna() + 2 < 10))
            {
                if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 2]))
                {
                    valid = true;
                    posArr[0] = Posicio(pos.getFila(), pos.getColumna() - 1);
                    posArr[1] = Posicio(pos.getFila(), pos.getColumna() + 2);
                }
                else
                {

                    if ((pos.getColumna() - 2 > 0) && (pos.getColumna() + 1 < 10))
                    {
                        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 2]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 1]))
                        {
                            valid = true;
                            posArr[0] = Posicio(pos.getFila(), pos.getColumna() - 2);
                            posArr[1] = Posicio(pos.getFila(), pos.getColumna() + 1);
                        }
                        else
                        {
                            if (pos.getColumna() - 3 >= 0)
                            {
                                if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 2]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 3]))
                                {
                                    valid = true;
                                    posArr[0] = Posicio(pos.getFila(), pos.getColumna() - 3);
                                    posArr[1] = Posicio(pos.getFila(), pos.getColumna());
                                }
                            }


                        }

                    }

                }
            }



        }
    }

    return valid;
}

bool Tauler::checkForRow(Posicio pos, Posicio posArr[], int candiesInARow)
{
    Candy c = m_tauler[pos.getFila()][pos.getColumna()];
    bool valid = false;


    if ((pos.getColumna() + 1 < 10) && (pos.getFila() < 10) && (m_tauler[pos.getFila()][pos.getColumna()].getColor() != NO_COLOR))
    {
        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 2]))
        {
            valid = true;
            posArr[0] = Posicio(pos.getFila(), pos.getColumna());
            posArr[1] = Posicio(pos.getFila(), pos.getColumna() + 2);
        }
        else
        {
            if (pos.getColumna() - 1 > 0)
            {
                if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() + 1]))
                {
                    valid = true;
                    posArr[0] = Posicio(pos.getFila(), pos.getColumna() - 1);
                    posArr[1] = Posicio(pos.getFila(), pos.getColumna() + 1);
                }
                else
                {
                    if (pos.getColumna() - 2 >= 0)
                    {
                        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 1]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila()][pos.getColumna() - 2]))
                        {
                            valid = true;
                            posArr[0] = Posicio(pos.getFila(), pos.getColumna() - 2);
                            posArr[1] = Posicio(pos.getFila(), pos.getColumna());
                        }
                    }
                }
            }

        }
    }


    if ((pos.getFila() + 1 < 10) && (m_tauler[pos.getFila()][pos.getColumna()].getColor() != NO_COLOR))
    {
        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 2][pos.getColumna()]))
        {
            valid = true;
            posArr[0] = Posicio(pos.getFila(), pos.getColumna());
            posArr[1] = Posicio(pos.getFila() + 2, pos.getColumna());
        }
        else
        {
            if (pos.getFila() - 1 > 0)
            {
                if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 1][pos.getColumna()]))
                {
                    valid = true;
                    posArr[0] = Posicio(pos.getFila() - 1, pos.getColumna());
                    posArr[1] = Posicio(pos.getFila() + 1, pos.getColumna());
                }
                else
                {

                    if (pos.getFila() - 2 >= 0)
                    {
                        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 2][pos.getColumna()]))
                        {
                            valid = true;
                            posArr[0] = Posicio(pos.getFila() - 2, pos.getColumna());
                            posArr[1] = Posicio(pos.getFila(), pos.getColumna());
                        }
                    }
                }
            }

        }
    }


    return valid;

}

bool Tauler::checkForRowVertical(Posicio pos, Posicio posArr[], int candiesInARow)
{
    bool valid = false;

    if ((pos.getFila() + 1 < 10) && (m_tauler[pos.getFila()][pos.getColumna()].getColor() != NO_COLOR))
    {
        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 2][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 3][pos.getColumna()]))
        {
            valid = true;
            posArr[0] = Posicio(pos.getFila(), pos.getColumna());
            posArr[1] = Posicio(pos.getFila() + 3, pos.getColumna());
        }
        else
        {
            if ((pos.getFila() - 1 > 0) && (pos.getFila() + 2 < 10))
            {
                if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 2][pos.getColumna()]))
                {
                    valid = true;
                    posArr[0] = Posicio(pos.getFila() - 1, pos.getColumna());
                    posArr[1] = Posicio(pos.getFila() + 2, pos.getColumna());
                }
                else
                {
                    if ((pos.getFila() - 2 > 0) && (pos.getFila() + 1 < 10))
                    {
                        if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 2][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() + 1][pos.getColumna()]))
                        {
                            valid = true;
                            posArr[0] = Posicio(pos.getFila() - 2, pos.getColumna());
                            posArr[1] = Posicio(pos.getFila() + 1, pos.getColumna());
                        }
                        else
                        {
                            if (pos.getFila() - 3 >= 0)
                            {
                                if ((m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 1][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 2][pos.getColumna()]) && (m_tauler[pos.getFila()][pos.getColumna()] == m_tauler[pos.getFila() - 3][pos.getColumna()]))
                                {
                                    valid = true;
                                    posArr[0] = Posicio(pos.getFila() - 3, pos.getColumna());
                                    posArr[1] = Posicio(pos.getFila(), pos.getColumna());
                                }
                            }


                        }
                    }
                }
            }

        }
    }

    return valid;
}

bool Tauler::checkForCross(Posicio pos, Posicio posArr[])
{
    bool valid = false;
    Candy c = m_tauler[pos.getFila()][pos.getColumna()];
    for (int i = 0; i < 3 && !valid; i++)
    {
        int j = pos.getFila() - i;
        bool equal = true;
        while (equal && j < pos.getFila() + 3 - i)
        {
            if (j < 0 && j >= m_nColumnes)
                equal = false;
            else if (!(c == m_tauler[j][pos.getColumna()]))
                equal = false;
            else
                j++;
        }

        if (equal)
        {
            posArr[0] = Posicio(j - 3, pos.getColumna());
            posArr[1] = Posicio(j, pos.getColumna());
            for (int k = 0; k < 3; k++)
            {
                int j = pos.getColumna() - k;
                bool equal = true;
                while (equal && j < pos.getColumna() + 3 - k)
                {
                    if (j < 0 && j >= m_nColumnes)
                        equal = false;
                    else if (!(c == m_tauler[pos.getFila()][j]))
                        equal = false;
                    else
                        j++;
                }
                if (equal)
                {
                    posArr[2] = Posicio(j - 3, pos.getFila());
                    posArr[3] = Posicio(j, pos.getFila());
                }
            }
        }
        valid = equal;
    }
    return valid;
}



