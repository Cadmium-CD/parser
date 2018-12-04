//
//  ConflictGraph.hpp
//  
//
//  Created by Irene Zhang on 11/17/18.
//

#ifndef ConflictGraph_hpp
#define ConflictGraph_hpp

#include <stdio.h>
#include <math.h>
#include <vector>
#include "../parser/lefdef/RGReader.h"

using namespace std;

class AP {
public:
    double x;
    double y;
    bool via;

    AP (double x, double y) {
	this->x = x;
	this->y = y;
	this->via = false;
    }
};

class APC {
public:
    DefParser::Net net;
    vector <AP> vAP;
};


class Segment {
public:
    DefParser::Net net;
    APC* apc1; //TODO: ???
    APC* apc2;
    RouteGuide* rg1;
    RouteGuide* rg2;
    AP* AP1;
    AP* AP2;
    double weight;
    int degree;
    
    Segment(DefParser::Net net, APC apc1, APC apc2, RouteGuide rg1, RouteGuide rg2, AP AP1, AP AP2) {
        this->net = net;
        this->apc1 = &apc1;
        this->apc2 = &apc2;
        this->rg1 = &rg1;
        this->rg2 = &rg2;
        this->AP1 = &AP1;
        this->AP2 = &AP2;
        this->weight = abs(AP1.x - AP2.x) + abs(AP1.y - AP2.y);
        this->degree = 0;
    }
};


class GridPt {
public:
    double x;
    double y;
    
    vector<Segment> vSegment;
    
};


class Grid {
public:
    vector<vector<GridPt>> vGridPt;
    // sort in increasing order
    void sort() {
        
        
    }

};

class Edge {
public:
    Segment* seg1;
    Segment* seg2;

    Edge(Segment seg1, Segment seg2){
        this->seg1 = &seg1;
        this->seg2 = &seg2;
    }

};

class ConflictGraph {
public:
    vector<Segment> vSegment;
    vector<Edge> vUniEdge;
    vector<Edge> vDRCEdge;
    vector<Segment> MIS; //maximum independent set

    
    void findMIS () {
        
        vector<Segment> vertices = vSegment;
        
        while (vertices.size() != 0) {
        
        /*
         
          find vertex with min degree
          add to set
          remove its neighbors
    
        
        
        */
            
        }
    }
    
    void addSegment (Segment segment) {
        
        vSegment.push_back(segment);
        
    }
    
    void addUniEdge(Segment segment) {
        
        for (int i = 0; i < vSegment.size(); ++i ) {
            
            Edge edge = Edge (segment, vSegment[i]);
            vUniEdge.push_back(edge);
            
        }
        
    }
    
    void addDRCEdgeInGridPt(GridPt gridPt) {
        
        // currently checking overlapping short only
        vector<Segment> vSegment = gridPt.vSegment;
        
        for (int i = 0; i < vSegment.size(); ++i) {
            for (int j = i + 1; j < vSegment.size(); ++j) {
                
                Edge edge = Edge(vSegment[i], vSegment[j]);
                ++vSegment[i].degree;
                ++vSegment[j].degree;
                
            }
        }
    }
    
    
    void genDRCEdge(Grid grid) {
        
        for (int i = 0; i < grid.vGridPt.size(); ++i) {
            
            for (int j = 0; j < grid.vGridPt[i].size(); ++j) {
                
                addDRCEdgeInGridPt(grid.vGridPt[i][j]);
                
            }
        }
        
    }

    
};


#endif /* ConflictGraph_hpp */
