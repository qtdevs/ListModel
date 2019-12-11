import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.12

import ListModelDemo 1.0

Window {
    title: qsTr("ListModelDemo")

    width: 1280
    height: 720

    visible: true

    DemoCore {
        id: core
    }

    ListView {
        id: listView
        anchors {
            fill: parent
        }

        model: core.nodes
        delegate: Item {
            width: listView.width
            height: 40

            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                    bottom: parent.bottom
                }
                height: 1
                color: "red"
            }

            Text {
                id: label
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: parent.left
                    leftMargin: 8
                }

                text: index + ":" + modelData.text
                font {
                    pixelSize: 16
                }
            }

            Row {
                anchors {
                    verticalCenter: parent.verticalCenter
                    left: label.right
                    leftMargin: 8
                }

                Button {
                    text: "Move up"
                    onClicked: {
                        core.move(index, index - 1);
                    }
                }
            }
        }
    }
}
