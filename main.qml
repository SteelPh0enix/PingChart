import QtQuick 2.15
import QtQuick.Window 2.15
import QtCharts 2.3

import com.steelph0enix.pingchart 1.0

Window {
    id: mainWindow
    width: 500
    height: 200
    visible: true
    title: qsTr("PingChart")

    color: "#00000000"

    flags: Qt.WA_TranslucentBackground | Qt.WindowStaysOnTopHint | Qt.FramelessWindowHint
    property color backgroundTransparentColor: "#88222222"
    property color gridColor: "#CACACA"
    property string pingedIP: uiBackend.destinationIP
    property double averagePing: latencyData.avgLatency
    property double maximumPing: latencyData.maxLatency
    property double minimumPing: latencyData.minLatency

    x: uiBackend.windowPosition.x
    y: uiBackend.windowPosition.y

    ChartView {
        id: pingChart
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: pingInfoBackground.bottom
        anchors.bottom: parent.bottom
        layer.mipmap: true
        layer.samples: 4
        layer.smooth: true
        dropShadowEnabled: false
        anchors.rightMargin: 5
        anchors.leftMargin: 5
        anchors.bottomMargin: 5
        anchors.topMargin: 5

        legend.visible: false
        margins.top: 0
        margins.bottom: 0
        margins.left: 0
        margins.right: 0

        antialiasing: true

        backgroundColor: backgroundTransparentColor
        backgroundRoundness: 1

        theme: ChartView.ChartThemeDark
        LineSeries {
            id: pingSeries

            axisX: ValueAxis {
                id: pingSeriesX
                labelsVisible: false
                min: 0
                max: latencyData.size
                gridLineColor: gridColor
                minorGridLineColor: gridColor
            }

            axisY: ValueAxis {
                id: pingSeriesY
                labelsFont.family: "Hack"
                labelsFont.bold: true
                labelsFont.pointSize: 9
                labelFormat: "%dms"
                min: latencyData.minLatency
                max: latencyData.maxLatency
                gridLineColor: gridColor
                minorGridLineColor: gridColor
            }
        }

        LatencyModelSeriesMapper {
            id: latencyDataMapper
            model: latencyData
            series: pingSeries
        }
    }

    Rectangle {
        id: pingInfoBackground
        anchors.left: parent.left
        anchors.top: parent.top
        anchors.leftMargin: 5
        anchors.topMargin: 5
        width: pingInfo.width
        height: 15

        color: backgroundTransparentColor
        Text {
            id: pingInfo
            text: qsTr("Dest: %1 | avg: %2ms | min: %3ms | max: %4ms").arg(
                      pingedIP).arg(averagePing.toLocaleString()).arg(
                      minimumPing.toLocaleString()).arg(
                      maximumPing.toLocaleString())
            font.family: "Hack"
            font.pixelSize: 12
            color: "white"
        }
    }

    MouseArea {
        property var clickPos

        CursorPositionProvider {
            id: cursorPositionProvider
        }

        id: mouseDragHelper
        anchors.fill: parent

        onPressed: {
            clickPos = {
                "x": mouse.x,
                "y": mouse.y
            }
        }

        onPositionChanged: {
            uiBackend.windowPosition.x = cursorPositionProvider.cursorPosition(
                        ).x - clickPos.x
            uiBackend.windowPosition.y = cursorPositionProvider.cursorPosition(
                        ).y - clickPos.y
        }
    }
}
