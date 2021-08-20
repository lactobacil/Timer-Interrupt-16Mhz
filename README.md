# Timer-Interrupt-16Mhz
A task to trigger an interrupt for every 1.02 seconds or 1020ms with high kept timer resolution. Using 256 as prescaler

# Register
The selected register is TIMSK1 and the set enable bit of OCIE1A for time mask mode

# Testing
Testing was done with Atmega328P on an arduino code, tested with the millis library, oscilloscope test should be done further.

![IMG_4407](https://user-images.githubusercontent.com/72569245/130217267-2cd768b0-476c-42e1-a4c2-aedc7d49f420.jpg)


![image](https://user-images.githubusercontent.com/72569245/130217168-764b4cb9-3390-415b-b0fc-f0fc225cf1dd.png)

