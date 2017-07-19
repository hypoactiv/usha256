# About
usha256 is an implementation of the SHA256 message digest for the Atmel AVR series 8-bit microcontrollers found in Arduino boards. It aims to have small size, which is currently 2,510 bytes to hash an empty string.

This implementation is a heavily modified version of Brad Conte's public domain implementation, found at https://github.com/B-Con/crypto-algorithms.

Pull requests that reduce the compiled size are always welcome.

# Caveat Lector
This library is being developed for another project currently in progress. As such, usha256's API is still in flux.

usha256 currently has an input size limitation of 512MB.

# Usage
Please see the `examples` folder for usage examples.
