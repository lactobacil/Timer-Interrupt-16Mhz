# Timer-Interrupt-16Mhz
A task to trigger an interrupt for every 1.02 seconds or 1020ms with high kept timer resolution

# Register
The selected register is TIMSK1 and the set enable bit of OCIE1A for time mask mode

# Testing
Testing was done with Atmega328P on an arduino code, tested with the millis library, oscilloscope test should be done further.

