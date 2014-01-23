#include "WorkingWindow.h"
#include "ui_WorkingWindow.h"
#include <QFont>
#include <startpage.h>
#include <QSqlQuery>
#include <QTextStream>
#include <QDir>
#include <QFile>
#include <InfoDialog.h>
#include <cstring>
#include <QIcon>
#include <QDebug>

#ifdef Q_OS_LINUX
#define DOSBOXCONST "dosbox"
#endif

#ifdef Q_OS_WIN32
#define DOSBOXCONST "dosbox.exe"
#endif

WorkingWindow::WorkingWindow(QString p,QWidget *parent) :
    QMainWindow(parent),
    // some constants
    ui(new Ui::WorkingWindow), dosbox(DOSBOXCONST), tasmDir("C:\\tasm\\"){
    // read currentProject from constructor
    currentProject = p;
    // setup ui
    ui->setupUi(this);
    // init SQLITE driver
    asmlist = QSqlDatabase::addDatabase("QSQLITE");

    // init font details
    QFont font;
    font.setFamily("Courier");
    font.setFixedPitch(true);
    font.setPointSize(12);
    // apply font to input textEdit
    ui->input->setFont(font);

    // highlight input textEdit
    highlighter = new Highlighter(ui->input->document());
    // set tabulation size to 44
    ui->input->setTabStopWidth(44);
    // focus on input box
    ui->input->setFocus();

    // set window title
    this->setWindowTitle(currentProject + " - SimpleASM by SimpleCode Developemnt");



    // current project directory
    projDir = "C:\\projects\\"+currentProject+"\\";

    /* args start */
    // default arguments for all execution modes
    defaultArgs << "-noautoexec"  << "-c" << "mount C \""+ QDir::toNativeSeparators(QCoreApplication::applicationDirPath())
                + "\"" << "-c" << "C:" // mounted to C and changed current device to C:
                << "-c"
                << tasmDir + "tasm.exe /z "+ projDir + "main.asm " + projDir
                + "main.OBJ > OUTPUT.TXT"
                <<  "-c" // executed compiling process
                << tasmDir+ "tlink.exe " +projDir + "MAIN.OBJ >> OUTPUT.TXT";
        // executed linking process
    /* args end */


    //init newFork process
    newFork = new QProcess;
    // init main file of project
    QFile mainFile(QDir::toNativeSeparators("projects/"+currentProject+"/main.asm"));
    // line - temp var for writing into input textBox
    QString line;
    // if exists just open needed file
    if(mainFile.exists())
        mainFile.open(QIODevice::ReadOnly | QIODevice::Text);
    // if not copy hello.asm to main.asm
    else{
        QFile helloFile("hello.asm");
        helloFile.open(QIODevice::ReadOnly | QIODevice::Text);
        mainFile.open(QIODevice::ReadWrite | QIODevice::Text);
        mainFile.write(helloFile.readAll());
        helloFile.close();
    }
    // writing in input from main.asm
    ui->input->clear();
    QTextStream stream(&mainFile);
    while(!stream.atEnd()){
        line = stream.readLine();
        ui->input->append(line);
    }
    mainFile.close();
    ui->saveButton->setDisabled(true);
    saved = 1;
}

WorkingWindow::~WorkingWindow(){
    delete newFork;
    delete ui;
}

void WorkingWindow::setPrjName(QString src){
    currentProject = src; // initialize project name
}

// function to search command info in database
void WorkingWindow::on_commandSearch_editingFinished(){
    if(ui->commandSearch->text() == "")
        return;
    //reset result window
    ui->commandInfo->clear();
    ui->commandInfo->append("Short info about commands");
    ui->commandInfo->append("--------------------------------------");
    //qreate DB connection

    // initialize name

    QDir::setCurrent(QCoreApplication::applicationDirPath());
    asmlist.setDatabaseName(QDir::toNativeSeparators("asmlist/asmlist.sqlite"));

    bool db_open = asmlist.open();
    if(!db_open)
        return;
    QString q = "select command, info from asms where command like '%"+
            ui->commandSearch->text().toUpper()+"%'";
    QSqlQuery query = asmlist.exec(q);
    if(query.size() == 0)
        ui->commandInfo->append("No info about: <b>"+ui->commandSearch->text()+"</b>");
    else
        while (query.next()) {
            ui->commandInfo->append("Info about <b>"+query.value("command").toString()+"</b>");
            ui->commandInfo->append("<i>"+query.value("info").toString()+"</i>");
            ui->commandInfo->append("--------------------------------------");

        }
    asmlist.close();
}
// if changed notify about save needing
void WorkingWindow::on_input_textChanged(){
    saved = 0;
    ui->saveButton->setEnabled(true);
}

void WorkingWindow::saveInput(){
    if(saved){
        ui->saveButton->setDisabled(true);
        return;
    }
    QFile file(QDir::toNativeSeparators("projects/"+currentProject+"/main.asm"));
    file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    file.write(ui->input->document()->toPlainText().toStdString().c_str());
    file.close();
    saved = 1;
    ui->saveButton->setDisabled(true);
}

// function to build and link project
// but not run
void WorkingWindow::executeMode(int job){
    // save at first
    saveInput();

    // remove old object file
    QFile objFile(QDir::toNativeSeparators("projects/"+currentProject+"/MAIN.OBJ"));
    objFile.remove();

    // load args to change
    QStringList args = defaultArgs;

    // if job == 0 just build and link

     if(job == 1){ // execution job
        QFile executable(QDir::toNativeSeparators("projects/" + currentProject + "/MAIN.EXE"));
        // if execution file exist -> add execution command to args
        if(executable.exists())
            args << "-c"
            << "C:\\projects\\"+currentProject+"\\MAIN.EXE"
            << "-c"<< "pause";
    }

    // debuging job
    else if(job == 2){
        QFile executable(QDir::toNativeSeparators("projects/" + currentProject + "/MAIN.EXE"));
        // if execution file exists -> add debug command to args
        if(executable.exists())
            args << "-c"
                 <<"C:\\tasm\\td.exe C:\\projects\\"+currentProject+"\\MAIN.EXE";
    }

    // exit when finished
    args << "-c" << "exit";


    // start execution
    newFork->start(dosbox, args);
    // waiting for finish
    // newFork->waitForFinished(-1);
    // close process
    // newFork->close();
    // qDebug() << newFork->nativeArguments();
    // read output from OUTPUT.TXT
    QFile res("OUTPUT.TXT");
    res.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream stream(&res);
    ui->output->clear();
    ui->output->append("Building and Linking Output");
    ui->output->append("-----------------------------------------------");
    QString line;
    while(!stream.atEnd()){
        line = stream.readLine();
        ui->output->append(line);
    }
    res.close();
    // truncate OUTPUT.TXT
    res.resize(0);

}

// on save button clicked
void WorkingWindow::on_saveButton_clicked(){
    saveInput();
}
// on build button clicked
void WorkingWindow::on_buildButton_clicked(){
    executeMode(0);
}

// on execute button clicked
void WorkingWindow::on_executeButton_clicked(){
    executeMode(1);
}

void WorkingWindow::on_debugButton_clicked(){
    executeMode(2);
}
// exiting function
void WorkingWindow::on_exitButton_clicked(){
    saveInput();
    this->close();
}
// info button clicked
void WorkingWindow::on_infoButton_clicked(){
    inf.show();
}
