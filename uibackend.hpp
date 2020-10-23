#ifndef UIBACKEND_HPP
#define UIBACKEND_HPP

#include <QObject>
#include <QPoint>
#include <QString>

class UIBackend : public QObject
{
  Q_OBJECT
  Q_PROPERTY(QPoint windowPosition READ windowPosition WRITE setWindowPosition NOTIFY windowPositionChanged)
  Q_PROPERTY(QString destinationIP READ destinationIP WRITE setDestinationIP NOTIFY destinationIPChanged)
  Q_PROPERTY(double avgLatency READ avgLatency NOTIFY avgLatencyChanged);
  Q_PROPERTY(double maxLatency READ maxLatency NOTIFY maxLatencyChanged);
  Q_PROPERTY(double minLatency READ minLatency NOTIFY minLatencyChanged);

 public:
  explicit UIBackend(QObject* parent = nullptr);

  void setWindowPosition(QPoint const& newPosition);
  void setDestinationIP(QString const& newIP);

  QPoint windowPosition() const;
  QString destinationIP() const;
  double avgLatency() const;
  double minLatency() const;
  double maxLatency() const;

 signals:
  void windowPositionChanged(QPoint newPosition);
  void destinationIPChanged(QString newIP);
  void avgLatencyChanged(double newAvgLatency);
  void minLatencyChanged(double newMinLatency);
  void maxLatencyChanged(double newMaxLatency);

 private:
  QPoint m_windowPosition{};
  QString m_destinationIP{};

  double m_avgLatency{0};
  double m_minLatency{0};
  double m_maxLatency{0};
};

#endif // UIBACKEND_HPP
