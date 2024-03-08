#include "stdafx.h"
#include "Visualizer.h"
#include "OpenGLWindow.h"


Graphics::Visualizer::Visualizer(QWindow* parent) : QMainWindow(nullptr)
{
    setupUi();
}

Graphics::Visualizer::~Visualizer()
{}

void Graphics::Visualizer::setupUi()
{
    resize(900, 800);
    mGridLayout = new QGridLayout(this);
    QFont font("Arial", 12);
    font.setBold(true);// Example: Arial font with size 12

    //Window
    mRenderer = new OpenGLWindow(QColor(1, 1, 0), this);
    mGridLayout->addWidget(mRenderer, 0, 0, 100, 6);

    // Shape options
    mShapeLabel = new QLabel("Choose Shape");
    mShapeLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mShapeLabel, 11, 6, 2, 3);
    mShapeLabel->setFont(font);

    //Droplet
    mDropletShapeButton = new QRadioButton("Droplet", this);
    mGridLayout->addWidget(mDropletShapeButton, 15, 6, 1, 1.5);
    mDropletShapeButton->setFont(font);


    //Heart
    mHeartShapeButton = new QRadioButton("Heart", this);
    mGridLayout->addWidget(mHeartShapeButton, 15, 7, 1, 1.5);
    mHeartShapeButton->setFont(font);

    // Customisation Tools 
    mCustomLabel = new QLabel("Curves List");
    mCustomLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mCustomLabel, 27, 6, 2, 3);
    mCustomLabel->setFont(font);

    mCurvesList = new QListWidget();
    mGridLayout->addWidget(mCurvesList, 30, 6, 2, 3);


    mCustomLabel = new QLabel("Points List");
    mCustomLabel->setAlignment(Qt::AlignLeft);
    mGridLayout->addWidget(mCustomLabel, 44, 6, 2, 3);
    mCustomLabel->setFont(font);

    mPointsList = new QListWidget();
    mGridLayout->addWidget(mPointsList, 48, 6, 2, 3);

    mCustomLabel = new QLabel("X");
    mCustomLabel->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabel, 53, 6, 2, 1);
    mCustomLabel->setFont(font);

    mCustomLabel = new QLabel("Y");
    mCustomLabel->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabel, 53, 7, 2, 1);
    mCustomLabel->setFont(font);

    mCustomLabel = new QLabel("Z");
    mCustomLabel->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabel, 53, 8, 2, 1);
    mCustomLabel->setFont(font);

    //Spin Box for X
    mXCoordinate = new QSpinBox();
    mXCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mXCoordinate, 56, 6, 2, 1);

    //Spin Box for X
    mYCoordinate = new QSpinBox();
    mYCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mYCoordinate, 56, 7, 2, 1);

    //Spin Box for X
    mZCoordinate = new QSpinBox();
    mZCoordinate->setRange(-50, 50);
    mGridLayout->addWidget(mZCoordinate, 56, 8, 2, 1);


    //Add 
    mAddButton = new QPushButton("Add", this);
    mGridLayout->addWidget(mAddButton, 60, 6, 2, 1.5);
    mAddButton->setFont(font);

    //Modify 
    mModifyButton = new QPushButton("Modify", this);
    mModifyButton->setDisabled(true);
    mModifyButton->setFont(font);
    mGridLayout->addWidget(mModifyButton, 60, 7, 2, 1.5);

    
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
    connect(mAddButton, &QPushButton::clicked, this, &Visualizer::addNewCoordinates);
    connect(mPointsList, &QListWidget::clicked, this, &Visualizer::loadCoordinatesToSpinBox);
    connect(mModifyButton, &QPushButton::clicked, this, &Visualizer::modifyCoordinates);
    connect(mFinishButton, &QPushButton::clicked, this, &Visualizer::finishCustomization);

    setWindowTitle(QCoreApplication::translate("Visualiser", "JewelCraft - Customize Your Sparkle", nullptr));
}

void Graphics::Visualizer::onDropletShapeButtonClicked()
{
    mRenderer->toggleDropletVisibility();
    mRenderer->update();
}


void Graphics::Visualizer::onHeartShapeButtonClicked()
{   
    mRenderer->toggleHeartVisibility();
    mRenderer->update();   
}

void Graphics::Visualizer::addNewCoordinates()
{
    QString xValue = mXCoordinate->text();
    QString yValue = mYCoordinate->text();
    QString zValue = mZCoordinate->text();

       if (!xValue.isEmpty() && !yValue.isEmpty() && !zValue.isEmpty()) 
    {
        QString newItem = QString("(%1, %2, %3)").arg(xValue, yValue, zValue);
        QListWidgetItem* item = new QListWidgetItem(newItem);
        
        mPointsList->addItem(item);
        mXCoordinate->clear();
        mYCoordinate->clear();
        mZCoordinate->clear();
    }
}

void Graphics::Visualizer::loadCoordinatesToSpinBox()
{
    // Get the currently selected item
    QListWidgetItem* selectedItem = mPointsList->currentItem();

    if (selectedItem)
    {
        // Get the text of the selected item
        QString text = selectedItem->text();

        // Extract x, y, z values from the text
        QStringList values = text.mid(1, text.length() - 2).split(", "); // Remove the parentheses

        if (values.size() == 3)
        {
            // Set x, y, z values in corresponding spin boxes
            mXCoordinate->setValue(values[0].toInt());
            mYCoordinate->setValue(values[1].toInt());
            mZCoordinate->setValue(values[2].toInt());

            mAddButton->setDisabled(true);
            mModifyButton->setEnabled(true); // Enable modifyButton when an item is selected
        }
    }
}


void Graphics::Visualizer::modifyCoordinates()
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

void Graphics::Visualizer::finishCustomization()
{
    mAddButton->setDisabled(true);
    mModifyButton->setDisabled(true);
}
