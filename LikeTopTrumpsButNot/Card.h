#pragma once

class Card
{
public:
	
	Card(int value, int suit);

	Card(const Card& otherCard);

	~Card();

	int GetValue() { return m_iValue; }

private:

	int m_iValue;
	int m_iSuit;
};