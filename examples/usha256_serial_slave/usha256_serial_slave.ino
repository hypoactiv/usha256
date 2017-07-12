#include <usha256.h>

Sha256Context ctx;

void setup() {
  Serial.begin(115200);
  sha256_init(&ctx);
  Serial.println("READY");
  Serial.flush();
}

void loop() {
  uint8_t buf[256];
  uint8_t len;
  if (Serial.available() > 0) {
    // read data chunk size
    len = Serial.read();
    if (len < 0) {
      Serial.println("read error");
      Serial.flush();
      sha256_init(&ctx);
    } else if (len == 0) {
      // end of data, finalize hash
      sha256_final(&ctx, buf);
      // print hash
      for (uint8_t i = 0; i < 32; i++) {
        if (buf[i] < 0x10) {
          Serial.print('0'); // print leading 0 for this byte
        }
        Serial.print(buf[i], HEX);
      }
      Serial.flush();
      // re-initialize context for next message
      sha256_init(&ctx);
    } else {
      // read the chunk of data
      if (Serial.readBytes(buf, len) != len) {
        // error -- did not read the entire chunk of data
        Serial.write(0);
        Serial.flush();
        sha256_init(&ctx);
      } else {
        // read a chunk of data successfully
        sha256_update(&ctx, buf, len);
        Serial.write(len);
        Serial.flush();
      }
    }
  }
}
