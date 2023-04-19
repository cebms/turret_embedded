#include <Arduino.h>
#include <Servo.h>

#include "defines.h"
#include "movements.h"

Servo tilt_servo;
Servo shoot_servo;

int tilt_angle = INITIAL_TILT_ANGLE;
bool impulse_on = false;

byte rotation_bits_mask = 0b00000011;
byte tilt_bits_mask = 0b00001100;
byte impulse_bit_mask = 0b00010000;
byte shoot_bit_mask = 0b00100000;

void setup() {
    pinMode(TILT_SERVO_PIN, OUTPUT);
    pinMode(SHOOT_SERVO_PIN, OUTPUT);
    pinMode(ROTATION_D1, OUTPUT);
    pinMode(ROTATION_D2, OUTPUT);
    pinMode(IMPULSE_PWM, OUTPUT);
    pinMode(IMPULSE_D1, OUTPUT);
    pinMode(IMPULSE_D2, OUTPUT);

    tilt_servo.attach(TILT_SERVO_PIN);
    shoot_servo.attach(SHOOT_SERVO_PIN);

    Serial.begin(9600);
    Serial.println("Turret ready!");

    tilt_servo.write(INITIAL_TILT_ANGLE);
    shoot_servo.write(0);

    digitalWrite(ROTATION_D1, LOW);
    digitalWrite(ROTATION_D2, LOW);
    digitalWrite(IMPULSE_D1, LOW);
    digitalWrite(IMPULSE_D2, LOW);

    analogWrite(IMPULSE_PWM, 90);
    
}

void loop() {
    // Run through SERIAL

    if(Serial.available()){
        char movement = Serial.read();

        Serial.println((byte)movement);

        byte rotation_input = movement & rotation_bits_mask;
        byte tilt_input = movement & tilt_bits_mask;
        byte impulse_input = movement & impulse_bit_mask;
        byte shoot_input = movement & shoot_bit_mask;

        move_y_axis(tilt_servo, tilt_angle, tilt_input);

        move_x_axis(rotation_input);

        set_impulse(impulse_input);

        if(shoot_input){
            shoot(shoot_servo);
        }
        
        
    }
}