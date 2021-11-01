#include "Card.h"

Card::Card(int value, int suit)
	:m_iValue(value), m_iSuit(suit)
{

}

Card::Card(const Card& otherCard)
	: m_iValue(otherCard.m_iValue), m_iSuit(otherCard.m_iSuit)
{

}

Card::~Card()
{

}
