#include <Vector.h>

const int ELEMENT_COUNT_MAX = 9999;

typedef struct  effect{
  int life;
  void (*effectp) (struct effect *self);
}effect;


void star( effect *self) {
  if (self -> life > 0) {
    self -> life--;
  }
  else {
    //delete from queue here
  }
  Serial.print("Life is ");
  Serial.println(self -> life);
  delay(10);
}


typedef Vector<effect> Elements;
effect e;


void setup() {
  Serial.begin(115200);
  e.life = 30;
  e.effectp = star;
}


void loop() {

  e.effectp(&e);


  
}
