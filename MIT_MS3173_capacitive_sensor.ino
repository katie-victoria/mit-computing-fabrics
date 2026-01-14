#include <CapacitiveSensor.h>
CapacitiveSensor sensor=CapacitiveSensor(4,8);

int sum=0;
int n=0;
int gamma=0.1;
int At=0;
int At_minus_one=0;
int number_of_taps=0;
int double_tap=0;
int length_of_tap=0;
int delay_time=100;
bool last_touch=false;
     
void setup() {
     sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
     Serial.begin(9600);
}

void loop() {
    long at=sensor.capacitiveSensor(30); // measurement
    At=gamma*At_minus_one+(1-gamma)*at; // exponential moving average to decrease noise
    int average=At;
    Serial.println(average);
    delay(delay_time); // set to 100 ms
    int touchthreshold=350; // tune based on measurement changes from touch vs. hovering
    
    if (average>touchthreshold) { // if touch is happening
      length_of_tap+=1; // increment number of time units touch has been happening
    }
    if (last_touch && average<touchthreshold){ // if touched and now released (tapped)
      if (length_of_tap*delay_time > 500) { // if touch was > .5s, then it was a long touch
        Serial.println("LONG TOUCH");
      } else { // if touch was <= .5s, then it was a short touch
        Serial.println("SHORT TOUCH");
      }
      number_of_taps+=1; // taps counted regardless if short or long
      double_tap+=1;
      if (double_tap==2) {
        Serial.println("DOUBLE TAP");
        double_tap=0;
      }
      Serial.println("number of taps: ");
      Serial.println(number_of_taps);
    }

    
    if (average>touchthreshold){ // if touch
      last_touch = true;
      length_of_tap+=1;
    }
    else {last_touch = false;
           length_of_tap=0;
    }
}
