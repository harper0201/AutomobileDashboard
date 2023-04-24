import QtQuick 2.0
import QtQml.Models 2.1

Row {
    id: rowIndicators
    spacing: height * 0.2

    property alias iconModel: iconRep.model

    Repeater {
        id : iconRep
        model:IndicatorModel{}
        Rectangle{
            height: parent.height
            width: height
            color: "black"
            Image {
                id: iconImage
                anchors.fill: parent
                source: src
                visible:isvisible
            }
        }
    }

}
