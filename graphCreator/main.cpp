/*
  This is graph creator. It creates a graph and adjacency matrix.
  Author: Dieter Voegels
  Date: May 22, 2018
 */
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

//node struct that holds information on the node
struct node{
  int color = -1;
  char* label;
  int index = -1;
  node* previous = NULL;
  int tentativeDistance = 999999999999;
};

//constants for black or red, aka not visited and visited
const int BLACK = 0;
const int RED = 1;

//prototypes
void addEdge(node* nodes[20], int adjacency[20][20], char* labelA, char* labelB, int edgeWeight);
void addVertex(node* nodes[20], node* &Node, char* label);
void deleteEdge(node* nodes[20], int adjacency[20][20], char* labelA, char* labelB);
void deleteVertex(int adjacency[20][20], int index);
void print(int adjacency[20][20]);

//constructor
int main(){
  //initialize variables
  node* nodes[20];
  for(int i = 0; i < 20; i++){
    nodes[i] = NULL;
  }
  int adjacency[20][20];
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      adjacency[i][j] = -1;
    }
  }
  bool quit = false;
  char input[20];

  //main while loop
  while(quit == false){
    cout << "Welcome to graph creator. Input add, delete, or quit..." << endl;
    cin >> input;
    cin.ignore();

    //add something to the graph
    if(strcmp(input, "add") == 0){
      cout << "Input vertex or edge..." << endl;
      cin >> input;
      cin.ignore();
      //add a vertex
      if(strcmp(input, "vertex") == 0){
	char* label = new char[100];
	node* Node = new node;
	cout << "Input the vertex's label..." << endl;
	cin >> label;
	cin.ignore();
	addVertex(nodes, Node, label);
      }
      //add an edge
      else if(strcmp(input, "edge") == 0){
	char labelA[100];
	char labelB[100];
	int edgeWeight;
	cout << "Input the label of the first vertex..." << endl;
	cin >> labelA;
	cin.ignore();
	cout << "Input the label of the second vertex..." << endl;
	cin >> labelB;
	cin.ignore();
	cout << "Input the magnitude of the edge..." << endl;
	cin >> edgeWeight;
	cin.ignore();
	addEdge(nodes, adjacency, labelA, labelB, edgeWeight);
      }
    }
    //delete something from the graph
    else if(strcmp(input, "delete") == 0){
      cout << "Would you like to delete an vertex or edge?" << endl;
      cin >> input;
      //delete a vertex and its connections
      if(strcmp(input, "vertex") == 0){
	char label[100];
	cout << "What is the label of the vertex?" << endl;
	cin >> label;
	int index;
	for(int i = 0; i < 20; i++){
	  if(nodes[i] != NULL && strcmp(nodes[i]->label, label) == 0){
	    index = i;
	    delete nodes[i];
	    nodes[i] = NULL;
	  }
	}

	deleteVertex(adjacency, index);
      }
      //delete an edge
      if(strcmp(input, "edge") == 0){
	char labelA[100];
	char labelB[100];
	cout << "Input the label of the first vertex..." << endl;
	cin >> labelA;
	cin.ignore();
	cout << "Input the label of the second vertex..." << endl;
	cin >> labelB;
	cin.ignore();
	deleteEdge(nodes, adjacency, labelA, labelB);
      }
    }
    //quit the program
    else if(strcmp(input, "quit") == 0){
      quit = true;
    }
    print(adjacency);
  }
}

//add an edge function, add it to the adjacency matrix.
void addEdge(node* nodes[20], int adjacency[20][20], char* labelA, char* labelB, int edgeWeight){
  int indexA = 0;
  int indexB = 0;

  for(int i = 0; i < 20; i++){
    if(nodes[i] != NULL){
      if(*(nodes[i]->label) == *labelA){
	indexA = i;
      }
      else if(*(nodes[i]->label) == *labelB){
	indexB = i;
      }
    }
  }

  adjacency[indexA][indexB] = edgeWeight;
  adjacency[indexB][indexA] = edgeWeight;
}

//add a vertex, add it to the nodes array
void addVertex(node* nodes[20], node* &Node, char* label){
  Node->label = label;
  Node->color = BLACK;
  for(int i = 0; i < 20; i++){
    if(nodes[i] == NULL){
      nodes[i] = Node;
      Node->index = i;
      return;
    }
  }
}

//delete an edge
void deleteEdge(node* nodes[20], int adjacency[20][20], char* labelA, char* labelB){
  int indexA = 0;
  int indexB = 0;

  for(int i = 0; i < 20; i++){
    if(nodes[i] != NULL){
      if(*nodes[i]->label == *labelA){
	indexA = i;
      }
      else if(*nodes[i]->label == *labelB){
	indexB = i;
      }
    }
  }

  adjacency[indexA][indexB] = -1;
  adjacency[indexB][indexA] = -1;
}

//delete vertex and its connections
void deleteVertex(int adjacency[20][20], int index){
  for(int i = 0; i < 20; i++){
    if(adjacency[index][i] != -1){
      adjacency[index][i] = -1;
      adjacency[i][index] = -1;
    }
  }
}

//print the adjacency matrix
void print(int adjacency[20][20]){
  for(int i = 0; i < 20; i++){
    for(int j = 0; j < 20; j++){
      cout << "(" << adjacency[i][j] << ")";
    }
    cout << endl;
  }
}
