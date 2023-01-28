#define NOMINMAX
#include "stdafx.h"
#include "searchingapp.h"
#include "./ui_searchingapp.h"


using namespace std;

//QString defualtValue = "No Result Found";

QString desktopPath = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);

SearchingApp::SearchingApp(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::SearchingApp )

{
    ui->setupUi(this);

    ui->customeSearch->setChecked(true);
    ui->nameSearch->setChecked(true);
    ui->inputPath->setPlaceholderText(desktopPath);

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
    /* Declaration for Important Variables */
    QString path = ui->inputPath->toPlainText();
    QString NameFile = ui->nameInput->toPlainText();
    int max_distance = ui->spinBox->value();
    QVector<QString> results;

    if (ui->bothSearch->isChecked()) {
        if (ui->mathSearch->isChecked()) {
            QVector<QString> pathesNameFile = find_file_mathcing(NameFile,path);
            QVector<QString> pathesExtFile = get_by_ext(NameFile, path);
            results = pathesNameFile;
            results.append(pathesExtFile);
        }
        else if (ui->approxSearch->isChecked()) {

            QVector<QString> pathesNameFile = find_file_approx(NameFile, max_distance ,path);
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
    else if (ui->nameSearch->isChecked()){
        if (ui->mathSearch->isChecked()) {
            results = find_file_mathcing(NameFile, path);
            QMessageBox messageBox;
            messageBox.critical(0, "Error", "An error has occured !");
            messageBox.setFixedSize(500, 200);

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
    else {
        QMessageBox messageBox;
        messageBox.critical(0, "Error", "An error has occured !");
        messageBox.setFixedSize(500, 200);
    }

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
        ui->nameInput->setPlaceholderText("Enter Name of the file");
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

bool SearchingApp::isArabic(const QString& fileName)
{
    // Create a locale object for Arabic
    QLocale arabic(QLocale::Arabic, QLocale::Egypt);

    int length = fileName.length();
    int arab = 0;
    // Iterate through each character in the file name
    for (auto c : fileName) {

        if (c.isLetter()) {
            if (c.script() == QChar::Script_Arabic) {
                ++arab;
            }
        }

        // Check if the character is classified as a letter in the Arabic locale
    }



    return arab >= round(length / 2);
}

QVector<QString> SearchingApp::getAllLogicalDrive()
{
    QVector<QString> drives;
    QVector<char> charDrive(256);
    DWORD result = GetLogicalDriveStringsA(charDrive.size(), charDrive.data());
    if (result == 0) {
        drives.emplace_back("-1");
        return drives;
    }
    for (int i = 0; i < result; i += 4)
    {
        string drive_name(&charDrive[i], &charDrive[i + 3]);

        drives.emplace_back(fromStoQs(drive_name));
    }
    return drives;
}




string SearchingApp::removeSpaces(string str) {
    int j = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            str[j++] = str[i];
    }
    str[j] = '\0';
    return str;
}


int SearchingApp::levenshtein_distance( const string& str1, const string& str2) {
    // Create a matrix to store the distance values
    vector<vector<size_t>> distance(str1.size() + 1, vector<size_t>(str2.size() + 1));

    // Initialize the distance matrix
    for (size_t i = 0; i <= str1.size(); ++i) {
        distance[i][0] = i;
    }
    for (size_t j = 0; j <= str2.size(); ++j) {
        distance[0][j] = j;
    }

    // Fill in the distance matrix
    for (size_t i = 1; i <= str1.size(); ++i) {
        for (size_t j = 1; j <= str2.size(); ++j) {
            size_t cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
            distance[i][j] = min({ distance[i - 1][j] + 1, distance[i][j - 1] + 1, distance[i - 1][j - 1] + cost });
        }
    }

    // Return the distance value in the bottom-right corner of the matrix
    return distance[str1.size()][str2.size()];
}






QVector<QString> SearchingApp::find_file_mathcing(const QString& search_term,  const QString& path)
{
    QVector<QString> paths;
   string path_std=  path.toStdString();
    boost::filesystem::path root_path(path_std);
    if (boost::filesystem::exists(root_path) && boost::filesystem::is_directory(root_path))
    {
        for (auto const& entry : boost::filesystem::recursive_directory_iterator(root_path))
        {
            QString filename = QString::fromStdString(entry.path().filename().string());
            if (boost::filesystem::is_regular_file(entry))
                if (filename.toLower().contains(search_term.toLower()))
                {
                    paths.emplace_back(fromStoQs(entry.path().string()));
                }
        }
    }


    
return paths;
}



QString SearchingApp::fromStoQs(string str) {
    return QString::fromStdString(str);
}

string SearchingApp::fromQstoS(QString str) {
    string stre = str.toStdString();
    return stre;
}


QVector<QString> SearchingApp::find_file_approx( QString& search_term, int max_distance,  QString& root_path) {
    QVector<QString> paths;
    // Use a recursive directory iterator to visit all the files in the directory tree
    string path_std = root_path.toStdString();
    boost::filesystem::path path(path_std);

    // Iterate over the files
    if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path))
    {
        for (auto const& entry : boost::filesystem::recursive_directory_iterator(path))
        {
            string filename_std = entry.path().filename().string();
            QString filename = QString::fromStdString(filename_std);
            if (boost::filesystem::is_regular_file(entry))
            {
                if(levenshtein_distance(boost::algorithm::to_lower_copy(removeSpaces(filename_std)),
                  boost::algorithm::to_lower_copy(fromQstoS(search_term))) <= max_distance)
                {
                    paths.emplace_back(fromStoQs(entry.path().string()));
                }
            }
        }
    }


    return paths;
}





QVector<QString> SearchingApp::get_by_ext(const QString& ext, const QString& root_path) {
    QVector<QString> paths;
    string path = root_path.toStdString();
    boost::filesystem::path root(path);
    if (boost::filesystem::exists(root) && boost::filesystem::is_directory(root))
    {
        for (auto const& entry : boost::filesystem::recursive_directory_iterator(root))
        {
           
            if (boost::filesystem::is_regular_file(entry) && entry.path().extension() == ext.toStdString()) {
                QString filename = QString::fromStdString(entry.path().filename().string());

                paths.emplace_back(fromStoQs(entry.path().string()));
            }
        }


    }
    return paths;
}

//QString word = "Bonjour";
//QLocale locale(word);
//QString language = QLocale::languageToString(locale.language());
//qDebug() << "The language of the word " << word << " is " << language;
