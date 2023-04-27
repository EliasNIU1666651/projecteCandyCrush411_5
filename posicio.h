#ifndef POSICIO_H
#define POSICIO_H

#include "definicions.h"

class Posicio
{
public:
	Posicio() : m_fila(-1), m_columna(-1) {}
	Posicio(int fila, int columna) : m_fila(fila), m_columna(columna) {}
	void set(int fila, int columna) { m_fila = fila; m_columna = columna; }
	int getFila() { return m_fila; }
	int getColumna() { return m_columna; }
	void setFila(int fila) { m_fila = fila; }
	void setColumna(int columna) { m_columna = columna; }
private:
	int m_fila;
	int m_columna;
};



#endif
