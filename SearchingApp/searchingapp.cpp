#define NOMINMAX
#include "stdafx.h"
#include "searchingapp.h"
#include "./ui_searchingapp.h"
#include "worker.h"

using namespace std;

//QString defualtValue = "No Result Found";

QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

SearchingApp::SearchingApp(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SearchingApp )

{
    ui->setupUi(this);


    ui->mathSearch->setChecked(true);
    ui->customeSearch->setChecked(true);
    ui->nameSearch->setChecked(true);
    ui->inputPath->setPlaceholderText(desktopPath);
    ui->nameInput->setPlaceholderText("Enter the Name of The file");

    ui->spinBox->setEnabled(false);
    ui->spinBox->setStyleSheet("background-color:#567189;color:#fff;");
    ui->spinBox->setValue(1);
    ui->spinBox->setMinimum(1);

    connect(ui->searchButton, SIGNAL(released()), this, SLOT(Search()));
    connect(ui->extSearch, SIGNAL(released()), this, SLOT(kindSearch()));
    connect(ui->nameSearch, SIGNAL(released()), this, SLOT(kindSearch()));
    connect(ui->bothSearch, SIGNAL(released()), this, SLOT(kindSearch()));
    connect(ui->approxSearch, SIGNAL(released()), this, SLOT(spinBox()));
    connect(ui->fullSearch, SIGNAL(released()), this, SLOT(aboutSearch()));
    connect(ui->customeSearch, SIGNAL(released()), this, SLOT(aboutSearch()));
}

SearchingApp::~SearchingApp()
{
    delete ui;
}

void SearchingApp::Search() {

    QString path = ui->inputPath->toPlainText();
    QString NameFile = ui->nameInput->toPlainText();
    int max_distance = ui->spinBox->value();

    
    // Start the search in a separate thread
    QThread* thread = new QThread();
    worker* work = new worker(path, NameFile, max_distance, ui);
    work->moveToThread(thread);
    connect(thread, &QThread::started, work, &worker::doSearch);
    connect(work, &worker::resultsReady, this, &SearchingApp::updateResults);
    connect(work, &worker::finished, thread, &QThread::quit);
    connect(work, &worker::finished, work, &worker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
    thread->start();
    
}

void SearchingApp::updateResults(QVector<QString> results)
{
    if (results.isEmpty())
        results.append("No Thing Found");

    MyModel* model = new MyModel(results);
    ui->listView->setSpacing(3);
    ui->listView->setModel(model);
    ui->listView->show();
}


void SearchingApp::aboutSearch()
{
    if (ui->fullSearch->isChecked()) {
        ui->inputPath->setEnabled(false);
        ui->inputPath->setStyleSheet("border:none;"
            "background-color:#567189;"
            "color:#fff;"
            "border-style: solid;"
            "border-radius: 12;"
            "padding: 3px;"
            "font-size: 12px;"
            "padding-left: 5px;"
            "padding-right: 5px; "
            );

    }
    else{
        ui->inputPath->setEnabled(true);
        ui->inputPath->setStyleSheet("border:none;"
            "background-color:#fff;"
            "color:#205295;"
            "border-style: solid;"
            "border-radius: 12;"
            "padding: 3px;"
            "font-size: 12px;"
            "padding-left: 5px;"
            "padding-right: 5px; "
            );
        ui->inputPath->setPlaceholderText(desktopPath);
    }


}

void SearchingApp::kindSearch()
{
    if (ui->bothSearch->isChecked()) {
        ui->nameInput->setPlaceholderText("Enter Name of the file with the extension");
    }
    else if (ui->extSearch->isChecked()) {
        ui->nameInput->setPlaceholderText("Enter  the extension with dot in first.");
    }
    else if (ui->nameSearch->isChecked()) {
        ui->nameInput->setPlaceholderText("Enter the Name of The file");
    }
}

void SearchingApp::spinBox()
{

    if (ui->approxSearch->isChecked()) {
        ui->spinBox->setEnabled(true);
        ui->spinBox->setStyleSheet(
            "QSpinBox{font-size: 12pt;}"
            "QSpinBox:up-button{ border:none; image:url(:/icons/up-white.png);width:12px;height:12px;}"
            "QSpinBox:down-button{border:none;image:url(:/icons/down-white.png);width:12px;height:12px;}"
            "QSpinBox:down-button::pressed{image:url(:/icons/down.png);background-color:#ced4da;}"
            "QSpinBox:up-button::pressed{image:url(:/icons/up.png);background-color:#ced4da;}"
        );

    }
    else {
        ui->spinBox->setEnabled(false);
        ui->spinBox->setStyleSheet(
           
            "QSpinBox{font-size: 12pt;background-color:#567189;color:#fff;}"
            "QSpinBox:up-button{ border:none; image:url(:/icons/up-white.png);width:12px;height:12px;}"
            "QSpinBox:down-button{border:none;image:url(:/icons/down-white.png);width:12px;height:12px;}"

        );
    }
}



//QString word = "Bonjour";
//QLocale locale(word);
//QString language = QLocale::languageToString(locale.language());
//qDebug() << "The language of the word " << word << " is " << language;
