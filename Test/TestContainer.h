#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QObject>

// forward (partial) declaration of class.  When possible this is better than adding extra includes to a header file
class CQtSched;

class CTestContainer : public QObject {
    Q_OBJECT

public:
    CTestContainer(QQmlApplicationEngine *_engine, QObject *_parent=nullptr);
    ~CTestContainer();

public slots:
    void schedTimeout();
    void start();
    void stop();

public:
    QQmlApplicationEngine *m_engine;
    CQtSched *m_sched;
};

