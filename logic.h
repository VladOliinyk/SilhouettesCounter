#ifndef LOGIC_H
#define LOGIC_H

#include <QFileDialog>
#include <QMessageBox>

#include <iostream>

#include <QTime>
#include <QPainter>

/* The global image variable for work with an image from the whole scope. */
QImage GLOBAL_IMAGE;

/* The magic number: lightness filter for clearing image process. */
int LIGHTNESS = 90;

/* The magic number: the mask -
 *  interest characteristics of the objects
 *  that will be dropped by the counter.
 */
double MINIMUM_SILHOUETTE_SIZE = 0.005;

/* The global SHOW-switcher to showing image. */
bool SHOW = true;

/* The method thаt save input image into global image variable. */
void saveImage(QImage image) {
    GLOBAL_IMAGE = image;
}

/* The method that returns global image variable. */
QImage getImage() {
    return GLOBAL_IMAGE;
}

/* The method that set the SHOW-switcher in accordance with a showRadioButton. */
void setShow(bool switcher) {
    SHOW = switcher;
}

/* The method that returns the SHOW-switcher. */
bool getShow() {
    return SHOW;
}

/* The method that shows the image on the program screen (ui.label)
 * @param ui - user interfase inherited from window;
 * @param image - image that need to show on the program screen.
 */
template <typename T>
void showImage(T ui, QImage image) {
    if (SHOW) {
        image = image.scaledToWidth(ui->scrollArea->width()-50);
        ui->label->setPixmap(QPixmap::fromImage(image));
    }
}

/* The method that fixing the image.
 * @param ui - user interfase inherited from window;
 * @param image - image that need to fix.
 * @return - fixed image.
 */
template <typename T>
QImage fixImage(T ui, QImage image) {
    ui->titleLabel->setText("Initializating...");

    int imgHeight = image.height();
    int imgWidth = image.width();

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

            // if (last pixel) { save image }
            if ((x == imgWidth-1) && (y == imgHeight-1)) {
                GLOBAL_IMAGE = tempImage;
            }
        }
    }
    ui->titleLabel->setText("Image cleared.");
    ui->findSilhButton->setEnabled(true);
    return GLOBAL_IMAGE;
}

/* The method which finds the number of silhouettes of the objects.
 *  Calls the getCountOfObj() method which doing the dirty job.
 * @param ui - user interfase inherited from window;
 * @param image - image that need to analyze.
 */
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

/* The main method of finding the number of silhouettes of the objects.
 *  Calling recursive method fillArea() to mark all the pixels of image.
 * @param ui - user interfase inherited from window;
 * @param image - image that need to analyze.
 * @return counter - count of the objects.
 */
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

/* The recursive method which marks all the pixels of image.
 *  Analyze the pixel under "cursor" with (x, y) coords.
 * @param ui - user interfase inherited from window;
 * @param image - image that need to analyze.
 * @param x - X-coord of "cursor".
 * @param y - Y-coord of "cursor".
 * @param &silhouetteSize - address to the silhouetteSize variable
 *                          which contains the number of pixels for the minimum size of a silhouette.
 */
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

#endif // LOGIC

