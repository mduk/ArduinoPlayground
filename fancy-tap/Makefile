arduino=../arduino-1.8.9/arduino

build:
	$(arduino) --verify *.ino

upload:
	$(arduino) --upload *.ino \
		--verbose-upload \
		--port /dev/ttyUSB0 \
		--board arduino:avr:nano:cpu=atmega328
