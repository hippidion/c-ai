#include <stdio.h>
#include <map>
#include <vector>
#include <string>
using namespace std;

template<class T>
class CQueue {
private:
    vector<T> elements;
    int head;
    int tail;
    int size;
    
public:
    CQueue(int arg) : elements(arg, 0) {
        head = -1;
        tail = 0;
        size = arg;
    }
    
    ~CQueue() {
    }
    
    void Enqueue(T arg) {
        if (tail == head) 
            throw "Overflow";
        elements[tail] = arg;
        if (head == -1)
            head = tail;
        if (tail + 1 == size)
            tail = 0;
        else
            tail++;
    }
    
    T Dequeue() {
        if (head == -1) 
            throw "Underflow";
        T result = elements[head];
        if (head + 1 == size)
            head = 0;
        else
            head++;
        if (head == tail)
            head = -1;
        return result;
    }
    
    bool IsEmpty() {
        return head == -1;
    }
};


class Vertex {
public:
    int key;
    int visit;
    int distance;
    int finish;
    Vertex* parent;
    
    Vertex(int arg) {
        key = arg;
        visit=0;
        distance = 0x7fffffff;
        finish = 0x7fffffff;
        parent = 0;
    }
};

class CGraph {
private:
    map<Vertex*, vector<Vertex*> > adjacencyMap;
    int time;
    
public:
    CGraph(map<Vertex*, vector<Vertex*> >& arg) {
        adjacencyMap = arg;
        time = 0;
    }	
    
    void BFS(Vertex* source) {
		source->visit = -1;
        CQueue<Vertex*> open(20);
		source->distance=0;
        open.Enqueue(source);
        while (!open.IsEmpty()) {
           Vertex* cur=open.Dequeue();
            printf("%d\n", cur->key);
            
            vector<Vertex*> neighbors = adjacencyMap[cur];
            for (int i = 0; i < neighbors.size(); ++i) {
                if (neighbors[i]->visit == 0) {
					neighbors[i]->visit = -1;
                    open.Enqueue(neighbors[i]);
					neighbors[i]->distance=cur->distance+1;
					neighbors[i]->parent=cur;
                      
                }
            }
            cur->visit=1;
            CQueue<Vertex*> closed(20);
			closed.Enqueue(cur);
            
            
            
        }
    }
};
void test_BFS() {
    Vertex v_2(2);
    Vertex v_1(1);
    Vertex v_4(4);
    Vertex v_5(5);
    Vertex v_3(3);
    Vertex v_8(8);
    Vertex v_6(6);
    Vertex v_7(7);
    
    map<Vertex*, vector<Vertex*> > adjacencyMap;
    
    vector<Vertex*> b_neighbors;
    b_neighbors.push_back(&v_1);
    b_neighbors.push_back(&v_4);
	b_neighbors.push_back(&v_5);
    adjacencyMap[&v_2] = b_neighbors;
	vector<Vertex*> a_neighbors;
	a_neighbors.push_back(&v_2);
    a_neighbors.push_back(&v_3);
    adjacencyMap[&v_1] = a_neighbors;
    vector<Vertex*> d_neighbors;
	d_neighbors.push_back(&v_2);
    d_neighbors.push_back(&v_8);
    adjacencyMap[&v_4] = d_neighbors;
	vector<Vertex*> e_neighbors;
    e_neighbors.push_back(&v_2);
	e_neighbors.push_back(&v_8);
    adjacencyMap[&v_5] = e_neighbors;
	vector<Vertex*> c_neighbors;
    c_neighbors.push_back(&v_1);
    c_neighbors.push_back(&v_6);
    c_neighbors.push_back(&v_7);
    adjacencyMap[&v_3] =c_neighbors;
	vector<Vertex*> h_neighbors;
    h_neighbors.push_back(&v_4);
    h_neighbors.push_back(&v_5);
    adjacencyMap[&v_8] =h_neighbors;
	vector<Vertex*> f_neighbors;
    f_neighbors.push_back(&v_3);
    f_neighbors.push_back(&v_7);
    adjacencyMap[&v_6] =f_neighbors;
	vector<Vertex*> g_neighbors;
    g_neighbors.push_back(&v_3);
    g_neighbors.push_back(&v_6);
    adjacencyMap[&v_7] = g_neighbors;

    
    
    
    
    
   
    printf("BFS starts\n");
    CGraph graph(adjacencyMap);
    graph.BFS(&v_2);



}

int main() {
    test_BFS();
    return 0;
}
