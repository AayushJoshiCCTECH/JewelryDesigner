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
		void handleCurveItemSelection(const QModelIndex& index);
		void loadCoordinatesToSpinBox();
		void onAddControlPointButtonClicked();
		void onModifyControlPointButtonClicked();
		void onSaveImageButtonClicked();
		void onResetButtonClicked();

	private:
		QWidget* mWidget;
		OpenGLWindow* mRenderer;

		QGridLayout* mCentralGrid;
		QGridLayout* mGridLayout;

		string mCurrentShape;
		string mSelectedCurve;

		int	mSelectedCurveIndex;
		int	mSelectedPointIndex;

		QLabel* mShapeLabel;
		QLabel* mCustomLabelCurves;
		QLabel* mCustomLabelPoints;
		QLabel* mXCoordinateLabel;
		QLabel* mYCoordinateLabel;
		QLabel* mZCoordinateLabel;

		QListWidget* mCurvesList;
		QListWidget* mPointsList;

		QSpinBox* mXCoordinate;
		QSpinBox* mYCoordinate;
		QSpinBox* mZCoordinate;

		QRadioButton* mDropletShapeButton;
		QRadioButton* mHeartShapeButton;

		QPushButton* mAddButton;
		QPushButton* mModifyButton;		
		QPushButton* mResetButton;
		QPushButton* mSaveImageButton;

		Geometry::Heart3D mHeart;
		Geometry::Droplet3D mDroplet;
	};
}

