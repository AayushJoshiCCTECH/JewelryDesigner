#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"


Graphics::Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();

    mCurvesList->setVisible(false);
    mPointsList->setVisible(false);
    mCustomLabelCurves->setVisible(false);
    mCustomLabelPoints->setVisible(false);
    mCustomLabelX->setVisible(false);
    mCustomLabelY->setVisible(false);
    mCustomLabelZ->setVisible(false);
    mAddButton->setVisible(false);
    mModifyButton->setVisible(false);
    mXCoordinate->setVisible(false);
    mYCoordinate->setVisible(false);
    mZCoordinate->setVisible(false);
    mFinishButton->setVisible(false);    
}

Graphics::Visualizer::~Visualizer()
{}

void Graphics::Visualizer::setupUi()
{
    resize(900, 800);
    mGridLayout = new QGridLayout(this);
    QFont font("Arial", 12);
    font.setBold(true);

    // window
    mRenderer = new OpenGLWindow(QColor(1, 1, 0), this);
    mGridLayout->addWidget(mRenderer, 0, 0, 100, 6);

    // shape options
    mShapeLabel = new QLabel("Choose Shape");
    mShapeLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mShapeLabel, 11, 6, 2, 3);
    mShapeLabel->setFont(font);

    // droplet button
    mDropletShapeButton = new QRadioButton("Droplet", this);
    mGridLayout->addWidget(mDropletShapeButton, 15, 6, 1, 1.5);
    mDropletShapeButton->setFont(font);

    // heart button
    mHeartShapeButton = new QRadioButton("Heart", this);
    mGridLayout->addWidget(mHeartShapeButton, 15, 7, 1, 1.5);
    mHeartShapeButton->setFont(font);

    // curve text label
    mCustomLabelCurves = new QLabel("Curves List");
    mCustomLabelCurves->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mCustomLabelCurves, 27, 6, 2, 3);
    mCustomLabelCurves->setFont(font);

    // curves list
    mCurvesList = new QListWidget();
    mGridLayout->addWidget(mCurvesList, 30, 6, 2, 3);

    // point text label
    mCustomLabelPoints = new QLabel("Points List");
    mCustomLabelPoints->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mCustomLabelPoints, 44, 6, 2, 3);
    mCustomLabelPoints->setFont(font);

    // points list
    mPointsList = new QListWidget();
    mGridLayout->addWidget(mPointsList, 48, 6, 2, 3);

    // "X" text label  
    mCustomLabelX = new QLabel("X");
    mCustomLabelX->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabelX, 53, 6, 2, 1);
    mCustomLabelX->setFont(font);

    // "Y" text label
    mCustomLabelY = new QLabel("Y");
    mCustomLabelY->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabelY, 53, 7, 2, 1);
    mCustomLabelY->setFont(font);

    // "Z" text label
    mCustomLabelZ = new QLabel("Z");
    mCustomLabelZ->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabelZ, 53, 8, 2, 1);
    mCustomLabelZ->setFont(font);

    // spin Box for "X"
    mXCoordinate = new QSpinBox();
    mXCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mXCoordinate, 56, 6, 2, 1);

    // spin Box for "Y"
    mYCoordinate = new QSpinBox();
    mYCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mYCoordinate, 56, 7, 2, 1);

    // spin Box for "Z"
    mZCoordinate = new QSpinBox();
    mZCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mZCoordinate, 56, 8, 2, 1);

    // add button
    mAddButton = new QPushButton("Add", this);
    mGridLayout->addWidget(mAddButton, 60, 6, 2, 1.5);
    mAddButton->setFont(font);

    // modify button
    mModifyButton = new QPushButton("Modify", this);
    mModifyButton->setDisabled(true);
    mModifyButton->setFont(font);
    mGridLayout->addWidget(mModifyButton, 60, 7, 2, 1.5);


    // finish button
    mFinishButton = new QPushButton("Finish", this);
    mGridLayout->addWidget(mFinishButton, 80, 6, 2, 3);
    mFinishButton->setFont(font);
    mFinishButton->clicked();
    mFinishButton->setStyleSheet("background-color: skyblue");

    mWidget = new QWidget(this);
    mWidget->setLayout(mGridLayout);
    setCentralWidget(mWidget);

    // signal-slot connections
    connect(mDropletShapeButton, &QRadioButton::clicked, this, &Visualizer::onDropletShapeButtonClicked);
    connect(mHeartShapeButton, &QRadioButton::clicked, this, &Visualizer::onHeartShapeButtonClicked);

    connect(mCurvesList, &QListWidget::clicked, this, &Visualizer::handleCurveItemSelection);
    connect(mPointsList, &QListWidget::clicked, this, &Visualizer::loadCoordinatesToSpinBox);

    connect(mAddButton, &QPushButton::clicked, this, &Visualizer::onAddControlPointButtonClicked);
    connect(mModifyButton, &QPushButton::clicked, this, &Visualizer::onModifyControlPointButtonClicked);
    connect(mFinishButton, &QPushButton::clicked, this, &Visualizer::onFinishCustomizationButtonClicked);
   
    setWindowTitle(QCoreApplication::translate("Visualiser", "JewelCraft - Customize Your Sparkle", nullptr));
}

// selects "Droplet" radio button and displays its list of curves
void Graphics::Visualizer::onDropletShapeButtonClicked()
{
    mCurrentShape = "Droplet";

    vector<Geometry::Point3D> points = mDroplet.curvePoints();
    vector<double> colors = mDroplet.curveColor();

    mCurvesList->clear();
    mCurvesList->addItems(Geometry::Droplet3D::CURVE_NAMES);

    mCustomLabelCurves->setVisible(true);
    mCurvesList->setVisible(true);

    mRenderer->setRenderAttributes(points, colors);
    mRenderer->update();
}

// selects "Heart" radio button and displays its list of curves
void Graphics::Visualizer::onHeartShapeButtonClicked()
{   
    mCurrentShape = "Heart";

    vector<Geometry::Point3D> points = mHeart.curvePoints();
    vector<double> colors = mHeart.curveColor();    

    mCurvesList->clear();
    mCurvesList->addItems(Geometry::Heart3D::CURVE_NAMES);

    mCustomLabelCurves->setVisible(true);
    mCurvesList->setVisible(true);

    mRenderer->setRenderAttributes(points, colors);
    mRenderer->update();
}

// selects a curve from curves list and displays its list of points
void Graphics::Visualizer::handleCurveItemSelection()
{
    QListWidgetItem* selectedItem = mCurvesList->currentItem();

    if (selectedItem)
    {
        QString selectedCurve = selectedItem->text();
        vector<Geometry::Point3D> curvePoints;

        if (mCurrentShape == "Heart")
        {
            if (selectedCurve == "Top Left Curve")
            {
                curvePoints = mHeart.topLeftCurve();
            }
            else if (selectedCurve == "Bottom Curve")
            {
                curvePoints = mHeart.bottomCurve();
            }
            else if (selectedCurve == "Top Right Curve")
            {
                curvePoints = mHeart.topRightCurve();
            }
        }
        else if (mCurrentShape == "Droplet")
        {
            if (selectedCurve == "Left Curve")
            {
                curvePoints = mDroplet.leftCurve();
            }
            else if (selectedCurve == "Right Curve")
            {
                curvePoints = mDroplet.rightCurve();
            }
        }

        mPointsList->clear();
        for (const auto& point : curvePoints)
        {
            mPointsList->addItem(QString("(%1, %2, %3)").arg(point.x()).arg(point.y()).arg(point.z()));
        }

        mCustomLabelPoints->setVisible(true);
        mPointsList->setVisible(true);
        mCustomLabelX->setVisible(true);
        mCustomLabelY->setVisible(true);
        mCustomLabelZ->setVisible(true);
        mXCoordinate->setVisible(true);
        mYCoordinate->setVisible(true);
        mZCoordinate->setVisible(true);
        mAddButton->setVisible(true);
        mModifyButton->setVisible(true);
        mFinishButton->setVisible(true);
    }
    else
    {
        mCustomLabelPoints->setVisible(false);
        mPointsList->setVisible(false);
        mCustomLabelX->setVisible(false);
        mCustomLabelY->setVisible(false);
        mCustomLabelZ->setVisible(false);
        mXCoordinate->setVisible(false);
        mYCoordinate->setVisible(false);
        mZCoordinate->setVisible(false);
        mAddButton->setVisible(false);
        mModifyButton->setVisible(false);
        mFinishButton->setVisible(false);
    }
}

// loads point coordinates selected from points list to spin box for (X, Y, Z)
void Graphics::Visualizer::loadCoordinatesToSpinBox()
{
    // gets currently selected item
    QListWidgetItem* selectedItem = mPointsList->currentItem();

    if (selectedItem)
    {
        // gets text of selected item
        QString text = selectedItem->text();

        // extracts x, y, z values from text & removes parentheses
        QStringList values = text.mid(1, text.length() - 2).split(", ");

        if (values.size() == 3)
        {
            // sets x, y, z values in corresponding spin boxes
            mXCoordinate->setValue(values[0].toInt());
            mYCoordinate->setValue(values[1].toInt());
            mZCoordinate->setValue(values[2].toInt());

            mAddButton->setDisabled(true);
            mModifyButton->setEnabled(true);
        }
    }
}

// adds a new point to the selected curve
void Graphics::Visualizer::onAddControlPointButtonClicked()
{
    vector<Geometry::Point3D> points = mHeart.curvePoints();
    vector<double> colors = mHeart.curveColor();
    mHeart.addControlPoint(Point3D(0, 0, 0));
}
//
//void Graphics::Visualizer::onAddControlPointButtonClicked()
//{
//    QString xValue = mXCoordinate->text();
//    QString yValue = mYCoordinate->text();
//    QString zValue = mZCoordinate->text();
//
//    if (!xValue.isEmpty() && !yValue.isEmpty() && !zValue.isEmpty())
//    {
//        QString newItem = QString("(%1, %2, %3)").arg(xValue, yValue, zValue);
//        QListWidgetItem* item = new QListWidgetItem(newItem);
//
//        mPointsList->addItem(item);
//        mXCoordinate->clear();
//        mYCoordinate->clear();
//        mZCoordinate->clear();
//    }
//}

//void Graphics::Visualizer::onAddControlPointButtonClicked()
//{
//    QString xValue = mXCoordinate->text();
//    QString yValue = mYCoordinate->text();
//    QString zValue = mZCoordinate->text();
//
//    if (!xValue.isEmpty() && !yValue.isEmpty() && !zValue.isEmpty())
//    {
//        double x = xValue.toDouble();
//        double y = yValue.toDouble();
//        double z = zValue.toDouble();
//
//        // Add the input values as a control point to the mHeart object
//        mHeart.addControlPoint(Geometry::Point3D(x, y, z));
//
//        // Update the UI list
//        QString newItem = QString("(%1, %2, %3)").arg(xValue, yValue, zValue);
//        QListWidgetItem* item = new QListWidgetItem(newItem);
//        mPointsList->addItem(item);
//
//        // Clear the input fields
//        mXCoordinate->clear();
//        mYCoordinate->clear();
//        mZCoordinate->clear();
//    }
//}

// updates coordinates of selected point
void Graphics::Visualizer::onModifyControlPointButtonClicked()
{
    int xValue = mXCoordinate->value();
    int yValue = mYCoordinate->value();
    int zValue = mZCoordinate->value();

    QString modifiedItem = QString("(%1, %2, %3)").arg(QString::number(xValue), QString::number(yValue), QString::number(zValue));

    if (!modifiedItem.isEmpty())
    {
        QListWidgetItem* selectedItem = mPointsList->currentItem();

        if (selectedItem)
        {
            selectedItem->setText(modifiedItem);
            mXCoordinate->setValue(0);
            mYCoordinate->setValue(0);
            mZCoordinate->setValue(0);

            mModifyButton->setDisabled(true); // Disable modifyButton after modifying the item
            mAddButton->setEnabled(true);
        }
    }

}

// disables add, mofidy and points list and spin boxes
void Graphics::Visualizer::onFinishCustomizationButtonClicked()
{
    mAddButton->setVisible(false);
    mModifyButton->setVisible(false);
    mPointsList->setVisible(false);
    mXCoordinate->setVisible(false);
    mYCoordinate->setVisible(false);
    mZCoordinate->setVisible(false);
    mCustomLabelX->setVisible(false);
    mCustomLabelY->setVisible(false);
    mCustomLabelZ->setVisible(false);
    mCustomLabelPoints->setVisible(false);
    mFinishButton->setVisible(false);
}