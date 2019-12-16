import QtQuick 2.0

Item {
    width: 180
    height: 25

    Rectangle {
        id: rectangle
        color: "#1e80ea"
        radius: 3
        anchors.fill: parent

        Text {
            id: element
            color: "#eae2e2"
            text: qsTr("Button")
            anchors.fill: parent
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.family: "Arial"
            font.pixelSize: 16
        }
    }

}

/*##^##
Designer {
    D{i:2;anchors_x:67;anchors_y:4}D{i:1;anchors_height:25;anchors_width:180;anchors_x:0;anchors_y:0}
}
##^##*/
