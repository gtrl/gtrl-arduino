
#include <DHT.h>

#define BAUD_RATE 115200
#define CMD_READ 0x0

const int PINS[2] = { 6, 7 };
DHT *sensors[sizeof(PINS)];

void setup() {
    Serial.begin( BAUD_RATE );
    for( int i=0; i<2; i++ ) {
        DHT *sensor = new DHT( PINS[i], DHT22 );
        sensor->begin();
        sensors[i] = sensor;
    }
}

void loop() {
    int available = Serial.available();
    if( available == 2 ) {
        uint8_t cmd = Serial.read();
        uint8_t pin = Serial.read();
        if( cmd == CMD_READ ) {
            //TODO select sensor
            DHT *sensor = sensors[pin-1];
            float t = sensor->readTemperature();
            float h = sensor->readHumidity();
            Serial.write( (byte *) &t, 4 );
            Serial.write( (byte *) &h, 4 );
        }
    }
}
