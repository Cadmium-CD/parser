
#include "RGReader.h"


using namespace std;


RouteGuide addRouteGuide(DefParser::Net net, double x0, double y0, double x1, double y1){
    
    RouteGuide rg = RouteGuide(x0,y0,x1,y1);
    rg.addNet(net);
    return rg;
    
}

RouteGuide* searchRouteGuide(vector<RouteGuide> vRouteGuide,double x0, double y0, double x1, double y1){
    for (int i = 0; i < vRouteGuide.size(); ++i) {
        
        RouteGuide rg = vRouteGuide[i];
        
        if ((rg.x0 == x0) && (rg.y0 == y0) && (rg.x1 == x1) && (rg.y1 == y1)){
            return &rg;
        }
    }
    
    return nullptr;
}

// net stored in route guides
vector<vector<RouteGuide>> parseRouteGuid(string fileName, RawDataBase r_db){
    
    
    std::ifstream fin(fileName);
    
    DefParser::Net currentNet;
    //RouteGuide currentRouteGuide;
    vector<vector<RouteGuide>> vRouteGuide(9);
    
    // helper var for parsing
    bool isNet = true;
    bool firstParen = false;
    
    std::string currentStr;
    
    std::string netName;
    double x0,y0, x1, y1;
    int numMetal;
    std::string metal;
    
    //for each line in route guide file
    for (std::string line; std::getline(fin, line); ) {
        
        // removing punctuation like paranthesis, commas
        //std::replace_if(std::begin(line), std::end(line), [] (char x) { return std::ispunct(x); }, ' ');
        
        // inserting the line into a stream that helps us parse the content
        std::stringstream ss;
        ss<<line;
        
        ss >> currentStr;
        //cout<<currentStr[0]<<endl;
        
        if (isNet){
            
            isNet = false;
            
            // search for current net
            stringstream stream(currentStr);
            stream >> netName;
            currentNet = r_db.getNet(netName);
            //cout <<currentNet<<endl;
            
        } else if ((currentStr[0] == 0x28) | (currentStr[0] == 0x29) ){
                //cout<<"hey"<<endl;
            if (firstParen == true) {
                isNet = true;
                firstParen = false;
                //cout<<"true"<<endl;
            } else {
                firstParen = true;
            }
            
        } else {
            //parse line to get route guide info
            stringstream stream(currentStr);
            stream >> x0;
            ss >> y0 >> x1 >> y1 >> metal;
            numMetal = (int) metal[5] - 48;
            
            //search if the route guide is already in list
            RouteGuide* rgPtr = searchRouteGuide(vRouteGuide[numMetal],x0,y0,x1,y1);
            if (!rgPtr) {
                RouteGuide rg = addRouteGuide(currentNet,x0,y0,x1,y1);
                vRouteGuide[numMetal].push_back(rg);
            } else {
                rgPtr->addNet(currentNet);
            }
        }
    }
    return vRouteGuide;
}

/*vector<Metal> processRG(vector<RouteGuide> RG){
    vector<Metal> vMetal[9];
    for(int i = 0;i<9;i++){
        vmetal[i].setHoriz((i+1)%2);
    }
    for(int i = 0;i<9;i++){
        vmetal[i].seIndex((i+1)%2);
    }
    for(int i = 0;i<9;i++){
    }

    return vMetal;
}

processMetal(vector<Metal> MT,top* top){

}*/
