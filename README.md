# ethernet-examples for SPRESENSE

Ethernet アドオンつかったアプリケーションを
ArduinoIDE または arduino-cli で開発する方法

# arduino-cli を使う方法

## あらかじめ必要なもの

- git(2.0 or later)
- golang(1.14 or later)
- python3(3.8 or later)
  - pyserial(3.5 or later)

```shell
git clone https://github.com/144lab/arduino-cli.git -b fix-#1198
cd arduino-cli
go install .
```

Go でインストールするツールを実行可能にするのに以下の記述を環境変数設定に加えましょう。

```shell
PATH=$(go env GOPATH)/bin:$PATH
```

```shell
arduino-cli config init
arduino-cli config add board_manager.additional_urls https://github.com/sonydevworld/spresense-arduino-compatible/releases/download/generic/package_spresense_index.json
arduino-cli core update-index
arduino-cli core install SPRESENSE:spresense
```

```shell
git clone github.com/144lab/spresense-ethernet-examples
cd examples
make NAME=dhcp-client build upload
```
