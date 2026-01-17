ln -s $(pwd)/qmk_firmware/keyboards/keyball ../__qmk__/keyboards/keyball
qmk compile -j 4 -kb keyball/keyball39 -km default
mkdir -p tmp
cp ../__qmk__/keyball_keyball39_default.hex tmp/keyball39.hex
