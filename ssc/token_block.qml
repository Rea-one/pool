import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Rectangle
{
    property string token: ""
    property string token_type: ""
    property color token_color: "black"
    property int font_size: 14

    id: tBlock
    height: font_size
    width: token_text.implicitWidth + 4
    color: token_color
    Text
    {
        id: token_text
        anchors.centerIn: parent
        text: token
        font.pixelSize: font_size
    }
}