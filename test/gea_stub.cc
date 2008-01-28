
#include <gea/API.h>
#include <gea/posix/ShadowEventHandler.h>
#include <gea/posix/PosixApiIface.h>

extern "C"
int gea_main(int argc, const char * const *argv);


int main(int argc, const char **argv) {
  int ret;
  gea::initPosixApiIface(); // initialise GEA 

  ret = gea_main(argc,argv);
  
  if (ret == 0) {
    // start the event loop
    static_cast<gea::ShadowEventHandler *>( gea::geaAPI().subEventHandler )->run();
  }
  return ret;
}

