#include "widget.h"
#include "ui_widget.h"
#include "source.h"
#include "sourcethread.h"

#include <QFileDialog>
#include <QXmlStreamReader>
#include <QMutexLocker>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->pbFillSources, &QPushButton::clicked, this, &Widget::onFillSources);
    connect(ui->pbStartTransfer, &QPushButton::clicked, this, &Widget::onStartTransfer);
}

Widget::~Widget()
{
    delete ui;
    qDeleteAll(m_sources);
}

void Widget::onFillSources()
{
    const auto success = deserializeSources();
    if(!success){
        return;
    }
    showSources();
    showTotalVolume();
}

void Widget::onStartTransfer()
{
    ui->leCurrentTank->setText("0");
    ui->leLoss->setText("0");

    for (const auto source : m_sources){
        Q_UNUSED(source);
        auto thread = new SourceThread(m_sources, &m_mutex);
        connect(thread, &SourceThread::sourceLostFluid, this, &Widget::onSourceLostFluid);
        connect(thread, &SourceThread::finished, thread, &SourceThread::deleteLater);
        thread->start();
    }
}

void Widget::onSourceLostFluid(unsigned int lostFluid)
{
    const auto fullTankVolume = ui->leTotalTank->text().toUInt();
    auto currentTankVolume = ui->leCurrentTank->text().toUInt();
    auto currentLossVolume = ui->leLoss->text().toUInt();

    if (fullTankVolume > currentTankVolume + lostFluid){
        currentTankVolume += lostFluid;
        ui->leCurrentTank->setText(QString::number(currentTankVolume));
    }
    else{
        ui->leCurrentTank->setText(QString::number(fullTankVolume));

        const auto loss = lostFluid - (fullTankVolume - currentTankVolume);
        currentLossVolume += loss;
        ui->leLoss->setText(QString::number(currentLossVolume));
    }
    QMutexLocker lock(&m_mutex);
    for (auto i = 0; i < m_sources.size(); ++i){
        ui->lwSources->item(i)->setText(m_sources[i]->toQString());
    }
}

bool  Widget::deserializeSources()
{
    const auto fileName = QFileDialog::getOpenFileName(this, "Select XML file with Sources.", "", "XML files (*.xml)");
    QFile input(fileName);
    if (!input.open(QFile::ReadOnly)){
        return false;
    }

    qDeleteAll(m_sources);
    m_sources.clear();

    QXmlStreamReader xmlStream(&input);
    xmlStream.readNextStartElement(); // cita <sources>
    while(xmlStream.readNextStartElement()){ // sve dok imamo <source>
        auto source = new Source;
        QVariantMap map;

        while(xmlStream.readNextStartElement()){ // <name> , <volume>
            const auto elementName = xmlStream.name().toString();
            const auto elementValue = xmlStream.readElementText();

            if (elementName == "name"){
                map.insert("name", elementValue);
            }
            else if (elementName == "volume"){
                map.insert("volume", elementValue.toUInt());
            }
        }
        source->fromQVariant(map);
        m_sources.push_back(source);
    }

    return true;
}

void Widget::showSources()
{
    ui->lwSources->clear();
    for(const auto source : m_sources){
        ui->lwSources->addItem(source->toQString());
    }
}

void Widget::showTotalVolume()
{
    auto totalVolume = 0u;
    for(const auto source : m_sources){
        totalVolume += source->volume();
    }
    ui->leTotalSources->setText(QString::number(totalVolume));
}

