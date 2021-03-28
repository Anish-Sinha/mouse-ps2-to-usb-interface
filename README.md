# Project Summary
This project is my exploration of the PS/2 interface. Through this project I am learning about how the PS/2 protocol worked.

## Project Goal
My goal for this project is to receive data being sent from the PS/2 mouse and use an arduino as a way to decode and translate it into commands that control my cursor on my computer, essentially creating a PS/2 to USB interface. 

## Observations Log
### 24 March 2021
The Clock and Data pins are connected to the Arduino and are being read by AnalogRead, which reads the raw analog voltage. This data is outputted to the Serial Console and graphed in Excel.

The graph below shows that the Clock and Data values oscillate with the same values and possibly have high frequency noise present. Also, the waveforms translate downwards during the duration a mouse button is pressed down and only translate back to its original position after the mouse button is released.

![Clock and Data Waveforms plotted together](./pics-and-graphs/MouseWaveform-240321.png)

The waveforms do not translate however when the scroll wheel is scrolled or when the mouse is moved.
