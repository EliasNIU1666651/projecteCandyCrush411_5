#include "candy.h"

bool Candy::operator==(Candy& candyIgual)
{
	//Caramels compatibles, ha de ser mateix color. El tipus es indiferent ja que al fer un moviment v�lid, s'accionar� el tipus tamb�, sent valida la parella (normal, normal, ratllat)
	return candyIgual.getColor() == m_color;
}

string Candy::intToString(int& canvi)
{
	//Per poder inicialitzar a traves d'un string o per poder llegir o escriure
	ostringstream ss;
	ss << canvi;
	return ss.str();
}

