#include <vector>
#include <string>
#include <iostream>
using namespace std;

class Pin
{
public:
  string name;
  double pinX1,pinY1,pinXh,pinYh;
};


class StdCell
{
public:
  std::string macroName;
  double sizeX;
  double sizeY;

  int leftEdge;
  int rightEdge;

  vector<Pin> pinArray;

  void setSizeX(double size){
    sizeX = size;
  }

  void setSizeY(double size){
    sizeY = size;
  }

  void setEdgeLeft(int edge){
    leftEdge = edge;
  }

  void setEdgeRight(int edge){
    rightEdge = edge;
  }

  void setBottomVss(bool vss){
    Pin *p = new Pin();
    if (vss) {
      p->name = "vss";
      pinArray.push_back(*p);
    } else {
      p->name = "vdd";
      pinArray.push_back(*p);
    }

  }

  void setMacroName(std::string name){
    macroName = name;
  }

  void addPin(double x1, double y1, double xh, double yh, std::string name){
    Pin *p = new Pin();
    p->pinX1 = x1;
    p->pinY1 = y1;
    p->pinXh = xh;
    p->pinYh = yh;
    p->name = name;
    pinArray.push_back(*p);
  }

};

class Unit
{
  bool haspower;
  bool hasDatabase;
  bool hasCapacitance;
  double power;
  double capacitance;
  bool hasDatabase;
  std::string databaseName;
  double databaseNumber;
};

class MacroDataBase
{
public:
//LEF code
  double siteSizeX;
  double siteSizeY;

  string busBitChars;
  string clearanceMeasure;
  string divideChar;
  string version;
  double manufacturingGrid;

  vector<Unit> unitArray;
  vector<StdCell> stdCellArray;
  vector<LefLayerCut> cutLayersArray;

  void setLefSiteSizeX(double sizeX){
    siteSizeX = sizeX;
  }

  void setLefSiteSizeY(double sizeY){
    siteSizeY = sizeY;
  }

  void addStdCellLib(StdCell stdCell){
    stdCellArray.push_back(stdCell);
  }

  StdCell getStdCellLib(std::string name){
    for (int i = 0; i < stdCellArray.size(); ++i){
      if (name.compare(stdCellArray[i].macroName) == 0){
        return stdCellArray[i];
      }
    }
  }

  void setVersion(const std::string &v){
    version = v;
  }

  void setDivideChar(const std::string &v){
    divideChar = v;
  }

  void setManufacturingGrid(double v){
    manufacturingGrid = v;
  }

  void setClearanceMeasure(const std::string &v){
    clearanceMeasure = v;
  }

  void addUnitArray(Unit &unit){
    unitArray.push_back(unit);
  }

  void setBusbitChars_cbk(const std::string &v){
    busBitChars = v;
  }

  vector<LefLayerCut> cutLayers() {
    return cutLayersArray;
  } 

  vector<LefLayerRouting> cutLayers() {
    return cutLayersArray;
  } 

};
