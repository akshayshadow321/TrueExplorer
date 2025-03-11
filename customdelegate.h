#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H


#include <QStyledItemDelegate>
#include <QPainter>

class CustomDelegate : public QStyledItemDelegate {
    Q_OBJECT

public:
    explicit CustomDelegate(QObject *parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    // Method to enable/disable bar graph mode
    void setBarGraphEnabled(bool enabled);

private:
    bool barGraphEnabled;
    qint64 getMaxFileSize(const QModelIndex &parent) const;  // To get the largest file size in the directory
};


#endif // CUSTOMDELEGATE_H
