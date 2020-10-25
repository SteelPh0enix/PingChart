#ifndef UIBACKEND_HPP
#define UIBACKEND_HPP

#include <QObject>
#include <QPoint>
#include <QString>
#include <QVXYModelMapper>
#include <QtQml>

class UIBackend : public QObject
{
  Q_OBJECT
  QML_ELEMENT

  Q_PROPERTY(QPoint windowPosition READ windowPosition WRITE setWindowPosition NOTIFY windowPositionChanged)
  Q_PROPERTY(QString destinationIP READ destinationIP WRITE setDestinationIP NOTIFY destinationIPChanged)

 public:
  explicit UIBackend(QObject* parent = nullptr);

  void setWindowPosition(QPoint const& newPosition);
  void setDestinationIP(QString const& newIP);

  QPoint windowPosition() const;
  QString destinationIP() const;

 signals:
  void windowPositionChanged(QPoint newPosition);
  void destinationIPChanged(QString newIP);

 private:
  QPoint m_windowPosition{};
  QString m_destinationIP{};

};

#endif // UIBACKEND_HPP
