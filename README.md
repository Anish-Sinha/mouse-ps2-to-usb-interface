# Project Summary 
This project is my exploration of the PS/2 interface. Through this project I am learning about how the PS/2 protocol worked by reverse engineering it.

## Project Goal
My goal for this project is to receive data being sent from the PS/2 mouse and use an arduino as a way to decode and translate it into commands that control my cursor on my computer, essentially creating a PS/2 to USB interface. I also hope to build an intuition as to how communication protocols worked from a practical standpoint and develop personal methodologies for further reverse engineering.

## Observations Log
### 24 March 2021
The Clock and Data pins are connected to the Arduino and are being read by AnalogRead, which reads the raw analog voltage. This data is outputted to the Serial Console and graphed in Excel.
<!---![Clock and Data Waveforms plotted together](./pics-and-graphs/MouseWaveform-240321.png)--->
<div>
    <img src="/pics-and-graphs/MouseWaveform-240321.png">
    <p align="center">Figure 1. Mouse Clicks identified on plotted Analog Clock and Data Waveforms</p>
</div>
The graph above shows that the Clock and Data values oscillate with the same values and possibly have high frequency noise present. Also, the waveforms translate downwards during the duration a mouse button is pressed down and only translate back to its original position after the mouse button is released.

The waveforms do not translate however when the scroll wheel is scrolled or when the mouse is moved.

### 31 March 2021 
Using the analog values from the Data pins, I have been able to implement a rudimentary click detection. When the mouse is clicked, I am outputting to the Arduino Serial Console as well as lighting an LED. This was done by using the waveform information shown in the graph above. Through this approach, I am able to detect when a button on the mouse is clicked and for the full duration the button is pressed down.

Through trial and error, I found that the analog values from the Data pin only drop below the *magic number 977* when a button on the mouse is ***clicked*** and only exceed the *magic number 995* when a button on the mouse is ***not clicked***. 

<div align="center">
    <figure>
        <img width="auto" height="200" class="center" src="pics-and-graphs/ClickDetectionV1-noClick.jpg">
        <img width="auto" height="200" class="center" src="pics-and-graphs/ClickDetectionV1-Click.jpg">
        <p align="center">Figure 2. LED lights up when a Mouse Button is clicked or pressed down and stays lit the entire duration of the press.</p>
    </figure>
</div>
<div margin="0">
  <img width="auto" height="350" class="center" src="pics-and-graphs/ClickDetectionV1-consoleOutput.png">
  <p align="center" margin="0">Figure 3. When a button is pressed, the Serial Console prints the Click message.<br>When a button is not pressed, the Serial Console prints the analog voltage.<p>
</div>

#### Limitations With This Approach
1. This approach sends multiple messages when a button on the mouse is held down. Depending upon how the message is interpretated on the other end, one held down button may trigger multiple short clicks rather than one long click. This is not ideal. 

2. This approach can not differentiate between which button on the mouse is pressed. The mouse I am using has three buttons: left, right, and scroll wheel (which can also click down). Therefore, this approach prevents triggering button specific events such as left click to select versus right click for more options. 

3. Also, this approach is only looking at the transformations to the waveform as a whole, and is thus susceptible to noise triggering false clicks or prematurely ending a click.

4. Finally, by only analyzing the waveform, I am not decoding the actual bytes of data being sent by the mouse. Therefore, not only am I not able to detect which button was pressed, but I also am not able to detect when the mouse has been moved or when the scroll wheel has been scrolled. 

### 1 April 2021 - This is no joke.
I have updated the rudimentary click detection code to remember state: the click status. If the mouse button is held down, rather than repeatedly sending a message that the button has been clicked, it only sends a message when the button was first pressed down and when the button is finally released. This can be seen in the screenshot below of the serial console. The output messages have been timestamped. 
<!---
![Serial Console Output of Rudimentary Click Detection V2](./pics-and-graphs/ClickDetectionV2-consoleOutput.png)
<p align="center">Figure 4. Serial Console outputting Button Clicked and Button Released Messages</p>
--->
<div>
    <img src="/pics-and-graphs/ClickDetectionV2-consoleOutput.png">
    <p align="center">Figure 4. Serial Console outputting Button Clicked and Button Released Messages</p>
</div>
This iteration on the rudimentary click detection overcomes Limitation #1 listed under 31 March's Log entry. 

As you see in the code, rudimentary click detection is separate from the actual click detection because I had never intended the rudimentary click detection to be further used. It was only for me to see how much functionality I could derive just by blindly analyzing waveform transformations rather than analyzing the actual bits sent. I am genuinely surprised and happy by the fact I was able to detect clicks and their duration as well as I did. From now on, however, I will analyze the bits being sent. 

### 8 April 2021
I'm going to take my talents to South Beach and decode the data packets being sent by the mouse. I feel like it's going to give me the best opportunity to win and derive the most granular functionality from the mouse. Paraphrasing King James aside, this has been a bit more bumpy than I realized. There have been a lot of emotional highs and lows and I'll illustrate below what I mean.

Turns out, to receive data packets from the mouse, the Host (my computer) must first send commands to the mouse. The Host should:
1. 'Reset' the mouse by sending the command '0xFF'
2. Wait for the mouse to "Acknowledge" the Reset command, the mouse sends the message '0xFA'
3. Wait for the mouse to send the BAT (Basic Assurance Test) completion code, '0xAA' if succesful and '0xFC' if error
4. Wait for the mouse to send its Device ID, usually '0x00'
5. After all of that, send the "Enable Reporting Mode" command to the mouse, '0xF4'
6. Wait for the mouse to "Acknowledge" the Reset command, the mouse sends the message '0xFA'
7. Read movement and button data packets from the mouse

From my reading I learned that it is important for the Host to reset the mouse upon turning on to ensure the mouse's values are changed from an unknown state to default values. After entering the Reset mode, the mouse enters a self diagnostic test known as the Basic Assurance Test (BAT) and sets the following default values: 
* Sample Rate - 100 samples/sec
* Resolution - 4 counts/mm
* Scaling - 1:1
* Data Reporting Disabled

Upon completion of the Basic Assurance Test, the mouse sends either '0xAA' to signify that it has succesfully completed the test or '0xFC' if an error occured. If the Host receives anything other than '0xAA', then it can either cycle the mouse's power to reset it or send the 'Reset' command again. Once a '0xAA' completion code has been received, the mouse sends its device ID of '0x00' to distinguish itself from a keyboard or a mouse in an extended mode (not sure what extended means yet). It seems that datasheets recommend the Host not transmit any data packets until the mouse device ID has been received. After sending the ID, the mouse enters Stream Mode where it continuously samples and collects data about mouse activity. **However** as you can see above in the Default values, "Data Reporting Disabled". This means that though the mouse is collecting data, it is not reporting (sending the data packets) to the Host and it will continue to not do so until the Host Enables Reporting by sending the command '0xF4' to the mouse. Once the mouse "Acknowledges" the "Enable Reporting Mode" command with the message '0xFA', the mouse enters Stream Mode where the mouse is setup to stream data packets regarding button clicks and mouse movements back to the Host.

#### Attempt 1
Send reset and try to read every bit in the loop part of the code and print every bit to the console log. Maybe increase the port speed for the Serial Console. *Talk about how to send and receive data between Host and Mouse, include pictures of the timing diagrams*

#### Attampt 2
Send reset and this time in loop part batch the data received from mouse and then print every byte to console log

#### Attempt 3
Realize the loop part of the code is based on Arduino's internal timing frequency and might not always line up with mouse's sending frequency, so what if I speed up arduino's sampling frequency. 

#### Attempt 4
Facepalm really hard and realize that once I send the Reset data to the mouse, I can have the clock signals being received from the mouse cause interrupts which then causes the Arduino to go the Interrupt Handler where I have written code to read and batch data until the whole packet is sent. Then print it out to the Console Log. This attempt has been the most promising as this is the only attempt where I was able to *sorta clearly* read a response from the mouse. Here is what I saw:
*insert picture of console log, breakdown what the numbers could mean*

#### 8 April Conclusions
What do the 1's in the beginning mean? I don't know. Where did they come from? I don't know. What I do know though is that progress has been made. Something happened! I was able to send data to the mouse with correct timing and receive some kind of response that seems to so far check off Steps 2 and 3. Why I have not receieved a Device ID is yet to be figured out. But 3/7 Steps completed on my first day is not bad at all. Looking forward to how I progress. 
