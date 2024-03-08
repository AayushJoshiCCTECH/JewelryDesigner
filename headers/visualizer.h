#pragma once
// delete this comment later
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
		void onAddControlPointClicked();


	private:
		QWidget* mWidget;
		OpenGLWindow* mRenderer;

		QGridLayout* mCentralGrid;
		QGridLayout* mGridLayout;

		QLabel* mShapeLabel;
		QLabel* mCustomLabel;

		QListWidget* mCurvesList;
		QListWidget* mPointsList;
		QListWidget* mListView;

		QSpinBox* mPoint3DSpinBox;

		QRadioButton* mDropletShapeButton;
		QRadioButton* mHeartShapeButton;

		QPushButton* mAddButton;
		QPushButton* mModifyButton;
		QPushButton* mFinishButton;

		Geometry::Heart3D mHeart;
		Geometry::Droplet3D mDroplet;
	};
}

