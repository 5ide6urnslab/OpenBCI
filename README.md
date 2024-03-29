# OpenBCI
This repository is the Debugging for the OpenBCI "Cyton Biosensing Board Kit (8-channel)" that runs on openFrameworks v0.80. 

<img class="photo" src="https://github.com/5ide6urnslab/OpenBCI/blob/master/Resource/System.png" width="600px" />

## Description
##### ReceiveOpenBCI
This ReceiveOpenBCI is the openFrameworks Application for Debugging the OpenBCI "Cyton Biosensing Board Kit (8-channel)". This Application is received the EEG data x 8ch and Acceleration(x, y, z) data from OpenBCI.

<img class="photo" src="https://github.com/5ide6urnslab/OpenBCI/blob/master/Resource/ReceiveOpenBCI.png" width="340px" />

<br>
##### PlaybackLog
This PlaybackLog is the openFrameworks Application for OpenBCI "Cyton Biosensing Board Kit (8-channel)". This Application is played the OpenBCI log and send the EEG data x 8ch by OSC.

<img class="photo" src="https://github.com/5ide6urnslab/OpenBCI/blob/master/Resource/PlayBack.png" width="340px" />

## Installation
(1) To use the above application, first you need to download and install  
http://openframeworks.cc

(2) To get a copy of the repository you can download the source from  
https://github.com/5ide6urnslab/OpenBCI/blob/master/Application

(3) If you use the ReceiveOpenBCI application, you have to change the Serial Port Name of testApp.h.

<img class="photo" src="https://github.com/5ide6urnslab/OpenBCI/blob/master/Resource/SerialPortName.png" width="340px" />

(4) If you use the PlaybackLog application, you have to change the Serial Port Number of testApp.h.

<img class="photo" src="https://github.com/5ide6urnslab/OpenBCI/blob/master/Resource/SerialPortNumber.png" width="340px" />


## Reference
(1) OpenBCI  
http://docs.openbci.com/Getting%20Started/00-Welcome

(2) openFrameworks v0.80  
http://openframeworks.cc

## Copyright
© 2016 OpenBCI All Rights Reserved.  
   http://openbci.com

## License
##### About this manual and image files.
<a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-sa/4.0/88x31.png" /></a><br />5ide6urns lab is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-sa/4.0/">Creative Commons Attribution-ShareAlike 4.0 International License</a>.

## Credit
##### ReceiveOpenBCI:

Programmer:   [Show Kawabata](http://www.dum6sen5e.com) (5ide6urns lab)

##### PlaybackLog:

Programmer:   [Show Kawabata](http://www.dum6sen5e.com) (5ide6urns lab)
