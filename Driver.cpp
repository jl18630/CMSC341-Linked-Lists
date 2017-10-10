// Name: Kyle lee                                                               
//                                                                              
// File: Driver.cpp                                                             
//                                                                              
// CMSC341 Spring 2017                                                          
//                                                                              
// test cases for Graph class                                                   
//                                                                              

#include <iostream>

#include <utility>
using namespace std;

#include "Graph.h"

int main(){
  cout << "TEST CASE 1: DUPLICATE VERTICES" << endl;

  //Test 1: duplicate vertices                                                  
  Graph G(7);
  //G.addEdge(0,0);                                                             
  G.addEdge(1,1);
  G.addEdge(2,2);
  G.addEdge(2,2);
  G.addEdge(3,4);
  G.addEdge(5,4);
  G.dump();

  //UMCOMMENT TO SEE EXCEPTIONS                                                 
  cout << "TEST: OUT OF RANGE CASES" << endl;
    
 //Graph E(-1);                                                                

  /*                                                                            
  Graph E(10);                                                                  
  //or                                                                          
  Graph E(0);                                                                   
  E.addEdge(11, 9);                                                             
  E.dump();                                                                     
  */

  /*                                                                            
  Graph F(1);                                                                   
  F.addEdge(0,1);                                                               
  F.dump();                                                                     
  */


  cout << "\nTEST CASE 2: GPTR" << endl;

  Graph* Gptr1 = new Graph(7) ;

  // add some edges                                                            
  Gptr1->addEdge(2,4) ;
  Gptr1->addEdge(4,4) ;
  Gptr1->addEdge(5,2) ;
  Gptr1->addEdge(2,5) ;
  Gptr1->addEdge(0,1) ;
  Gptr1->addEdge(5,5) ;
  Gptr1->addEdge(3,6) ;
  Gptr1->dump();

  Graph::NbIterator nit;
  cout << "\n\nThe neighbors of vertex 6 are:\n";
  for(nit = Gptr1 -> nbBegin(6); nit != Gptr1 -> nbEnd(6); nit++){
    cout << *nit << " ";
  }
  cout << endl;
    
 // Test edge iterator                                                        
  Graph::EgIterator eit ;
  pair<int,int> edge ;

  cout << "The edges in the graph are:\n" ;
  for (eit = Gptr1 -> egBegin() ; eit != Gptr1 -> egEnd() ; eit++) {
    edge = *eit ;   // get current edge                                         

    // the two data members of a pair are first and second                     
    cout << "(" << edge.first << ", " << edge.second << ") " ;

  }
  cout << endl ;


  cout << "\nTEST CASE 3: COPY OF GRAPH 2" << endl;
  // Make another graph and dump                                                
  cout << "Graph 3:" << endl;
  Graph G3(4) ;
  G3.addEdge(0,1) ;
  G3.addEdge(2,0) ;
  G3.addEdge(1,2) ;
  G3.addEdge(3,3) ;
  G3.dump() ;
    
 cout << "\nGraph 3 copying Graph 2: " << endl;
  // Copy over G3 and dump                                                     
  G3 = *Gptr1 ;
  G3.dump() ;

  cout << "\nThe neighbors of vertex 0 are:\n" ;
  for (nit = G3.nbBegin(0); nit != G3.nbEnd(0); nit++) {
    cout << *nit << " " ;
  }
  cout << endl ;


  cout << "\nThe edges in the graph are:\n" ;
  for (eit = G3.egBegin() ; eit != G3.egEnd() ; eit++) {
    edge = *eit ;   // get current edge                                         

    // the two data members of a pair are first and second                      
    //                                                                          
    cout << "(" << edge.first << ", " << edge.second << ") " ;

  }
  cout << endl ;
    
  delete Gptr1;

}
