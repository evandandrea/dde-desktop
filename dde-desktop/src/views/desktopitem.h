#ifndef DESKTOPITEM_H
#define DESKTOPITEM_H

#include "widgets/elidelabel.h"
#include "dbusinterface/dbustype.h"
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

class DesktopItem;
typedef QSharedPointer<DesktopItem> DesktopItemPointer;

class DesktopItem : public QFrame
{
    Q_OBJECT

    Q_PROPERTY(bool checked READ isChecked WRITE setChecked)
    Q_PROPERTY(bool hover READ isHover WRITE setHover)
public:

    explicit DesktopItem(QWidget *parent = 0);
    explicit DesktopItem(QString icon, QString name, QWidget *parent = 0);
    explicit DesktopItem(QPixmap icon, QString name, QWidget *parent = 0);
    explicit DesktopItem(QString url, QString icon, QString name, QWidget *parent = 0);
    ~DesktopItem();

    void initUI();
    void initConnect();

    QPixmap getDesktopIcon();
    QString getDesktopName();
    QPixmap getAppGroupIcon();
    QString getUrl();
    bool isChecked();
    bool isHover();
    QString gridKey();
    DesktopItemInfo getDesktopItemInfo();
    QMap<QString, DesktopItemInfo> getAppGroupItems();

signals:
    void desktopIconChanged(QString icon);
    void desktopIconChanged(QPixmap& icon);
    void desktopNameChanged(QString name);
    void hoverChanged(bool hover);
    void checkedChanged(bool checked);

public slots:
    void setDesktopIcon(QString icon);
    void setDesktopIcon(QPixmap& icon);
    void updateAppGroupIcon();
    void setDesktopName(QString name);
    void setChecked(bool checked);
    void setHover(bool hover);
    void setUrl(QString url);
    void setDesktopItemInfo(DesktopItemInfo desktopItemInfo);
    void setAppGroupItems(QMap<QString, DesktopItemInfo> items);

protected:
    void moveEvent(QMoveEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:
    QLabel* iconLabel;
    ElidedLabel* nameLabel;
    QPixmap m_desktopIcon;
    QString m_desktopName;
    QString m_url;
    bool m_checked;
    bool m_hover;
    DesktopItemInfo m_desktopItemInfo;
    QMap<QString, DesktopItemInfo> m_appGounpItems;
};

#endif // DESKTOPITEM_H
