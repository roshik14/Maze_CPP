#include "mainwindow.h"

#include <QFileDialog>
#include <QTimer>

#include "../Model/Drawer/drawer.h"
#include "ui_mainwindow.h"

using s21::MainWindow;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), ui(std::make_unique<Ui::MainWindow>()), timer_(std::make_unique<QTimer>()) {
    ui->setupUi(this);
    controller_ = std::make_unique<Controller>(ui->labyrinthDrawer, ui->caveDrawer);
    ConnectSignals();
    LockButtonsOnStart();
}

MainWindow::~MainWindow() {}

void MainWindow::ConnectSignals() {
    ConnectSlotToButton(ui->newMazeButton, &MainWindow::btnClicked);
    ConnectSlotToButton(ui->openFileLabyrinthButton, &MainWindow::openFileLabyrinthBtnClicked);
    ConnectSlotToButton(ui->openFileCaveButton, &MainWindow::openFileCaveBtnClicked);
    ConnectSlotToButton(ui->writeFileLabyrinthButton, &MainWindow::WriteFileLabyrinthBtnClicked);
    ConnectSlotToButton(ui->writeFileCaveButton, &MainWindow::WriteFileCaveBtnClicked);
    ConnectSlotToButton(ui->newCaveButton, &MainWindow::btnCaveClicked);
    ConnectSlotToButton(ui->nextStepButton, &MainWindow::btnStepClicked);
    ConnectSlotToButton(ui->autoStepButton, &MainWindow::btnAutoStepClicked);
    ConnectSlotToButton(ui->stopAutoStepButton, &MainWindow::btnStopAutoStepClicked);
    connect(ui->labyrinthDrawer, &LabyrinthDrawer::findPath, this, &MainWindow::findPathSlot);
    connect(timer_.get(), &QTimer::timeout, this, &MainWindow::btnStepClicked);
}

void MainWindow::ConnectSlotToButton(QPushButton* button, BtnClickSlot slot) {
    connect(button, &QPushButton::clicked, this, slot);
}

void MainWindow::LockButtonsOnStart() {
    LockCaveButtons(false);
    ui->writeFileLabyrinthButton->setEnabled(false);
    ui->writeFileCaveButton->setEnabled(false);
}

void MainWindow::LockCaveButtons(bool state) {
    ui->nextStepButton->setEnabled(state);
    ui->autoStepButton->setEnabled(state);
    ui->stopAutoStepButton->setEnabled(state);
}

void MainWindow::btnClicked() {
    timer_->stop();
    auto width = ui->widthLabyrinthSpinBox->value();
    auto height = ui->heightLabyrinthSpinBox->value();
    controller_->GenerateMaze(width, height);
    LockCaveButtons(false);
    ui->writeFileLabyrinthButton->setEnabled(true);
}

void MainWindow::btnCaveClicked() {
    timer_->stop();
    CaveData caveData = GetCaveData();
    controller_->GenerateCave(caveData);
    LockCaveButtons(true);
    ui->writeFileCaveButton->setEnabled(true);
}

void MainWindow::btnStepClicked() {
    CaveData caveData = GetCaveData();
    controller_->CaveIterationStep(caveData.birthLimit, caveData.deathLimit);
}

void MainWindow::btnAutoStepClicked() { timer_->start(ui->periodSpinBox->value()); }

void MainWindow::btnStopAutoStepClicked() { timer_->stop(); }

void MainWindow::openFileLabyrinthBtnClicked() {
    auto name = OpenTextFile();
    if (!name.isEmpty()) {
        controller_->ReadLabyrinthFromFile(name.toStdString());
        ui->writeFileLabyrinthButton->setEnabled(true);
    }
}

void MainWindow::openFileCaveBtnClicked() {
    auto name = OpenTextFile();
    if (!name.isEmpty()) {
        controller_->ReadCaveFromFile(name.toStdString());
        ui->writeFileCaveButton->setEnabled(true);
        LockCaveButtons(true);
    }
}

QString MainWindow::OpenTextFile() {
    return QFileDialog::getOpenFileName(nullptr, QObject::tr("Open File"), "./",
                                        QObject::tr("Text files(*.txt)"));
}

void MainWindow::WriteFileLabyrinthBtnClicked() {
    auto fileName = SaveTextFile();
    if (!fileName.isEmpty()) {
        controller_->SaveLabyrinthFile(fileName.toStdString());
    }
}

void MainWindow::WriteFileCaveBtnClicked() {
    auto fileName = SaveTextFile();
    if (!fileName.isEmpty()) controller_->SaveCaveFile(fileName.toStdString());
}

QString MainWindow::SaveTextFile() {
    return QFileDialog::getSaveFileName(nullptr, QObject::tr("Save File"), "./",
                                        QObject::tr("Text files(*.txt)"));
}

void MainWindow::findPathSlot(const CoordinatePoints& coordinate) { controller_->SearchWay(coordinate); }

s21::CaveData MainWindow::GetCaveData() const {
    return CaveData{ui->widthCaveSpinBox->value(), ui->heightCaveSpinBox->value(),
                    ui->birthLimit_spinBox->value(), ui->deathLimit_spinBox->value(),
                    static_cast<unsigned>(ui->chanceSpinBox->value())};
}
