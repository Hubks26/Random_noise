#include "Grid.h"

Grid::Grid()
: m_seed(std::chrono::steady_clock::now().time_since_epoch().count())
{
	srand(m_seed);
	m_cursor.push_back(rand() % (m_dim-2) + 1);
	m_cursor.push_back(rand() % (m_dim-2) + 1);
	m_table[m_cursor[0]][m_cursor[1]] = sf::Color(rand() % 245 + 10, rand() % 245 + 10, rand() % 245 + 10);
}

void Grid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::RectangleShape rectangle;
	
	for(int i = 1; i < m_dim-1; i++)
	{
		for(int j = 1; j < m_dim-1; j++)
		{
			rectangle.setSize(sf::Vector2f((600+m_dim)/m_dim, (600+m_dim)/m_dim));
			rectangle.setPosition(i*600/m_dim, j*600/m_dim);
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
    std::normal_distribution<double> distN_R(m_valR, 20.);
	std::normal_distribution<double> distN_G(m_valG, 20.);
	std::normal_distribution<double> distN_B(m_valB, 20.);
	double r_value = round(distN_R(generator));
	double g_value = round(distN_G(generator));
	double b_value = round(distN_B(generator));
	if(r_value > 255) {r_value = 255;}
	if(r_value < 10) {r_value = 10;}
	if(g_value > 255) {g_value = 255;}
	if(g_value < 10) {g_value = 10;}
	if(b_value > 255) {b_value = 255;}
	if(b_value < 10) {b_value = 10;}
	
	sf::Color new_value = sf::Color(r_value, g_value, b_value);
	
	modif(m_cursor[0], m_cursor[1], new_value);
}


void Grid::getNeighboorMean(const int x, const int y)
{
	int x = m_cursor[0];
	int y = m_cursor[1];
	
	m_valR=0, m_valG=0, m_valB=0;
	int count=0;
	
	while(x == 0 || x == m_dim-1 || y == 0 || y == m_dim-1)
	{
		while(x != randNb(x-1, x+1) && y != randNb(y-1, y+1)) {}
	}

	m_cursor[0]=x;
	m_cursor[1]=y;
	
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
