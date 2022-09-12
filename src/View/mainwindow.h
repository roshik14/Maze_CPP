#ifndef SRC_VIEW_MAINWINDOW_H_
#define SRC_VIEW_MAINWINDOW_H_

#include <QMainWindow>
#include <QPushButton>

#include "../Controller/controller.h"
#include "../coordinatepoints.h"
#include "../useful_structs.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
namespace s21 {
class MainWindow;
}
QT_END_NAMESPACE

class s21::MainWindow : public QMainWindow {
    Q_OBJECT
    using BtnClickSlot = void (MainWindow::*)();

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ConnectSignals();

private:
    void LockCaveButtons(bool);
    void LockButtonsOnStart();
    void ConnectSlotToButton(QPushButton *btn, BtnClickSlot slot);
    CaveData GetCaveData() const;
    QString OpenTextFile();
    QString SaveTextFile();

private:
    std::unique_ptr<Ui::MainWindow> ui;
    std::unique_ptr<Controller> controller_;
    std::unique_ptr<QTimer> timer_;

private slots:
    void findPathSlot(const CoordinatePoints &coordinate);
    void btnClicked();
    void btnCaveClicked();
    void btnStepClicked();
    void btnAutoStepClicked();
    void btnStopAutoStepClicked();
    void openFileLabyrinthBtnClicked();
    void openFileCaveBtnClicked();
    void WriteFileLabyrinthBtnClicked();
    void WriteFileCaveBtnClicked();
};

#endif  // SRC_VIEW_MAINWINDOW_H_
