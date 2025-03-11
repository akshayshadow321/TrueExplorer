#include "customdelegate.h"
#include <QApplication>
#include <QAbstractItemModel>
#include <qabstractitemview.h>

CustomDelegate::CustomDelegate(QObject *parent)
    : QStyledItemDelegate(parent), barGraphEnabled(false) {}

void CustomDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    if (!index.isValid()) return;

    painter->save();

    // Get file size data from model (stored in Qt::UserRole + 1)
    qint64 fileSize = index.data(Qt::UserRole + 1).toLongLong();
    qint64 maxFileSize = getMaxFileSize(index.parent());  // Get largest file size in directory

    // Draw bar background if bar graph mode is enabled
    if (barGraphEnabled && maxFileSize > 0) {
        double percentage = static_cast<double>(fileSize) / maxFileSize;
        int barWidth = static_cast<int>(percentage * option.rect.width());

        QRect barRect(option.rect.x(), option.rect.y() + 5, barWidth, option.rect.height() - 10);
        painter->setBrush(QColor(100, 100, 100, 100));  // Semi-transparent grey
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(barRect, 5, 5);
    }

    // Draw the default item text and icon
    QStyledItemDelegate::paint(painter, option, index);

    painter->restore();
}

void CustomDelegate::setBarGraphEnabled(bool enabled) {
    if (barGraphEnabled != enabled) {
        barGraphEnabled = enabled;

        // Check if the parent is a valid QAbstractItemView
        QAbstractItemView *view = qobject_cast<QAbstractItemView *>(parent());
        if (view && view->viewport()) {
            view->viewport()->update();  // Force repaint
        } else {
            qDebug() << "Error: CustomDelegate parent is not a QAbstractItemView!";
        }
    }
}

qint64 CustomDelegate::getMaxFileSize(const QModelIndex &parent) const {

    qint64 maxSize = 0;
    const QAbstractItemModel *model = parent.model();

    if (!model) return maxSize;

    for (int i = 0; i < model->rowCount(parent); ++i) {
        qint64 fileSize = model->index(i, 0, parent).data(Qt::UserRole + 1).toLongLong();
        if (fileSize > maxSize) {
            maxSize = fileSize;
        }
    }
    return maxSize;
}
