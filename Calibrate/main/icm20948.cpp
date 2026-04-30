#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/message_buffer.h"
#include "esp_log.h"
#include "esp_err.h"
#include "cJSON.h"

#include "parameter.h"

extern MessageBufferHandle_t xMessageBufferToClient;

static const char *TAG = "IMU";

#include "ICM20948_WE.h"

ICM20948_WE myIMU = ICM20948_WE(CONFIG_I2C_ADDR);

void icm20948(void *pvParameters){
	// Initialize IMU
	if (!myIMU.init()) {
		ESP_LOGI(TAG, "Initialize fail");
		vTaskDelete(NULL);
	}
	if (!myIMU.initMagnetometer()) {
		ESP_LOGE(TAG, "Magnetometer does not respond");
		vTaskDelete(NULL);
	}
	myIMU.setMagOpMode(AK09916_CONT_MODE_20HZ);

	while(1) {
		xyzFloat magValue; // x/y/z magnetic flux density
		myIMU.readSensor();
		myIMU.getMagValues(&magValue);
		//printf("magValue=%f %f %f\n", magValue.x, magValue.y, magValue.z);

		float mx, my, mz;
		mx = magValue.x + CONFIG_MAG_OFFSET_X;
		my = magValue.y + CONFIG_MAG_OFFSET_Y;
		mz = magValue.z + CONFIG_MAG_OFFSET_Z;
		ESP_LOGI(TAG, "%f %f %f", mx, my, mz);

		// Send WEB request
		cJSON *request;
		request = cJSON_CreateObject();
		cJSON_AddStringToObject(request, "id", "data-request");
		cJSON_AddNumberToObject(request, "roll", mx);
		cJSON_AddNumberToObject(request, "pitch", my);
		cJSON_AddNumberToObject(request, "yaw", mz);
		char *my_json_string = cJSON_Print(request);
		ESP_LOGD(TAG, "my_json_string\n%s",my_json_string);
		size_t xBytesSent = xMessageBufferSend(xMessageBufferToClient, my_json_string, strlen(my_json_string), 100);
		if (xBytesSent != strlen(my_json_string)) {
			ESP_LOGE(TAG, "xMessageBufferSend fail");
		}
		cJSON_Delete(request);
		cJSON_free(my_json_string);
		vTaskDelay(10);
	} // end while

	// Never reach here
	vTaskDelete(NULL);
}
