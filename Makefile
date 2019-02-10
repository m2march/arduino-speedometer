.PHONY: verify

PORT=/dev/ttyUSB0
ARDUINO_PATH=/home/march/Downloads/arduino-1.8.8/arduino
SKETCH=m2_speedometer.ino

verify:
	$(ARDUINO_PATH) --verify $(SKETCH) 

upload:
	$(ARDUINO_PATH) --upload $(SKETCH) --port $(PORT)
