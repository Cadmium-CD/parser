#include <vector>
#include <string>
#include <iostream>
#include "../gr/ConflictGraph.hpp"
using namespace std;

int main(){

  string def_file = "/home/CAD/parser/src/main/ispd18_sample.input.def";
  string lef_file = "/home/CAD/parser/src/main/ispd18_sample.input.lef";
  string RG_file = "/home/CAD/parser/src/main/ispd18_sample.input.guide";


  RawDataBase* db = new RawDataBase();
  MacroDataBase* macro_db = new MacroDataBase();
  top* panelRG = new top();


  readDef(def_file, *db);
  readLef(lef_file, *macro_db);

  //obtain raw Rout GUide
  vector<vector<RouteGuide>> vRG = parseRouteGuid(RG_file, *db);
  
  //find potential parser coordinates 
  panelRG->searchHoriz(vRG);
  panelRG->searchVert(vRG);
  panelRG->postProcessing();
  panelRG->mapCoordinates();

  //sort RG by metal
  vector<Metal> MT = processRG(vRG, panelRG->vertMap, panelRG->horizMap);

  //find overlap
  findOverlap(&MT);
  //cout<<"aa"<<endl;

  for(int i = 0;i<MT.size();i++){
    cout << "Metal ="<<MT[i].indexOfmetal<<endl;
    for(int j = 0;j<MT[i].panelArray.size();j++){
       vector<bool> temp = MT[i].panelArray[j].upperOverlap;
        for (int k = 0;k<temp.size();k++){
          //cout<<"hey"<<endl;
         cout<< MT[i].panelArray[j].upperOverlap[k];
        }
      cout<<endl;
    }
  }
 //out<< MT[0].panelArray[0].upperOverlap[2]<<endl;

  /*printf("row name: %d\n",db->getRowArray()[0].step[0]);
  printf("macro name: %f\n",macro_db->siteSizeX);
//print 
  for(int i = 0;i<MT.size();i++){
  	cout << "Metal ="<<MT[i].indexOfmetal<<endl;
  	for(int j = 0;j<MT[i].panelArray.size();j++){
  			map<int,RouteGuide> printmap;
  			printmap = MT[i].panelArray[j].rgList;
  			for (const auto &p : printmap) {
    			std::cout << "m[" << p.first << "] = " << p.second.x0 << '\n';
			}
  	}
  }

  for(int i = 0;i<vRG.size();i++){
  	for(int k = 0;k<vRG[i].size();i++){
  		//cout<<vRG[k].size()<<endl;
  		//cout << "x0 ="<<vRG[i][k].x0<<"y0 ="<<vRG[i][k].y0<<"x1 ="<<vRG[i][k].x1<<"y1 ="<<vRG[i][k].y1<<endl;
  		for(int j = 0;j<vRG[i][k].netArray.size();j++){
  		    //cout<< "net_name = " << RG[i].netArray[j].net_name << endl;
  		    	//cout <<vRG[i][k].netArray[j]<<endl;
  		}
  	}
  }

  for(int i = 0;i<panelRG->vertCoordinate.size();i++){
  	//cout <<panelRG->vertCoordinate[i]<<endl;
  }*/


}
