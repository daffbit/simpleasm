#ifndef WORKINGWINDOW_H
#define WORKINGWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QSql>
#include <InfoDialog.h>
#include "Highlighter.h"
#include <QSqlDatabase>
#include <QStringList>
#include <QProcess>
namespace Ui {
class WorkingWindow;
}

class WorkingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit WorkingWindow(QString p, QWidget *parent = 0);
    void setPrjName(QString src);
    ~WorkingWindow();

private slots:
    void on_commandSearch_editingFinished();

    void on_input_textChanged();

    void on_saveButton_clicked();

    void on_buildButton_clicked();

    void on_executeButton_clicked();

    void on_debugButton_clicked();

    void on_exitButton_clicked();

    void on_infoButton_clicked();

private:
    void saveInput();
    QString currentProject;
    Ui::WorkingWindow *ui;
    InfoDialog inf;
    Highlighter *highlighter;
    bool saved;
    QSqlDatabase asmlist;
    QProcess *newFork;
    void executeMode(int job = 0);
    QStringList defaultArgs;
    const QString dosbox;
    const QString tasmDir;
    QString projDir;


};

#endif // WORKINGWINDOW_H
