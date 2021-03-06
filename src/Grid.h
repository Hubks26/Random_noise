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

	Grid();
	void update();
	void getNeighboorMean();

private :

	virtual void draw(sf::RenderTarget&, sf::RenderStates) const;
	void modif(int, int, sf::Color);
	template<typename type> type randNb(type Min, type Max); // Méthode générique renvoyant un nb aléatoire entre Min et Max
	void toggleDirection();

private :
	static constexpr int m_dim = 200;
	double m_valR, m_valG, m_valB;
	sf::Color m_table[m_dim][m_dim]{sf::Color::Black};
	std::vector<unsigned> m_cursor;
	unsigned m_seed;
	float m_dev_r, m_dev_g, m_dev_b;
	static constexpr bool m_black_and_white = false;
};

template<typename type>
type Grid::randNb(type Min, type Max) // Renvoie un nombre entier dans l'intervalle [Min;Max]
{
    type offset=0;
    if(abs(Min) > 0) { offset = Min; }
    type res = float(rand())/float(RAND_MAX) * (Max+1 + Min*(-1)) ;
    return res + offset;
}

#endif // GRID_H
