/*

  Filter manager class.

  Some of the filters are implemented by ImageMagick through the Magick++ API.

*/

#include "FilterManager.h"

#include <QApplication>
#include <Magick++.h>
#include <QBuffer>
#include <QColor>
#include <QPolygon>

class FilterManagerPrivate
{
public:
    FilterManagerPrivate()
    {

    }

    ~FilterManagerPrivate()
    {

    }

    Magick::Image* fromQtImage(const QImage &image) const
    {
        // TODO: May need to convert images pixel by pixel.
        // Also need to take into account whether the image has an alpha channel or not.
        QByteArray byteArray;
        QBuffer buffer(&byteArray);
        buffer.open(QIODevice::WriteOnly);

        //Use raw format instead of JPG to avoid image format conversion and quality loss
        if (!image.save(&buffer, "PNG"))
            return 0;

        Magick::Blob blob(byteArray.data(), byteArray.length());
        return new Magick::Image(blob);
    }

    QImage toQtImage(Magick::Image *image)
    {
        Magick::Blob blob;
        image->write(&blob);

        QByteArray arr((char *)blob.data(), blob.length());
        QImage img;
        img.loadFromData(arr);

        return img;
    }
};

FilterManager* FilterManager::m_instance = 0;

FilterManager::~FilterManager()
{
    delete d;
}

FilterManager *FilterManager::instance()
{
    if (!m_instance)
        m_instance = new FilterManager;

    return m_instance;
}

QImage FilterManager::oilPaint(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->oilPaint();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::charcoal(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->charcoal();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::swirl(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->swirl(90);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::solarize(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->solarize();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::wave(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->wave();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::implode(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->implode(0.5);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::soften(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->blur(0.1,1.0);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::blur(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->blur(0.5,1.0);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::sharpen(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->sharpen(0.1,1.0);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::reinforce(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->sharpen(0.5,1.0);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::grayscale(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->type(Magick::GrayscaleType);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::oldPhoto(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->emboss(1.0,1.0);
    magickImage->type(Magick::GrayscaleType);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::fitImage(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->thumbnail(Magick::Geometry(640,400,0,0,false,false));

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::explode(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->spread(25);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::skew(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->shear(1.5,20.5);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::advFrame(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->raise(Magick::Geometry(15,15,0,0,false,false));

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::normalize(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->normalize();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::motionBlur(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->motionBlur(55.5,22.5,1.2);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::simpleFrame(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->frame(15,15,6,6);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::cropToCenter(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->extent(Magick::Geometry(640,400,0,0,false,false),Magick::Color(127,127,127),Magick::StaticGravity);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::equalizeColours(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->equalize();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::monoChromeEdges(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->edge(0.1);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::gaussianNoise(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->addNoise(Magick::GaussianNoise);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::impulseNoise(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->addNoise(Magick::ImpulseNoise);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::laplacianNoise(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->addNoise(Magick::LaplacianNoise);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::poissonNoise(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->addNoise(Magick::PoissonNoise);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::emboss(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->shade(30,30,true);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::trim(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->chop(Magick::Geometry(15,15,0,0,false,false));

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::dustreduction(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);

    magickImage->reduceNoise();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::flipHorz(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->flop();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::flipVert(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->flip();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::rotateCCW(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->rotate(270);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::rotateCW(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->rotate(90);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

static Magick::ChannelType channelById(int channelId)
{
    switch(channelId)
    {
    case 0:
        return Magick::AllChannels;
    case 1:
        return Magick::RedChannel;
    case 2:
        return Magick::GreenChannel;
    case 3:
        return Magick::BlueChannel;
    case 4:
        return Magick::CyanChannel;
    case 5:
        return Magick::MagentaChannel;
    case 6:
        return Magick::YellowChannel;
    default:
        return Magick::AllChannels;
    }
}

QImage FilterManager::setBrightness(const QImage &image, int brightness, int channelId)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->modulate(brightness + 100.0f, 100.0f, 100.0f);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::setSaturation(const QImage &image, int saturation, int channelId)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->modulate(100.0f, saturation + 100.0f, 100.0f);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::setContrast(const QImage &image, int contrast, int channelId)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->contrast(contrast);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::setGamma(const QImage &image, float agamma, int channelId)
{
    double gamma = agamma / 100.0f;
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->gamma(0, 0, gamma);

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::outsideFrame(const QImage &image, int width)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->border(Magick::Geometry(width,width,0,0,false,false));

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage.convertToFormat(QImage::Format_ARGB32_Premultiplied);
}

QImage FilterManager::deSpeckle(const QImage &image)
{
    Magick::Image *magickImage = d->fromQtImage(image);
    magickImage->despeckle();

    QImage modifiedImage = d->toQtImage(magickImage);
    delete magickImage;

    return modifiedImage;
}

QImage FilterManager::floodFill(const QImage &image, const QPoint &pos, const QColor &color)
{
    //RAII - magickImage will be deleted automatically after func return
    QScopedPointer<Magick::Image> magickImage( d->fromQtImage(image) );

    //Workaround to make it work on black color. May be it could be done more gracefully
    bool changeStartColor = (QColor(image.pixel(pos)) == QColor("black")) ? true : false;

    if(changeStartColor)
        magickImage->opaque(Magick::ColorRGB(0, 0, 0), Magick::ColorRGB(0.01f, 0, 0));

    magickImage->floodFillColor(pos.x(), pos.y(), Magick::ColorRGB(color.redF(), color.greenF(), color.blueF()));

    if(changeStartColor)
        magickImage->opaque(Magick::ColorRGB(0.01f, 0, 0), Magick::ColorRGB(0, 0, 0));

    return d->toQtImage(magickImage.data());
}

QPolygon FilterManager::selectArea(const QImage &image, const QPoint &pos, int tolerance, bool color)
{
    //RAII - magickImage will be deleted automatically after func return
    QScopedPointer<Magick::Image> magickImage( d->fromQtImage(image) );
    QScopedPointer<Magick::Image> magickImage2( d->fromQtImage(image) );

    //Workaround to make it work on black color. May be it could be done more gracefully
    bool changeStartColor = (QColor(image.pixel(pos)) == QColor("black")) ? true : false;

    Magick::Color targetColor = magickImage->pixelColor(pos.x(), pos.y());

    if(changeStartColor)
        magickImage->opaque(Magick::ColorRGB(0, 0, 0), Magick::ColorRGB(0.01f, 0, 0));

    magickImage->colorFuzz(tolerance);
    magickImage->floodFillColor(pos.x(), pos.y(), Magick::ColorRGB(0,0,0));

    QPolygon polygon;
    for(int j=0; j<magickImage->rows(); j++)
    {
        bool marked = false;
        for(int i=0; i<magickImage->columns(); i++)
        {
            if(color && magickImage->pixelColor(i,j) == targetColor)
            {
                magickImage->floodFillColor(i, j, Magick::ColorRGB(0,0,0));
            }

            if((i == magickImage->columns() - 1) && marked)
                marked = false;

            if(magickImage->pixelColor(i,j) == Magick::ColorRGB(0, 0, 0) && !marked ||
               magickImage->pixelColor(i,j) != Magick::ColorRGB(0, 0, 0) && marked )
            {
                polygon<<QPoint(i,j);
                //marked = !marked;
                break;
            }
        }
    }

    for(int j=magickImage->rows(); j>0; j--)
    {
        bool marked = false;
        for(int i=magickImage->columns(); i>0; i--)
        {
            if((i == magickImage->columns() - 1) && marked)
                marked = false;

            if(magickImage->pixelColor(i,j) == Magick::ColorRGB(0, 0, 0) && !marked ||
               magickImage->pixelColor(i,j) != Magick::ColorRGB(0, 0, 0) && marked )
            {
                polygon<<QPoint(i,j);
                //marked = !marked;
                break;
            }
        }
    }

    if(changeStartColor)
        magickImage->opaque(Magick::ColorRGB(0.01f, 0, 0), Magick::ColorRGB(0, 0, 0));

    return polygon;//d->toQtImage(magickImage2.data());
}

FilterManager::FilterManager()
    : d(new FilterManagerPrivate)
{
    Magick::InitializeMagick(qApp->applicationDirPath().toLocal8Bit());
}
