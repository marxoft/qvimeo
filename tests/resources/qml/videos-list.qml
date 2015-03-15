import QtQuick 2.0
import QVimeo 1.0

Rectangle {
    width: 800
    height: 480
    color: "#000"

    Rectangle {
        id: searchBox

        height: 50
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
            margins: 10
        }
        color: "#fff"
        border {
            width: 2
            color: "green"
        }

        TextInput {
            id: searchField

            anchors.fill: parent
            onAccepted: videosModel.list("/videos", {query: text})
        }
    }

    ListView {
        id: view

        anchors {
            left: parent.left
            right: parent.right
            top: searchBox.bottom
            topMargin: 10
            bottom: parent.bottom
        }
        clip: true
        model: ResourcesModel {
            id: videosModel

            clientId: "b73846eb250c788a08bda2458be6ae9aebfda98e"
            clientSecret: "6d6a7f4b5f013efe183f12d6e09be31051eb5eed"
            accessToken: "1016a25c36458be921de6a2325489766"
            onStatusChanged: if (status == ResourcesRequest.Failed) console.log("ResourcesModel error: " + errorString);
        }
        delegate: Item {
            width: view.width
            height: 100

            Image {
                id: image

                width: 120
                height: 90
                anchors {
                    left: parent.left
                    leftMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                source: pictures.sizes[0].link
            }

            Column {
                anchors {
                    left: image.right
                    leftMargin: 10
                    right: parent.right
                    rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                spacing: 10

                Text {
                    width: parent.width
                    elide: Text.ElideRight
                    color: "#fff"
                    text: name
                }

                Text {
                    width: parent.width
                    elide: Text.ElideRight
                    color: "#999"
                    text: "By " + user.name
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: streams.list(uri.substring(uri.lastIndexOf("/") + 1))
            }
        }
    }

    StreamsRequest {
        id: streams

        onFinished: {
            if (status == StreamsRequest.Ready) {
                for (var i = 0; i < result.length; i++) {
                    var stream = result[i];
                    console.log(stream.description + " - " + stream.width + "x" + stream.height + ": " + stream.url);
                }
            }
            else {
                console.log("StreamsRequest error: " + errorString);
            }
        }
    }
}
