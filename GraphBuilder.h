#include "GraphVisualizer.h"

template<typename T>
class GraphBuilder{
public:
	GraphBuilder(){
		m_vertices.clear();
		m_edges.clear();
		m_directed = false;
	}
	~GraphBuilder() {}
	void addVertex(T v){
		m_vertices.insert(v);
	}
	void addEdge(T v1, T v2){
		if (!containsVertex(v1) || ! containsVertex(v2)) std::invalid_argument("Error : no such vertex in graph builder.");
		m_edges.insert(std::pair<T, T>(v1, v2));
	}
	void addEdge(std::pair<T, T> e){
		if (!containsVertex(e.first) || ! containsVertex(e.second)) std::invalid_argument("Error : no such vertex in graph builder.");
		m_edges.insert(e);
	}
	void removeVertex(T v){
		if (!containsVertex(v)) throw std::invalid_argument("Error : no such vertex in graph builder.");
		m_vertices.erase(v);
	}
	void removeEdge(T v1, T v2){
		if (!containsEdge(std::pair<T, T>(v1, v2))) std::invalid_argument("Error : no such edge in graph builder.");
		m_edges.erase(std::pair<T, T>(v1, v2));
	}
	void removeEdge(std::pair<T, T> e){
		if (!containsEdge(e)) std::invalid_argument("Error : no such edge in graph builder.");
		m_edges.erase(e);
	}
	void setDirected(bool d){
		m_directed = d;
	}
	Graph<T> build(){
		return Graph<T>(m_vertices, m_edges, m_directed);
	}
	bool containsVertex(T v){
		return m_vertices.find(v) != m_vertices.end();
	}
	bool containsEdge(std::pair<T, T> e){
		return m_edges.find(e) != m_edges.end();
	}

private:
	std::set<T> m_vertices;
	std::set<std::pair<T, T> > m_edges;
	bool m_directed;
};