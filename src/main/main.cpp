#include <stdlib.h>
#include <iostream>
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include <string>

int main(){

  string def_file = "/home/yi/Utexas/CAD/CAD/parser/ispd18_sample.input.def";

  RawDataBase* db = new RawDataBase();

  readDef(def_file, *db);

  printf("row name: %d\n",db->getRowArray()[0].step[0]);
}
