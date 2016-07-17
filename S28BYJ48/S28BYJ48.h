#ifndef S28BYJ48_h
#define S28BYJ48_h

class S28BYJ48 {
public:
    S28BYJ48(int In1, int In2, int In3, int In4);    // Constructor that will set the inputs
    void setStepDuration(int duration);    // Function used to set the step duration in ms
    void step(int noOfSteps);    // Step a certain number of steps. + for one way and - for the other
    void stop();

    int duration;    // Step duration in micros(minimum : 800)
    int inputPins[4];    // The input pin numbers
};

#endif
