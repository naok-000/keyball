ln -s $(pwd)/qmk_firmware/keyboards/keyball ../__qmk__/keyboards/keyball
qmk compile -j 1 -kb keyball/keyball39 -km mac
mkdir -p build
cp ../__qmk__/keyball_keyball39_mac.hex build/keyball39.hex
