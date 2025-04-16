#ifndef MyButton_H
#define MyButton_H

class MyButton
{
    #define MYBUTTON_NO_CLICK 0 
    #define MYBUTTON_SHORT_CLICK 2 
    #define MYBUTTON_LONG_CLICK 3 
    #define MYBUTTON_DOUBLE_CLICK 4 
    const bool beginningState=false;
    const int timeBegin=0;
    private :
        int buttonGPIO;
        int buttonDebounceDelay;
        int buttonLongPressDuration;
        int buttonDoubleClickMaxDelay;
        bool isPressed;
        bool lastRawState;
        unsigned long lastDebounceTime;
        unsigned long pressStart;
        unsigned long lastReleaseTime;
        bool waitingSecondClick;
        bool pendingSingleClick;
    public:
       /// @brief constructor
       /// @param gpioNumber 
       /// @param typebouton 
       MyButton(int gpioNumber,int typebouton);
       /// @brief initialize the delay of the debounce 
       /// @param debounceDelay 
       void setButtonDebounceDelay(int debounceDelay);
       /// @brief initialize the delay of the long press 
       /// @param longPressDuration 
       void setButtonLongPressDuration(int longPressDuration);
       /// @brief initialize the delay of double click 
       /// @param doubleClickMxDelay 
       void setButtonDoubleClickMaxDelay(int doubleClickMxDelay);
       /// @brief method to check the type of button and return it 
       /// @return 
       int checkMyButton();
    }; 
#endif
