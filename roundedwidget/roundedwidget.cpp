#include "roundedwidget.h"

void RoundedWidget::setDisabled(bool disable) {
    QWidget::setDisabled(disable);

    for (QObject *child : children()) {
        QWidget *widget = qobject_cast<QWidget*>(child);
        if (widget)
            widget->setDisabled(disable);
    }
}

void RoundedWidget::setDisabledTemp(bool disable) {
    qDebug() << "set disabled temp";
    tempState = !isEnabled();
    QWidget::setDisabled(disable);

    widgetChildren.clear();
    childrenStates.clear();
    for (QObject *child : children()) {
        QWidget *widget = qobject_cast<QWidget*>(child);
        if (widget) {
            widgetChildren.append(widget);
            childrenStates.append(!widget->isEnabled());
        }
    }
}

void RoundedWidget::unsetDisabledTemp(void) {
    qDebug() << "unset disabled temp";
    QWidget::setDisabled(tempState);
    for (quint8 i = 0; i < widgetChildren.length(); i++)
        widgetChildren.at(i)->setDisabled(childrenStates.at(i));
}


QString RoundedWidget::title(void) const {
    return iTitle;
}
void RoundedWidget::setTitle(QString title) {
    this->iTitle = title;
    emit titleChanged();
    update();
}

QColor RoundedWidget::titleColor(void) const {
    return iTitleColor;
}
void RoundedWidget::setTitleColor(QColor color) {
    this->iTitleColor = color;
    emit titleColorChanged();
    update();
}

QColor RoundedWidget::borderColor(void) const {
    return iBorderColor;
}
void RoundedWidget::setBorderColor(QColor color) {
    this->iBorderColor = color;
    emit borderColorChanged();
    update();
}

QColor RoundedWidget::backgroundColor(void) const {
    return iBackgroundColor;
}
void RoundedWidget::setBackgroundColor(QColor color) {
    this->iBackgroundColor = color;
    emit backgroundColorChanged();
    update();
}

void RoundedWidget::setColor(QColor color) {
    setBorderColor(color);
    setTitleColor(color);
}


void RoundedWidget::paintEvent(QPaintEvent *event) {
    bool isDisabled = !this->isEnabled();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    QString fontName = "Corbel";
    int textSize = 10;
    int textOffsetTop = 2;
    float textSidePosition = 0.08f;
    int textPaddingH = 5;

    int borderWidth = 2;
    int borderRadius = 15;

    // Параметры текста в разрыве
    QFont font(fontName, textSize, QFont::Bold);
    font.setLetterSpacing(QFont::PercentageSpacing, letterSpacing * 100);
    painter.setFont(font);
    QFontMetrics fm(font);
    int textWidth = fm.horizontalAdvance(iTitle);
    int textHeight = fm.height();
    int verticalPos = textHeight / 2 - borderWidth + textOffsetTop;

    // Расчёт позиции разрыва рамки
    QRect rect = this->rect().adjusted(borderWidth, verticalPos, -borderWidth, -borderWidth);
    int textX = (titleAlignmentType == Center? (rect.width() - textWidth) : rect.width()) * textSidePosition;
    int textY = fm.ascent();

    // Запрет рисования в области текста
    QRegion region{this->rect()};
    QRegion gap{QRect(textX - textPaddingH, verticalPos - 0.5, textWidth + 2 * textPaddingH, borderWidth + 0.5)};
    painter.setClipRegion(region - gap);

    // Отрисовка закруглённой рамки
    QPen pen(isDisabled? iDisabledColor : iBorderColor, borderWidth);
    painter.setPen(pen);
    painter.setBrush(iBackgroundColor);
    painter.drawRoundedRect(rect, borderRadius, borderRadius);

    // Текст в разрыве
    painter.setClipRegion(region);
    painter.setBrush(Qt::transparent);
    painter.setPen(isDisabled? iDisabledColor : iTitleColor);
    painter.drawText(textX, textY, iTitle);

    // Стандартное завершение события
    QWidget::paintEvent(event);
}
