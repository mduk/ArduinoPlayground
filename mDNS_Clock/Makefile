arduino=${HOME}/Development/mduk/ArduinoPlayground/arduino-1.8.5/arduino
tty=/dev/ttyUSB0

build:
	$(arduino) --verify *.ino

upload:
	$(arduino) --upload *.ino \
		--verbose-upload \
		--port ${tty} \
		--board esp8266:esp8266:d1
