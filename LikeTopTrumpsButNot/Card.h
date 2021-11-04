#pragma once

// Calss to hold a cards suit and value

class Card
{
public:
	
	// Olny primitives used so rule of 3/5 does not apply. Instead, applied the rule of zero for code clarity
	Card(int value, int suit);

	Card(const Card& otherCard) = default;

	Card& operator=(const Card& otherCard) = default;

	~Card() = default;

	int GetValue() { return m_iValue; }

private:

	int m_iValue;
	int m_iSuit;
};