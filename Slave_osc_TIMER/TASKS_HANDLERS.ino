
void tIncHue() {
  //Serial.println("incrementing hue");
  gHue++;
  baseColorValue++;
}

void tNextPattern() {
  // Serial.println("incrementing pattern");
  nextPattern();
}

void tDoLight() {
  gPatterns[animationNumber]();
  //Serial.println("doLights");

  for (int i = 0; i < vector.size(); i++) {
    Serial.print("Vector ");
    vector[i].effectp(&vector[i]);
    if (vector[i].life == 0) {
      vector.remove(i);
    }
    //    Serial.print("Array ");
    //    array[0].effectp(&array[i]);

  }

  //  if ( doEffect == true) {
  //
  //    effectCounter--;
  //    double now = millis() / 1000.0;
  //    double now_scaled = now / 10; //(slow down cycling)
  //    //CRGB color = CRGB(pow(sin(now_scaled), 2) * baseColorValue, BRIGHTNESS_SCALE[min(soundVals[0] / 4, MAX_BRIGHTNESS - 1)], pow(cos(now_scaled), 2) * baseColorValue);
  //    //fill_solid(leds, NUM_LEDS, color);
  //    //fill_solid(leds, NUM_LEDS, CRGB(0, 0, soundVals[0] / 4));
  //    FastLED.showColor(CHSV(soundVals[2] / 4, 255, soundVals[2] / 4));
  //    //fill_rainbow( leds, NUM_LEDS, soundVals[0] / 4, 7);
  //    if (effectCounter == 0){
  //      doEffect = false;
  //    }
  //  }

  FastLED.show();
}
