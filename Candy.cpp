#include "candy.h"

bool Candy::operator==(Candy& candyIgual)
{
	//Caramels compatibles, ha de ser mateix color. El tipus es indiferent ja que al fer un moviment vàlid, s'accionarà el tipus també, sent valida la parella (normal, normal, ratllat)
	if (candyIgual.getColor()==m_color)
	{
		return true;
	}
    return false;
}

string Candy::intToString(int& canvi)
{
	//Per poder inicialitzar a traves d'un string o per poder llegir o escriure
	ostringstream ss;
	ss << canvi;
	return ss.str();
}

