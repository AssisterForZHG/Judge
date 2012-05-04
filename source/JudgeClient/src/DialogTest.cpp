#include "include/DialogTest.h"
#include "ui_DialogTest.h"

DialogTest::DialogTest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogTest)
{
    ui->setupUi(this);
}

DialogTest::~DialogTest()
{
    this->compileProcess->close();
    this->runProcess->close();
    delete ui;
}

void DialogTest::setCompiler(qint32 compiler)
{
    this->compiler = compiler;
}

void DialogTest::setTestFileName(const QString &fileName)
{
    this->testFileName = fileName;
}

void DialogTest::selectInputFile()
{
    this->inputFileName = QFileDialog::getOpenFileName(this, tr("Select Input File"));
}

void DialogTest::testFile()
{
    this->isCompileCorrect = true;
    this->compileProcess = new QProcess(this);
    this->connect(this->compileProcess, SIGNAL(readyReadStandardError()), this, SLOT(compileError()));
    this->connect(this->compileProcess, SIGNAL(finished(int)), this, SLOT(compileComplete()));
    switch(compiler)
    {
    case Information::COMPILER_GNU_C:
        this->compileProcess->start("gcc -Wall " + this->testFileName +  " -o main.exe");
        break;
    case Information::COMPILER_GNU_CPP:
        this->compileProcess->start("g++ -Wall " + this->testFileName +  " -o main.exe");
        break;
    case Information::COMPILER_JAVA:
        this->compileProcess->start("javac " + this->testFileName);
        break;
    }
    this->exec();
}

void DialogTest::compileError()
{
    this->ui->compilerTextEdit->appendPlainText(this->compileProcess->readAllStandardError());
    this->isCompileCorrect = false;
}

void DialogTest::compileComplete()
{
    if(this->isCompileCorrect)
    {
        this->ui->compilerTextEdit->appendPlainText(tr("Compile successfully."));
        this->runProcess = new QProcess(this);
        this->runProcess->setStandardInputFile(this->inputFileName);
        this->connect(this->runProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(standardOutput()));
        this->connect(this->runProcess, SIGNAL(readyReadStandardError()), this, SLOT(standardError()));
        this->connect(this->runProcess, SIGNAL(finished(int)), this, SLOT(standardComplete()));
        this->runTime = new QTime();
        switch(this->compiler)
        {
        case Information::COMPILER_GNU_C:
        case Information::COMPILER_GNU_CPP:
            this->runProcess->start("main.exe");
            break;
        case Information::COMPILER_JAVA:
            this->runProcess->start("java Main");
            break;
        }
        this->runTime->start();
    }
    else
    {
        this->ui->standardTextEdit->setPlainText(tr("There is no output."));
    }
}

void DialogTest::standardError()
{
    this->ui->standardTextEdit->appendPlainText(this->runProcess->readAllStandardError());
}

void DialogTest::standardOutput()
{
    this->ui->standardTextEdit->appendPlainText(this->runProcess->readAllStandardOutput());
}

void DialogTest::standardComplete()
{
    this->ui->standardTextEdit->appendPlainText(tr("\nThe program runs %1 millisecond.").arg(this->runTime->elapsed()));
    delete this->runTime;
}
