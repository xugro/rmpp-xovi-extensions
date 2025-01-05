# qt-resource-rebuilder

This extension lets you rebuild the QT resources loaded by an application on the fly.

It expects to see `*.qrr` files in `$XOVI_EXTHOME/exthome/qt-resource-rebuilder`.
QRR files follow the format:

```
R <qml path> <file path>
R <qml path 2> <file path 2>
...
```

For example:
```
R /images/test.png test.png
R /images/example.qml /home/root/example.qml
```

Note: Both absolute and relative paths are supported (relative paths' base is `$XOVI_EXTHOME/exthome/qt-resource-rebuilder`)

Note: By default, `$XOVI_EXTHOME` is `/home/root/xovi`

QMLDiff and raw RCC files are also supported. They use the *.qmd / *.rcc extensions, and will also be loaded automatically. RCC files let you add new resources - QML files, images, etc...

P.S.:

`QML_DISABLE_DISK_CACHE=1` is your friend

### Please remember to clear your qmlcache directory after creating / deleting qrr files, to make sure no cached versions are loaded

