#pragma once
#define NOMINMAX
#include "stdafx.h"
#include <iostream>
#include "helperfunction.h"
using namespace std;


QString  fromStoQs(string str) {
    return QString::fromStdString(str);
}

string  fromQstoS(QString str) {
    string stre = str.toStdString();
    return stre;
}


bool  isArabic(const QString& fileName)
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

QVector<QString>  getAllLogicalDrive()
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




string  removeSpaces(string str) {
    int j = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
            str[j++] = str[i];
    }
    str[j] = '\0';
    return str;
}


int  levenshtein_distance(const string& str1, const string& str2) {
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






QVector<QString>  find_file_mathcing(const QString& search_term, const QString& path)
{
    QVector<QString> paths;
    string path_std = path.toStdString();
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




QVector<QString>  find_file_approx(QString& search_term, int max_distance, QString& root_path) {
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
                if (levenshtein_distance(boost::algorithm::to_lower_copy(removeSpaces(filename_std)),
                    boost::algorithm::to_lower_copy(fromQstoS(search_term))) <= max_distance)
                {
                    paths.emplace_back(fromStoQs(entry.path().string()));
                }
            }
        }
    }


    return paths;
}





QVector<QString>  get_by_ext(const QString& ext, const QString& root_path) {
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