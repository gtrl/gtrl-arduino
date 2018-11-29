
#include <DHT.h>

#define BAUD_RATE 115200

DHT dht( 6, DHT22 );

void setup() {
    Serial.begin( BAUD_RATE );
    dht.begin();
}

void loop() {
    int available = Serial.available();
    if( available == 2 ) {
        uint8_t cmd = Serial.read();
        uint8_t pin = Serial.read();
        if( cmd == 0x0 ) {
            float t = dht.readTemperature();
            float h = dht.readHumidity();
            Serial.write( 0x0 );
            Serial.write( pin );
            Serial.write( (byte *) &t, 4 );
            Serial.write( (byte *) &h, 4 );
        }
    }
}
