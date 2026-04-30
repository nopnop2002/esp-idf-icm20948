# Get Compass offset
```
git clone https://github.com/nopnop2002/esp-idf-icm20948
cd esp-idf-icm20948/Calibrate
idf.py set-target {esp32/esp32s2/esp32s3/esp32c2/esp32c3/esp32c6}
idf.py menuconfig
idf.py flash
```

### Configuration   
To find the offset value, set the compass offset to 0.   
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/e8e157a5-f635-4317-859e-ef0259b89b97" />
<img width="659" height="486" alt="Image" src="https://github.com/user-attachments/assets/8caf7c5d-bb57-49b0-9ec0-b6f60fd3496f" />

### Execute calibration   
ESP32 acts as a web server.   
I used [this](https://github.com/Molorius/esp32-websocket) component.   
This component can communicate directly with the browser.   
Enter the following in the address bar of your web browser.   
```
http:://{IP of ESP32}/
or
http://esp32.local/
```

As you move the IMU it plots the X, Y and Z values.   
X, Y, Z offset are displayed.   
<img width="924" height="786" alt="Image" src="https://github.com/user-attachments/assets/55d33468-4684-444c-a8ee-90e6fe6bf8a0" />

### Execute calibration again   
If you set the offset you got from the calibration and run it again, the circle position will change.   
<img width="924" height="786" alt="Image" src="https://github.com/user-attachments/assets/726efb7a-d184-4432-880a-b67d4876186e" />
