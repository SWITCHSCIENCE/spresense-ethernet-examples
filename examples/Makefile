NAME:=dhcp-client
TAG:=localhost/spresense-arduino
FQBN:=SPRESENSE:spresense:spresense
PORT=$$(ls -1 /dev/tty.usbserial-14*)
REV:=$(shell git describe --tags || echo none)
NAME_SUFFIX=
BUILD=./build
CFLAGS:=
OPTS:=--build-property="build.debug_flags=$(CFLAGS)"
OUTPUT_NAME:=$(NAME)-$(REV)$(NAME_SUFFIX)
OUTPUT_DIR:=$(NAME)-$(REV)$(NAME_SUFFIX)
COPYFILE_DISABLE=1
export COPYFILE_DISABLE
#WRITER:=$(HOME)/Library/Arduino15/packages/SPRESENSE/tools/spresense-tools/2.2.0/flash_writer/macosx/flash_writer

.PHONY: build upload setup mon docker

build:
	docker build --rm -t $(TAG) ../docker
	docker run -it \
	--mount type=bind,source="$$(pwd)",target="$$(pwd)" \
	-w "$$(pwd)" \
	$(TAG) \
	make compile

compile:
	arduino-cli compile -b $(FQBN) --output-dir ./build $(OPTS) $(NAME)
	mkdir -p $(BUILD)/$(OUTPUT_DIR)
	mv $(BUILD)/$(NAME).ino.elf $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.elf
	mv $(BUILD)/$(NAME).ino.spk $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.spk

upload:
	arduino-cli upload -t -b $(FQBN) -p $(PORT) -i $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.spk
	# $(WRITER) -c $(PORT) -a $(BUILD)/$(OUTPUT_DIR)/$(OUTPUT_NAME).ino.spk

clean:
	@-rm -rf $(BUILD)

sleep:
	sleep 2

props:
	arduino-cli compile -b $(FQBN) --show-properties $(NAME)

mon:
	pyserial-miniterm $(PORT) 115200
