#ifndef DIALOGTEST_H
#define DIALOGTEST_H

#include <QTime>
#include <QDialog>
#include <QProcess>
#include <QFileDialog>
#include "Information.h"

namespace Ui {
    class DialogTest;
}

class DialogTest : public QDialog
{
    Q_OBJECT

public:
    explicit DialogTest(QWidget *parent = 0);
    ~DialogTest();
    void setCompiler(qint32 compiler);
    void setTestFileName(const QString &fileName);
    void selectInputFile();
    void testFile();

private:
    Ui::DialogTest *ui;
    qint32 compiler;
    QString testFileName;
    QString inputFileName;
    QProcess *compileProcess;
    QProcess *runProcess;
    QTime *runTime;
    bool isCompileCorrect;

private slots:
    void compileError();
    void compileComplete();
    void standardError();
    void standardOutput();
    void standardComplete();
};

#endif // DIALOGTEST_H
