/* Hash the string "Hello, world!" and send its SHA256 sum to serial output.
   The correct hash is
   315F5BDB76D078C43B8AC0064E4A0164612B1FCE77C869345BFC94C75894EDD3
   */

#include <usha256.h>
#include <string.h>

Sha256Context ctx;

void setup() {
  sha256_init(&ctx);
  Serial.begin(9600);
}

void loop() {
  uint8_t hash[32];
  char *data = "Hello, world!";
  sha256_update(&ctx, (uint8_t *)data, strlen(data));
  sha256_final(&ctx, hash);
  // print hash
  for (uint8_t i = 0; i < 32; i++) {
    if (hash[i] < 0x10) {
      Serial.print('0'); // print leading 0 for this byte
    }
    Serial.print(hash[i], HEX);
  }
  Serial.println();
  Serial.flush();
  // halt
  while(1);
}
