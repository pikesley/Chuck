#ifndef Chuck_h
#define Chuck_h

#include "Arduino.h"

class Chuck {
  public:
    Chuck(int *pins, int pinCount);
    void resetPins();
    String lightLed(int index);
    void lightSeveral(int *list, int width);
    void wiring();
    void debug(bool toggle);

    bool debugging;
    int lights;
    int sleep;

  private:
    void inputise();
    void setPins(int highIndex, int lowIndex);
    void validateRhs(int *candidates, int left);

    int *_pins;
    int _pinCount;
};

#endif
