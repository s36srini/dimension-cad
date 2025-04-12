#include "PreCompiled.h"
#include "RigidInsoleTaskPanel.h"
#include "ui_RigidInsole.h"

#include <Gui/Application.h>
#include <Gui/Document.h>
#include <Gui/Selection.h>
#include <Gui/SelectionObject.h>
#include <Gui/Command.h>
#include <Gui/Control.h>
#include <Base/Console.h>
#include <App/Document.h>
#include <App/DocumentObject.h>
#include <Mod/Part/App/PartFeature.h>

using namespace OrthoticCppGui;

class RigidInsoleTaskPanel::Private
{
public:
    Ui_rigidInsole ui;
    App::DocumentObject* heelPoint;
    App::DocumentObject* firstMetatarsalPoint;
    App::DocumentObject* fifthMetatarsalPoint;
    
    Private() : heelPoint(nullptr), firstMetatarsalPoint(nullptr), fifthMetatarsalPoint(nullptr) {}
};

RigidInsoleTaskPanel::RigidInsoleTaskPanel(QWidget* parent)
    : QWidget(parent)
    , d(new Private)
{
    d->ui.setupUi(this);
    
    // Connect signals and slots
    connect(d->ui.selectHeel, SIGNAL(clicked()), this, SLOT(onSelectHeel()));
    connect(d->ui.selectFirstMetatarsal, SIGNAL(clicked()), this, SLOT(onSelectFirstMetatarsal()));
    connect(d->ui.selectFifthMetatarsal, SIGNAL(clicked()), this, SLOT(onSelectFifthMetatarsal()));
    connect(d->ui.buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(d->ui.buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

RigidInsoleTaskPanel::~RigidInsoleTaskPanel()
{
    delete d;
}

void RigidInsoleTaskPanel::onSelectHeel()
{
    // Clear current selection
    Gui::Selection().clearSelection();
    
    // Update UI
    d->ui.statusHeel->setText(tr("Heel: Selecting..."));
    
    // Connect to selection change signal
    QObject::connect(
        &Gui::Selection(), SIGNAL(selectionChanged(const Gui::SelectionChanges&)),
        this, [this](const Gui::SelectionChanges& msg) {
            if (msg.Type == Gui::SelectionChanges::AddSelection) {
                // Get the selected object
                std::vector<Gui::SelectionObject> selection = Gui::Selection().getSelectionEx();
                if (!selection.empty()) {
                    App::DocumentObject* obj = selection[0].getObject();
                    if (obj) {
                        d->heelPoint = obj;
                        d->ui.statusHeel->setText(tr("Heel: Selected (%1)").arg(QString::fromLatin1(obj->Label.getValue())));
                        
                        // Disconnect from selection change signal
                        QObject::disconnect(&Gui::Selection(), nullptr, this, nullptr);
                    }
                }
            }
        }
    );
}

void RigidInsoleTaskPanel::onSelectFirstMetatarsal()
{
    // Clear current selection
    Gui::Selection().clearSelection();
    
    // Update UI
    d->ui.statusFirstMetatarsal->setText(tr("1st Metatarsal: Selecting..."));
    
    // Connect to selection change signal
    QObject::connect(
        &Gui::Selection(), SIGNAL(selectionChanged(const Gui::SelectionChanges&)),
        this, [this](const Gui::SelectionChanges& msg) {
            if (msg.Type == Gui::SelectionChanges::AddSelection) {
                // Get the selected object
                std::vector<Gui::SelectionObject> selection = Gui::Selection().getSelectionEx();
                if (!selection.empty()) {
                    App::DocumentObject* obj = selection[0].getObject();
                    if (obj) {
                        d->firstMetatarsalPoint = obj;
                        d->ui.statusFirstMetatarsal->setText(tr("1st Metatarsal: Selected (%1)").arg(QString::fromLatin1(obj->Label.getValue())));
                        
                        // Disconnect from selection change signal
                        QObject::disconnect(&Gui::Selection(), nullptr, this, nullptr);
                    }
                }
            }
        }
    );
}

void RigidInsoleTaskPanel::onSelectFifthMetatarsal()
{
    // Clear current selection
    Gui::Selection().clearSelection();
    
    // Update UI
    d->ui.statusFifthMetatarsal->setText(tr("5th Metatarsal: Selecting..."));
    
    // Connect to selection change signal
    QObject::connect(
        &Gui::Selection(), SIGNAL(selectionChanged(const Gui::SelectionChanges&)),
        this, [this](const Gui::SelectionChanges& msg) {
            if (msg.Type == Gui::SelectionChanges::AddSelection) {
                // Get the selected object
                std::vector<Gui::SelectionObject> selection = Gui::Selection().getSelectionEx();
                if (!selection.empty()) {
                    App::DocumentObject* obj = selection[0].getObject();
                    if (obj) {
                        d->fifthMetatarsalPoint = obj;
                        d->ui.statusFifthMetatarsal->setText(tr("5th Metatarsal: Selected (%1)").arg(QString::fromLatin1(obj->Label.getValue())));
                        
                        // Disconnect from selection change signal
                        QObject::disconnect(&Gui::Selection(), nullptr, this, nullptr);
                    }
                }
            }
        }
    );
}

void RigidInsoleTaskPanel::accept()
{
    // Check if all points are selected
    if (!d->heelPoint || !d->firstMetatarsalPoint || !d->fifthMetatarsalPoint) {
        Base::Console().Warning("Please select all three points before creating the rigid insole\n");
        return;
    }
    
    // Get the active document
    App::Document* doc = App::GetApplication().getActiveDocument();
    if (!doc) {
        Base::Console().Warning("No active document available\n");
        return;
    }
    
    // Create the rigid insole
    // This implementation will be replaced with actual C++ code later
    Gui::Command::doCommand(Gui::Command::Doc,
        "import Part\n"
        "# Create a boundary curve using the three selected points\n"
        "heel = FreeCAD.ActiveDocument.%s\n"
        "first_metatarsal = FreeCAD.ActiveDocument.%s\n"
        "fifth_metatarsal = FreeCAD.ActiveDocument.%s\n"
        "# Create a BSpline curve through the points\n"
        "points = [heel.Shape.Vertexes[0].Point, first_metatarsal.Shape.Vertexes[0].Point, fifth_metatarsal.Shape.Vertexes[0].Point, heel.Shape.Vertexes[0].Point]\n"
        "curve = Part.BSplineCurve()\n"
        "curve.interpolate(points)\n"
        "# Create a wire from the curve\n"
        "edge = curve.toShape()\n"
        "wire = Part.Wire(edge)\n"
        "# Create a face from the wire\n"
        "face = Part.Face(wire)\n"
        "# Create a solid from the face\n"
        "solid = face.extrude(FreeCAD.Vector(0, 0, 10))\n"
        "# Create a new object for the insole\n"
        "insole = FreeCAD.ActiveDocument.addObject('Part::Feature', 'RigidInsole')\n"
        "insole.Shape = solid\n"
        "FreeCAD.ActiveDocument.recompute()\n",
        d->heelPoint->getNameInDocument(),
        d->firstMetatarsalPoint->getNameInDocument(),
        d->fifthMetatarsalPoint->getNameInDocument());
    
    // Close the task panel
    Gui::Control().closeDialog();
}

void RigidInsoleTaskPanel::reject()
{
    // Close the task panel without creating anything
    Gui::Control().closeDialog();
}
