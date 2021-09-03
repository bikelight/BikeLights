
typedef struct  effect {
  int life;
  int number;
  int chan;
  void (*effectp) (struct effect *self);
} effect;


const int ELEMENT_COUNT_MAX = 99;
effect storage_array[ELEMENT_COUNT_MAX];
Vector<effect> vector(storage_array);


void star( effect *self) {
  if (self -> life > 0) {
    self -> life = (self -> life ) - 1;
  }

  Serial.print("Life is ");
  Serial.print(self -> chan);
  Serial.print(" ");
  Serial.println(self -> life);
  //delay(10);
  CRGB color;
  if (self -> chan) {
    color = CRGB::Blue;
    fill_solid(leds + 30, 10, color );
  }
  else {
    color =  CRGB::Red;
    fill_solid(leds + 40, 10, color );
  }
  //fill_solid(leds, NUM_LEDS,color );
}

void createEffect(int chan) {
  effect e;
  e.life = 30;
  e.chan = chan;
  e.effectp = star;
  e.number = 1024;
  vector.push_back(e);
}
