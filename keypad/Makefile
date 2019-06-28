arduino=../arduino-1.8.5/arduino
tty=/dev/ttyUSB0

build:
	$(arduino) --verify *.ino

upload:
	$(arduino) --upload *.ino \
		--verbose-upload \
		--port ${tty} \
		--board arduino:avr:nano:cpu=atmega328
