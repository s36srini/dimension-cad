#ifndef ORTHOTIC_GUI_RIGIDINSOLE_TASK_PANEL_H
#define ORTHOTIC_GUI_RIGIDINSOLE_TASK_PANEL_H

#include <Gui/TaskView/TaskView.h>
#include <Gui/TaskView/TaskDialog.h>
#include <QWidget>

namespace OrthoticCppGui {

class RigidInsoleTaskPanel : public QWidget, public Gui::TaskView::TaskPanel
{
    Q_OBJECT

public:
    RigidInsoleTaskPanel(QWidget* parent = nullptr);
    ~RigidInsoleTaskPanel();

    void accept();
    void reject();
    bool shouldDeleteOnClose() const { return true; }

private Q_SLOTS:
    void onSelectHeel();
    void onSelectFirstMetatarsal();
    void onSelectFifthMetatarsal();

private:
    class Private;
    Private* d;
};

} // namespace OrthoticCppGui

#endif // ORTHOTIC_GUI_RIGIDINSOLE_TASK_PANEL_H
