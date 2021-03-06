# Rain Gauge Sensor
Here is a way to translate the excellent (wired) tipping bucket rain gauge from Rainwise into a more flexibe sensor using MySensors framework https://www.mysensors.org/

![1](https://github.com/boanjo/boanjo.github.io/blob/master/rain_mounted.jpg?raw=true "Pic 1")

You can of course use a simpler tipping bucket like you can find on ebay for a few dollars (or print your own) but i can garantuee that You are in for a lot of job and it will most likely not be accurate. Or you can buy a Davis or RainWise and mod it in the way you like it. Both brands are excellent but for the rain gauge i have 4 units (relatives wants precise data too:-)) and it just does the job excellent. If you live in the US you can pick one up for $72 https://rainwise.com/wired-rain-gauge. Here in Sweden it's been probably 50% higher.

Fusion 360 - 3D printed parts (optional)
-  Either you place the rain sensor in a open location (no trees or object to stop the rain...) on a flat surface that needs to be in level for the best accuracy or you can print the pole mounting model.
Download model from: https://www.thingiverse.com/thing:4641372
Youtube video: https://youtu.be/HJxwO2gRy1I

![2](https://github.com/boanjo/boanjo.github.io/blob/master/rain_mounting.jpg?raw=true "Pic 2")

- I've also added a small casing to make the access to the sensor a bit easier and to protect the antenna. 
Download model from: https://www.thingiverse.com/thing:4641372

![3](https://github.com/boanjo/boanjo.github.io/blob/master/rain_case.jpg?raw=true "Pic 3")

Building the sensor (These are the same steps as the temp_indoor sensor). First step is to remove the voltage regulator (If you are using battery powering or the sensor will die in a few days) also remove the power LED. It's quite easy to do with a sharp set of pliers. Or you can solder it off: https://www.mysensors.org/build/battery

![4](https://github.com/boanjo/boanjo.github.io/blob/master/temp_indoor_1_remove.jpg?raw=true "Pic 4")

Next add the step up (and or down) converter and arduino with some hot glue.
![5](https://github.com/boanjo/boanjo.github.io/blob/master/temp_indoor_2_hot_glue.jpg?raw=true "Pic 5")

Prepare the Radio (RFM69HW, the HIGH power version) wires: https://www.mysensors.org/build/connect_radio, solder the resistors and capacitor to measure the battery https://www.mysensors.org/build/battery and then also the home-made antenna http://www.byvac.com/downloads/RLnn/How-to-make-a-Air-Cooled-433MHz-antenna.pdf.

Oh and you need a pull-up resistor as well for the reed switch (i'm using 4k7ohm)
![6](https://github.com/boanjo/boanjo.github.io/blob/master/rain_radio.jpg?raw=true "Pic 6")

Put the sensor in the casing (which will make it easier to pick up again and protect the antenna). Then screw the reed switch connectors in place
![7](https://github.com/boanjo/boanjo.github.io/blob/master/rain_case.jpg?raw=true "Pic 7")


Here is a YouTube video showing the setup.
https://youtu.be/QY3R7Q7T6TU

Enjoy!