//
//  ConflictGraph.cpp
//  
//
//  Created by Irene Zhang on 11/17/18.
//

#include "ConflictGraph.hpp"

void genSegments (APC apc1, APC apc2, RouteGuide rg1, RouteGuide rg2, ConflictGraph conflictGraph) {

    AP ap1, ap2;
    
    for (int i = 0; i < apc1.vAP.size(); ++i) {
        
        ap1 = apc1.vAP[i];
    
        for (int j = 0; j < apc2.vAP.size(); ++j) {
            
            ap2 = apc2.vAP[j];
            
            Segment segment = Segment(apc1.net, apc1, apc2, rg1, rg2, ap1, ap2);
            
            //TODO: need to points to grid
            
            conflictGraph.addSegment(segment);
            
            conflictGraph.addUniEdge(segment);
            
        }
    }
    
}

