
#include <DHT.h>

#define BAUD_RATE 115200
#define CMD_READ 0x0

const uint8_t PINS[1] = { 6 };
DHT *sensors[sizeof(PINS)];

void setup() {
    Serial.begin( BAUD_RATE );
    for( uint8_t i=0; i<sizeof(PINS); i++ ) {
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
            DHT *sensor = sensors[pin-1];
            float t = sensor->readTemperature();
            float h = sensor->readHumidity();
            Serial.write( (byte *) &t, 4 );
            Serial.write( (byte *) &h, 4 );
        }
    }
}
