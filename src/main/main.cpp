
#include <stdlib.h>
#include <iostream>
#include "../parser/lefdef/DefReader.h"
#include <string>

int main(){

  string def_file = "/home/cadmium/CAD_project/code/cp_aroutex/ispd18_sample.input.def";

  RawDataBase* db = new RawDataBase();

  readDef(def_file, *db);

  printf("row name: %d\n",db->getRowArray()[0].step[0]);
}
