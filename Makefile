NAME:=dhcp-client
TAG:=localhost/spresense-arduino
FQBN:=SPRESENSE:spresense:spresense
PORT=$$(ls -1 /dev/tty.usbserial-14*)
REV:=$(shell git describe --tags || echo none)
PWD:=$(shell pwd)
NAME_SUFFIX=
BUILD=./build
CFLAGS:=
OPTS:=--build-property="build.debug_flags=$(CFLAGS)"
OUTPUT_NAME:=$(NAME)-$(REV)$(NAME_SUFFIX)
OUTPUT_DIR:=$(NAME)-$(REV)$(NAME_SUFFIX)
COPYFILE_DISABLE=1
export COPYFILE_DISABLE

.PHONY: build upload setup mon docker

build:
	docker build --rm -t $(TAG) ./docker
	docker run -it \
	--mount type=bind,source="$(PWD)",target=/app \
	-w /app \
	$(TAG) \
	make NAME=$(NAME) compile

test:
	@echo "$(PWD)"

compile:
	arduino-cli compile -b $(FQBN) --output-dir ./build $(OPTS) $(NAME)
	mkdir -p $(BUILD)/$(OUTPUT_DIR)
	mv $(BUILD)/$(NAME).ino.elf $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.elf
	mv $(BUILD)/$(NAME).ino.spk $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.spk

upload:
	arduino-cli upload -t -b $(FQBN) -p $(PORT) -i $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.spk

clean:
	@-rm -rf $(BUILD)

sleep:
	sleep 2

props:
	arduino-cli compile -b $(FQBN) --show-properties $(NAME)

mon:
	pyserial-miniterm $(PORT) 115200
