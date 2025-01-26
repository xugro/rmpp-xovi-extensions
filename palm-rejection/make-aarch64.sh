exit 0
source ~/Tools/remarkable-toolchain/environment-setup-cortexa53-crypto-remarkable-linux
SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
NM=${SCRIPT_DIR##*/}
python3 $XOVI_REPO/util/xovigen.py -c "aarch64-remarkable-linux-gcc -D_GNU_SOURCE --sysroot ~/Tools/remarkable-toolchain/sysroots/cortexa53-crypto-remarkable-linux" -m -o $TMP/$NM $NM.xovi
bash $TMP/$NM/make.sh
