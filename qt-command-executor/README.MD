# qt-command-executor

To use this module in your QML code, start by importing CommandExecutor:

```qml
import net.asivery.CommandExecutor 1.0
```

Then define the CommandExecutor object:

```qml
CommandExecutor {
    id: cmdExecutor
}
```

Finally, to execute any command, invoke:

```qml
const { stdout, stderr } = cmdExecutor.executeCommand("uname", ["-a"]);
```
