#ifndef UIBACKEND_HPP
#define UIBACKEND_HPP

#include <QObject>
#include <iostream>

class UIBackend : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QPoint windowPosition READ windowPosition WRITE setWindowPosition NOTIFY windowPositionChanged)
 public:
  explicit UIBackend(QObject *parent = nullptr);

  void setWindowPosition(QPoint newPosition);
  QPoint windowPosition() const;

 signals:
  void windowPositionChanged(QPoint newPosition);

 private:
  QPoint m_windowPosition;
};

#endif // UIBACKEND_HPP
