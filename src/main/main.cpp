#include <stdlib.h>
#include <iostream>
#include "../parser/lefdef/DefReader.h"
#include "../parser/lefdef/LefReader.h"
#include <string>

int main(){

<<<<<<< HEAD
  string def_file = "/home/yi/Utexas/CAD/CAD/parser/ispd18_sample.input.def";
  string lef_file = "/home/yi/Utexas/CAD/CAD/parser/ispd18_sample.input.lef";
=======
  string def_file = "/home/cadmium/CAD_project/parser/src/main/ispd18_sample.input.def";
  string lef_file = "/home/cadmium/CAD_project/parser/src/main/ispd18_sample.input.lef";
>>>>>>> cbd5d49d77bdde01054e8f31b214ddc17a460836

  RawDataBase* db = new RawDataBase();
  MacroDataBase* macro_db = new MacroDataBase();

  readDef(def_file, *db);
  readLef(lef_file, *macro_db);

<<<<<<< HEAD
  //printf("row name: %d\n",db->getRowArray()[0].step[0]);
  printf("siteSizeX: %f\n",macro_db->siteSizeX);
=======
  printf("row name: %d\n",db->getRowArray()[0].step[0]);
  printf("macro name: %f\n",macro_db->siteSizeX);
>>>>>>> cbd5d49d77bdde01054e8f31b214ddc17a460836
}
