arduino=../arduino-1.8.5/arduino
screen=/usr/bin/screen
board=esp8266:esp8266:d1_mini
tty=/dev/ttyUSB0
baud=115200

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
