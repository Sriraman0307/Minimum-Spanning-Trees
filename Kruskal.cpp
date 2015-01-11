#include<iostream>
#include<list>
#include<vector>
#include<queue>
#include<hash_map>
#include<unordered_map>

using namespace std;

struct Edge {
	char vertex1;
	char vertex2;
	int weight;
	Edge(char v1, char v2, int w):vertex1(v1), vertex2(v2), weight(w) {}
};

struct Graph {
	vector<char> vertice;
	vector<Edge> edges;
};

 unordered_map<char, char> PARENT;
 unordered_map<char, int> RANK;

char find(char vertex) {
	if (PARENT[vertex] == vertex)
		return PARENT[vertex];
	else
		return find(PARENT[vertex]);
}

void MST(Graph &g) {
	vector<Edge> res;

	for (auto c : g.vertice) {
		PARENT[c] = c;
		RANK[c] = 0;
	}

	sort(g.edges.begin(), g.edges.end(), [](Edge x, Edge y) {return x.weight < y.weight;});   // O(E*log(E))

	for (Edge e : g.edges) {         // O(E)
		char root1 = find(e.vertex1);  // O(E) worst case
		char root2 = find(e.vertex2);
		if (root1 != root2) {
			res.push_back(e);
			if (RANK[root1] > RANK[root2]) {
				PARENT[root2] = root1;
				RANK[root1]++;
			} else {
				PARENT[root1] = root2;
				RANK[root2]++;
			}
		}
	}

	for (Edge e : res) {
		cout << e.vertex1 << " -- " << e.vertex2 << "  " << e.weight << endl;
	}
}

void Union( char vertex_1, char vertex_2 ) {
}

int main() {

	char t[] = {'a', 'b', 'c', 'd', 'e', 'f'};

	Graph g;
	g.vertice = vector<char>(t, t + sizeof(t)/sizeof(t[0]));

	g.edges.push_back(Edge('a', 'b', 4));  // sparse graph (E = O(V)) represented with Adjacency List.
	g.edges.push_back(Edge('a', 'f', 2));  // If it is a dense graph (E = O(V*V)), use Adjacency Matrix
	g.edges.push_back(Edge('f', 'b', 5));  // Most interesting graphs are sparse.
	g.edges.push_back(Edge('c', 'b', 6));
	g.edges.push_back(Edge('c', 'f', 1));
	g.edges.push_back(Edge('f', 'e', 4));
	g.edges.push_back(Edge('d', 'e', 2));
	g.edges.push_back(Edge('d', 'c', 3));
   for (vector<Edge>::iterator it = g.edges.begin(); it != g.edges.end(); it++)
    cout << it->vertex1 << "--"<< it->weight << "--"<< it->vertex2 <<' ';
	MST(g);

	return 0;
}

