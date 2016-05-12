#include "logic.h"


template <typename T>
void showImage(T ui, QImage image) {
    if (SHOW) {
        image = image.scaledToWidth(ui->scrollArea->width()-50);
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

template <typename T>
QImage fixImage(T ui, QImage image) {
    ui->titleLabel->setText("Initializating...");

    int imgHeight = image.height();
    int imgWidth = image.width();

    //QImage newImage(imgHeight, imgWidth, QImage::Format_RGB32);
    //newImage = image;

    //      white - qRgb(255, 255, 255);
    //      black - qRgb(0, 0, 0);
    //        red - qRgb(255, 0, 0);
    //     yellow - qRgb(255, 255, 0);

    ui->titleLabel->setText("Clearing image...");

    for (int x = 0; x < imgWidth; x++) {
        if (SHOW) {
            std::cout << (  (x*100)/imgWidth  ) << std::endl;
        }
        for (int y = 0; y < imgHeight; y++) {

            QImage tempImage = image;

            //set yellow cursor
            if (SHOW) {
                tempImage.setPixel(x, y, qRgb(255, 255, 0));
                showImage(ui, tempImage);
            }
            //small pause
            delay(ui);
            //clearing current pixel
            QColor curPixCol = image.pixel(x, y);
            if (curPixCol.lightness() >= LIGHTNESS) {
                image.setPixel(x, y, qRgb(255, 255, 255));
            } else {
                image.setPixel(x, y, qRgb(0, 0, 0));
            }

            if (SHOW) {
                //repaint image
                showImage(ui, tempImage);
            }

            if ((x == imgWidth-1) && (y == imgHeight-1)) {
                GLOBAL_IMAGE = tempImage;
            }
        }
    }
    ui->titleLabel->setText("Image cleared.");
    ui->findSilhButton->setEnabled(true);
    return GLOBAL_IMAGE;
}

template <typename T>
void findSilhouettes(T ui, QImage image) {
    ui->titleLabel->setText("Searching for silhouettes...");
    int counter = getCountOfObj(ui, image);
    ui->titleLabel->setText(" ");

    QString finalStr = "Here I found " + QString::number(counter) + " objects.";

    QMessageBox msgBox;
    msgBox.setText("Done!");
    msgBox.setInformativeText(finalStr);
    msgBox.exec();
}

template <typename T>
int getCountOfObj(T ui, QImage image) {
    int counter = 0;

    int imgHeight = image.height();
    int imgWidth = image.width();

    /* Calculating the MINIMUM_SILHOUETTE_SIZE given the image size */
    MINIMUM_SILHOUETTE_SIZE = (imgHeight*imgWidth) * MINIMUM_SILHOUETTE_SIZE;

    for (int y = 0; y < imgHeight; y++) {
        for (int x = 0; x < imgWidth; x++) {
            QColor curPixCol = image.pixel(x, y);
            //set yellow cursor
            if (SHOW) {
                QImage tempImage = image;
                tempImage.setPixel(x, y, qRgb(255, 0, 255));
                showImage(ui, tempImage);
                delay(ui);
            }
            if (curPixCol.black() > 230) {
                int silhouetteSize = 0;
                fillArea(ui, &image, x, y, counter+1, silhouetteSize);
                if (silhouetteSize >= MINIMUM_SILHOUETTE_SIZE) {
                    counter++;
                    //ui->titleLabel->setText(QString::number(counter));
                    GLOBAL_IMAGE = image;
                }
            }
        }
    }

    return counter;
}

template <typename T>
void fillArea(T ui, QImage* image, int x, int y, int marker, int &silhouetteSize) {

    QColor curPixCol = image->pixel(x, y);
    int imgHeight = image->height();
    int imgWidth = image->width();


    //set yellow cursor
    if (SHOW) {
        QImage tempImage = *image;
        tempImage.setPixel(x, y, qRgb(255, 255, 0));
        showImage(ui, tempImage);
        delay(ui);
    }

    if ( (x > 0) &&
         (x < imgWidth-1) &&
         (y > 0) &&
         (y < imgHeight-1) &&
         (curPixCol.black() > 240) )
    {

        if (curPixCol.black() > 240) {
            image->setPixel(x, y, qRgb(220, 0, 0));

            showImage(ui, *image);

            delay(ui);

            silhouetteSize++;

            fillArea(ui, image, x+1, y, marker, silhouetteSize); // right
            fillArea(ui, image, x-1, y, marker, silhouetteSize); // left
            fillArea(ui, image, x, y+1, marker, silhouetteSize); // down
            fillArea(ui, image, x, y-1, marker, silhouetteSize); // up
        } else {
            return;
        }

    }
}
