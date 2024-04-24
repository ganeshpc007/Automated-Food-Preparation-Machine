#include <Wire.h>
#include <Keypad.h>
#include <Servo.h>

const byte ROWS = 4; // four rows
const byte COLS = 4; // four columns

// Define the symbols ON the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};
byte rowPins[ROWS] = {27, 28, 29, 30}; // connect to the row pinouts of the keypad
byte colPins[COLS] = {31, 32, 39, 40}; // connect to the column pinouts of the keypad

// Initialize an instance of class NewKeypad
Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

// Defining indication led's
#define maggi_led 41
#define pasta_led 42
#define soup_led 43
#define tea_led 44
#define preparing_led 45
#define complete_led 46

#define on_off 33    // red wire
#define fun 34       // stove fun pin
#define temp 35      // blue
#define venti_fan 36 // ventilation fan
#define valve_1 37   // funnel 1
#define valve_2 38   // funnel 2

Servo small_fun_servo;
Servo big_fun_servo;
Servo lid_servo;
Servo milk_servo;
Servo tea_servo;
Servo sugar_servo;
Servo maggi_servo;
Servo vegi_servo;
Servo maggibox_servo;
Servo pasta_servo;
Servo pastabox_servo;
Servo soup_servo;

// Servo positions
int small_fun_pos = 0;
int big_fun_pos = 0;
int lid_pos = 90;
int milk_pos = 0;
int tea_pos = 0;
int sugar_pos = 0;
int maggi_pos = 0;
int vegi_pos = 0;
int maggibox_pos = 0;
int pasta_pos = 0;
int pastabox_pos = 0;
int soup_pos = 0;

// Defining motor driver pins
const int in1 = 23; // vibration motor
const int in2 = 24; // vibration motor
const int in3 = 25; // stirer
const int in4 = 26; // stirer

// Relay connections
const int water_pump = 22;

void setup()
{
    // Indication led's
    pinMode(maggi_led, OUTPUT);
    pinMode(pasta_led, OUTPUT);
    pinMode(soup_led, OUTPUT);
    pinMode(tea_led, OUTPUT);
    pinMode(preparing_led, OUTPUT);
    pinMode(complete_led, OUTPUT);

    pinMode(on_off, OUTPUT);
    pinMode(fun, OUTPUT);
    pinMode(temp, OUTPUT);
    pinMode(venti_fan, OUTPUT);
    pinMode(valve_1, OUTPUT);
    pinMode(valve_2, OUTPUT);

    //  Servos
    small_fun_servo.attach(2);
    lid_servo.attach(3);
    big_fun_servo.attach(4);
    milk_servo.attach(5);
    tea_servo.attach(6);
    sugar_servo.attach(7);
    maggi_servo.attach(8);
    vegi_servo.attach(9);
    maggibox_servo.attach(10);
    pasta_servo.attach(11);
    pastabox_servo.attach(12);
    soup_servo.attach(13);

    // Relay
    pinMode(water_pump, OUTPUT);

    // Motor driver
    pinMode(in1, OUTPUT); // vibration motor
    pinMode(in2, OUTPUT); // vibration motor
    pinMode(in3, OUTPUT); // Stirer
    pinMode(in4, OUTPUT); // stirer

    // Intilizition servos to intial position
    milk_servo.write(0);
    small_fun_servo.write(0);
    big_fun_servo.write(0);
    lid_servo.write(90);
    tea_servo.write(0);
    sugar_servo.write(0);
    maggi_servo.write(0);
    vegi_servo.write(0);
    maggibox_servo.write(0);
    pasta_servo.write(0);
    pastabox_servo.write(0);
    soup_servo.write(0);
}

void loop()
{
    char customKey = customKeypad.getKey();

    if (customKey)
    {
        if (customKey == '1')
        {
            maggi();
        }
        else if (customKey == '2')
        {
            pasta();
        }
        else if (customKey == '3')
        {
            soup();
        }
        else if (customKey == '4')
        {
            tea();
        }
        else if (customKey == 'A')
        {
            maggi_process();
        }
    }
}

// User defined functions for high speed maggi process
void maggi_process()
{
    //  maggi indication led ON
    digitalWrite(maggi_led, HIGH);
    digitalWrite(preparing_led, HIGH);
    digitalWrite(pasta_led, LOW);
    digitalWrite(soup_led, LOW);
    digitalWrite(tea_led, LOW);
    digitalWrite(complete_led, LOW);

    // Ventilation fan and Light ON
    digitalWrite(venti_fan, HIGH);

    // Lid Opening
    lid_open();
    delay(1000);
    // Opening small ingridents funnel
    f1_open();
    delay(1000);

    // Dispensing maggi masala with servo
    for (maggi_pos = 0; maggi_pos <= 180; maggi_pos += 1)
    {
        maggi_servo.write(maggi_pos);
        delay(5);
    }

    // Turning ON vibration motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump ON
    digitalWrite(valve_1, HIGH); // Opening value 1
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(7000);

    // Closing maggi masala Lid
    maggi_servo.write(0);
    delay(2000);

    // Turning OFF vibration motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump OFF
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_1, LOW); // Opening value 1
    delay(5000);

    // Closing samll ingridents funnel
    f1_close();
    delay(1000);

    // Stove ON
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    // Time for water boiling
    delay(6000); // 1.30 min

    // Opening big ingridents funnel
    f2_open();
    delay(5000);

    // Despensing vegitables
    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    // Despensing maggi
    for (maggibox_pos = 0; maggibox_pos <= 170; maggibox_pos += 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(5);
    }
    delay(500);
    for (maggibox_pos = 170; maggibox_pos >= 0; maggibox_pos -= 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(10);
    }
    for (maggibox_pos = 0; maggibox_pos <= 170; maggibox_pos += 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(5);
    }
    delay(500);
    for (maggibox_pos = 170; maggibox_pos >= 0; maggibox_pos -= 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(10);
    }
    delay(2000);

    // Pump ON
    digitalWrite(valve_2, HIGH); // Opening value 2
    delay(800);
    digitalWrite(water_pump, HIGH);
    delay(4000);
    digitalWrite(water_pump, LOW);
    delay(800);
    digitalWrite(valve_2, LOW); // closing value 2
    delay(5000);

    // Closing big ingridents funnel
    f2_close();
    delay(5000);

    // Lid closing
    lid_close();
    delay(1000);

    // Stirer ON & OFF
    stirer_on();
    delay(1000);

    // Redusing temp 1700 to 800
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);

    // Stove OFF
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);
    delay(1000);

    // Ventilation fan OFF
    digitalWrite(venti_fan, LOW);
    delay(1000);

    // Lid Opening
    lid_open();
    delay(1000);

    // Maggi status: indication led ON
    digitalWrite(preparing_led, LOW);
    digitalWrite(complete_led, HIGH);
    // end
}

// Functions for maggi
void maggi()
{
    //  Maggi indication led ON
    digitalWrite(maggi_led, HIGH);
    digitalWrite(preparing_led, HIGH);
    digitalWrite(pasta_led, LOW);
    digitalWrite(soup_led, LOW);
    digitalWrite(tea_led, LOW);
    digitalWrite(complete_led, LOW);

    // Ventilation fan and Light ON
    digitalWrite(venti_fan, HIGH);

    // Lid Opening
    lid_open();
    delay(1000);

    // Opening small ingridents funnel
    f1_open();
    delay(1000);

    // Dispensing maggi masala with servo
    for (maggi_pos = 0; maggi_pos <= 180; maggi_pos += 1)
    {
        maggi_servo.write(maggi_pos);
        delay(5);
    }

    // Turning ON vibration motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump ON
    digitalWrite(valve_1, HIGH); // Opening value 1
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(14000);

    // Closing maggi masala Lid
    maggi_servo.write(0);
    delay(2000);

    // Turning OFF vibration motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump OFF
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_1, LOW); // Opening value 1
    delay(5000);

    // Closing samll ingridents funnel
    f1_close();
    delay(1000);

    // Stove ON
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    // Time for water boiling
    delay(90000); // 1.30 min

    // Opening big ingridents funnel
    f2_open();
    delay(3000);

    // Despensing vegitables
    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    // Despensing maggi
    for (maggibox_pos = 0; maggibox_pos <= 170; maggibox_pos += 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(5);
    }
    delay(500);
    for (maggibox_pos = 170; maggibox_pos >= 0; maggibox_pos -= 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(10);
    }
    for (maggibox_pos = 0; maggibox_pos <= 170; maggibox_pos += 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(5);
    }
    delay(500);
    for (maggibox_pos = 170; maggibox_pos >= 0; maggibox_pos -= 1)
    {
        maggibox_servo.write(maggibox_pos);
        delay(10);
    }
    delay(2000);

    // Pump ON
    digitalWrite(valve_2, HIGH); // Opening value 2
    delay(800);
    digitalWrite(water_pump, HIGH);
    delay(4000);
    digitalWrite(water_pump, LOW);
    delay(800);
    digitalWrite(valve_2, LOW); // closing value 2
    delay(5000);

    // Closing big ingridents funnel
    f2_close();
    delay(5000);

    // Lid closing
    lid_close();
    delay(1000);

    // Stirer ON & OFF
    stirer_on();
    delay(14000);
    stirer_on();
    delay(14000);

    // Stirer ON & OFF
    stirer_on();
    delay(10000);

    // Redusing temp 1700 to 800
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);

    stirer_on();
    delay(10000);

    //  Stove OFF
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);
    delay(10000);

    // Stirer ON & OFF
    stirer_on();
    delay(10000);

    // Ventilation fan OFF
    digitalWrite(venti_fan, LOW);
    delay(1000);

    // Lid Opening
    lid_open();
    delay(1000);

    // Maggi status: indication led ON
    digitalWrite(preparing_led, LOW);
    digitalWrite(complete_led, HIGH);
    // end
}

// Functions for pasta
void pasta()
{
    //  Pasta indication led ON
    digitalWrite(maggi_led, LOW);
    digitalWrite(preparing_led, HIGH);
    digitalWrite(pasta_led, HIGH);
    digitalWrite(soup_led, LOW);
    digitalWrite(tea_led, LOW);
    digitalWrite(complete_led, LOW);

    // Ventilation fan and Light ON
    digitalWrite(venti_fan, HIGH);

    // Lid Opening
    lid_open();
    delay(1000);

    // Opening small ingridents funnel
    f1_open();
    delay(1000);

    // Dispensing pasta masala with servo
    for (pasta_pos = 0; pasta_pos <= 180; pasta_pos += 1)
    {
        pasta_servo.write(pasta_pos);
        delay(5);
    }

    // Turning ON vibration motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump ON
    digitalWrite(valve_1, HIGH); // Opening value 1
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(16000);

    // Closing pasta masala Lid
    pasta_servo.write(0);
    delay(4000);

    // Turning OFF vibration motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump OFF
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_1, LOW); // closing value 1
    delay(5000);

    // Closing samll ingridents funnel
    f1_close();
    delay(1000);

    // Stove ON
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    // Time for water boiling
    delay(90000); // 1.30 min

    // Opening big ingridents funnel
    f2_open();
    delay(2000);

    // Despensing vegitables
    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    // Despensing pasta
    for (pastabox_pos = 0; pastabox_pos <= 170; pastabox_pos += 1)
    {
        pastabox_servo.write(pastabox_pos);
        delay(5);
    }
    delay(500);
    for (pastabox_pos = 170; pastabox_pos >= 0; pastabox_pos -= 1)
    {
        pastabox_servo.write(pastabox_pos);
        delay(10);
    }
    delay(200);
    for (pastabox_pos = 0; pastabox_pos <= 170; pastabox_pos += 1)
    {
        pastabox_servo.write(pastabox_pos);
        delay(5);
    }
    delay(500);
    for (pastabox_pos = 170; pastabox_pos >= 0; pastabox_pos -= 1)
    {
        pastabox_servo.write(pastabox_pos);
        delay(10);
    }
    delay(1000);

    // Pump ON
    digitalWrite(valve_2, HIGH); // Opening value 2
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(4000);
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_2, LOW); // closing value 2
    delay(5000);

    // Closing big ingridents funnel
    f2_close();
    delay(2000);

    // Lid closing
    lid_close();
    delay(1000);

    // Stirer ON & OFF
    stirer_on();
    delay(14000);
    stirer_on();
    delay(14000);

    // Stirer ON & OFF
    stirer_on();
    delay(10000);
    stirer_on();
    delay(10000);

    // Redusing temp
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);

    stirer_on();
    delay(10000);

    // Stove OFF
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    delay(10000);

    // Stirer ON & OFF
    stirer_on();
    delay(10000);

    // Ventilation fan OFF
    digitalWrite(venti_fan, LOW);
    delay(1000);

    // Pasta indication led ON
    digitalWrite(maggi_led, LOW);
    digitalWrite(preparing_led, LOW);
    digitalWrite(pasta_led, HIGH);
    digitalWrite(soup_led, LOW);
    digitalWrite(tea_led, LOW);
    digitalWrite(complete_led, HIGH);
    // end
}

// Functions for soup
void soup()
{
    // Soup indication led ON
    digitalWrite(maggi_led, LOW);
    digitalWrite(preparing_led, HIGH);
    digitalWrite(pasta_led, LOW);
    digitalWrite(soup_led, HIGH);
    digitalWrite(tea_led, LOW);
    digitalWrite(complete_led, LOW);

    // Ventilation fan and Light ON
    digitalWrite(venti_fan, HIGH);

    // Lid Opening
    lid_open();
    delay(1000);

    // Opening small ingridents funnel
    f1_open();
    delay(1000);

    // Dispensing soup masala with servo
    for (soup_pos = 0; soup_pos <= 180; soup_pos += 1)
    {
        soup_servo.write(soup_pos);
        delay(5);
    }

    // Turning ON vibration motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump ON
    digitalWrite(valve_1, HIGH); // Opening value 1
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(14000);

    // Closing soup masala Lid
    soup_servo.write(0);
    delay(4000);

    // Turning OFF vibration motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump OFF
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_1, LOW); // closing value 1
    delay(5000);

    // Closing samll ingridents funnel
    f1_close();
    delay(1000);

    // Stove ON
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    // Lid closing
    lid_close();
    delay(1000);

    // Stirer ON & OFF for 2 min
    stirer_on();
    delay(10000);
    stirer_on();
    delay(10000);
    stirer_on();
    delay(1000);

    // Lid Opening
    lid_open();
    delay(1500);

    // Opening big ingridents funnel
    f2_open();
    delay(2000);

    // Despensing vegitables
    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }

    for (vegi_pos = 0; vegi_pos <= 180; vegi_pos += 1)
    {
        vegi_servo.write(vegi_pos);
        delay(5);
    }
    delay(1000);
    for (vegi_pos = 180; vegi_pos >= 0; vegi_pos -= 1)
    {
        vegi_servo.write(vegi_pos);
        delay(8);
    }
    delay(1000);

    // Pump ON
    digitalWrite(valve_2, HIGH); // Opening value 2
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(4000);
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_2, LOW); // closing value 2
    delay(5000);

    // Closing big ingridents funnel
    f2_close();
    delay(2000);

    // Lid closing
    lid_close();
    delay(1000);

    // Stirer ON & OFF for 2 min
    stirer_on();
    delay(8000);
    stirer_on();
    delay(8000);
    stirer_on();
    delay(5000);

    // Redusing temp 1700 to 800
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);

    // Stirer ON and OFF
    stirer_on();
    delay(4000);
    stirer_on();
    delay(4000);

    // Stove OFF
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);
    delay(1000);

    // Ventilation fan OFF
    digitalWrite(venti_fan, LOW);
    delay(1000);

    // Soup indication led ON
    digitalWrite(maggi_led, LOW);
    digitalWrite(preparing_led, LOW);
    digitalWrite(pasta_led, LOW);
    digitalWrite(soup_led, HIGH);
    digitalWrite(tea_led, LOW);
    digitalWrite(complete_led, HIGH);
    // end
}

// Tea instruction function
void tea()
{
    // Tea indication led ON
    digitalWrite(maggi_led, LOW);
    digitalWrite(preparing_led, HIGH);
    digitalWrite(pasta_led, LOW);
    digitalWrite(soup_led, LOW);
    digitalWrite(tea_led, HIGH);
    digitalWrite(complete_led, LOW);

    // Ventilation fan and Ligh ON
    digitalWrite(venti_fan, HIGH);

    // Lid Opening
    lid_open();
    delay(1000);

    // Opening small ingredents funnel
    f1_open();
    delay(1500);

    // Droping the milk powder
    for (milk_pos = 0; milk_pos <= 180; milk_pos += 1)
    {
        milk_servo.write(milk_pos);
        delay(8);
    }

    // Turning ON vibration motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump ON
    digitalWrite(valve_1, HIGH);
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(15000);

    // Closing the milk powder Lid
    milk_servo.write(0);
    delay(4000);

    // Turning OFF vibration motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(500);

    // Pump OFF
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_1, LOW);
    delay(5000);

    // Closing small ingredents funnel
    f1_close();
    delay(2000);

    // Stove ON
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    // Lid closing
    lid_close();
    delay(1500);

    // Stirer ON & OFF
    stirer_on();
    delay(4000);
    stirer_on();
    delay(4000);

    // Lid Opening
    lid_open();
    delay(1000);

    // Stove OFF
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);

    // Opening small ingredents funnel
    f1_open();
    delay(1000);

    // Opening the tea powder and sugar container Lid
    for (tea_pos = 0; tea_pos <= 180; tea_pos += 1)
    {
        tea_servo.write(tea_pos);
        sugar_servo.write(tea_pos);
        delay(8);
    }

    // Turning ON vibration motor
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    delay(5000);

    // Pump ON
    digitalWrite(valve_1, HIGH);
    delay(500);
    digitalWrite(water_pump, HIGH);
    delay(5000);
    tea_servo.write(0);
    delay(4000);
    sugar_servo.write(0);

    // Pump OFF
    digitalWrite(water_pump, LOW);
    delay(500);
    digitalWrite(valve_1, LOW);
    delay(1000);

    // Turning OFF vibration motor
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    delay(5000);

    // Closing small ingredents funnel
    f1_close();
    delay(1000);

    //  Lid closing
    lid_close();
    delay(1000);

    // Stove ON
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);
    delay(1000);

    // Redusing temp 1700 to 1000
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);

    // Stirer ON & OFF
    stirer_on();
    delay(2000);
    stirer_on();
    delay(2000);

    // Redusing temp 1000 to 400
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);
    digitalWrite(temp, HIGH);
    delay(500);
    digitalWrite(temp, LOW);
    delay(500);

    // Stirer ON & OFF
    stirer_on();
    delay(2000);
    stirer_on();
    delay(2000);

    // Lid Opening
    lid_open();

    delay(15000); // Slow boiling 15sec

    // Lid closing
    lid_close();
    delay(1000);

    // Stove OFF
    digitalWrite(on_off, HIGH);
    delay(500);
    digitalWrite(on_off, LOW);
    delay(1000);

    // Stirer ON & OFF
    stirer_on();
    delay(1000);

    // Ventilation fan and Light OFF
    digitalWrite(venti_fan, LOW);
    delay(1000);

    // Tea indication led ON
    digitalWrite(maggi_led, LOW);
    digitalWrite(preparing_led, LOW);
    digitalWrite(pasta_led, LOW);
    digitalWrite(soup_led, LOW);
    digitalWrite(tea_led, HIGH);
    digitalWrite(complete_led, HIGH);
    // end
}

//  Reusable functions
void lid_open() // Lid Opening
{
    for (lid_pos = 90; lid_pos >= 0; lid_pos -= 1)
    {
        lid_servo.write(lid_pos);
        delay(10);
    }
}

// Lid closing
void lid_close()
{
    for (lid_pos = 0; lid_pos <= 90; lid_pos += 1)
    {
        lid_servo.write(lid_pos);
        delay(15);
    }
}

void stirer_on()
{
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(4000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(2000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(4000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(2000);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(4000);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

// Opening small ingridents funnel
void f1_open()
{
    for (small_fun_pos = 0; small_fun_pos <= 100; small_fun_pos += 1)
    {
        small_fun_servo.write(small_fun_pos);
        delay(15);
    }
}

void f1_close()
{
    for (small_fun_pos = 100; small_fun_pos >= 0; small_fun_pos -= 1)
    {
        small_fun_servo.write(small_fun_pos);
        delay(15);
    }
}

// Opening big ingridents funnel
void f2_open()
{
    for (big_fun_pos = 0; big_fun_pos <= 100; big_fun_pos += 1)
    {
        big_fun_servo.write(big_fun_pos);
        delay(10);
    }
}

// Closing big ingridents funnel
void f2_close()
{
    for (big_fun_pos = 100; big_fun_pos >= 0; big_fun_pos -= 1)
    {
        big_fun_servo.write(big_fun_pos);
        delay(10);
    }
}
