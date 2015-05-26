#include "GraphBuilder.h"
#include "Graph.h"
#include <fstream>
#include <string>

using namespace std;

std::string name(string n){return n;}

string base = "/usr/include/";

void findInclude(string fileName, GraphBuilder<string> &b){
	b.addVertex(fileName);
	ifstream file((base + fileName).c_str());
	string line;
	string incl = "#include <";
	while(getline(file, line)){
		int pos = line.find(incl);
		if (pos != string::npos){
			pos += incl.size();
			int nextpos = line.find_first_of(">");
			string nextfile = line.substr(pos, nextpos - pos );
			if (!b.containsVertex(nextfile)){
				cout << "next file = " << nextfile << endl;
			}
			b.addVertex(nextfile);
			b.addEdge(fileName, nextfile);
			findInclude(nextfile, b);
		}
	}
}

int main(){
	GraphBuilder<string> b;
	findInclude("SFML/baseSFML.hpp", b);
	Graph<string> g = b.build();
	int vcount = 0;
	int ecount = 0;
	for (std::set<string>::iterator it=g.getVertices().begin(); it != g.getVertices().end(); it ++){
		vcount ++;			
	}
	for (std::set<std::pair<string, string> >::iterator it2=g.getEdges().begin(); it2 != g.getEdges().end(); it2 ++){
		ecount ++;			
	}
	cout << "---------------------" << endl;
	cout << "Total vertices : " << vcount << endl;
	cout << "Total edges : " << ecount << endl;
	GraphVisualizer<string> gv(g, name);
	gv.draw();
	return 0;
}
