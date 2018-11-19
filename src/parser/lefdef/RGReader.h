#ifndef _RGREADER_H
#define _RGREADER_H

#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <map>
#include "DefReader.h"
#include "LefReader.h"
using namespace std;


class RouteGuide{
public:
    double x0,y0,x1,y1;
    int metal;
    vector<DefParser::Net>netArray;
    //vector<net2pin> netToPin;
    //vector<int> overlap;

    RouteGuide(double x0, double y0, double x1, double y1, int metal) {
        this->x0 = x0;
        this->y0 = y0;
        this->x1 = x1;
        this->y1 = y1;
        this->metal = metal;

    }

    void addNet(DefParser::Net net){
        netArray.push_back(net);
    }
};
//petal class
/*class panel{

public:
	int fixedWidth;
	bool horiz;
		
	// map<int,bool>mapList;
	// vector<route_guide nsize>rgList;/
	map<int,RouteGuide>rgList;
	
//numOfVert or numOfHoriz;	
	void setHoriz(bool horiz){
		this->horiz = horiz;
	}
	
//map from top class
	//void creatPanel(RouteGuide routeGuide,map<int, double> vertMap,map<int, double> horizMap)
};

//metal class
class Metal{
	
public:
	bool horiz; //1 means metal is in horizontal direction
	int indexOfmetal;
	
	vector<panel> panelArray;
	
	void setHoriz(bool horiz){
		this->horiz = horiz;
	}
	
	void seIndex(int indexOfmetal){
		this->indexOfmetal = indexOfmetal;
	}
	
	
	void addPanel(panel panel){
		panelArray.push_back(panel);
	}

//input each layer's raw routguide	and map from top class
	void creatPanel(vector<RouteGuide> routeGuide,map<int, double> vertMap,map<int, double> horizMap){
		if(this->horiz){
			for(int i = 0;i<vertMap.size();i++){
				panel p = new panel();
				p.setHoriz(true);
				register double y = vertMap[i]；
				for(int j = 0;j<horizMap.size();j++){
					register double x = horizMap[j];
					//查找对应xy的routeguideraw 类??用的遍历 如何用find_if?
					for(int k = 0;k<routeGuide.size();k++){
						if((routeGuide[k].x0 == x) & (routeGuide[k].y0 == y)){
							p.rgList.insert(pair<int,RouteGuide>(j,routeGuide[k]))
						}
					}	
				}
				this->addPanel(p);
			}
		}else{	
			for(int i = 0;i<horizMap.size();i++){
				panel p = new panel();
				p.setHoriz(false);
				register double x = horizMap[i]；
				for(int j = 0;j<vertMap.size();j++){
					register double x = vertMap[j];
					//查找对应xy的routeguideraw 类??用的遍历 如何用find_if?
					for(int k = 0;k<routeGuide.size();k++){
						if((routeGuide[k].x0 == x) & (routeGuide[k].y0 == y)){
							p.rgList.insert(pair<int,RouteGuide>(j,routeGuide[k]))
						}
					}	
				}
				this->addPanel(p);
			}
		}
	}
};
*/




//RouteGuide




RouteGuide addRouteGuide(DefParser::Net net, double x0, double y0, double x1, double y1, int metal);

RouteGuide* searchRouteGuide(vector<RouteGuide> vRouteGuide,double x0, double y0, double x1, double y1, int numMetal);

vector<RouteGuide> parseRouteGuid(string fileName, RawDataBase r_db);

/*vector<Metal> processRG(vector<RouteGuide> RG);

processMetal(vector<Metal> MT,top* top);*/

#endif