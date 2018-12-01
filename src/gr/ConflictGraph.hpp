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


class AP {
    Double x;
    Double y;
};

class GridPt {
    
    double x;
    double y;
    
    vector<Segment> vSegment;
    
};


class Grid {
    
    vector<vector<GridPt>> vGridPt;
    
    // sort in increasing order
    void sort() {
        
        
    }

};

class APC {
public:
    Net net;
    vector <AP> vAP;
};

class Segment {
public:
    Net net;
    APC apc1; //TODO: ???
    APC apc2;
    AP AP1;
    AP AP2;
    double weight;
    int degree;
    
    Segment(Net net, APC apc1, APC apc2, AP AP1, AP AP2) {
        this.net = net;
        this.apc1 = apc1;
        this.apc2 = apc2;
        this.AP1 =AP1;
        this.AP2 = AP2;
        this.weight = abs(AP1.x - AP2.x) + abs(AP1.y - AP2.y);
        this.degree = 0;
    }
};

class Edge {
    Segment seg1;
    Segment seg2;
};

class ConflctGraph {
    vector<Segment> vSegment;
    vector<Edge> vUniEdge;
    vector<Edge> vDRCEdge;
    vector<Segment> MIS; //maximum independent set

    
    void findMIS () {
        
        vertex<Segment> vertices = vSegment;
        
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

    
}


#endif /* ConflictGraph_hpp */
