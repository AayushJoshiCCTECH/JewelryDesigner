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
    mAddButton->setVisible(false);
    mModifyButton->setVisible(false);
    mXCoordinateLabel->setVisible(false);
    mYCoordinateLabel->setVisible(false);
    mZCoordinateLabel->setVisible(false);
    mXCoordinate->setVisible(false);
    mYCoordinate->setVisible(false);
    mZCoordinate->setVisible(false);
    mResetButton->setVisible(false);
    mSaveImageButton->setVisible(false);
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
    mGridLayout->addWidget(mRenderer, 0, 0, 100, 8);

    // shape options
    mShapeLabel = new QLabel("Choose Shape");
    mShapeLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mShapeLabel, 2, 8, 2, 1);
    mShapeLabel->setFont(font);

    // droplet button
    mDropletShapeButton = new QRadioButton("Droplet", this);
    mGridLayout->addWidget(mDropletShapeButton, 5, 8, 1, 1);
    mDropletShapeButton->setFont(font);

    // heart button
    mHeartShapeButton = new QRadioButton("Heart", this);
    mGridLayout->addWidget(mHeartShapeButton, 6, 8, 1, 1);
    mHeartShapeButton->setFont(font);

    // curve text label
    mCustomLabelCurves = new QLabel("Curves List");
    mCustomLabelCurves->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mCustomLabelCurves, 10, 8, 1, 1);
    mCustomLabelCurves->setFont(font);

    // curves list
    mCurvesList = new QListWidget();
    mGridLayout->addWidget(mCurvesList, 11, 8, 1, 1);
    mCurvesList->setFixedWidth(100);
    mCurvesList->setFixedHeight(100);

    // point text label
    mCustomLabelPoints = new QLabel("Points List");
    mCustomLabelPoints->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mCustomLabelPoints, 15, 8, 1, 1);
    mCustomLabelPoints->setFont(font);

    // points list
    mPointsList = new QListWidget();
    mGridLayout->addWidget(mPointsList, 16, 8, 1, 1);
    mPointsList->setFixedWidth(100);
    mPointsList->setFixedHeight(100);

    // "X" coordinate label
    mXCoordinateLabel = new QLabel("X: ");
    mXCoordinateLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mXCoordinateLabel, 20, 8, 1, 1);
    mXCoordinateLabel->setFont(font);

    // spin Box for "X"
    mXCoordinate = new QSpinBox();
    mXCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mXCoordinate, 21, 8, 1, 1);
    //mXCoordinate->setPrefix("X: ");

    // "Y" coordinate label
    mYCoordinateLabel = new QLabel("Y: ");
    mYCoordinateLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mYCoordinateLabel, 22, 8, 1, 1);
    mYCoordinateLabel->setFont(font);

    // spin Box for "Y"
    mYCoordinate = new QSpinBox();
    mYCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mYCoordinate, 23, 8, 1, 1);
    //mYCoordinate->setPrefix("Y: ");

    // "Z" coordinate label
    mZCoordinateLabel = new QLabel("Z: ");
    mZCoordinateLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mZCoordinateLabel, 24, 8, 1, 1);
    mZCoordinateLabel->setFont(font);

    // spin Box for "Z"
    mZCoordinate = new QSpinBox();
    mZCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mZCoordinate, 25, 8, 1, 1);
    //mZCoordinate->setPrefix("Z: ");

    // add button
    mAddButton = new QPushButton("Add", this);
    mGridLayout->addWidget(mAddButton, 29, 8, 1, 1);
    mAddButton->setFont(font);

    // modify button
    mModifyButton = new QPushButton("Modify", this);
    mModifyButton->setDisabled(true);
    mModifyButton->setFont(font);
    mGridLayout->addWidget(mModifyButton, 31, 8, 1, 1);
   
    //reset button 
    mResetButton = new QPushButton("Reset Shape", this);
    mGridLayout->addWidget(mResetButton, 33, 8, 1, 1);
    mResetButton->setFont(font);
    mResetButton->setStyleSheet("background-color: skyblue");

    //save button 
    mSaveImageButton = new QPushButton("Save as Image", this);
    mGridLayout->addWidget(mSaveImageButton, 40, 8, 1, 1);
    mSaveImageButton->setFont(font);
    mSaveImageButton->setStyleSheet("background-color: skyblue");
        
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
    connect(mSaveImageButton, &QPushButton::clicked, this, &Visualizer::onSaveImageButtonClicked);
    connect(mResetButton, &QPushButton::clicked, this, &Visualizer::onResetButtonClicked);
   
    setWindowTitle(QCoreApplication::translate("Visualiser", "JewelCraft - Customize Your Sparkle", nullptr));
}

// method trigger upon selecting "Droplet" radio button (displays its list of curves)
void Graphics::Visualizer::onDropletShapeButtonClicked()
{
    // hide widget visibility
    mCustomLabelPoints->setVisible(false);
    mPointsList->setVisible(false); 
    mXCoordinateLabel->setVisible(false);
    mYCoordinateLabel->setVisible(false);
    mZCoordinateLabel->setVisible(false);
    mXCoordinate->setVisible(false);
    mYCoordinate->setVisible(false);
    mZCoordinate->setVisible(false);
    mAddButton->setVisible(false);
    mModifyButton->setVisible(false);

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
    mSaveImageButton->setVisible(true);

    mDroplet.generateOffsetAndConnectingVertices();

    // set render attributes and updates renderer
    mRenderer->setRenderAttributes(points, colors, mDroplet.controlPoints(), mDroplet.offsetVertices(), 
        mDroplet.connectingVertices(), mDroplet.normalVertices());
    mRenderer->update();
}

// method trigger upon selecting "Heart" radio button (displays its list of curves)
void Graphics::Visualizer::onHeartShapeButtonClicked()
{   
    // hide widget visibility
    mCustomLabelPoints->setVisible(false);
    mPointsList->setVisible(false);
    mXCoordinateLabel->setVisible(false);
    mYCoordinateLabel->setVisible(false);
    mZCoordinateLabel->setVisible(false);
    mXCoordinate->setVisible(false);
    mYCoordinate->setVisible(false);
    mZCoordinate->setVisible(false);
    mAddButton->setVisible(false);
    mModifyButton->setVisible(false);

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
    mSaveImageButton->setVisible(true);

    mHeart.generateOffsetAndConnectingVertices();

    // set render attributes and updates renderer
    mRenderer->setRenderAttributes(points, colors, mHeart.controlPoints(), mHeart.offsetVertices(), 
        mHeart.connectingVertices(), mHeart.normalVertices());

    mRenderer->update();
}

// method triggered upon selecting a curve from curves list (displays its list of points)
void Graphics::Visualizer::handleCurveItemSelection(const QModelIndex& index)
{
    mSelectedCurveIndex = index.row();

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

        mRenderer->update();

        // show widgets
        mCustomLabelPoints->setVisible(true);
        mPointsList->setVisible(true); 
        mXCoordinateLabel->setVisible(true);
        mYCoordinateLabel->setVisible(true);
        mZCoordinateLabel->setVisible(true);
        mXCoordinate->setVisible(true);
        mYCoordinate->setVisible(true);
        mZCoordinate->setVisible(true);
        mAddButton->setVisible(true);
        mModifyButton->setVisible(true);  
    }
    else
    {      
        // hide widgets
        mCustomLabelPoints->setVisible(false);
        mPointsList->setVisible(false);      
        mXCoordinateLabel->setVisible(false);
        mYCoordinateLabel->setVisible(false);
        mZCoordinateLabel->setVisible(false);
        mXCoordinate->setVisible(false);
        mYCoordinate->setVisible(false);
        mZCoordinate->setVisible(false);
        mAddButton->setVisible(false);
        mModifyButton->setVisible(false);
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
    // get values from the spin boxes for the X, Y, and Z coordinates
    double xValue = mXCoordinate->value();
    double yValue = mYCoordinate->value();
    double zValue = mZCoordinate->value();

    // add input values as a control point to "mHeart" object
    if (mCurrentShape == "Heart")
    {          
        mHeart.addControlPoint(Point3D(xValue, yValue, zValue), static_cast<HeartCurveIndex>(mSelectedCurveIndex));
        mHeart.updateControlPoints();
        mHeart.compute();
        mHeart.generateOffsetAndConnectingVertices();
        mRenderer->setRenderAttributes(mHeart.curvePoints(), mHeart.curveColor(), mHeart.controlPoints(),
                mHeart.offsetVertices(), mHeart.connectingVertices(), mDroplet.normalVertices());           
    }
    // add input values as a control point to "mDroplet" object
    else if (mCurrentShape == "Droplet")
    {
        mDroplet.addControlPoint(Point3D(xValue, yValue, zValue), static_cast<DropletCurveIndex>(mSelectedCurveIndex));
        mDroplet.updateControlPoints();
        mDroplet.compute();
        mDroplet.generateOffsetAndConnectingVertices();
        mRenderer->setRenderAttributes(mDroplet.curvePoints(), mDroplet.curveColor(), mDroplet.controlPoints(),
            mDroplet.offsetVertices(), mDroplet.connectingVertices(), mHeart.normalVertices());
    }
    mRenderer->update();
    mResetButton->setVisible(true);

    // create new list item with point coordinates and add to points list
    QString newItem = QString("(%1, %2, %3)").arg(xValue, yValue, zValue);
    QListWidgetItem* item = new QListWidgetItem(newItem);
    mPointsList->addItem(item);

    // clear input fields
    mXCoordinate->clear();
    mYCoordinate->clear();
    mZCoordinate->clear();           
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

            // modify control point (Heart or Droplet)
            if (mCurrentShape == "Heart")
            {
                mHeart.modifyControlPoint(Point3D(xValue, yValue, zValue), static_cast<HeartCurveIndex>(mSelectedCurveIndex), mSelectedPointIndex);
                mHeart.updateControlPoints();
                mHeart.generateOffsetAndConnectingVertices();
                mRenderer->setRenderAttributes(mHeart.curvePoints(), mHeart.curveColor(), mHeart.controlPoints(),
                    mHeart.offsetVertices(), mHeart.connectingVertices(), mDroplet.normalVertices());                               
            }
            else if (mCurrentShape == "Droplet")
            {
                mDroplet.modifyControlPoint(Point3D(xValue, yValue, zValue), static_cast<DropletCurveIndex>(mSelectedCurveIndex), mSelectedPointIndex);
                mDroplet.updateControlPoints();
                mDroplet.generateOffsetAndConnectingVertices();
                mRenderer->setRenderAttributes(mDroplet.curvePoints(), mDroplet.curveColor(), mDroplet.controlPoints(),
                    mDroplet.offsetVertices(), mDroplet.connectingVertices(), mHeart.normalVertices());
            }
            mRenderer->update();

            // reset spin box to 0
            mXCoordinate->setValue(0);
            mYCoordinate->setValue(0);
            mZCoordinate->setValue(0);

            // disable the "Modify" button and enable the "Add" button after modification
            mModifyButton->setDisabled(true); // Disable modifyButton after modifying the item
            mAddButton->setEnabled(true);
        }        
    }
    mResetButton->setVisible(true);
}

// saves shape in .png file format 
void  Graphics::Visualizer::onSaveImageButtonClicked() 
{
    QString defaultFilePath = "\\savefile";
    QString filePath = QFileDialog::getSaveFileName(this, "Save File", defaultFilePath, "PNG Files (*.png)");

    if (!filePath.isEmpty()) 
    {
        QPixmap pixmap(mRenderer->size());
        mRenderer->render(&pixmap);

        if (pixmap.save(filePath, "PNG")) 
        {
            QMessageBox::information(this, "Success", "File saved successfully.");
        }
        else 
        {
            QMessageBox::critical(this, "Error", "Unable to save file!");
        }
    }
}

// resets to original shape 
void  Graphics::Visualizer::onResetButtonClicked()
{
    if (mCurrentShape == "Heart")
    {
        mHeart = Geometry::Heart3D();     

        mHeart.generateOffsetAndConnectingVertices();
        mRenderer->setRenderAttributes(mHeart.curvePoints(), mHeart.curveColor(), mHeart.controlPoints(), 
            mHeart.offsetVertices(), mHeart.connectingVertices(), mDroplet.normalVertices());

        mRenderer->update();

    }    
    else if (mCurrentShape == "Droplet")
    {
        mDroplet = Geometry::Droplet3D();
        mRenderer->setRenderAttributes(mDroplet.curvePoints(), mDroplet.curveColor(), mDroplet.controlPoints(),
            mDroplet.offsetVertices(), mDroplet.connectingVertices(), mHeart.normalVertices());
        mRenderer->update();
    }
}