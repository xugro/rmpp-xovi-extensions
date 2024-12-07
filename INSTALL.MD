# Disclaimers and general info

I am NOT responsible for any damages that you may incur to your device using my software. If you end up permanently bricking your device, or damaging the screen, you cannot expect me to fix it. I have written these extensions for myself, and sharing them in hopes that someone might also find them useful.

You are installing this at your own risk.

XOVI is a tethered extension manager - after a restart, the tablet will get back to the stock OS. To get XOVI back, simply run `xovi/start` from the SSH prompt. Your tablet will restart, and you will get XOVI back.

## To install XOVI:
- Download [this](https://github.com/asivery/xovi/releases/latest/download/xovi.so) file
- Over SSH, create the following directory structure:
```
/home/root
    |
    \->xovi
       |
       |->extensions.d
       |
       |->exthome
       |
       \->xovi.so (copy the file here)
```
- Run the following commands (copy and paste into SSH shell):
```
echo "#!/bin/bash" > /home/root/xovi/_start
echo "#!/bin/bash" > /home/root/xovi/start
echo "systemctl stop xochitl; killall xochitl 2>/dev/null; screen -dm bash -c '/home/root/xovi/_start'" >> /home/root/xovi/start
echo "QML_DISABLE_DISK_CACHE=1 LD_PRELOAD=/home/root/xovi/xovi.so xochitl" >> /home/root/xovi/_start
chmod a+x /home/root/xovi/{_start,start}
```

## To install extensions:
- Before installing an extension, read its readme to make sure you also installed all of its dependencies. An extension without dependencies will either fail to load, or crash on startup.
- Download an extension's `.so` file (in case of this repository, download the `extensions.zip` file, then unpack it to get all the currently available xovi extensions)
- Run `xovi/start` to restart xovi
