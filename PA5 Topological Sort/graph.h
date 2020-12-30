#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <unordered_map>
#include <list>
#include <queue>
#include <sstream>
#include <fstream>

using namespace std;

//edits to this are likely not needed
template <class T>
struct Vertex {
  T label; // unique int for a vertex
  vector<T> adj_list;
  int indegree; // Part 2: number of nodes pointing in
  int top_num; // Part 2: topological sorting number
  Vertex(T l) : label(l) {top_num = 0; label = l;} //Part 1
};

// optional, but probably helpful
// template <class T>
// ostream& operator<<(ostream &o, Vertex<T> v){};

template <class T>
ostream& operator<<(ostream &o, Vertex<T> v){

  o << v.label << ": ";
  for (auto it : v.adj_list){
    o << it << " ";
  }
  o << endl;
}

// syntax for custom compare functor
// template<class T>
// class VertexCompare
// {
// public:
//   bool operator()(Vertex<T> v1, Vertex<T> v2){
//     //todo - implement
//     return false;
//   }
// };

template<class T>
class VertexCompare
{
public:
  bool operator()(Vertex<T> v1, Vertex<T> v2){
    //todo - implement
    return v1.top_num > v2.top_num; 
    //return false;
  }
};


template <class T>
class Graph {
private:
  //c++ stl hash table
  // unordered_map<T, Vertex<T>> node_set;
  //Use other data fields if needed

  unordered_map<T, Vertex<T> > node_set;

public:
  Graph() {};  // default constructor
  ~Graph() {};
  // build a graph
  void buildGraph(istream &input){
    string l;
    while (getline(input, l)) {
      //cout << l << endl;
      istringstream i(l);

      T vId;
      i >> vId;
      //Vertex<int> vtemp = new Vertex<int>(vId);
      Vertex<T> vtemp(vId);
      vtemp.indegree = 0;

      T x;
      while (i >> x){
        vtemp.adj_list.push_back(x);
      }
      //node_set[vId] = vtemp;
      node_set.insert(make_pair(vId, vtemp));
    }

    // for (pair<int, Vertex<int> > element : node_set)
    // {
    //   cout << element.first << endl;  // << " :: " << element.second << endl;
    // }


    //printf("%lu\n", node_set.bucket_count());

  }

  // display the graph into o
  void displayGraph(ostream& o){
    for (pair<T, Vertex<T> > element : node_set)
    {
      //cout << "-----" << endl;
      o << element.second;
    }
  }

  //return the vertex at label, else throw any exception
  Vertex<T> at(T label){

    for (pair<T, Vertex<T> > element : node_set)
    {
      if (element.first == label)
        return element.second;
    }

    throw "Element with given lable not Found";

  }

  //return the graph size (number verticies)
  int size(){
    return node_set.size();
  }

  // topological sort
  // return true if successful, false on failure (cycle)
  bool topological_sort(){

    int visited = 0;

    //queue<T> q;
    // unordered_map<T, int> umap;
    // for (pair<T, Vertex<T> > element : node_set)
    // {
    //   umap.insert(make_pair(element.first, element.second.indegree));
    // }
    // for (pair<T, int > element : umap)
    // {
    //   cout << element.first << " " << element.second << endl;
    // }

    queue<Vertex<T>> q;
    for (pair<T, Vertex<T> > element : node_set)
    {
      if (element.second.indegree == 0){
        q.push(element.second);
        node_set.at(element.second.label).top_num = visited;
        visited++;
      }
    }

    while (!q.empty()){
      Vertex<T> temp = q.front();
      //cout << temp << endl;
      q.pop();

      for (T val: temp.adj_list){
        node_set.at(val).indegree--;
        if (node_set.at(val).indegree == 0){
          q.push(node_set.at(val));
          node_set.at(val).top_num = visited;
          visited++;
        }
        if (node_set.at(val).indegree < 0){
          return false;
        }
      }

    }

    return visited == node_set.size();





    // for (pair<T, Vertex<T> > element : node_set)
    // {
    //   for (T temp: element.second.adj_list){
    //     node_set.at(temp).indegree = 0;
    //   }
        
    // }




    return false;

  }; // Part 2

  // find indegree
  void compute_indegree(){


    for (pair<T, Vertex<T> > element : node_set)
    {
      for (T temp: element.second.adj_list){
        node_set.at(temp).indegree++;
      }
        
    }

    // for (pair<T, Vertex<T> > element : node_set)
    // {
    //   cout << element.first << " " << element.second.indegree << endl;
        
    // }



  }; // Part 2


  // print topological sort into o
  //  if addNewline is true insert newline into stream
  void print_top_sort(ostream& o, bool addNewline=true)
  { 
    //TODO - implement things here

    // for (pair<T, Vertex<T> > element: node_set )
    //   o << element.first << " "<< element.second.top_num << endl;


    priority_queue<Vertex<T>, vector<Vertex<T>>, VertexCompare<T>> pq;

    for (pair<T, Vertex<T> > element: node_set )
      pq.push(element.second);

    while (!pq.empty()){
      o << pq.top().label << " ";
      pq.pop();
    } 

    if(addNewline){o << '\n';};
    
  }; // Part 2
};

#endif
