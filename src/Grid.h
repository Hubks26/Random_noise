#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <chrono>
#include <vector>
#include <random>
#include <iostream>

class Grid : public sf::Drawable
{
public :
	enum Direction
	{
		Horizontal,
		Vertical
	};
	
public :
	
	Grid();
	void update();
	void getNeighboorMean(const int x, const int y);

private :
	
	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void modif(int, int, sf::Color);
	void toggleDirection();
	
private :
	
	static constexpr int m_dim = 302;
	double m_valR, m_valG, m_valB;
	sf::Color m_table[m_dim][m_dim]{sf::Color::Black};
	std::vector<unsigned> m_cursor;
	Direction m_direction;
	unsigned m_level;
	unsigned m_seed;
};

#endif // GRID_H
