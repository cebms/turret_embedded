#include <Arduino.h>

#include "defines.h"
#include "movements.h"

void move_y_axis(Servo &tilt_servo, int &tilt_angle, char movement){
    switch (movement >> 2){
        case 0b10:
            Serial.println("Move down");
            if(tilt_angle + 5 > 60)
                Serial.println("Maximum down");
            else {
                tilt_angle += 5;
                tilt_servo.write(tilt_angle);
            }
            break;
        case 0b01:
            Serial.println("Move up");
            if(tilt_angle - 5 < 0)
                Serial.println("Maximum up");
            else {
                tilt_angle -= 5;
                tilt_servo.write(tilt_angle);
            }
            break;
        default:
            Serial.println("Unrecognized command");
    }
}

void move_x_axis(char movement){

    switch(movement){
        case 0b10:
            Serial.println("Rotate clockwise");
            digitalWrite(ROTATION_D1, HIGH);
            digitalWrite(ROTATION_D2, LOW);
            delay(10);
            digitalWrite(ROTATION_D1, LOW);
            digitalWrite(ROTATION_D2, LOW);
            break;
        case 0b01:
            Serial.println("Rotate counter-clockwise");
            digitalWrite(ROTATION_D1, LOW);
            digitalWrite(ROTATION_D2, HIGH);
            delay(10);
            digitalWrite(ROTATION_D1, LOW);
            digitalWrite(ROTATION_D2, LOW);
            break;
    }
}

void shoot(Servo &shoot_servo){
    Serial.println("Shoot!");
    shoot_servo.write(100);
    delay(200);
    shoot_servo.write(0);
}

void set_impulse(bool impulse_state){
    if(impulse_state){
        Serial.println("Impulse on");
        digitalWrite(IMPULSE_D1, LOW);
        digitalWrite(IMPULSE_D2, HIGH);
    } else {
        Serial.println("Impulse off");
        digitalWrite(IMPULSE_D1, LOW);
        digitalWrite(IMPULSE_D2, LOW);
    }
}