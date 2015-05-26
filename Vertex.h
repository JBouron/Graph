#include <SFML/Graphics.hpp>

template<typename T>
class Vertex{
public:
	bool operator==(Vertex<T> const& a){
		return a.value == value && a.pos == pos;
	}
	Vertex<T>& operator=(Vertex<T> const& that){
		Vertex<T> res;
		res.value = that.value;
		res.pos = that.pos;
		res.name = that.name;
		return res;
	}
	Vertex(T value, sf::Vector2f pos, std::string name){
		this->value = value;
		this->pos = pos;
		this->name = name;
	}
	Vertex() {}
	~Vertex() {}
	T value;
	sf::Vector2f pos;
	std::string name = "";
};