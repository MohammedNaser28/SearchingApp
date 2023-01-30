#pragma once
#include "stdafx.h"
#include "searchingapp.h"
#include "helperfunction.h"
#include "./ui_searchingapp.h"
#include <qobject.h>

class worker :
    public QObject
{
    Q_OBJECT;
public:
    worker(QString path, QString NameFile, int max_distance, Ui::SearchingApp* ui);

public slots:
    void doSearch();
signals:
    void finished();

signals:
    void resultsReady(QVector<QString> results);

private:
    QString path;
    QString NameFile;
    int max_distance;
    Ui::SearchingApp* ui;


};
