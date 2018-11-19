#include "RGReader.h"
//#include "RawDataBase.h"
//#include "DefDataBase.h"
//using namespace DefParser;

RouteGuide addRouteGuide(DefParser::Net net double x0, double y0, double x1, double y1, int metal){
    
    RouteGuide rg = RouteGuide(x0,y0,x1,y1,metal);
    rg.addNet(net);
    return rg;
    
}

RouteGuide searchRouteGuide(vector<RouteGuide> vRouteGuide,double x0, double y0, double x1, double y1, int numMetal){
    for (int i = 0; i < vRouteGuide.size(); ++i) {
        
        RouteGuide rg = vRouteGuide[i];
        
        if ((rg.x0 == x0) && (rg.y0 == y0) && (rg.x1 == x1) && (rg.y1 == y1) && (rg.metal == numMetal)){
            return rg;
        }
    }
    
    //return nullptr;
}

// net stored in route guides
vector<RouteGuide> parseRouteGuid(string fileName, RawDatabase r_db){
    
    
    std::ifstream read(fileName);
    
    DefParser::Net currentNet;
    RouteGuide currentRouteGuide;
    vector<RouteGuide> vRouteGuide;
    
    // helper var for parsing
    bool isNet = true;
    bool firstParen = false;
    
    stringstream stream;
    char* currentStr;
    
    std::string netName;
    double x0,y0, x1, y1;
    int numMetal;
    std::string metal;
    
    //for each line in route guide file
    for (std::string line; std::getline(read, line); ) {
        
        // removing punctuation like paranthesis, commas
        std::replace_if(std::begin(line), std::end(line), [] (char x) { return std::ispunct(x); }, ' ');
        
        // inserting the line into a stream that helps us parse the content
        std::stringstream ss(line);
        
        ss >> currentStr;
        
        if (isNet){
            
            isNet = false;
            
            // search for current net
            stream(currentStr);
            stream >> netName;
            currentNet = r_db.getNet(netName);
            
        } else if (currentStr[0] == 0x28) {
            
            if (firstParen == true) {
                isNet = true;
                firstParen = false;
            } else {
                firstParen = true;
            }
            
        } else {
            //parse line to get route guide info
            stream(currentStr);
            stream >> x0;
            ss >> y0 >> x1 >> y1 >> metal;
            numMetal = (int) metal[5] - 48;
            
            //search if the route guide is already in list
            RouteGuide rg = searchRouteGuide(vRouteGuidex0,y0,x1,y1,numMetal);
            if (rg != NULL) {
                rg.addNet(currentNet);
            } else {
                
                rg = addRouteGuide(currentNet,x0,y0,x1,y1,numMetal);
                vRouteGuide.push_back(rg);
                
            }
        }
    }
    return vRouteGuide;
}
