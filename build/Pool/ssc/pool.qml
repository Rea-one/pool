import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15

Window
{
    property var pool: vesita
    id: root
    visible: true
    width: 800
    height: 600

    Row
    {
        TreeView
        {
            id: ftree

            width: 200
            height: 200
        }
        Rectangle
        {
            width: 10
            height: editor.height
        }
        TextEdit
        {
            id: editor
            anchors.left: ftree.right
            width: 200
            height: 200
        }
    }
}
