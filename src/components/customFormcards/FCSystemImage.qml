import QtQuick
// import QtQuick.Layouts
import org.kde.kirigamiaddons.formcard as FC

FC.FormCard {
    id: root
    required property string url
    required property string name
    required property list<string> tags
    required property list<string> features

    FormDelegateCollapsible {
        text: root.features.join(", ")
        description: `${root.url}/${root.name}`

        Repeater {
            model: root.tags
            delegate: FC.FormButtonDelegate {
                text: modelData

                onClicked: {
                    console.log(`${root.url}/${root.name}:${modelData}`);
                }
            }
        }
    }
}
