#define THRESHOLD_0 600
#define THRESHOLD_1 600
#define THRESHOLD_2 600
#define THRESHOLD_3 600
#define THRESHOLD_4 600
#define THRESHOLD_5 600
#define THRESHOLD_6 600

bool didFire_0 = false;
bool didFire_1 = false;
bool didFire_2 = false;
bool didFire_3 = false;
bool didFire_4 = false;
bool didFire_5 = false;
bool didFire_6 = false;

void led0(OSCMessage &msg) {
  ledState = msg.getInt(0);
  Serial.print("/led0: ");
  Serial.println(ledState);
  soundVals[0] = ledState;

  if ( ledState >  THRESHOLD_0 ) {
    if (didFire_0 == false) {
      createEffect(0);
      didFire_0 = true;
    }
  }
  else {
    didFire_0 = false;
  }

}

void led1(OSCMessage &msg) {
  ledState = msg.getInt(0);
  //Serial.print("/led1: ");
  //Serial.println(ledState);
  soundVals[1] = ledState;

  if ( ledState >  THRESHOLD_1 ) {
    if (didFire_1 == false) {
      createEffect(1);
      didFire_1 = true;
    }
  }
  else {
    didFire_1 = false;
  }

}

void led2(OSCMessage &msg) {
  ledState = msg.getInt(0);
  //Serial.print("/led2: ");
  //Serial.println(ledState);
  soundVals[2] = ledState;
  //  if (soundVals[0] > 700) {
  //    doEffect = true;
  //    effectCounter = 3;
  //  }
}

void led3(OSCMessage &msg) {
  ledState = msg.getInt(0);
  //Serial.print("/led3: ");
  //Serial.println(ledState);
  soundVals[3] = ledState;
}
void led4(OSCMessage &msg) {
  ledState = msg.getInt(0);
  //Serial.print("/led4: ");
  //Serial.println(ledState);
  soundVals[4] = ledState;
}

void led5(OSCMessage &msg) {
  ledState = msg.getInt(0);
  //Serial.print("/led5: ");
  //Serial.println(ledState);
  soundVals[5] = ledState;
}
void led6(OSCMessage &msg) {
  ledState = msg.getInt(0);
  //Serial.print("/led6: ");
  //Serial.println(ledState);
  soundVals[6] = ledState;
}



void parseUdp() {
  OSCBundle bundle;
  int size = Udp.parsePacket();

  if (size > 0) {
    //    Serial.print("Size is");
    //    Serial.println(size);
    while (size--) {
      bundle.fill(Udp.read());
    }
    if (!bundle.hasError()) {
      bundle.dispatch("/vals/0", led0);
      bundle.dispatch("/vals/1", led1);
      bundle.dispatch("/vals/2", led2);
      bundle.dispatch("/vals/3", led3);
      bundle.dispatch("/vals/4", led4);
      bundle.dispatch("/vals/5", led5);
      bundle.dispatch("/vals/6", led6);
    }
  } else {
    error = bundle.getError();
    //    Serial.print("error: ");
    //    Serial.println(error);
  }
}
