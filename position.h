#pragma once
#include "constants.h"

class Position {
public:
	Position(int = 0, int = 0);
	Position(Position, DIRECTION);
	Position(const Position&);
	int getX() const;
	int getY() const;
	int setX(int);
	int setY(int);
	private:
	int m_x, m_y;
};

bool operator==(const Position&, const Position&); //No sé si seria millor si aquesta funció fos una funció membre de Position o un overload global (com està actualment)
//Operacions que permeten tractar els objectes Position com a vectors ja que els hi donen les operacions necessaries per a formar un espai vectorial
Position operator+(const Position&, const Position&);
Position operator-(const Position&, const Position&);
Position operator*(int, const Position&); //Donat que les coordenades de Position (m_x i m_y) són enters el argument que pren és un int per evitar tenir que fer conversions de float a int. Si en un futur hi ha la necessitat de multiplicar per un float es pot afegir un nou métode que funcioni amb floats (i fagi conversions) o modificar aquest métode
