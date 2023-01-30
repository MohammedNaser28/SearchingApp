#pragma once
#define NOMINMAX
#include "stdafx.h"
#include <QtWidgets/QMainWindow>
#include "./ui_searchingapp.h"
#include "helperfunction.h"
#include "worker.h"



using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui { class SearchingApp; }
QT_END_NAMESPACE
class SearchingApp : public QMainWindow
{
    Q_OBJECT

public:

    SearchingApp(QWidget* parent= nullptr);
    ~SearchingApp();

private:
    Ui::SearchingApp *ui;


private slots:
    void Search();
    void aboutSearch();
    void kindSearch();
    void spinBox();

    void updateResults(QVector<QString> results);
 
};


class MyModel : public QAbstractListModel
{
    Q_OBJECT

public:
    MyModel(QVector<QString> results, QObject* parent = nullptr) : QAbstractListModel(parent), m_results(results)
    {
    }

    // returns the number of rows in the model
    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        return m_results.size();
    }

    // returns the data for the specified index and role
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
    {
        if (!index.isValid())
            return QVariant();

        if (index.row() >= m_results.size() || index.row() < 0)
            return QVariant();

        if (role == Qt::DisplayRole)
            return m_results.at(index.row());

        return QVariant();
    }

private:
    QVector<QString> m_results;
};

