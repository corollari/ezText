#include "position.h"

Position::Position(int x, int y) {
	m_x = x;
	m_y = y;
}

Position::Position(Position origin, DIRECTION direccion) {
	int sumPosX = 0;
	int sumPosY = 0;
	switch (direccion)
	{
	case UP:
		sumPosY = -1;
		break;
	case DOWN:
		sumPosY = 1;
		break;
	case LEFT:
		sumPosX = -1;
		break;
	case RIGHT:
		sumPosX = 1;
		break;
	default:
		break;
	}
	m_x = origin.getX() + sumPosX;
	m_y = origin.getY() + sumPosY;
}

int Position::getX() const {
	return m_x;
}

int Position::getY() const {
	return m_y;
}

int Position::setX(int x) {
	return m_x = x;
}

int Position::setY(int y) {
	return m_y = y;
}

Position::Position(const Position& copy) {
	m_x = copy.getX();
	m_y = copy.getY();
}

bool operator==(const Position& compare1, const Position& compare2) {
	return compare1.getX() == compare2.getX() && compare1.getY() == compare2.getY();
}

Position operator+(const Position& sumant1, const Position& sumant2) {
	return Position(sumant1.getX() + sumant2.getX(), sumant1.getY() + sumant2.getY());
}

Position operator-(const Position& sumant1, const Position& sumant2) {
	return Position(sumant1.getX() - sumant2.getX(), sumant1.getY() - sumant2.getY());
}

Position operator*(int factor, const Position& factorPos) {
	return Position(factor*factorPos.getX(), factor*factorPos.getY());
}