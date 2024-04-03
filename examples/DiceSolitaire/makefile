ARDUINO_PATH = /opt/arduino-1.8.13
#BOARD = teensy:avr:teensyLC
#USB_PREF = custom_usb=teensyLC_xinput
#OPTIONS = --board $(BOARD) --pref $(USB_PREF) --pref build.path=build --preserve-temp-files
OPTIONS = --pref build.path=build --preserve-temp-files

all: build
	$(ARDUINO_PATH)/arduino --verify $(OPTIONS) .

install: build
	$(ARDUINO_PATH)/arduino --upload $(OPTIONS) .

build:
	mkdir build

clean:
	rm -r build
