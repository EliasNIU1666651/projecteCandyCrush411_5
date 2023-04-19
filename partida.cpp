#include "partida.h"

ifstream& fitxer;

void Partida::inicialitza(const string& nomFitxer)
{
	string c;
	fitxer >> c;
	setCaramelObjectiu(c);
	int QuantitatObjectiu, Moviments;
	fitxer >> QuantitatObjectiu;
	setQuantitatObjectiu(QuantitatObjectiu);
	fitxer >> Moviments;
	setMoviments(Moviments);
	Candy caramel;
	char input;
	int indexFiles = 0;
	fitxer >> input;
	stringToCandy(input);
	while (!fitxer.eof() && (indexFiles < MAX_FILES))
	{
		int indexColumnes = 0;
		
		while (!fitxer.eof() && (indexColumnes < MAX_COLUMNES))
		{
			m_tauler.setTauler(caramel);
			indexColumnes++;
			m_tauler.setNColumnesUtilitzades(indexColumnes);
			fitxer >> input;
			stringToCandy(input);
		}
		
		indexFiles++;
		m_tauler.setNFilesUtilitzades(indexFiles);
	}
	fitxer.close();
}

Candy Partida::stringToCandy(const char& caramelInput)
{
	Candy convertir;
	switch (caramelInput)
	{
		//Caramels Normals
	case 'R':
	{
		convertir.setColor(VERMELL);
		convertir.setTipus(NORMAL);
	}
		break;

	case 'O':
	{
		convertir.setColor(TARONJA);
		convertir.setTipus(NORMAL);
	}
		break;
	case 'Y':
	{
		convertir.setColor(GROC);
		convertir.setTipus(NORMAL);
	}
		break;
	case 'B':
	{
		convertir.setColor(BLAU);
		convertir.setTipus(NORMAL);
	}
		break;
	case 'G':
	{
		convertir.setColor(VERD);
		convertir.setTipus(NORMAL);
	}
		break;
	case 'P':
	{
		convertir.setColor(LILA);
		convertir.setTipus(NORMAL);
	}
		break;
	//Caramels ratllats (suposem que tots son caramels horitzontals)
	case 'r':
	{
		convertir.setColor(VERMELL);
		convertir.setTipus(RATLLAT_HORITZONTAL);
	}
	break;

	case 'o':
	{
		convertir.setColor(TARONJA);
		convertir.setTipus(RATLLAT_HORITZONTAL);
	}
	break;
	case 'y':
	{
		convertir.setColor(GROC);
		convertir.setTipus(RATLLAT_HORITZONTAL);
	}
	break;
	case 'b':
	{
		convertir.setColor(BLAU);
		convertir.setTipus(RATLLAT_HORITZONTAL);
	}
	break;
	case 'g':
	{
		convertir.setColor(GROC);
		convertir.setTipus(RATLLAT_HORITZONTAL);
	}
	break;
	case 'p':
	{
		convertir.setColor(LILA);
		convertir.setTipus(RATLLAT_HORITZONTAL);
	}
	break;
	//POSAR MES CASE AMB CARAMELS BOMBA I CARAMELS "TOCHOS"
	default:
		break;
	}
	return convertir;
}


