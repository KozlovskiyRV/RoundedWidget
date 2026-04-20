#ifndef ROUNDEDWIDGET_H
#define ROUNDEDWIDGET_H

#include <QtUiPlugin/QDesignerExportWidget>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QDebug>

class RoundedWidget : public QWidget {

    // Механизм метаобъектов (сигналы/слоты, QMetaObject, Q_PROPERTY)
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QColor titleColor READ titleColor WRITE setTitleColor NOTIFY titleColorChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBorderColor NOTIFY borderColorChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)

public:
    explicit RoundedWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setAttribute(Qt::WA_StyledBackground, true);
        setAttribute(Qt::WA_TranslucentBackground, true);
    }

    void setDisabled(bool disable);

    void setDisabledTemp(bool disable);

    void unsetDisabledTemp(void);

    QString title(void) const;
    void setTitle(QString title);

    QColor titleColor(void) const;
    void setTitleColor(QColor color);

    QColor borderColor(void) const;
    void setBorderColor(QColor color);

    QColor backgroundColor(void) const;
    void setBackgroundColor(QColor color);

    void setColor(QColor color);

signals:
    void titleChanged();
    void titleColorChanged();
    void borderColorChanged();
    void backgroundColorChanged();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    qreal letterSpacing = 1.25;
    QString iTitle = "";
    QColor iBorderColor = QColor(30, 150, 200);
    QColor iDisabledColor = QColor(150, 150, 150);
    QColor iTitleColor = QColor(30, 150, 200);
    QColor iBackgroundColor = QColor(255, 255, 255);
    enum TitleAlignmentType {
        Left, Center, Right
    };
    quint8 titleAlignmentType = Left;
    bool tempState;
    QList<QWidget*> widgetChildren = QList<QWidget*>();
    QList<bool> childrenStates = QList<bool>();
};

#endif // ROUNDEDWIDGET_H
