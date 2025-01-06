#include <QObject>
#include <QProcess>
#include <QProcessEnvironment>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

class CommandExecutor : public QObject
{
    Q_OBJECT
public:
    explicit CommandExecutor(QObject *parent = nullptr) : QObject(parent) {}

    Q_INVOKABLE QString executeCommand(const QString &command, const QStringList &arguments)
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.remove("LD_PRELOAD");
        QProcess process;
        process.setProcessEnvironment(env);
        process.start(command, arguments);
        process.waitForFinished();

        QString stdout = process.readAllStandardOutput();
        QString stderr = process.readAllStandardError();

        QJsonObject outputJson;
        outputJson.insert("stdout", stdout);
        outputJson.insert("stderr", stderr);

        QJsonDocument outputDoc(outputJson);
        QString output(outputDoc.toJson(QJsonDocument::Compact));
        return output;
    }
    Q_INVOKABLE bool executeCommandDetached(const QString &command, const QStringList &arguments)
    {
        QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
        env.remove("LD_PRELOAD");
        QProcess process;
        process.setProcessEnvironment(env);
        return process.startDetached(command, arguments);
    }
};

