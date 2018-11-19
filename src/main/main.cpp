#include <vector>
#include <string>
#include <iostream>
#include "../parser/lefdef/RGReader.h"
using namespace std;

int main(){

  string def_file = "/home/cadmium/CAD_project/parser1117/src/main/ispd18_sample.input.def";
  string lef_file = "/home/cadmium/CAD_project/parser1117/src/main/ispd18_sample.input.lef";
  string RG_file = "/home/cadmium/CAD_project/parser1117/src/main/ispd18_sample.input.guide";


  RawDataBase* db = new RawDataBase();
  MacroDataBase* macro_db = new MacroDataBase();
  //top* panelRG  new top();
  //vector<Metal> MT = parse
  std::ostringstream ss;

  readDef(def_file, *db);
  readLef(lef_file, *macro_db);

  //obtain raw Rout GUide
  vector<RouteGuide> RG = parseRouteGuid(RG_file, *db);
  
  //sort RG by metal
  /*MT = processRG(RG);

  //build panel in each layer
  processMetal(MT,*top);*/
  
  

  printf("row name: %d\n",db->getRowArray()[0].step[0]);
  printf("macro name: %f\n",macro_db->siteSizeX);

  for(int i = 0;i<RG.size();i++){
  	cout << "x0 ="<<RG[i].x0<<"	y0 ="<<RG[i].y0<<"x1 ="<<RG[i].x1<<"y1 ="<<RG[i].y1<<"metal"<<RG[i].metal<<endl;
  	for(int j = 0;j<RG[i].netArray.size();j++){
  		    //cout<< "net_name = " << RG[i].netArray[j].net_name << endl;
  		    	cout <<RG[i].netArray[j]<<endl;
  	}
  }

}
