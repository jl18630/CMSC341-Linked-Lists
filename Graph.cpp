// Name: Kyle Lee                                                               
//                                                                              
// File: Graph.cpp                                                              
//                                                                              
// CMSC 341 Spring 2017 Project 1                                               
//                                                                              
// File implementing functions for Graph.h                                      
//                                                                              

#include "Graph.h"
#include <iostream>
#include <string>

using namespace std;

// Function: Graph (constructor)                                                
// Input: number of vertices to create                                          
// Output: allocate memory for adjacentcy list                                  
Graph::Graph(int n){
  if(n <= 0)
    throw out_of_range("out of range");
  else{
    m_size = n;
    m_adjLists = new AdjListNode*[m_size];

    for(int i = 0; i < size(); i++){
      m_adjLists[i] = NULL;
    }
  }
}


// Function: Graph (destructor)                                                 
// Input: none                                                                  
// Output: deallocate linked lists and m_adjLists[]                             
Graph::~Graph(){
  AdjListNode *curr;
  AdjListNode *temp;

  //traverse through the graph                                                  
  for(int i; i < size(); i++){
    curr = m_adjLists[i];
    while(curr != NULL){
      //deallocate each vertex                                                  
      temp = curr -> next;
      delete curr;
      curr = temp;
    }
  }

  //delete entire graph                                                         
  delete [] m_adjLists;
  m_adjLists = NULL;
}


// Function: Graph (copy constructor)                                           
// Input: Graph object                                                          
// Output: copy graph                                                           
Graph::Graph(const Graph& G){
  m_size = G.m_size;
  m_adjLists = new AdjListNode*[m_size];

  AdjListNode *curr;
  AdjListNode *copy;

  for(int i = 0; i < m_size; i++){
    curr = G.m_adjLists[i];
    if(curr == NULL)
      m_adjLists[i] = NULL;
    else{
      //create copy of vertex                                                   
      copy = new AdjListNode(curr -> m_vertex);
      m_adjLists[i] = copy;
      curr = curr -> next;

      while(curr != NULL){
        //create a new node next to copied vertex                              
        copy -> next = new AdjListNode(curr -> m_vertex);
        curr = curr -> next;
        copy = copy -> next;
      }
    }
  }
}


// Function: Graph operator= (overloaded operator)                              
// Input: object being compared                                                 
// Output: return *this                                                         
const Graph& Graph::operator=(const Graph& rhs){
  AdjListNode *curr;
  AdjListNode *temp;

  //deallocate current graph                                                    
  for(int i; i < size(); i++){
    curr = m_adjLists[i];
    while(curr != NULL){
      temp = curr -> next;
      delete curr;
      curr = temp;
    }
  }
  delete [] m_adjLists;
  m_adjLists = NULL;

  //Copy graph                                                                  
  m_size = rhs.m_size;
  m_adjLists = new AdjListNode*[m_size];

  AdjListNode *node;
  AdjListNode *copy;

  for(int i = 0; i < m_size; i++){
    node = rhs.m_adjLists[i];
    if(node == NULL)
      m_adjLists[i] = NULL;
    else{
      copy = new AdjListNode(node -> m_vertex);
      m_adjLists[i] = copy;
      node = node -> next;
      while(node != NULL){
        copy -> next = new AdjListNode(node -> m_vertex);
        node = node -> next;
        copy = copy -> next;
      }
    }
  }

  return *this;
}


// Function: AdjListNode (constructor)                                          
// Input: number of vertices, AdjListNode pointer                               
// Output: assign member                                                        
Graph::AdjListNode::AdjListNode(int v, AdjListNode *ptr){
  m_vertex = v;
  next = ptr;
}

// Function: size                                                               
// Input: none                                                                  
// Output: return size of graph                                                 
int Graph::size(){
  return m_size;
}


// Function: addEdge                                                            
// Input: x value and y value of pair                                           
// Output: create new AdjListNode of (u,v) and/or (v,u)                         
void Graph::addEdge(int u, int v){
  //throw exception if out of range                                             
  if(u >= size() || v >= size())
    throw out_of_range("addEdge error");

  //if the index has no vertices...                                             
  if(m_adjLists[u] == NULL){
    //create a new AdjListNode                                                  
    m_adjLists[u] = new AdjListNode(v);
  }
  //if a vertex exists in the index...                                          
  else{
    //append a new AdjListNode in front of the existing vertex                  
    m_adjLists[u] = new AdjListNode(v, m_adjLists[u]);
  }
  //check if <u,v> are unique numbers                                           
  if(u != v){
    if(m_adjLists[v] == NULL){
      m_adjLists[v] = new AdjListNode(u);
    }
    else{
      m_adjLists[v] = new AdjListNode(u, m_adjLists[v]);
    }
  }
}


// Function: dump                                                               
// Input: none                                                                  
// Output: print out graph                                                      
void Graph::dump(){
  AdjListNode *curr;

  cout << "Dump out graph (size = " << size() << ")" << endl;

  //iterate through the m_adjLists[]                                            
  for(int i = 0; i < size(); i++){
    cout << "[ " << i << "]: ";
    curr = m_adjLists[i];
    //if not at the end of the linked list...                                   
    while(curr != NULL){
      //print out the vertex and iterate to next vertex                         
      cout << curr -> m_vertex << " ";
      curr = curr -> next;
    }
    cout << endl;
  }
}


// Function: NbIterator (constructor)                                           
// Input: Graph pointer, number of vertices, isEnd                              
// Output: construct nbBegin or nbEnd iterator                                  
Graph::NbIterator::NbIterator(Graph *Gptr, int v, bool isEnd){
  m_Gptr = Gptr;

  //if the linked list is empty                                                 
  if(m_Gptr == NULL){
    //return default values                                                     
    return;
  }
  else{
    //throw exception of out of range for number of vertices                    
    if(v > m_Gptr -> size())
      throw out_of_range("NbIterator constructor error");
    //nbEnd                                                                     
    if(isEnd == true){
      m_source = v;
      m_where = NULL;
    }
    else{
      //nbBegin                                                                 
      m_source = v;
      m_where = m_Gptr -> m_adjLists[m_source];
    }
  }
}


// Function: nbBegin                                                            
// Input: index of m_adjLists[] to iterate through                              
// Output: return NbIterator constructor                                        
Graph::NbIterator Graph::nbBegin(int v){
  return NbIterator(this, v, false);
}

// Function: nbEnd                                                              
// Input: index of m_adjLists[] to iterate through                              
// Output: return NbIterator constructor                                        
Graph::NbIterator Graph::nbEnd(int v){
  return NbIterator(this, v, true);
}


// Function: EgIterator                                                         
// Input: Graph pointer, isEnd                                                  
// Output: construct isBegin or is Begin                                        
Graph::EgIterator::EgIterator(Graph *Gptr, bool isEnd){
  m_Gptr = Gptr;

  if(m_Gptr == NULL){
    return;
  }
  //isEnd                                                                       
  else if(isEnd == true){
      m_source = m_Gptr -> size();
      m_where = NULL;
  }
  //isBegin                                                                     
  else{
    //if there are no vertices in m_adjLists[0]                                 
    if(m_Gptr -> m_adjLists[0] == NULL){
      //start at the next row                                                   
      m_source = 1;
      m_where = m_Gptr -> m_adjLists[m_source];
    }
    else{
      m_source = 0;
      m_where = m_Gptr -> m_adjLists[m_source];
    }
  }
}


// Function: egBegin                                                            
// Input: none                                                                  
// Output: return EgIterator constructor                                        
Graph::EgIterator Graph::egBegin(){
  return EgIterator(this, false);
}

// Function: egEnd                                                              
// Input: none                                                                 
// Output: return EgIterator constructor                                        
Graph::EgIterator Graph::egEnd(){
  return EgIterator(this, true);
}


// Functon: NbIterator operator!= (overloaded operator)                         
// Input: object being compared                                                 
// Output: return true if m_source, m_where, or m_Gptr of 'this' is not equal t\
o that of the rhs object, false otherwise                                       
bool Graph::NbIterator::operator!=(const NbIterator& rhs){
  return (m_source != rhs.m_source || m_where != rhs.m_where || m_Gptr != rhs.m\
_Gptr);
}

// Function: NbIterator operator* (overloaded operator)                         
// Input: none                                                                  
// Output: return vertex                                                        
int Graph::NbIterator::operator*(){
  return m_where -> m_vertex;
}

// Function: NbIterator operator++ (overloaded operator)                        
// Input: dummy (none)                                                          
// Output: iterate to the next neighber vertex                                  
void Graph::NbIterator::operator++(int dummy){
  m_where = m_where -> next;
}


// Function: EgIterator operator != (overloaded operator)                       
// Input: object being compared                                                 
// Output: return true if m_where or m_source of 'this' and rhs are not equal, \
false otherwise                                                                 
bool Graph::EgIterator::operator!=(const EgIterator& rhs){
  if(m_where != rhs.m_where || m_source != rhs.m_source)
    return true;
  else{
      return false;
    }
}

// Function: EgIterator operator* (overloaded operator)                         
// Input: none                                                                  
// Output: dereference pair                                                     
pair<int,int> Graph::EgIterator::operator*(){
  if(m_where == NULL)
    throw out_of_range("EgIterator operator* error.");

  return pair<int,int>(m_source, m_where -> m_vertex);
}


// Function: EgIterator operator++ (overloaded operator)                        
// Input: dummy (none)                                                          
// Output: iterate to the next edge                                             
void Graph::EgIterator::operator++(int dummy){
  do{
    m_where = m_where -> next;
    //if not at the end of the linked list...                                   
    while(m_where == NULL){
      //go to the next row of m_adjLists[]                                      
      m_source++;
      //if out of range...                                                      
      if(m_source == m_Gptr -> size())
        return;
      //start at the first neighbor vertex                                      
      else{
        m_where = m_Gptr -> m_adjLists[m_source];
      }
    }
    //break out of do loop                                                      
    if(m_where == NULL)
      return;
  } while(m_source > m_where -> m_vertex);
}