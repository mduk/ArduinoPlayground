arduino=${DEV_DIR}/mduk/ArduinoPlayground/arduino-1.8.5/arduino
screen=/usr/bin/screen
board=esp8266:esp8266:d1_mini
#board=arduino:avr:nano:cpu=atmega328
tty=/dev/ttyUSB0
baud=$(shell sed -n '/\s*Serial.begin(\([0-9]\+\));/s//\1/p' *.ino)

build:
	$(arduino) --verify *.ino \
		--board $(board)

upload:
	$(arduino) --upload *.ino \
		--verbose-upload \
		--port $(tty) \
		--board $(board)

screen:
	$(screen) $(tty) $(baud)
