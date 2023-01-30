#pragma once
#define NOMINMAX
#include "stdafx.h"
#include <iostream>
using namespace std;


QString  fromStoQs(string str);
string  fromQstoS(QString str);

bool  isArabic(const QString& fileName);

QVector<QString>  getAllLogicalDrive();




string  removeSpaces(string str);

int  levenshtein_distance(const string& str1, const string& str2);



QVector<QString>  find_file_mathcing(const QString& search_term, const QString& path);




QVector<QString>  find_file_approx(QString& search_term, int max_distance, QString& root_path);





QVector<QString>  get_by_ext(const QString& ext, const QString& root_path);