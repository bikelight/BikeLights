#include <Arduino.h>
#include <Vector.h>
#include <Array.h>


typedef struct  effect {
  int life;
  int number;
  void (*effectp) (struct effect *self);
} effect;


void star( effect *self) {
  if (self -> life > 0) {
    self -> life = (self -> life ) - 1;
  }
  else {
    //delete from queue here


  }
  Serial.print("Life is ");
  Serial.print(self -> number);
  Serial.print(" ");
  Serial.println(self -> life);
  delay(10);
}


const int ELEMENT_COUNT_MAX = 99;
effect storage_array[ELEMENT_COUNT_MAX];
Vector<effect> vector(storage_array);

Array<effect, ELEMENT_COUNT_MAX> array;

void setup() {
  Serial.begin(115200);

  for (int i = 0; i < 10; i++) {
    effect e;
    e.life = random(100);
    e.effectp = star;
    e.number = i;
    vector.push_back(e);
  }

  //  for (int i = 0; i < 10; i++) {
  //    effect e;
  //    e.life = random(100);
  //    e.effectp = star;
  //    e.number = i;
  //    array.push_back(e);
  //  }
}


void loop() {
  // e.effectp(&e);



  if (vector.size() == 0) {
    Serial.println("---->>>>>>>>\n\n\n\n\n\n End here ------->>>>>>> ");
    for (int i = 0; i < 10; i++) {
      effect e;
      e.life = random(100);
      e.effectp = star;
      e.number = i;
      vector.push_back(e);
    }

  }



}
