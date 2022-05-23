// This #include statement was automatically added by the Particle IDE.
#include <BH1750.h>

BH1750 sensor(0x23, Wire);

double brightnessdata = 0; //creates a variable that can be made into a particle variable
int changeFlag = 0;

int Ledlight = D7; //sets up the argon's LED to blink

void setup() {
    sensor.begin();
    sensor.set_sensor_mode(BH1750::forced_mode_high_res2); //configures the sensor
 
    Serial.begin();
  
    Particle.variable("Brightness", brightnessdata);
}

void loop() {
    sensor.make_forced_measurement(); //takes a brightness measurement

    brightnessdata = sensor.get_light_level();
    String lightdata = String(brightnessdata);
    
    if(brightnessdata > 50 && changeFlag != 1)
    {
        changeFlag = 1;
        Particle.publish("Sunlight is here!", "It's nice and sunny.", 60, PRIVATE);
        Particle.publish("lightlevel", lightdata, PRIVATE); //publishes an event with the brightness data
    }
    
    if(brightnessdata < 50 && changeFlag != 2)
    {
        changeFlag = 2;
        Particle.publish("Oh no darkness!", "Scary times.", 60, PRIVATE);
        Particle.publish("lightlevel", lightdata, PRIVATE); //publishes an event with the brightness data
    }
  
  delay(3000); //waits 5 minutes between measurements
}