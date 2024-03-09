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
{

}

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
    mXCoordinate = new QDoubleSpinBox();
    mXCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mXCoordinate, 56, 6, 2, 1);

    // spin Box for "Y"
    mYCoordinate = new QDoubleSpinBox();
    mYCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mYCoordinate, 56, 7, 2, 1);

    // spin Box for "Z"
    mZCoordinate = new QDoubleSpinBox();
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

    // central widget
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

// method trigger upon selecting "Droplet" radio button (displays its list of curves)
void Graphics::Visualizer::onDropletShapeButtonClicked()
{
    // set current shape to "Droplet"
    mCurrentShape = "Droplet";

    // get "Droplet" curvePoints and colors
    vector<Geometry::Point3D> points = mDroplet.curvePoints();
    vector<double> colors = mDroplet.curveColor();

    // clear existing curves list and adds "Droplet" curve names
    mCurvesList->clear();
    mCurvesList->addItems(Geometry::Droplet3D::CURVE_NAMES);

    // set visibility = true for curves list and label
    mCustomLabelCurves->setVisible(true);
    mCurvesList->setVisible(true);

    // set render attributes and updates renderer
    mRenderer->setRenderAttributes(points, colors, mDroplet.controlPoints());
    mRenderer->update();
}

// method trigger upon selecting "Heart" radio button (displays its list of curves)
void Graphics::Visualizer::onHeartShapeButtonClicked()
{   
    // set current shape to "Heart"
    mCurrentShape = "Heart";

    // get "Heart" curvePoints and colors
    vector<Geometry::Point3D> points = mHeart.curvePoints();
    vector<double> colors = mHeart.curveColor();    

    // clear existing curves list and adds "Heart" curve names
    mCurvesList->clear();
    mCurvesList->addItems(Geometry::Heart3D::CURVE_NAMES);

    // set visibility = true for curves list and label
    mCustomLabelCurves->setVisible(true);
    mCurvesList->setVisible(true);

    // set render attributes and updates renderer
    mRenderer->setRenderAttributes(points, colors, mHeart.controlPoints());
    mRenderer->update();
}

// method triggered upon selecting a curve from curves list (displays its list of points)
void Graphics::Visualizer::handleCurveItemSelection()
{
    // get current selected item
    QListWidgetItem* selectedItem = mCurvesList->currentItem();

    // checks if a curve is selected
    if (selectedItem)
    {
        mSelectedCurve = (selectedItem->text()).toStdString();
        vector<Geometry::Point3D> curvePoints;

        // determine curve selection (based on shape selection) and get its points 
        if (mCurrentShape == "Heart")
        {
            if (mSelectedCurve == "Top Left Curve")
            {
                curvePoints = mHeart.topLeftCurve();
            }
            else if (mSelectedCurve == "Bottom Curve")
            {
                curvePoints = mHeart.bottomCurve();
            }
            else if (mSelectedCurve == "Top Right Curve")
            {
                curvePoints = mHeart.topRightCurve();
            }
        }
        else if (mCurrentShape == "Droplet")
        {
            if (mSelectedCurve == "Left Curve")
            {
                curvePoints = mDroplet.leftCurve();
            }
            else if (mSelectedCurve == "Right Curve")
            {
                curvePoints = mDroplet.rightCurve();
            }
        }
        
        // clear points list
        mPointsList->clear();

        // iterate through all points of the selected curve and add the selected point to points list
        for (const auto& point : curvePoints)
        {
            mPointsList->addItem(QString("(%1, %2, %3)").arg(point.x()).arg(point.y()).arg(point.z()));
        } 

        // show widgets
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
        // hide widgets
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

// method triggered upon selecting a point from points list (loads point coordinates to spin boxes)
void Graphics::Visualizer::loadCoordinatesToSpinBox()
{
    // get currently selected item
    QListWidgetItem* selectedItem = mPointsList->currentItem();

    if (selectedItem)
    {
        // get text of selected item
        QString text = selectedItem->text();

        // extract x, y, z values from text & removes parentheses
        QStringList values = text.mid(1, text.length() - 2).split(", ");

        if (values.size() == 3)
        {
            // set x, y, z values in corresponding spin boxes
            mXCoordinate->setValue(values[0].toDouble());
            mYCoordinate->setValue(values[1].toDouble());
            mZCoordinate->setValue(values[2].toDouble());

            // disbaling "Add" button and enabling "Modify" button
            mAddButton->setDisabled(true);
            mModifyButton->setEnabled(true);
        }
    }
}

// method triggered upon clicing "Add" button (adds a new point to the selected curve)
void Graphics::Visualizer::onAddControlPointButtonClicked()
{
    // get text values from the spin boxes for the X, Y, and Z coordinates and assign as QString
    QString xValue = mXCoordinate->text();
    QString yValue = mYCoordinate->text();
    QString zValue = mZCoordinate->text();

    // check if the coordinate values are not empty
    if (!xValue.isEmpty() && !yValue.isEmpty() && !zValue.isEmpty())
    {
        // convert QString to double value
        double x = xValue.toDouble();
        double y = yValue.toDouble();
        double z = zValue.toDouble();

        // add input values as a control point to "mHeart" object
        if (mCurrentShape == "Heart")
        {
            mHeart.addControlPoint(Point3D(x, y, z), mSelectedCurve);
        }
        // add input values as a control point to "mDroplet" object
        else if (mCurrentShape == "Droplet")
        {
            mDroplet.addControlPoint(Point3D(x, y, z), mSelectedCurve);
        }

        // create new list item with point coordinates and add to points list
        QString newItem = QString("(%1, %2, %3)").arg(xValue, yValue, zValue);
        QListWidgetItem* item = new QListWidgetItem(newItem);
        mPointsList->addItem(item);

        // clear input fields
        mXCoordinate->clear();
        mYCoordinate->clear();
        mZCoordinate->clear();
    }
}

// method triggered upon clicing "Modify" button (modifies the selected point)
void Graphics::Visualizer::onModifyControlPointButtonClicked()
{
    // get values from the spin boxes for the X, Y, and Z coordinates
    double xValue = mXCoordinate->value();
    double yValue = mYCoordinate->value();
    double zValue = mZCoordinate->value();

    // string representation of modified point
    QString modifiedItem = QString("(%1, %2, %3)").arg(QString::number(xValue), QString::number(yValue), QString::number(zValue));

    // checks if modified item is not empty
    if (!modifiedItem.isEmpty())
    {
        // get current selected item in points list & store its index
        QListWidgetItem* selectedItem = mPointsList->currentItem();
        mSelectedPointIndex = mPointsList->row(selectedItem);

        // upon selection, update text with the modified point
        if (selectedItem)
        {
            selectedItem->setText(modifiedItem);
            double x = mXCoordinate->value();
            double y = mYCoordinate->value();
            double z = mZCoordinate->value();

          /*QString xValue = mXCoordinate->text();
            QString yValue = mYCoordinate->text();
            QString zValue = mZCoordinate->text();

            double x = xValue.toDouble();
            double y = yValue.toDouble();
            double z = zValue.toDouble();*/

            // modify control point (Heart or Droplet)
            if (mCurrentShape == "Heart")
            {
                mHeart.modifyControlPoint(Point3D(x, y, z), mSelectedCurve, mSelectedPointIndex);
            }
            else if (mCurrentShape == "Droplet")
            {
                mDroplet.modifyControlPoint(Point3D(x, y, z), mSelectedCurve, mSelectedPointIndex);
            }

            // reset spin box to 0
            mXCoordinate->setValue(0);
            mYCoordinate->setValue(0);
            mZCoordinate->setValue(0);

            // disable the "Modify" button and enable the "Add" button after modification
            mModifyButton->setDisabled(true); // Disable modifyButton after modifying the item
            mAddButton->setEnabled(true);
        }
    }

}

// method triggered upon clicing "Finish" button 
void Graphics::Visualizer::onFinishCustomizationButtonClicked()
{    
    // hide widgets
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

    // update control points and renderer attributes for "Heart" shape
    if (mCurrentShape == "Heart")
    {
        mHeart.updateControlPoints();
        mRenderer->setRenderAttributes(mHeart.curvePoints(), mHeart.curveColor(), mHeart.controlPoints());
        mRenderer->update();
    }
    // update control points and renderer attributes for "Droplet" shape
    else if (mCurrentShape == "Droplet")
    {
        mDroplet.updateControlPoints();
        mRenderer->setRenderAttributes(mDroplet.curvePoints(), mDroplet.curveColor(), mDroplet.controlPoints());
        mRenderer->update();
    }
}


