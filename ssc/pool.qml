import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window
{
    id: root
    visible: true
    width: 800
    height: 600

    Row
    {
        TreeViewDelegate
        {
            id: ftree

            width: 200
            height: 200
        }

        TableView
        {
            id: editor
            anchors.left: rightMargin
            width: 200
            height: 200
        }
    }
}
