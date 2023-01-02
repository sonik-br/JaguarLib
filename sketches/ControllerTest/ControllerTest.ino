/*******************************************************************************
 * Atari Jaguar controller input library.
 * https://github.com/sonik-br/JaguarLib
 * 
 * The library depends on greiman's DigitalIO library.
 * https://github.com/greiman/DigitalIO
 * 
 * I recommend the usage of SukkoPera's fork of DigitalIO as it supports a few more platforms.
 * https://github.com/SukkoPera/DigitalIO
 * 
 * 
 * This sketch is ready to use on a Leonardo but may work on any
 * arduino with the correct number of pins and proper setup.
*/

#include <JaguarLib.h>

#define ENABLE_SERIAL_DEBUG

//Jaguar pins
#define JAGPIN_J3_J4   8
#define JAGPIN_J2_J5   9
#define JAGPIN_J1_J6   10
#define JAGPIN_J0_J7   11
#define JAGPIN_B0_B2   A0
#define JAGPIN_B1_B3   A1
#define JAGPIN_J11_J15 A2
#define JAGPIN_J10_J14 A3
#define JAGPIN_J9_J13  A4
#define JAGPIN_J8_J12  A5


JagPort<JAGPIN_J3_J4, JAGPIN_J2_J5, JAGPIN_J1_J6, JAGPIN_J0_J7, JAGPIN_B0_B2, JAGPIN_B1_B3, JAGPIN_J11_J15, JAGPIN_J10_J14, JAGPIN_J9_J13, JAGPIN_J8_J12> jaguar;


#ifdef ENABLE_SERIAL_DEBUG
#define dstart(spd) do {Serial.begin (spd); while (!Serial) {delay(10);}} while (0);
#define debug(...) Serial.print (__VA_ARGS__)
#define debugln(...) Serial.println (__VA_ARGS__)
#else
#define dstart(...)
#define debug(...)
#define debugln(...)
#endif

#define DIGITALSTATE(D) \
if(sc.digitalJustPressed(D)) { \
  debugln(F("Digital pressed: " #D)); \
} else if(sc.digitalJustReleased(D)) {\
  debugln(F("Digital released: " #D)); \
}

#define DEVICE(A, B) \
if(A == B) {\
  debug(#B); \
}

void printDeviceType (const JagDeviceType_Enum d){
  DEVICE(d, JAG_DEVICE_NONE)
  DEVICE(d, JAG_DEVICE_NOTSUPPORTED)
  DEVICE(d, JAG_DEVICE_PAD)
}

void printButtons(const JagController& sc) {
  DIGITALSTATE(JAG_PAD_UP)
  DIGITALSTATE(JAG_PAD_DOWN)
  DIGITALSTATE(JAG_PAD_LEFT)
  DIGITALSTATE(JAG_PAD_RIGHT)
  DIGITALSTATE(JAG_C)
  DIGITALSTATE(JAG_B)
  DIGITALSTATE(JAG_A)
  DIGITALSTATE(JAG_PAUSE)
  DIGITALSTATE(JAG_OPTION)
  DIGITALSTATE(JAG_0)
  DIGITALSTATE(JAG_1)
  DIGITALSTATE(JAG_2)
  DIGITALSTATE(JAG_3)
  DIGITALSTATE(JAG_4)
  DIGITALSTATE(JAG_5)
  DIGITALSTATE(JAG_6)
  DIGITALSTATE(JAG_7)
  DIGITALSTATE(JAG_8)
  DIGITALSTATE(JAG_9)
  DIGITALSTATE(JAG_STAR)
  DIGITALSTATE(JAG_HASH)
}

void setup() {
  //Init the library.
  jaguar.begin();
  
  delay(50);

  dstart (115200);
  debugln (F("Powered on!"));
}

void loop() {
  static unsigned long idleTimer = 0;
  static uint8_t lastControllerCount = 0;
  static uint8_t lastMultitapPorts = 0;
  static JagDeviceType_Enum dtype[1] = { JAG_DEVICE_NONE };
  
  //uint8_t hatData;

  const unsigned long start = micros();
  
  //Call update to read the controller(s)
  jaguar.update();
  
  //Time spent to read controller(s) in microseconds
  const unsigned long delta = micros() - start;

  //debugln(delta);

  const uint8_t multitapPorts = jaguar.getMultitapPorts();

  //A multitap was connected or disconnected?
  if (lastMultitapPorts > multitapPorts) {
    debugln(F("Multitap disconnected"));
  } else if (lastMultitapPorts < multitapPorts) {
    debug(F("Multitap connected. Ports: "));
    debugln(jaguar.getMultitapPorts());
  }
  
  const uint8_t joyCount = jaguar.getControllerCount();
  //debugln(joyCount);
  if (lastControllerCount != joyCount) {
    debug(F("Connected devices: "));
    debugln(joyCount);
  }
  
  bool isIdle = true;
  for (uint8_t i = 0; i < joyCount; ++i) {
    const JagController& sc = jaguar.getJagController(i);
    if (sc.stateChanged()) {
      isIdle = false;
      
      //hatData = sc.hat();
      //dtype = sc.deviceType();

      //Controller just connected.
      if (sc.deviceJustChanged()) {
        debug(F("Device changed from "));
        printDeviceType(dtype[i]);
        debug(F(" to "));
        dtype[i] = sc.deviceType();
        printDeviceType(dtype[i]);
        debugln(F(""));
      }

      //bool isPressed = sc.digitalPressed(JAG_A);
      
      printButtons(sc);
      
    }
    
  }

  //Controller has been disconnected?
  if (lastControllerCount > joyCount) {
    for (uint8_t i = joyCount; i < lastControllerCount; ++i) {
      const JagController& sc = jaguar.getJagController(i);
      if (sc.stateChanged() && sc.deviceJustChanged()) {
        debugln(F("Device disconnected"));
        dtype[i] = JAG_DEVICE_NONE;
      }
    }
  }
  
  lastControllerCount = joyCount;
  lastMultitapPorts = multitapPorts;

  if(isIdle) {
    if (millis() - idleTimer >= 3000) {
      idleTimer = millis();
      debug(F("Idle. Read time: "));
      debugln(delta);
    }
  } else {
    idleTimer = millis();
    debug(F("Read time: "));
    debugln(delta);
  }

  delayMicroseconds(100);
}
