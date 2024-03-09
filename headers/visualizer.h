#pragma once
#include <QtWidgets/QMainWindow>

#include "heart3D.h"
#include "droplet3D.h"

class OpenGLWindow;

namespace Graphics
{
	class Visualizer : public QMainWindow
	{
		Q_OBJECT

	public:
		Visualizer(QWindow* parent = nullptr);
		~Visualizer();

	private:
		void setupUi();

	private slots:
		void onDropletShapeButtonClicked();
		void onHeartShapeButtonClicked();	
		void handleCurveItemSelection();
		void loadCoordinatesToSpinBox();
		void onAddControlPointButtonClicked();
		void onModifyControlPointButtonClicked();
		void onFinishCustomizationButtonClicked();

	private:
		QWidget* mWidget;
		OpenGLWindow* mRenderer;

		QGridLayout* mCentralGrid;
		QGridLayout* mGridLayout;

		QString mCurrentShape;

		QLabel* mShapeLabel;
		QLabel* mCustomLabelCurves;
		QLabel* mCustomLabelPoints;

		QLabel* mCustomLabelX;
		QLabel* mCustomLabelY;
		QLabel* mCustomLabelZ;

		QListWidget* mCurvesList;
		QListWidget* mPointsList;

		QSpinBox* mXCoordinate;
		QSpinBox* mYCoordinate;
		QSpinBox* mZCoordinate;

		QRadioButton* mDropletShapeButton;
		QRadioButton* mHeartShapeButton;

		QPushButton* mAddButton;
		QPushButton* mModifyButton;
		QPushButton* mFinishButton;

		Geometry::Heart3D mHeart;
		Geometry::Droplet3D mDroplet;
	};
}

