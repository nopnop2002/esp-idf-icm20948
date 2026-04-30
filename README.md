# esp-idf-icm20948
A demo showing the pose of the icm20948 9DoF IMU sensor in 3D using esp-idf.   

You can use the Kalman filter or the Madgwick filter to estimate the Euler angle.   
Euler angles are roll, pitch and yaw.   
It's very intuitive and easy to understand.   
![a-Pitch-yaw-and-roll-angles-of-an-aircraft-with-body-orientation-O-u-v-original](https://user-images.githubusercontent.com/6020549/224452743-d4cf419d-f936-4e46-9ece-a12f21bf2e32.jpg)   
You can view like this.   
![Image](https://github.com/user-attachments/assets/cb9f1408-b372-4e55-84f6-1191f068cd1a)


# Installation overview

- Get Compass offset from IMU.

- Get Euler angles from IMU.

- Display Euler angles in browser.

# Software requirements
ESP-IDF V5.2 or later.   
Because this project uses the new I2C driver.   

# Hardware requirements
ICM20948 9-Axis MEMS MotionTracking Device.

# Wireing
|ICM20948||ESP32|ESP32-S2/S3|ESP32-C2/C3/C6||
|:-:|:-:|:-:|:-:|:-:|:-:|
|VCC|--|3.3V|3.3V|3.3V||
|GND|--|GND|GND|GND||
|SCL|--|GPIO22|GPIO12|GPIO5|(*1)|
|SDA|--|GPIO21|GPIO11|GPIO4|(*1)|
|NCS|--|3.3V|3.3V|3.3V|Use i2c|
|ADO|--|GND/3.3V|GND/3.3V|GND/3.3V|(*2)|

(*1)You can change it to any pin using menuconfig.   

(*2)I2C address selection.   
GND:i2c address is 0x68.   
3.3V:i2c address is 0x69.   

# Find the sensor
We can find the sensor using [i2c-tools](https://github.com/espressif/esp-idf/tree/master/examples/peripherals/i2c/i2c_tools).   

- Select SCL and SDA using menuconfig.   
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/7c182697-378f-43e6-967f-67a43f6aa483" />

- Detect senser.   
The i2c address for this sensor is 0x68 or 0x69.   
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/76b8f07b-dc80-4e1c-adc0-2c63c56076dc" />

- Read register.   
Register #0x0F for this sensor is 0xEA.   
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/170f5cfd-7658-4a12-b6f4-305ce5788693" />

# Get Compass offset from IMU
Use [Calibrate](https://github.com/nopnop2002/esp-idf-icm20948/tree/main/Calibrate) to find the compass offset.   

# Get Euler angles from IMU using Kalman filter
```
git clone https://github.com/nopnop2002/esp-idf-icm20948
cd esp-idf-icm20948/Kalman
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

### Configuration
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/f5ac137b-94b6-41d1-a6fa-aa15ea3816b7" />
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/35e45918-d532-4157-998c-23e819cbaae8" />

# Get Euler angles from IMU using Madgwick filter
```
git clone https://github.com/nopnop2002/esp-idf-icm20948
cd esp-idf-icm20948/Madgwick
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

### Configuration
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/043fd7b2-b3f0-4190-92ad-ec9ed671305e" />
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/88302591-f76d-41db-aae8-5c45db76d697" />

# View Euler angles with built-in web server   
ESP32 acts as a web server.   
I used [this](https://github.com/Molorius/esp32-websocket) component.   
This component can communicate directly with the browser.   
Enter the following in the address bar of your web browser.   
```
http:://{IP of ESP32}/
or
http://esp32.local/
```

![browser-roll-pitch-yaw](https://user-images.githubusercontent.com/6020549/232365926-ccc6198b-42ec-44f7-891d-6caa93c3411c.JPG)

WEB pages are stored in the html folder.   
I used [this](https://threejs.org/) for 3D display.   
I used [this](https://canvas-gauges.com/) for gauge display.   
Configuration Options for the gauge display is [here](https://canvas-gauges.com/documentation/user-guide/configuration).   
You can change the design and color according to your preference like this.   
![Image](https://github.com/user-attachments/assets/d0e1ca46-0d46-41ed-bbbc-9f26af28900d)


# View Euler angles using PyTeapot   
You can view Euler angles using [this](https://github.com/thecountoftuscany/PyTeapot-Quaternion-Euler-cube-rotation) tool.   
It works as a UDP display server.   
This is a great application.   

```
+-------------+          +-------------+          +-------------+
|             |          |             |          |             |
|     IMU     |--(i2c)-->|    ESP32    |--(UDP)-->| pyteapot.py |
|             |          |             |          |             |
+-------------+          +-------------+          +-------------+
```

### Installation for Linux
```
$ python3 --version
Python 3.11.2
$ sudo apt install python3-pip python3-setuptools
$ python3 -m pip install -U pip
$ python3 -m pip install pygame
$ python3 -m pip install PyOpenGL PyOpenGL_accelerate
$ git clone https://github.com/thecountoftuscany/PyTeapot-Quaternion-Euler-cube-rotation
$ cd PyTeapot-Quaternion-Euler-cube-rotation
$ python3 pyteapot.py
```

The posture of your sensor is displayed.   
![pyteapot_2023-03-11_09-11-46](https://user-images.githubusercontent.com/6020549/224452173-2350704d-1fc4-4a12-8324-434c11f62c52.png)

### Installation for Windows   
Install Git for Windows from [here](https://gitforwindows.org/).   
Install Python Releases for Windows from [here](https://www.python.org/downloads/windows/).   
Open Git Bash and run:   
```
$ python --version
Python 3.11.9
$ python -m pip install -U pip
$ python -m pip install pygame
$ python -m pip install PyOpenGL PyOpenGL_accelerate
$ git clone https://github.com/thecountoftuscany/PyTeapot-Quaternion-Euler-cube-rotation
$ cd PyTeapot-Quaternion-Euler-cube-rotation
$ python pyteapot.py
```

The posture of your sensor is displayed.   
![PyTeapot-Windows](https://github.com/user-attachments/assets/2b0a1a70-40cb-47e5-8f51-eb4fe3adb1ab)


### String passed over Wifi to pyteapot.py
Yaw angle should be betweem two ```y```.   
Pitch angle should be between two ```p```.   
Roll angles should be between two ```r```.   
```
# yaw = 168.8099
# pitch = 12.7914
# roll = -11.8401
# Euler angles only
y168.8099yp12.7914pr-11.8401r

```

# View Euler angles using panda3d library   
You can view Euler angles using [this](https://www.panda3d.org/) library.   
It works as a UDP display server.   

```
+-------------+          +-------------+          +-------------+
|             |          |             |          |             |
|     IMU     |--(ic2)-->|    ESP32    |--(UDP)-->|  panda.py   |
|             |          |             |          |             |
+-------------+          +-------------+          +-------------+
```

### Installation for Linux
```
$ python3 --version
Python 3.11.2
$ sudo apt install python3-pip python3-setuptools
$ python3 -m pip install -U pip
$ python3 -m pip install panda3d
$ cd esp-idf-mpu6050-dmp/panda3d
$ python3 panda.py --help
usage: panda.py [-h] [--model {jet,biplain,707,fa18}]

options:
  -h, --help            show this help message and exit
  --model {jet,biplain,707,fa18}
```
![Image](https://github.com/user-attachments/assets/83804b5e-3ffe-4e18-966e-0ce180c1ab21)

### Installation for Windows
Install Git for Windows from [here](https://gitforwindows.org/).   
Install Python Releases for Windows from [here](https://www.python.org/downloads/windows/).   
Open Git Bash and run:   
```
$ python --version
Python 3.11.9
$ python -m pip install -U pip
$ python -m pip install panda3d
$ cd esp-idf-mpu6050-dmp/panda3d
$ python panda.py --help
usage: panda.py [-h] [--model {jet,biplain,707,fa18}]

options:
  -h, --help            show this help message and exit
  --model {jet,biplain,707,fa18}
```
![Image](https://github.com/user-attachments/assets/7f2fbdf4-97d9-40c3-87db-9f8386741220)

### How to use   
See [here](https://github.com/nopnop2002/esp-idf-mpu6050-dmp/blob/main/panda3d/README.md)   
