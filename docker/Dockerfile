FROM ubuntu:20.04

RUN apt update
RUN apt install -y curl git make
RUN curl -L https://github.com/arduino/arduino-cli/releases/download/0.18.3/arduino-cli_0.18.3_Linux_64bit.tar.gz | tar xz -C /bin
RUN arduino-cli config init
RUN arduino-cli config add board_manager.additional_urls https://github.com/sonydevworld/spresense-arduino-compatible/releases/download/generic/package_spresense_index.json
RUN arduino-cli core update-index
RUN arduino-cli core install SPRESENSE:spresense
RUN arduino-cli lib update-index
RUN arduino-cli lib install SSLClient
ADD ./Ethernet /root/Arduino/libraries/Ethernet
