#include "stdafx.h"
#include "worker.h"


worker::worker(QString path, QString NameFile, int max_distance, Ui::SearchingApp* ui)
    : path(path), NameFile(NameFile), max_distance(max_distance), ui(ui) {}

void worker::doSearch()
{
    /* Declaration for Important Variables */
    QString path = ui->inputPath->toPlainText();
    QString NameFile = ui->nameInput->toPlainText();
    int max_distance = ui->spinBox->value();
    QVector<QString> results;

    if (ui->bothSearch->isChecked()) {
        if (ui->mathSearch->isChecked()) {
            QVector<QString> pathesNameFile = find_file_mathcing(NameFile, path);
            QVector<QString> pathesExtFile = get_by_ext(NameFile, path);
            results = pathesNameFile;
            results.append(pathesExtFile);
        }
        else if (ui->approxSearch->isChecked()) {

            QVector<QString> pathesNameFile = find_file_approx(NameFile, max_distance, path);
            QVector<QString> pathesExtFile = get_by_ext(NameFile, path);

            results = pathesNameFile;
            results.append(pathesExtFile);
        }
        else if (ui->mathSearch->isChecked() && ui->approxSearch->isChecked())
        {
            QVector<QString> pathesNameFileMatch = find_file_mathcing(NameFile, path);
            QVector<QString> pathesExtFileMatch = get_by_ext(NameFile, path);
            QVector<QString> pathesNameFileApprox = find_file_approx(NameFile, max_distance, path);
            QVector<QString> pathesExtFileApprox = get_by_ext(NameFile, path);
            results = pathesNameFileMatch;
            results.append(pathesNameFileApprox);
            results.append(pathesExtFileMatch);
            results.append(pathesExtFileApprox);
        }
    }
    else if (ui->extSearch->isChecked()) {

        results = get_by_ext(NameFile, path);

    }
    else if (ui->nameSearch->isChecked()) {
        if (ui->mathSearch->isChecked()) {
            results = find_file_mathcing(NameFile, path);


        }
        else if (ui->approxSearch->isChecked()) {

            results = find_file_approx(NameFile, max_distance, path);

        }
        else if (ui->mathSearch->isChecked() && ui->approxSearch->isChecked())
        {
            QVector<QString> pathesNameFileMatch = find_file_mathcing(NameFile, path);
            QVector<QString> pathesNameFileApprox = find_file_approx(NameFile, max_distance, path);
            results = pathesNameFileMatch;
            results.append(pathesNameFileApprox);
        }
    }

    emit finished();
    emit resultsReady(results);

}
