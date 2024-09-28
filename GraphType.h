//
// Created by patel on 4/14/2024.
//

#ifndef FP02_GRAPHTYPE_H
#define FP02_GRAPHTYPE_H

#include <iostream>
#include <iomanip>
#include <fstream>

#include "QueType.h"
using namespace std;

template<class VertexType>
// Assumption: VertexType is a type for which the "=",
// "==", and "<<" operators are defined
class GraphType
{
public:
    GraphType();                 // Default of 50 vertices
    GraphType(int maxV);          // maxV <= 50
    ~GraphType();
//  void MakeEmpty();
//  bool IsEmpty() const;
//  bool IsFull() const;
    void AddVertex(VertexType);
    void AddEdge(VertexType, VertexType, int);
    int WeightIs(VertexType, VertexType);
    void GetToVertices(VertexType, QueType<VertexType>&);
    void ClearMarks();
    void MarkVertex(VertexType);
    bool IsMarked(VertexType);
    void Print();
    void Print(ofstream&);
    void PrintMarks();

private:
    int numVertices;
    int maxVertices;
    VertexType* vertices;
    int edges[50][50];
    bool* marks;	// marks[i] is mark for vertices[i].
};


template<class VertexType>
GraphType<VertexType>::GraphType()
// Post: Arrays of size 50 are dynamically allocated for
//       marks and vertices.  numVertices is set to 0;
//       maxVertices is set to 50.
{
    numVertices = 0;
    maxVertices = 50;
    vertices = new VertexType[50];
    marks = new bool[50];
}

template<class VertexType>
GraphType<VertexType>::GraphType(int maxV)
// Post: Arrays of size maxV are dynamically allocated for
//       marks and vertices.
//       numVertices is set to 0; maxVertices is set to maxV.
{
    numVertices = 0;
    maxVertices = maxV;
    vertices = new VertexType[maxV];
    marks = new bool[maxV];
}

template<class VertexType>
// Post: arrays for vertices and marks have been deallocated.
GraphType<VertexType>::~GraphType()
{
    delete [] vertices;
    delete [] marks;
}
const int NULL_EDGE = 0;

template<class VertexType>
void GraphType<VertexType>::AddVertex(VertexType vertex)
// Post: vertex has been stored in vertices.
//       Corresponding row and column of edges has been set
//       to NULL_EDGE.
//       numVertices has been incremented.
{
    vertices[numVertices] = vertex;

    for (int index = 0; index < numVertices; index++)
    {
        edges[numVertices][index] = NULL_EDGE;
        edges[index][numVertices] = NULL_EDGE;
    }
    numVertices++;
}
template<class VertexType>
int IndexIs(VertexType* vertices, VertexType vertex)
// Post: Returns the index of vertex in vertices.
{
    int index = 0;

    while (!(vertex == vertices[index]))
        index++;
    return index;
}

template<class VertexType>
void GraphType<VertexType>::AddEdge(VertexType fromVertex,
                                    VertexType toVertex, int weight)
// Post: Edge (fromVertex, toVertex) is stored in edges.
{
    int row;
    int col;

    row = IndexIs(vertices, fromVertex);
    col = IndexIs(vertices, toVertex);
    edges[row][col] = weight;
}

template<class VertexType>
int GraphType<VertexType>::WeightIs
        (VertexType fromVertex, VertexType toVertex)
// Post: Returns the weight associated with the edge
//       (fromVertex, toVertex).
{
    int row;
    int col;

    row = IndexIs(vertices, fromVertex);
    col = IndexIs(vertices, toVertex);
    return edges[row][col];
}
template<class VertexType>
void GraphType<VertexType>::GetToVertices(VertexType vertex,
                                          QueType<VertexType>& adjVertices)
// Post:
{
    int fromIndex;
    int toIndex;

    fromIndex = IndexIs(vertices, vertex);
    for (toIndex = 0; toIndex < numVertices; toIndex++)
        if (edges[fromIndex][toIndex] != NULL_EDGE)
            adjVertices.Enqueue(vertices[toIndex]);
}





// ===============================================
// GCB additions
// ===============================================




template<class VertexType>
void GraphType<VertexType>::ClearMarks(){
    //Post:  All marks have been cleared
    for (int index = 0; index < numVertices; index++){
        marks[index] = false;
    }
    // cout << "GT169: Marks Cleared" << endl;
}

template<class VertexType>
void GraphType<VertexType>::MarkVertex(VertexType thisVertex){
    // Post: the named vertex is marked
    // cout << "GT175: Marking " << thisVertex;
    marks[IndexIs(vertices, thisVertex)] = true;
    // cout << ", " << boolalpha << marks[IndexIs(vertices, thisVertex)] << endl;
}


template<class VertexType>
bool GraphType<VertexType>::IsMarked(VertexType thisVertex){
    // Returns true if the named vertex is marked
    return marks[IndexIs(vertices, thisVertex)];
}

template<class VertexType>
void GraphType<VertexType>::Print(){
    // Print Vertices
    cout << "Vertices: " << endl << "   ";
    for (int i = 0; i < numVertices; i++){
        cout <<  vertices[i] << " " ;
    }
    cout << endl;

    // Print Edges
    cout << "Edges: " << endl;
    for (int i = 0; i< numVertices; i++){
        cout << vertices[i] << "  ";
        for (int j = 0; j<numVertices; j++){
            if (edges[i][j] != NULL_EDGE) cout << "X ";
            else cout << "- ";
        }
        cout << endl;
    }
}

template<class VertexType>
void GraphType<VertexType>::Print(ofstream &logFile){
    // Print Vertices
    logFile << "Vertices: " << endl << "   ";
    for (int i = 0; i < numVertices; i++){
        logFile <<  vertices[i] << " " ;
    }
    logFile << endl;

    // Print Edges
    logFile << "Edges: " << endl;
    for (int i = 0; i< numVertices; i++){
        logFile << vertices[i] << "  ";
        for (int j = 0; j<numVertices; j++){
            if (edges[i][j] != NULL_EDGE) logFile << "X ";
            else logFile << "- ";
        }
        logFile << endl;
    }
}

template<class VertexType>
void GraphType<VertexType>::PrintMarks() {
    // Print Vertices
    cout << "Marks: " << endl;
    for (int i = 0; i < numVertices; i++) {
        cout << vertices[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < numVertices; i++) {
        if (marks[i]) cout << "X ";
        else cout << ". ";
    }
    cout << endl;
}
#endif //FP02_GRAPHTYPE_H
