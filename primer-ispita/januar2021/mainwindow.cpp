#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "source.h"
#include "sourcethread.h"

#include <QFileDialog>
#include <QXmlStreamReader>
#include <iostream>
#include <QMutexLocker>
#include <QJsonDocument>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pbFillSources, &QPushButton::clicked, this, &MainWindow::onFillSources);
    connect(ui->pbStartTransfer, &QPushButton::clicked, this, &MainWindow::onStartTransfer);
}

MainWindow::~MainWindow()
{
    delete ui;
    qDeleteAll(m_izvori);
}

bool MainWindow::deserialize()
{
    const auto fileNames = QFileDialog::getOpenFileNames(this, "Otvori XML fajlove", "", "XML files (*.xml)");
    for (const auto& fileName : fileNames){
        QFile input(fileName);
        if (!input.open(QFile::ReadOnly))
            return false;
        QXmlStreamReader xmlStream(&input);
        xmlStream.readNextStartElement();
        while(xmlStream.readNextStartElement()){
            QVariantMap map;
            auto m_izvor = new Source;
            while(xmlStream.readNextStartElement()){
                const auto elName = xmlStream.name().toString();
                const auto elValue = xmlStream.readElementText();

                if(elName == "name")
                    map.insert("name", elValue);
                else if(elName == "volume")
                    map.insert("volume", elValue.toUInt());
            }
            m_izvor->fromQVariant(map);
            m_izvori.push_back(m_izvor);
        }

    }
    return true;
}

bool MainWindow::deserialize2() //JSON
{
    const auto fileNames = QFileDialog::getOpenFileNames(this, "JSON files", "", "JSON files (*.json)");
    for (const auto& fileName : fileNames){
        QFile input(fileName);
        if(!input.open(QFile::ReadOnly))
            return false;

        QJsonDocument doc(QJsonDocument::fromJson(input.readAll()));

        QVariantMap map = doc.toVariant().toMap();
        const auto izvori = map.value("sources").toList();
        for(const auto& izvor : izvori){
            auto izvorNov = new Source;
            izvorNov->fromQVariant(izvor);
            m_izvori.push_back(izvorNov);
        }
    }
    return true;
}

bool MainWindow::deserialize3() //binary mozda ne radi
{
    const auto fileNames = QFileDialog::getOpenFileNames(this, "JSON files", "", "JSON files (*.json)");
    for (const auto& fileName : fileNames){
        QFile input(fileName);
        if(!input.open(QFile::ReadOnly))
            return false;

        QDataStream dataStream(&input);
        QVariant variant;

        dataStream >> variant;

        QVariantMap map = variant.toMap();
        const auto izvori = map.value("sources").toList();
        for(const auto& izvor : izvori){
            auto izvorNov = new Source;
            izvorNov->fromQVariant(izvor);
            m_izvori.push_back(izvorNov);
        }
    }
    return true;
}

void MainWindow::showSources()
{
    ui->lwSources->clear();

    for(const auto izvor : m_izvori){
        ui->lwSources->addItem(izvor->toQString());
    }
}

void MainWindow::showVolume()
{
    auto total = 0u;
    for(const auto izvor : m_izvori){
        total += izvor->zapremina();
    }
    ui->leTotalVolume->setText(QString::number(total));
}

void MainWindow::onFillSources()
{
    bool success = deserialize2();
    if(!success)
        return;
    showSources();
    showVolume();
}

void MainWindow::onStartTransfer()
{
    ui->leCurrentTankVolume->setText("0");
    ui->leLoss->setText("0");

    for (const auto izvor : m_izvori){
        Q_UNUSED(izvor);

        auto thread = new SourceThread(m_izvori, &m_mutex);
        connect(thread, &SourceThread::signalST, this, &MainWindow::onSourceLostFluid);
        connect(thread, &QThread::finished, thread, &SourceThread::deleteLater);
        thread->start();
    }
}

void MainWindow::onSourceLostFluid(unsigned int lostFluid)
{
    const auto fullTankVolume = ui->leTotalTankVolume->text().toUInt();
    auto currentTankVolume = ui->leCurrentTankVolume->text().toUInt();
    auto currentLossVolume = ui->leLoss->text().toUInt();

    if (fullTankVolume > currentTankVolume + lostFluid){
        currentTankVolume += lostFluid;
        ui->leCurrentTankVolume->setText(QString::number(currentTankVolume));
    }
    else{
        ui->leCurrentTankVolume->setText(QString::number(fullTankVolume));

        const auto loss = lostFluid - (fullTankVolume - currentTankVolume);
        currentLossVolume += loss;
        ui->leLoss->setText(QString::number(currentLossVolume));
    }
    QMutexLocker lock(&m_mutex);
    for (auto i = 0; i < m_izvori.size(); ++i){
        ui->lwSources->item(i)->setText(m_izvori[i]->toQString());
    }
}

