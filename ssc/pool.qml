// main.qml
import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15

ApplicationWindow {
    id: root
    visible: true
    width: 800
    height: 600

    // 绑定 C++ 后端
    vesita {
        id: backend
        onTextChanged: textArea.text = newText
    }

    ColumnLayout {
        anchors.fill: parent

        // 文本编辑区域
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: textArea
                font.family: "Monospace"
                textFormat: TextEdit.PlainText
                wrapMode: TextEdit.Wrap

                // 实时同步文本到 C++
                onTextChanged: backend.updateText(text)
            }
        }

        // 状态栏
        StatusBar {
            Label { text: backend.currentLanguage }
        }
    }
}