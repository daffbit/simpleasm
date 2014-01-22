#include "startpage.h"
#include "ui_startpage.h"
#include <QDesktopWidget>
#include <QDir>
#include <QFileInfoList>
#include <QString>
#include <QProcess>
#include <QFile>
#include "WorkingWindow.h"

startPage::startPage(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::startPage){
    ui->setupUi(this);
    /* initialize project name to "" */
    prjName = "";
    /* removing maximize button */
    this->setWindowFlags(this->windowFlags() ^ Qt::WindowMaximizeButtonHint);
    /* focusing on project name input */
    ui->projectName->setFocus();
    /* hiding "Already existst" text and Load Existing button */
    ui->existLabel->hide();
    ui->loadButton->hide();
    /* initializing chooseCombo */
    // path for all projects
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    QDir projectsPath("projects");
    // filter  dirs only and exclude . and ..
    projectsPath.setFilter(QDir::Dirs | QDir::NoDotAndDotDot);
    // set sorting by time
    projectsPath.setSorting(QDir::Time);
    // load fileinfo list
    QFileInfoList projectList = projectsPath.entryInfoList();
    // cout projects
    int projectsCnt = projectList.size();
    // add each project to chooseCombo
    for(int i = 0; i < projectsCnt; i++){
        ui->chooseCombo->addItem(projectList.at(i).baseName());
    }

}
/* getting selected project name */
QString startPage::getPrjName(){
    return prjName;
}

startPage::~startPage(){
    delete work;
    delete ui;
}
/*
If combo changed write value
in project name text edit
*/
void startPage::on_chooseCombo_currentIndexChanged(int index){
    //if choosen "Choose project" value write ""
    if(index == 0)
        ui->projectName->setText("");
    // transfer from combo box to input value
    else
        ui->projectName->setText(ui->chooseCombo->itemText(index));
}

/* if startButton is clicked */
void startPage::on_startButton_clicked(){
    QString tempName = ui->projectName->text();
    if(tempName.size() < 1)
        return;
    prjName = tempName;
    QDir testPath("projects/"+prjName);
    /* checking if project not exists */
    if(!testPath.exists()){
        // create subdirectory with project name
        testPath.mkpath(".");
        // make main.asm file in subdir
        QFile asmFile("projects/"+prjName+"/main.asm");
        // create file and close file if successed
        if(asmFile.open(QIODevice::ReadWrite | QIODevice::Text)){
            QFile helloFile("hello.asm");
            helloFile.open(QIODevice::ReadOnly | QIODevice::Text);
            asmFile.write(helloFile.readAll());
            asmFile.close();
            helloFile.close();
        }
        else // exit programm if cant create file
            exit(1);
        startSession();
    }
    else{ // if project exists
        // unhide existing label and load button
        ui->existLabel->show();
        ui->loadButton->show();
    }

}

// if clicked loadButton
void startPage::on_loadButton_clicked(){
    if(ui->chooseCombo->findText(prjName) == -1)
        return;
    startSession();
}

void startPage::startSession(){
    // passing project name to WodkingWindow
    work = new WorkingWindow(prjName);
    // show maximized
    work->showMaximized();
    // hide choosing window
    this->hide();
}
// enter is pressed in input box
void startPage::on_projectName_editingFinished(){
    on_startButton_clicked();
}
