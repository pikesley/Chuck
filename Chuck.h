#ifndef Chuck_h
#define Chuck_h

#include "Arduino.h"

class Chuck {
  public:
    Chuck(int *pins, int pinCount, int sleep);
    void resetPins();
    String lightLed(int index);
    void lightSeveral(int *list);
    void wiring();
    void debug(bool toggle);
    void forwards();
    void backwards();

    bool _debugging;
    int lights;
    int _sleep;

  private:
    void inputise();
    void setPins(int highIndex, int lowIndex);
    void validateRhs(int *candidates, int left);

    int *_pins;
    int _pinCount;
};

#endif
