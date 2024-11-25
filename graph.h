#ifndef MATRIX_H
#define MATRIX_H

#include "node.h"

const int infinity=999;
template <class type>
class graph {
    int** matrix;
    type* vertices;
    int total;
    int* costs;
    bool* visited;
    public:
    graph(int total,type* vertices) {
        this->total=total;
        this->vertices=vertices;
        costs=new int[total];
        visited=new bool[total];
        matrix=new int*[total];
        for (int i=0; i<total; i++) 
            matrix[i]=new int[total];
        for (int i=0; i<total; i++) {
            visited[i]=0;
            costs[i]=infinity;
            for(int j=0; j<total; j++) 
                matrix[i][j]=0; 
        }
    }
    ~graph() {
        delete vertices;
        delete costs;
        delete visited;
        for (int i=0; i<total; i++) 
            delete matrix[i];
    }
    int mindistance() {
        int min=infinity;
        int minlocation;
        for (int i=0; i<total; i++) {
            if (!(visited[i]) && costs[i]<=min) {
                min=costs[i];
                minlocation=i;
            }
        }
        return minlocation;
    }
    int shortest(int source,int destination) {

        costs[source]=0;
        for (int i=0; i<total-1; i++) {
            int loc=mindistance();
            visited[loc]=1;
            for (int j=0; j<total; j++) {
                if ((!(visited[j])) && (matrix[loc][j]!=0) 
                        && (costs[loc]!=infinity) && 
                    ((costs[loc]+matrix[loc][j])<costs[j])) 
                    costs[j]=costs[loc]+matrix[loc][j];
            }
        }
        return costs[destination];
    }

    void insert(int source,int destination,int distance) {
        matrix[source][destination]=distance;
        matrix[destination][source]=distance;
    }
};

#endif