#include <SFML/Graphics.hpp>
#include <cmath>
#include "Vertex.h"
#include "Graph.h"

template<typename T>
class GraphVisualizer{
public:
	GraphVisualizer(Graph<T> graph, std::string (*f)(T)): m_win(sf::VideoMode(1200, 900), "Graph Visualizer v1.0"), m_graph(graph.getVertices(), graph.getEdges(), graph.isDirected()){
		//m_graph = graph;
		std::set<T> v = m_graph.getVertices();
		m_vertices.clear();
		typename std::set<T>::iterator it;
		float max_val = 900;
		for (it=v.begin(); it != v.end(); it ++){
			sf::Vector2f pos = sf::Vector2f(-max_val + randomBelow(2*max_val), -max_val + randomBelow(2*max_val));
			float d = m_graph.getDegreeOf(*it);
			float k = 100/d;
			//pos = pos*k;
			m_vertices.insert(new Vertex<T>(*it, pos, (*f)(*it)));
		}
	}
	~GraphVisualizer() {}
	Vertex<T>* getVertexByValue(T val){
		typename std::set<Vertex<T>* >::iterator it;
		for (it=m_vertices.begin(); it != m_vertices.end(); it ++){
			if ((*it)->value == val){
				return *it;
			}
		}
		return NULL;
	}
	void draw(){
		m_font.loadFromFile("font.ttf");
		sf::CircleShape node;
		node.setRadius(5);
		m_win.clear();
		sf::Text name;
		name.setFont(m_font);
		name.setCharacterSize(20);
		moveVertices();
		for (typename std::set<Vertex<T>* >::iterator it=m_vertices.begin(); it != m_vertices.end(); it ++){
			node.setPosition(((*it)->pos - sf::Vector2f(5.f, 5.f) - m_camera)*m_zoom);
			m_win.draw(node);
			name.setString(((*it)->name));
			name.setPosition(((*it)->pos + sf::Vector2f(10.f, -20.f) - m_camera)*m_zoom);
			m_win.draw(name);
		}
		std::set<std::pair<T, T> > edges = m_graph.getEdges();
		for (typename std::set<std::pair<T, T> >::iterator it=edges.begin(); it != edges.end(); it ++){
			sf::Vertex vert[] = {
				sf::Vertex(((getVertexByValue((*it).first)->pos) - m_camera)*m_zoom, sf::Color::Red),
				sf::Vertex(((getVertexByValue((*it).second)->pos) - m_camera)*m_zoom, sf::Color::Red)
			};
			m_win.draw(vert, 2, sf::Lines);
		}

		m_win.display();
		while (m_win.isOpen()){
			// Event processing
			sf::Event event;
			while (m_win.pollEvent(event)){
				// Request for closing the m_win
				if (event.type == sf::Event::Closed)
				m_win.close();

				if (event.type == sf::Event::KeyPressed){
					switch (event.key.code){
						case sf::Keyboard::Q :
							m_zoom -= 0.01f;
							if (m_zoom <= 0.f) m_zoom = 0.f;
							break;
						case sf::Keyboard::W :
							m_zoom += 0.01f;
							break;
						case sf::Keyboard::Up :
							m_camera.y -= m_cameraSpeed*(1.f/m_zoom);
							break;
						case sf::Keyboard::Down :
							m_camera.y += m_cameraSpeed*(1.f/m_zoom);
							break;
						case sf::Keyboard::Right :
							m_camera.x += m_cameraSpeed*(1.f/m_zoom);
							break;
						case sf::Keyboard::Left :
							m_camera.x -= m_cameraSpeed*(1.f/m_zoom);
							break;
					}
				}
			}
			draw();
		}
	}
	void render(int delay){
		sf::Clock wait;
		wait.restart();
		while(wait.getElapsedTime().asSeconds() < delay){
			for (typename std::set<Vertex<T>* >::iterator it=m_vertices.begin(); it != m_vertices.end(); it ++){
				(*it)->pos = (*it)->pos + forceApplied(*it);
			}
		}
		draw();
	}
	int randomBelow(int n){
		return rd()%n;
	}

	sf::Vector2f forceApplied(Vertex<T>* v){
		sf::Vector2f totalForce = sf::Vector2f(0.f, 0.f);
		//if (length(v->pos) > 9000) return totalForce;
		for (typename std::set<Vertex<T>* >::iterator it=m_vertices.begin(); it != m_vertices.end(); it ++){
			if (!(*it == v)){
				float K = m_graph.getDegreeOf((*it)->value) * m_graph.getDegreeOf(v->value) * 100;
				sf::Vector2f unit = (*it)->pos - v->pos;
				float r = length(unit);
				unit = unit/length(unit);
				float forceMagnitude = pow(K, 2)/pow(r, 2);
				if (r < 9000) 
						totalForce += unit*forceMagnitude*(-1.f);
			}
		}
		//std::cout << "totalForce = " << totalForce.x << " ; " << totalForce.y  << std::endl;
		return totalForce;
	}

	float length(sf::Vector2f v){
		return sqrt(pow(v.x, 2) + pow(v.y, 2));
	}

	void moveVertices(){
		/*for (typename std::set<Vertex<T>* >::iterator it=m_vertices.begin(); it != m_vertices.end(); it ++){
			(*it)->pos = (*it)->pos + forceApplied(*it);
		}*/
		for (int i=0; i<100; i++){
			for (typename std::set<Vertex<T>* >::iterator it = m_vertices.begin(); it != m_vertices.end(); it ++){
				
			}
		}
	}

private:
	Graph<T> m_graph;
	sf::RenderWindow m_win;
	std::set<Vertex<T>* > m_vertices;
	std::random_device rd;
	sf::Font m_font;
	float m_zoom = 0.1f;
	sf::Vector2f m_camera = sf::Vector2f(0, 0);
	float m_cameraSpeed = 20.0f;
};
