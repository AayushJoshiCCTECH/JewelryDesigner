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
    mGridLayout->addWidget(mCustomLabel, 40, 6, 2, 3);
    mCustomLabel->setFont(font);

    mListView = new QListWidget();
    mGridLayout->addWidget(mListView, 43, 6, 2, 3);

    //Add 
    mAddButton = new QPushButton("Add", this);
    mGridLayout->addWidget(mAddButton, 53, 6, 2, 1.5);
    mAddButton->setFont(font);

    //Modify 
    mModifyButton = new QPushButton("Modify", this);
    mGridLayout->addWidget(mModifyButton, 53, 7, 2, 1.5);
    mModifyButton->setFont(font);

    mCustomLabel = new QLabel("X");
    mCustomLabel->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabel, 57, 6, 2, 1);
    mCustomLabel->setFont(font);

    mCustomLabel = new QLabel("Y");
    mCustomLabel->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabel, 57, 7, 2, 1);
    mCustomLabel->setFont(font);

    mCustomLabel = new QLabel("Z");
    mCustomLabel->setAlignment(Qt::AlignCenter);
    mGridLayout->addWidget(mCustomLabel, 57, 8, 2, 1);
    mCustomLabel->setFont(font);

    for (int i = 0; i < 3; i++) {
        mPoint3DSpinBox = new QSpinBox();
        mPoint3DSpinBox->setRange(-50, 50);
        mGridLayout->addWidget(mPoint3DSpinBox, 60, i + 6, 2, 1);
    }

    mFinishButton = new QPushButton("Finish", this);
    mGridLayout->addWidget(mFinishButton, 80, 6, 2, 3);
    mFinishButton->setFont(font);
    mFinishButton->clicked();
    mFinishButton->setStyleSheet("background-color: skyblue");

    // signal-slot connections
    connect(mDropletShapeButton, &QRadioButton::clicked, this, &Visualizer::onDropletShapeButtonClicked);
    connect(mHeartShapeButton, &QRadioButton::clicked, this, &Visualizer::onHeartShapeButtonClicked);

    mWidget = new QWidget(this);
    mWidget->setLayout(mGridLayout);
    setCentralWidget(mWidget);

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

