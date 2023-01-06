# tec-Magnetometers

## Magnetometers 
are sensors that measure the strength and direction of a magnetic field. They are commonly used in a wide range of applications, including navigation, geomagnetic field mapping, and metal detection.

There are several parameters that can be measured using a magnetometer:

Magnetic field strength: This is the magnitude of the magnetic field, typically measured in units of tesla (T) or gauss (G). The strength of the magnetic field can be affected by factors such as the distance from the magnetometer to the source of the magnetic field, the strength of the magnet, and the orientation of the magnetometer relative to the field.

Magnetic field direction: This is the direction of the magnetic field, typically measured as an angle in degrees or radians relative to a reference direction (e.g. north, east, up). The direction of the magnetic field can be affected by factors such as the orientation of the magnetometer and the location of the magnetometer relative to the Earth's magnetic field.

Magnetic field inclination: This is the angle between the magnetic field and a reference plane (e.g. the Earth's surface), typically measured in degrees or radians. The inclination of the magnetic field can be affected by factors such as the location of the magnetometer and the Earth's magnetic field.

Magnetic field declination: This is the angle between the magnetic field and true north, typically measured in degrees or radians. The declination of the magnetic field can be affected by factors such as the Earth's magnetic field and the location of the magnetometer.

To perform experiments with a magnetometer, you would need to set up a test environment that allows you to control or vary one or more of these parameters and measure the response of the magnetometer. This may involve using magnets of different sizes and strengths, positioning the magnetometer at different locations and orientations, or applying external magnetic fields. You would also need to use appropriate measurement tools and techniques, such as a compass, a protractor, or a digital multimeter, to accurately measure the parameters of interest.

## Arduino-Magnetometer
Its worth looking at this project to glean ideas for the tec-1 

![image](https://user-images.githubusercontent.com/58069246/210121917-d21dcce7-790e-4749-a5c0-1b8761793f53.png)


## code
drawArrow3d() is a function in C++ that appears to be used to draw an arrow on a graphical display, with the arrow pointing in a direction determined by three input values inxx, inyy, and inzz. These input values are assumed to range from 0 to 1023, and correspond to voltages ranging from 0 to 3.3V or 0 to 5V. This code part reads three analog input values inxx, inyy, and inzz from analog pins A1, A2, and A3 respectively. It then converts the values to voltage values vxx, vyy, and vzz by multiplying them by the voltage supply (3.3V or 5V) and dividing them by 1024.

An Arduino is a microcontroller, which is a type of computer that is designed to control electronic devices such as sensors, motors, and displays. It has a number of input and output (I/O) pins that can be used to read and write digital signals, as well as to read and write analog signals through a process called analog-to-digital conversion (ADC).

To read a voltage using an Arduino, you will need to connect the voltage source to one of the Arduino's analog input pins using a voltage divider circuit. The voltage divider circuit is used to scale the input voltage to a range that can be read by the Arduino's ADC.

To read the voltage, you will need to use the Arduino's analogRead() function, which takes the analog input pin number as an argument and returns the ADC value as an integer between 0 and 1023. You can then convert this value to a voltage by multiplying it by the voltage reference (Vref) and dividing by the maximum ADC value (1023).

For example, if the voltage reference is 5V and the ADC value is 512, the input voltage would be:
```
Voltage = (ADC value * Vref) / 1023
= (512 * 5V) / 1023
= 2.5V
```
Here is an example of code that reads the voltage on analog input pin 0 and prints the result to the serial monitor: ```rv.c```

## cct

![image](https://user-images.githubusercontent.com/58069246/210121928-655f1641-a7d0-48df-80a9-3509c9b9a152.png)

![image](https://user-images.githubusercontent.com/58069246/210121943-2ef4d2bf-0bf1-4e99-be4d-70f6dd9ac0cd.png)


It is possible to emulate an ADC (analog-to-digital converter) using a capacitor and resistor. This can be done using a charge-balancing ADC circuit, which measures the time it takes for a capacitor to charge or discharge to a certain voltage level. The capacitor is charged or discharged through a resistor, and the time it takes to reach the voltage level is proportional to the input voltage. By measuring the time it takes for the capacitor to charge or discharge, the input voltage can be approximated.

Here is an example of a charge-balancing ADC circuit using a capacitor and resistor:
```
       5V
      ----
      |  |
      R   C
      |  |
      ----
       0V
```
In this circuit, R is the resistor and C is the capacitor. The input voltage is applied across R and C, and the output is taken from the junction between the two components. To measure the input voltage, the capacitor is charged or discharged through the resistor until it reaches a certain voltage level. The time it takes for the capacitor to reach this voltage level is measured, and the input voltage is approximated based on this time. One way to measure the time it takes for the capacitor to charge or discharge is to use a microcontroller with a timer function. The microcontroller can be programmed to start the timer when the charging or discharging process begins, and to stop the timer when the capacitor reaches the target

## MINT
This Mint code defines three commands: charge-capacitor, discharge-capacitor, and loop. The charge-capacitor command sets the output pin to HIGH, starts the timer, and waits until the input voltage reaches 512. The discharge-capacitor command sets the output pin to LOW, starts the timer, and waits until the input voltage falls below 512. The loop command charges and discharges the capacitor and prints the elapsed time to the serial monitor. It then waits for 1 second before repeating the process.

To convert the elapsed time to an approximation of the input voltage, you can use the following formula:
```Input voltage = (Elapsed time / Time constant) * Voltage reference```
Where the time constant is the product of the resistor and capacitor values (RC), and the voltage reference is the maximum input voltage (in this case, 5V).
```cpr.f```



## Iterate
- https://github.com/SteveJustin1963/Magnetotelluric



## Ref
- https://en.wikipedia.org/wiki/Magnetometer
- https://www.instructables.com/Arduino-Magnetometer/
- https://www.falstad.com/vector3dm/
- https://en.wikipedia.org/wiki/3D_projection
- https://en.wikipedia.org/wiki/Isometric_projection

