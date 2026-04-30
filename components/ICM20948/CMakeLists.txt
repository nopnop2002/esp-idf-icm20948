idf_component_register(
	SRCS "ICM20948_WE.cpp" "xyzFloat.cpp"
	INCLUDE_DIRS "."
	PRIV_REQUIRES driver esp_driver_i2c esp_driver_gpio esp_timer
)
