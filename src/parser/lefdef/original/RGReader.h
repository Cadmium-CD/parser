#ifndef _RGREADER_H
#define _RGREADER_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

//#include "DefDatabase.h"


class RawDataBase;

class RouteGuide{
    double x0,y0,x1,y1;
    int metal;
    vector<DefParser::Net>netArray;
    //vector<net2pin> netToPin;
    //vector<int> overlap;

    void addNet(DefParser::Net net){
    	netArray.push_back(net);
    }
};

RouteGuide addRouteGuide(DefParser::Net net, double x0, double y0, double x1, double y1, int metal);

RouteGuide searchRouteGuide(vector<RouteGuide> vRouteGuide,double x0, double y0, double x1, double y1, int numMetal);

vector<RouteGuide> parseRouteGuid(string fileName, RawDataBase r_db);

#endif