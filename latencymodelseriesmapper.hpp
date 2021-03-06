#ifndef LATENCYMODELSERIESMAPPER_HPP
#define LATENCYMODELSERIESMAPPER_HPP

#include <QObject>
#include <QXYSeries>
#include <QtQml>

#include "latencydatamodel.hpp"

class LatencyModelSeriesMapper : public QObject {
  Q_OBJECT
  QML_ELEMENT

  Q_PROPERTY(LatencyDataModel* model READ model WRITE setModel NOTIFY modelChanged)
  Q_PROPERTY(QtCharts::QXYSeries* series READ series WRITE setSeries NOTIFY seriesChanged)

 public:
  explicit LatencyModelSeriesMapper(QObject* parent = nullptr);

  void setModel(LatencyDataModel* model);
  void setSeries(QtCharts::QXYSeries* series);

  LatencyDataModel* model() const;
  QtCharts::QXYSeries* series() const;

 signals:
  void modelChanged(LatencyDataModel* model);
  void seriesChanged(QtCharts::QXYSeries* series);

 protected:
  void connectSignals();
  void disconnectSignals();
  void updateSeries(double newLatency);

 private:
  LatencyDataModel* m_latencyModel{nullptr};
  QtCharts::QXYSeries* m_series{nullptr};
};

#endif // LATENCYMODELCHARTMAPPER_HPP
