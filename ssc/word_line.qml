import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

import token_block

Rectangle
{
    property var tokens: []
    property int line_width: 300
    id: wLine
    width: line_width
    height: tokens[0].height + 4
    RowLayout
    {
        id: tContainer
        anchors.fill: parent
        Repeater
        {
            model: tokens
            delegate: TokenBlock
            {
                token: modelData
                width: tContainer.width
            }
        }
    }
}