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
		void onSaveContentButtonClicked();

	private:
		QWidget* mWidget;
		OpenGLWindow* mRenderer;

		QGridLayout* mCentralGrid;
		QGridLayout* mGridLayout;

		string mCurrentShape;
		string mSelectedCurve;

		int	mSelectedPointIndex;

		QLabel* mShapeLabel;
		QLabel* mCustomLabelCurves;
		QLabel* mCustomLabelPoints;

		QLabel* mCustomLabelX;
		QLabel* mCustomLabelY;
		QLabel* mCustomLabelZ;

		QListWidget* mCurvesList;
		QListWidget* mPointsList;

		QDoubleSpinBox* mXCoordinate;
		QDoubleSpinBox* mYCoordinate;
		QDoubleSpinBox* mZCoordinate;

		QRadioButton* mDropletShapeButton;
		QRadioButton* mHeartShapeButton;

		QPushButton* mAddButton;
		QPushButton* mModifyButton;
		QPushButton* mFinishButton;
		QPushButton* mSaveButton;

		Geometry::Heart3D mHeart;
		Geometry::Droplet3D mDroplet;
	};
}

