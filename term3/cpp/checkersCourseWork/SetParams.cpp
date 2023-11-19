#include "SetParams.h"

void SetParams::setBackgroundColor(QColor color, QAbstractGraphicsShapeItem *item)
{
    QBrush brush;
    brush.setStyle((Qt::SolidPattern));
    brush.setColor(color);
    item->setBrush(brush);
}

void SetParams::setImage(QString imagePath, QGraphicsRectItem *item)
{
    QPixmap image(imagePath);
    QLabel *imageLabel = new QLabel();
    QGraphicsProxyWidget *pMyProxy = new QGraphicsProxyWidget(item);

    imageLabel->setPixmap(image);
    imageLabel->setAttribute(Qt::WA_TranslucentBackground);
    pMyProxy->setWidget(imageLabel);
}
