#include "partida.h"


void Partida::inicialitza(const string& nomFitxer)
{
	ifstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		char c;
		fitxer >> c;
		ColorCandy colorObjectiu = stringToCandy(c).getColor();
		setCaramelObjectiu(colorObjectiu);
		int QuantitatObjectiu, Moviments;
		fitxer >> QuantitatObjectiu;
		setQuantitatObjectiu(QuantitatObjectiu);
		fitxer >> Moviments;
		setMoviments(Moviments);
		Candy caramel;
		char input;
		int indexFiles = 0;
		while (!fitxer.eof() && (indexFiles < MAX_FILES))
		{
			int indexColumnes = 0;

			while (!fitxer.eof() && (indexColumnes < MAX_COLUMNES))
			{
				fitxer >> input;
				caramel = stringToCandy(input);
				m_tauler.setTauler(caramel, indexColumnes, indexFiles);
				indexColumnes++;
			}

			indexFiles++;
		}
	}
	fitxer.close();
}

void Partida::fesMoviment(const Posicio &pos1, const Posicio &pos2)
{
	m_tauler.move(pos1, pos2);
	m_nQuantitatCaramels = m_tauler.getCandiesDestroyed(m_CaramelObjectiu);
}

void Partida::escriuTauler(const string &nomFitxer)
{
	ofstream fitxer;
	fitxer.open(nomFitxer);
	if (fitxer.is_open())
	{
		for (int fFiles = 0; fFiles < MAX_FILES; fFiles ++)
		{
			for (int fColumnes = 0; fColumnes < MAX_FILES; fColumnes ++)
			{
				char c = candyToString(m_tauler.getTauler(fFiles, fColumnes));
				fitxer << c << " ";
			}
			fitxer << endl;
		}
	}
	fitxer.close();
}

Candy Partida::stringToCandy(const char& caramelInput)
{
	Candy convertir;
	if (caramelInput >= 'A' && caramelInput <= 'Z')
		convertir.setTipus(NORMAL);
	else if (caramelInput >= 'a' && caramelInput <= 'z') //Caramels ratllats (suposem que tots son caramels horitzontals)
		convertir.setTipus(RATLLAT_HORITZONTAL);

	switch (caramelInput)
	{
		//Caramels Normals
	case 'R':
	case 'r':
		convertir.setColor(VERMELL);
		break;

	case 'O':
	case 'o':
		convertir.setColor(TARONJA);
		break;

	case 'Y':
	case 'y':
		convertir.setColor(GROC);
		break;

	case 'B':
	case 'b':
		convertir.setColor(BLAU);
		break;

	case 'G':
	case 'g':
		convertir.setColor(VERD);
		break;

	case 'P':
	case 'p':
		convertir.setColor(LILA);
		break;
	//POSAR MES CASE AMB CARAMELS BOMBA I CARAMELS "TOCHOS"
	//De moment no representem atres caramels per falta de simbols
	default:
		convertir.setColor(NO_COLOR);
		convertir.setTipus(NO_TIPUS);
		break;
	}
	return convertir;
}

char Partida::candyToString(const Candy& caramelInput)
{
	char convertir;
	switch (caramelInput.getColor())
	{
		//Caramels Normals
	case VERD:
		convertir = 'G';
		break;

	case LILA:
		convertir = 'P';
		break;

	case TARONJA:
		convertir = 'O';
		break;

	case GROC:
		convertir = 'Y';
		break;

	case BLAU:
		convertir = 'B';
		break;

	case VERMELL:
		convertir = 'R';
		break;
	//POSAR MES CASE AMB CARAMELS BOMBA I CARAMELS "TOCHOS"
	//De moment no representem atres caramels per falta de simbols
	default:
		convertir = '#';
		break;
	}
	if (caramelInput.getTipus() == RATLLAT_HORITZONTAL || caramelInput.getTipus() == RATLLAT_VERTICAL)
		convertir += ('a' - 'A');
	return convertir;
}
