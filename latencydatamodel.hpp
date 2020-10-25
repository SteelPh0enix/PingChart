#ifndef LATENCYDATAMODEL_HPP
#define LATENCYDATAMODEL_HPP

#include <QList>
#include <QObject>
#include <QtQml>

class LatencyDataModel : public QObject {
  Q_OBJECT
  QML_ELEMENT

  Q_PROPERTY(double maxLatency READ maxLatency NOTIFY maxLatencyChanged)
  Q_PROPERTY(double minLatency READ minLatency NOTIFY minLatencyChanged)
  Q_PROPERTY(double avgLatency READ avgLatency NOTIFY avgLatencyChanged)
  Q_PROPERTY(unsigned size READ size NOTIFY sizeChanged)
 public:
  using Iterator = QList<double>::ConstIterator;

  explicit LatencyDataModel(unsigned maxSize, QObject *parent = nullptr);

  void setMaxSize(unsigned size);
  unsigned maxSize() const;
  unsigned size() const;

  double maxLatency() const;
  double minLatency() const;
  double avgLatency() const;

  void resetStatistics();

  Iterator begin() const;
  Iterator end() const;

 public slots:
  void addLatency(double latency);
  void clear();

 signals:
  void latencyAdded(double latency);
  void maxLatencyChanged(double maxLatency);
  void minLatencyChanged(double minLatency);
  void avgLatencyChanged(double avgLatency);
  void sizeChanged(unsigned newSize);

 protected:
  void recalculateStatistics();

 private:
  unsigned m_maxSize;
  QList<double> m_latencyData;

  double m_maxLatency;
  double m_minLatency;
  double m_avgLatency;
};

#endif  // LATENCYDATAMODEL_HPP
