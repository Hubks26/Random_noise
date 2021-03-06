#include "Grid.h"

Grid::Grid()
: m_seed(std::chrono::steady_clock::now().time_since_epoch().count())
{	
	srand(m_seed);
	m_cursor.push_back(rand() % (m_dim-2) + 1);
	m_cursor.push_back(rand() % (m_dim-2) + 1);
	
	if(m_black_and_white){
		unsigned rate = rand() % 245 + 10;
		m_table[m_cursor[0]][m_cursor[1]] = sf::Color(rate, rate, rate);
	}
	else{
		m_table[m_cursor[0]][m_cursor[1]] = sf::Color(rand() % 245 + 10, rand() % 245 + 10, rand() % 245 + 10);
		m_dev_r = rand() % 33 + 2;
		m_dev_g = rand() % 33 + 2;
		m_dev_b = rand() % 33 + 2;
	}
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rectangle;

	for(int i = 1; i < m_dim-1; i++)
	{
		for(int j = 1; j < m_dim-1; j++)
		{
			rectangle.setSize(sf::Vector2f((650+m_dim)/m_dim, (650+m_dim)/m_dim));
			rectangle.setPosition(i*650/m_dim, j*650/m_dim);
			//rectangle.setOutlineColor(sf::Color::Black);
			//rectangle.setOutlineThickness(1);

			rectangle.setFillColor(m_table[i][j]);

			target.draw(rectangle, states);
		}
	}
}

void Grid::modif(int numRow, int numCol, sf::Color new_value)
{
	m_table[numRow][numCol] = new_value;
}

void Grid::update()
{
	getNeighboorMean();
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	
	sf::Color new_value;
	
	if(m_black_and_white){
		std::normal_distribution<double> distN_R(m_valR, 20.);
		double r_value = round(distN_R(generator));
		if(r_value > 255) {r_value = 255;}
		if(r_value < 10) {r_value = 10;}
		
		new_value = sf::Color(r_value, r_value, r_value);
	}
	else{
		std::normal_distribution<double> distN_R(m_valR, m_dev_r);
		std::normal_distribution<double> distN_G(m_valG, m_dev_g);
		std::normal_distribution<double> distN_B(m_valB, m_dev_b);
		double r_value = round(distN_R(generator));
		double g_value = round(distN_G(generator));
		double b_value = round(distN_B(generator));
		if(r_value > 255) {r_value = 255;}
		if(r_value < 10) {r_value = 10;}
		if(g_value > 255) {g_value = 255;}
		if(g_value < 10) {g_value = 10;}
		if(b_value > 255) {b_value = 255;}
		if(b_value < 10) {b_value = 10;}
		
		new_value = sf::Color(r_value, g_value, b_value);
	}

	modif(m_cursor[0], m_cursor[1], new_value);
}


void Grid::getNeighboorMean()

{	
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	srand(seed);
	
	int a = 0;
	int b = 0;
	
	while(a == b || (a != 0 && b != 0)){
		a = rand() % 3 - 1;
		b = rand() % 3 - 1;
	}
	
	m_cursor[0] += a;
	m_cursor[1] += b;
	
	if(m_cursor[0] > m_dim-2) { m_cursor[0] = m_dim-2;}
	else if(m_cursor[0] < 1) { m_cursor[0] = 1;}

	if(m_cursor[1] > m_dim-2) { m_cursor[1] = m_dim-2;}
	else if(m_cursor[1] < 1) { m_cursor[1] = 1;}
	
	unsigned x = m_cursor[0];
	unsigned y = m_cursor[1];
	
	m_valR=0, m_valG=0, m_valB=0;
	int count=0;

	if(x == 0 || x == m_dim-1 || y == 0 || y == m_dim-1) { m_valR = 0;  m_valG = 0;  m_valB = 0; }
	else {
		// Voisins des cotés ?
		if( x-1 != 0 && m_table[x-1][y] != sf::Color::Black) {
			m_valR += m_table[x-1][y].r;
			m_valG += m_table[x-1][y].g;
			m_valB += m_table[x-1][y].b;
			count++;
		}
		if( x+1 != m_dim-1 && m_table[x+1][y] != sf::Color::Black) {
			m_valR += m_table[x+1][y].r;
			m_valG += m_table[x+1][y].g;
			m_valB += m_table[x+1][y].b;
			count++;
		}
		if( y-1 != 0 && m_table[x][y-1] != sf::Color::Black) {
			m_valR += m_table[x][y-1].r;
			m_valG += m_table[x][y-1].g;
			m_valB += m_table[x][y-1].b;
			count++;
		}
		if( y+1 != m_dim-1 && m_table[x][y+1] != sf::Color::Black) {
			m_valR += m_table[x][y+1].r;
			m_valG += m_table[x][y+1].g;
			m_valB += m_table[x][y+1].b;
			count++;
		}
		
		// Voisins des diagonales ? 
		
		if( x-1 != 0 && y-1 != 0 && m_table[x-1][y-1] != sf::Color::Black) {
			m_valR += m_table[x-1][y-1].r;
			m_valG += m_table[x-1][y-1].g;
			m_valB += m_table[x-1][y-1].b;
			count++;
		}
		if( x+1 != m_dim-1 && y+1 != m_dim-1 && m_table[x+1][y+1] != sf::Color::Black) {
			m_valR += m_table[x+1][y+1].r;
			m_valG += m_table[x+1][y+1].g;
			m_valB += m_table[x+1][y+1].b;
			count++;
		}
		if( x-1 != 0 && y+1 != m_dim-1 && m_table[x-1][y+1] != sf::Color::Black) {
			m_valR += m_table[x-1][y+1].r;
			m_valG += m_table[x-1][y+1].g;
			m_valB += m_table[x-1][y+1].b;

			count++;
		}
		if( x+1 != m_dim-1 && y-1 != 0 && m_table[x+1][y-1] != sf::Color::Black) {
			m_valR += m_table[x+1][y-1].r;
			m_valG += m_table[x+1][y-1].g;
			m_valB += m_table[x+1][y-1].b;
			
			count++;
		}

		m_valR /= count;
		m_valG /= count;
		m_valB /= count;
	}
}
