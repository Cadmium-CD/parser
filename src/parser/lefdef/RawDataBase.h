#include <vector>
#include <string>
#include <iostream>
#include "LefDriver.h"

using namespace std;
//using namespace LefParser;
class RawDataBase{

public:
  bool fence;
  bool guide;

  int defUnit;
  int DieXl;
  int DieYl;
  int DieXh;
  int DieYh;

  vector<DefParser::Row> rowArray;
  vector<DefParser::Component> componentArray;
  vector<DefParser::Pin> pinArray;
  vector<DefParser::Net> netArray;
  vector<DefParser::Snetp> snetpArray;
  vector<DefParser::Group> groupArray;
  vector<DefParser::Via> viaArray;


  void setDefUnit(int defUnit){
    this->defUnit = defUnit;
  }

  void setDieXl(int xl){
    this->DieXl = xl;
  }

  void setDieYl(int yl){
    this->DieYl = yl;
  }

  void setDieXh(int xh){
    this->DieXh = xh;
  }

  void setDieYh(int yh){
    this->DieYh = yh;
  }

  void addRowArray(const DefParser::Row &row){
    rowArray.push_back(row);
  }

  vector<DefParser::Row> getRowArray(){
    return rowArray;
  }

  void addComponentArray(const DefParser::Component &component){
    componentArray.push_back(component);
  }

  vector<DefParser::Component> getComponentArray(){
    return componentArray;
  }

  void addPinArray(const DefParser::Pin &pin){
    pinArray.push_back(pin);
  }

  vector<DefParser::Pin> getPinArray(){
    return pinArray;
  }

  void addNetArray(const DefParser::Net &net){
    netArray.push_back(net);
  }

  vector<DefParser::Net> getNetArray(){
    return netArray;
  }

  void addSnetpArray(const DefParser::Snetp &snetp){
    snetpArray.push_back(snetp);
  }

  vector<DefParser::Snetp> getSnetpArray(){
    return snetpArray;
  }

  void addGroupArray(const DefParser::Group &group){
    groupArray.push_back(group);
  }

  void addViaArray(const DefParser::Via &via){
    viaArray.push_back(via);
  }


//LEF code
  double siteSizeX;
  double siteSizeY;


  //vector<LefParser::StdCell> stdCellArray;
  std::unordered_map<std::string, const LefParser::StdCell> stdCellArray;

  void setLefSiteSizeX(double sizeX){
    siteSizeX = sizeX;
  }

  void setLefSiteSizeY(double sizeY){
    siteSizeY = sizeY;
  }

//TODO
  void addStdCellLib(std::string name, const LefParser::StdCell stdCell){
    stdCellArray.insert(name, stdCell);
  }

  LefParser::StdCell getStdCellLib(std::string name){
    return stdCellArray.find(name);
  }


  vector<LefParser::StdCell> stdCellArray;

  void setLefSiteSizeX(double sizeX){
    siteSizeX = sizeX;
  }

  void setLefSiteSizeY(double sizeY){
    siteSizeY = sizeY;
  }

//TODO
  void addStdCellLib(const LefParser::StdCell stdCell){
    stdCellArray.pushback(stdCell);
  }

  LefParser::StdCell getStdCellLib(std::string name){
    for (int = 0; i < stdCellArray.size(); ++i){
      if (name.compare(stdCellArray[i].macroName) == 0){
        return stdCellArray[i];
      }
    }

  }
