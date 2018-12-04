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

    RouteGuide(double x0, double y0, double x1, double y1) {
        this->x0 = x0;
        this->y0 = y0;
        this->x1 = x1;
        this->y1 = y1;

    }

    void addNet(DefParser::Net net){
        netArray.push_back(net);
    }
    
    bool operator==(const RouteGuide& rg) {
        if (this->metal == rg.metal) {
            if ((this->x0 == rg.x0) && (this->x1 == rg.x1)) {
                if ((this->y0 == rg.y0) && (this->y1 == rg.y1)){
                    return true;
                }
            }
        }
        return false;
        
    }
    
};
//petal class
class panel{

public:
	int fixedWidth;
	bool horiz;
		
	// map<int,bool>mapList;
	// vector<route_guide nsize>rgList;/
	vector<bool> upperOverlap;
	vector<bool> lowerOverlap;
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
	void creatPanel(vector<RouteGuide> routeGuide,map<int, int> vertMap,map<int, int> horizMap){
		if(this->horiz){
			for(int i = 0;i<vertMap.size();i++){
				panel* p = new panel();
				p->setHoriz(true);
				double y = vertMap[i];
				for(int j = 0;j<horizMap.size();j++){
					double x = horizMap[j];
					//查找对应xy的routeguideraw 类??用的遍历 如何用find_if?
					for(int k = 0;k<routeGuide.size();k++){
						if((routeGuide[k].x0 == x) & (routeGuide[k].y0 == y)){
							p->rgList.insert(pair<int,RouteGuide>(j,routeGuide[k]));
						}
					}	
				}
				//cout<<this->panelArray.size()<<endl;
				this->addPanel(*p);
			}
		}else{	
			for(int i = 0;i<horizMap.size();i++){
				panel* p = new panel();
				p->setHoriz(false);
				register double x = horizMap[i];
				for(int j = 0;j<vertMap.size();j++){
					register double y = vertMap[j];
					//查找对应xy的routeguideraw 类??用的遍历 如何用find_if?
					for(int k = 0;k<routeGuide.size();k++){
						if((routeGuide[k].x0 == x) & (routeGuide[k].y0 == y)){
							p->rgList.insert(pair<int,RouteGuide>(j,routeGuide[k]));
						}
					}	
				}
				this->addPanel(*p);
			}
		}
	}
};
/////???what class
class top{
	
public:
	//int numOfVert,numOfHoriz;
	//vector<metal> metalArray;
	vector<int> vertCoordinate;
	vector<int> horizCoordinate;
	map<int, int> vertMap;
	map<int, int> horizMap; 
	
//search coordinates of route guide in horiz/vert panel
	//search odd metal
	void searchHoriz(vector<vector<RouteGuide>> oddRouteGuide){//1,3,5,7
		bool exist;
	    for(int i=0;i<oddRouteGuide.size();i=i+2){
	    	for(int j=0;j<oddRouteGuide[i].size();j++){
	    		int tempx = oddRouteGuide[i][j].x0;
	    		exist = std::find(horizCoordinate.begin(), horizCoordinate.end(), tempx) != horizCoordinate.end();
	    		if(!exist){
	    			//cout<<tempx<<endl;
	    			horizCoordinate.push_back(tempx);
	    		} 
			} 
		}
	}
	 //search even metal
	void searchVert(vector<vector<RouteGuide>> evenRouteGuide){	
		bool exist;
	    for(int i=1;i<evenRouteGuide.size();i=i+2){
	    	for(int j=0;j<evenRouteGuide[i].size();j++){
	    		int tempy = evenRouteGuide[i][j].y0;
	    		exist = std::find(vertCoordinate.begin(), vertCoordinate.end(), tempy) != vertCoordinate.end();
	    		if(!exist){
	    			//cout<<tempx<<endl;
	    			vertCoordinate.push_back(tempy); 
	    		} 
			}
		}
	}
	//sort coordinates and delete repeated part
	void postProcessing(){
		//vector<int>::const_iterator pos;
		sort(this->vertCoordinate.begin(),this->vertCoordinate.end());
		sort(this->horizCoordinate.begin(),this->horizCoordinate.end());
		/*vector<int>::iterator it;
		it = unique(this->vertCoordinate.begin(),this->vertCoordinate.begin());
		cout << it - this->vertCoordinate.begin(); 
		this->vertCoordinate.erase(it,this->vertCoordinate.begin());
		this->horizCoordinate.erase(unique(this->horizCoordinate.begin(),this->horizCoordinate.begin()),this->horizCoordinate.begin());

		pos = unique(this->horizCoordinate.begin(),this->horizCoordinate.begin());
		earse(pos,this->horizCoordinate.end());*/
	}
	
//potential number of positions to be filled with routeguide
/*	void setNumVert(void){
		this->numOfVert = this->vertCoordinate.size();
	}

	void setNumHoriz(void){
		this->numOfHoriz = this->horizCoordinate.size();
	}*/
	
//map coordinates
	void mapCoordinates(){
		for(int i=0;i<this->vertCoordinate.size();i++){
			this->vertMap.insert(pair<int,double>(i,this->vertCoordinate[i]));
		}
		for(int i=0;i<this->horizCoordinate.size();i++){
			this->horizMap.insert(pair<int,double>(i,this->horizCoordinate[i]));
		}
	}
	
//store data in metalArray
	/*void addMetal(metal metal){
		metalArray.push_back(metal);
	}*/
};



//RouteGuide




RouteGuide addRouteGuide(DefParser::Net net, double x0, double y0, double x1, double y1);

RouteGuide* searchRouteGuide(vector<RouteGuide> vRouteGuide,double x0, double y0, double x1, double y1);

vector<vector<RouteGuide>> parseRouteGuid(string fileName, RawDataBase r_db);

vector<Metal> processRG(vector<vector<RouteGuide>> RG,map<int, int> vertMap,map<int, int> horizMap);

void findOverlap(vector<Metal>* iMetal);


#endif
