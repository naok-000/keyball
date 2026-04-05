ln -s $(pwd)/qmk_firmware/keyboards/keyball ../__qmk__/keyboards/keyball
qmk compile -j 1 -kb keyball/keyball39 -km default
mkdir -p build
cp ../__qmk__/keyball_keyball39_my_keymap.hex build/keyball39.hex
