/*
    _
   /_\  _ _ ___ ___
  / _ \| '_/ -_|_-<
 /_/ \_\_| \___/__/

*/
#include "Ares.h"

/*
Description:
Function that is called when the library is loaded, use this as an entry point.
*/
int __attribute__((constructor)) Ares() {

  SDL2::SetupSwapWindow();

  return 0;

}
