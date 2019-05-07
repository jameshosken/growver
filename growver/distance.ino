#define DISTANCE false

#if DISTANCE 
#include "SR04.h"
#endif

int dist;

#if DISTANCE
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
#endif


void handleDistance(){
  #if DISTANCE
  dist=sr04.Distance();
  Serial.print("dist: ");
  Serial.println(dist);
  #endif
}
