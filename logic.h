#ifndef LOGIC_H
#define LOGIC_H

#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

#include <QTime>
#include <QPainter>

QImage GLOBAL_IMAGE;
int LIGHTNESS = 90;
double MINIMUM_SILHOUETTE_SIZE = 0.005;
int delayMS = 10;
bool SHOW = true;

template <typename T>
void showImage(T ui, QImage image);

template <typename T>
QImage fixImage(T ui, QImage image);

template <typename T>
void findSilhouettes(T ui, QImage image);

template <typename T>
int getCountOfObj(T ui, QImage image);

template <typename T>
void fillArea(T ui, QImage* image, int x, int y, int marker, int &silhouetteSize);

#endif // LOGIC

