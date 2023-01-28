#pragma once
//levenshtein_distance
#define NOMINMAX

#include <QtWidgets/QMainWindow>
#include "./ui_searchingapp.h"
#include <boost/filesystem.hpp>
#include <QString>
#include <QLocale>
#include <QChar>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/range/combine.hpp>
#include <boost/filesystem.hpp>
#include <cmath>
#include <QAbstractListModel>
#include <QApplication>
#include <QVariant>
#include <cstring>
#include <QStandardPaths>
#include <Windows.h>


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
    bool isArabic(const QString& fileName);


    QVector<QString> getAllLogicalDrive();


    string removeSpaces(string str);


    string fromQstoS(QString str);

    QString fromStoQs(string str);
    QVector<QString> get_by_ext(const QString& ext, const QString& root);
    QVector<QString> find_file_approx( QString& search_term, int max_distance,  QString& root_path);
    QVector<QString> find_file_mathcing(const QString& search_term, const QString& path);
    int levenshtein_distance( const string& str1, const  string& str2);
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

