source ~/Tools/remarkable-toolchain/environment-setup-cortexa53-crypto-remarkable-linux
cd qmldiff
cargo build --target aarch64-unknown-linux-gnu --release --lib
cd ..
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
NM=${SCRIPT_DIR##*/}
python3 $XOVI_REPO/util/xovigen.py -c "aarch64-remarkable-linux-gcc -D_GNU_SOURCE --sysroot $SDKTARGETSYSROOT -lQt6Core" -m -o $TMP/$NM $NM.xovi
aarch64-remarkable-linux-g++ --sysroot $SDKTARGETSYSROOT -I $SDKTARGETSYSROOT/usr/include/QtCore/ -c $TMP/$NM/src/rccload.cpp -o $TMP/$NM/src/rccload.o
bash $TMP/$NM/make.sh
