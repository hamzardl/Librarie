#include <Arduino.h>
#include "MyButton.h"
/// @brief constructor that allow to initialize the class
/// @param gpioNumber 
/// @param typebouton 
MyButton::MyButton(int gpioNumber,int typebouton){
  buttonGPIO=gpioNumber;
 pinMode(buttonGPIO, INPUT_PULLDOWN);
 //si il n'Est pas clique donc le press est false et c'est le début 
 if(typebouton==MYBUTTON_NO_CLICK){
    isPressed = beginningState; 
    lastRawState = beginningState; 
    waitingSecondClick = beginningState; 
    pendingSingleClick = beginningState; 
    lastDebounceTime = MYBUTTON_NO_CLICK; 
    pressStart = MYBUTTON_NO_CLICK; 
    lastReleaseTime = MYBUTTON_NO_CLICK; 
 }

};
/// @brief initialize a delay of Debounce
/// @param debounceDelay 
void MyButton::setButtonDebounceDelay(int debounceDelay){
    if(debounceDelay>0){
        buttonDebounceDelay = debounceDelay;
    }
    
};
/// @brief initialize a duration of long press
/// @param longPressDuration 
void MyButton::setButtonLongPressDuration(int longPressDuration){
    if(longPressDuration>0){
        buttonLongPressDuration = longPressDuration;

    }

};
/// @brief initialize a delay of a double click
/// @param doubleClickMxDelay 
void MyButton::setButtonDoubleClickMaxDelay(int doubleClickMxDelay){
    if(doubleClickMxDelay>0){
        buttonDoubleClickMaxDelay = doubleClickMxDelay;
    }

};
/// @brief a method to check the type of button to identify if it's a short or long or double click
/// @return the type of the button 
int MyButton::checkMyButton(){

    bool rawState = digitalRead(buttonGPIO); 

    unsigned long now = millis(); 
    
    if (rawState != lastRawState) 
    
    { 
    
    lastDebounceTime = now; 
    
    lastRawState = rawState; 
    } 
    
    if ((now - lastDebounceTime) > buttonDebounceDelay) 
    
    { 
    
     if (rawState == HIGH && !isPressed) 
    
    { 
    
    isPressed = true; 
    
    pressStart = now; 
    
    } 
    
    if (rawState == LOW && isPressed) 
    
    { 
    
    isPressed = false; 
    
    unsigned long pressDuration = now - pressStart; 
    
    if (pressDuration >= buttonLongPressDuration) 
    
    { 
    
    waitingSecondClick = false; 
    
    pendingSingleClick = false; 
    
    return MYBUTTON_LONG_CLICK; // Long press 
    
    } 
    
    if (waitingSecondClick) 
    
    { 
    
     waitingSecondClick = false; 
    
    pendingSingleClick = false; 
    
    return MYBUTTON_DOUBLE_CLICK; // Double click 
    
    } 
    
    else 
    
    { 
    
    waitingSecondClick = true; 
    
    pendingSingleClick = true; 
    
    lastReleaseTime = now; 
    
    } 
    
    } 
    
    } 
    
    // If you wait for a second click but the timeout has passed 
    
    if (pendingSingleClick && (now - lastReleaseTime > buttonDoubleClickMaxDelay)) 
    
     { 
    
    pendingSingleClick = false; 
    
    waitingSecondClick = false; 
    
    return MYBUTTON_SHORT_CLICK; // Single click confirmed 
    
    } 
    
    return MYBUTTON_NO_CLICK; 
};