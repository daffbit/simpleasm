#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QMainWindow>
#include <WorkingWindow.h>
#include <QString>

namespace Ui {
class startPage;
}

class startPage : public QMainWindow
{
    Q_OBJECT

public:
    explicit startPage(QWidget *parent = 0);
    QString getPrjName();
    ~startPage();

private slots:
    void on_chooseCombo_currentIndexChanged(int index);

    void on_startButton_clicked();

    void on_loadButton_clicked();

    void on_projectName_editingFinished();

private:
    Ui::startPage *ui;
    QString prjName;
    WorkingWindow *work;
    void startSession();
};

#endif // STARTPAGE_H
