#ifndef CANDY_H
#define CANDY_H


#include "definicions.h"
#include <iostream>
#include <sstream>

using namespace std;

//Gestió caracteristiques de cada caramel

class Candy
{
public:
	Candy() {}
	Candy(ColorCandy c, TipusCandy t) : m_color(c), m_tipus(t) {}

	int getColor() const { return m_color; } 
	int getTipus() const { return m_tipus; } 
	void setColor(ColorCandy color) { m_color = color; }
	void setTipus(TipusCandy tipus) { m_tipus = tipus; }
	string intToString(int& canvi);

	bool operator==(Candy& candyIgual);


private:
	ColorCandy m_color;
	TipusCandy m_tipus;

};



#endif
