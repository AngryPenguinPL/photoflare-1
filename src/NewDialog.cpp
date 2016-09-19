/*

  Dialog for creating a new image.

*/

#include <cmath>
#include "NewDialog.h"
#include "ui_NewDialog.h"
#include <QTabWidget>
#include <QWidget>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <QDebug>

#include "Settings.h"

enum {PPM, PPI};
enum {PX, CM, IN};
enum {x100y100, x640y480, x800y600};

#define CM_IN_INCH 2.54f

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);

    width_px = 800;
    height_px = 600;
    imageRatio = (width_px/height_px);
    currentUnit = PX;
    ui->imageResCombo->setCurrentIndex(PPI);
    //Standard ppi
    ui->imageRvalue->setValue(96.0);
    ui->pixelWvalue->setValue(width_px);
    ui->pixelHvalue->setValue(height_px);
    ui->memoryValue->setValue((((width_px * height_px) * 3)/1024)/1024);
}

NewDialog::~NewDialog()
{
    delete ui;
}

QSize NewDialog::newImageSize() const
{
    return m_chosenSize;
}

void NewDialog::setImageSize(QSize size)
{
    ui->imageWvalue->setValue(size.width());
    ui->imageHvalue->setValue(size.height());
}

void NewDialog::on_buttonBox_accepted()
{
    m_chosenSize.setWidth(width_px);
    m_chosenSize.setHeight(height_px);
}

void NewDialog::on_imagePresetCombo_currentIndexChanged(int index)
{
    if (index == x100y100) {
        width_px = 100;
        height_px = 100;
    }
    if (index == x640y480) {
        width_px = 640;
        height_px = 480;
    }
    if (index == x800y600) {
        width_px = 800;
        height_px = 600;
    }
    on_imageWHcombo_currentIndexChanged(currentUnit);
}

void NewDialog::on_imageResCombo_currentIndexChanged(int index)
{
    if(index == PPI) {
        ui->imageRvalue->setValue(ui->imageRvalue->value() * CM_IN_INCH);
    } else {
        ui->imageRvalue->setValue(ui->imageRvalue->value() / CM_IN_INCH);
    }
}

void NewDialog::on_imageWHcombo_currentIndexChanged(int index)
{
    float resoulution_in = ui->imageRvalue->value();
    if(ui->imageResCombo->currentIndex() == PPM)
        resoulution_in = resoulution_in * CM_IN_INCH;

    if(index == PX) {
        currentUnit = index;
        ui->imageWvalue->setValue(width_px);
        ui->imageHvalue->setValue(height_px);
        ui->imageWvalue->setDecimals(0);
        ui->imageHvalue->setDecimals(0);
    } else if(index == CM) {
        currentUnit = index;
        ui->imageWvalue->setDecimals(2);
        ui->imageHvalue->setDecimals(2);
        ui->imageWvalue->setValue(width_px / resoulution_in * CM_IN_INCH);
        ui->imageHvalue->setValue(height_px / resoulution_in * CM_IN_INCH);
    } else if(index == IN) {
        currentUnit = index;
        ui->imageWvalue->setDecimals(2);
        ui->imageHvalue->setDecimals(2);
        ui->imageWvalue->setValue(width_px / resoulution_in);
        ui->imageHvalue->setValue(height_px / resoulution_in);
    }
}

void NewDialog::on_imageRvalue_valueChanged(double value)
{
    on_imageWHcombo_currentIndexChanged(currentUnit);
}

void NewDialog::on_imageHvalue_valueChanged(double value)
{
    float resoulution_in = ui->imageRvalue->value();
    if(ui->imageResCombo->currentIndex() == PPM)
        resoulution_in = resoulution_in * CM_IN_INCH;

    if(currentUnit == PX) {
        height_px = ui->imageHvalue->value();
    } else if(currentUnit == CM) {
        height_px = ui->imageHvalue->value() * resoulution_in / CM_IN_INCH;
    } else if(currentUnit == IN) {
        height_px = ui->imageHvalue->value() * resoulution_in;
    }
    ui->pixelHvalue->setValue(height_px);
    ui->memoryValue->setValue((((width_px * height_px) * 3)/1024)/1024);

    if(ui->lockedRatioButton->isChecked()) {
        if(ui->imageHvalue->hasFocus())
            ui->imageWvalue->setValue(ui->imageHvalue->value() * imageRatio); //width = height * imageRatio
    } else {
        imageRatio = (width_px/height_px);
    }
}

void NewDialog::on_imageWvalue_valueChanged(double value)
{
    float resoulution_in = ui->imageRvalue->value();
    if(ui->imageResCombo->currentIndex() == PPM)
        resoulution_in = resoulution_in * CM_IN_INCH;

    if(currentUnit == PX) {
        width_px = ui->imageWvalue->value();
    } else if(currentUnit == CM) {
        width_px = ui->imageWvalue->value() * resoulution_in / CM_IN_INCH;
    } else if(currentUnit == IN) {
        width_px = ui->imageWvalue->value() * resoulution_in;
    }
    ui->pixelWvalue->setValue(width_px);
    ui->memoryValue->setValue((((width_px * height_px) * 3)/1024)/1024);

    if(ui->lockedRatioButton->isChecked()) {
        if(ui->imageWvalue->hasFocus())
            ui->imageHvalue->setValue(ui->imageWvalue->value() / imageRatio); //height = width / imageRatio
    } else {
        imageRatio = (width_px/height_px);
    }
}