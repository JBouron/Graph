#ifndef G_INCLUDED
#define G_INCLUDED
#include <iostream>
#include <stdexcept>
#include <map>
#include <set>
template <typename T>
class Graph{
public:
	Graph(std::set<T> vertices, std::set<std::pair<T, T> > edges, bool directed){
		m_vertices = vertices;
		m_edges = edges;
		m_directed = directed;
		m_map.clear();
		constructMap();
	}
	~Graph() {}
	std::set<T> getVertices() {return m_vertices;}
	std::set<std::pair<T, T> > getEdges() {return m_edges;}
	std::set<T> neighborVertices(T v){
		if (contains(v)){
			return m_map[v];
		}
		else{
			throw std::invalid_argument("Error : no such vertex in graph.");
		}
	}
	bool contains(T v) {return m_map.find(v) != m_map.end();}
	bool contains(T v1, T v2){if (m_directed) return m_edges.find(std::pair<T, T>(v1, v2)) != m_edges.end(); else return m_edges.find(std::pair<T, T>(v1, v2)) != m_edges.end() || m_edges.find(std::pair<T, T>(v2, v1)) != m_edges.end()}
	bool isDirected(){return m_directed;}
	int getDegreeOf(T v){
		if (!this->contains(v)) throw std::invalid_argument("Error : no such vertex in graph");
		else {
			int size = 0;
			typename std::set<T>::iterator it;
			for (it = m_map[v].begin(); it != m_map[v].end(); it ++){
				size ++;
			}
			return size;
		}
	}

private:
	void constructMap(){
		typename std::set<T>::iterator it;
		for (it=m_vertices.begin(); it != m_vertices.end(); it ++){
			std::set<T> v;
			v.clear();
			m_map[*it] = v;
		}
		typename std::set<std::pair<T, T> >::iterator it2;
		for (it2=m_edges.begin(); it2 != m_edges.end(); it2 ++){
			if (m_directed){
				std::set<T> v = m_map[(*it2).first];
				v.insert((*it2).second);
				m_map[(*it2).first] = v;
			}
			else{
				std::set<T> v = m_map[(*it2).first];
				v.insert((*it2).second);
				m_map[(*it2).first] = v;
				v = m_map[(*it2).second];
				v.insert((*it2).first);
				m_map[(*it2).second] = v;
			}
		}
	}
	std::set<T> m_vertices;
	std::set<std::pair<T, T> > m_edges;
	std::map<T, std::set<T> > m_map;
	bool m_directed;
};
#endif
