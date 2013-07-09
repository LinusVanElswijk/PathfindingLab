#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QFileDialog>
#include <QListWidgetItem>

#include <iostream>

#include "TileMap.h"
#include "TileMapFile.h"
#include "QGraphicsTileMapScene.h"
#include "ScenarioFile.h"
#include "position.h"
#include "InteractionHandler.h"
#include "SearchManager.h"
#include "SearchAlgorithmTypes.hpp"

//#include "TaskRunner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow, InteractionHandler
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void updateWindowTitle();

private slots:
    void on_actionLoad_Map_triggered();
    void on_actionLoad_Scenario_triggered();

    void on_mapScaleSlider_valueChanged(int value);

    void on_editProblemButton_clicked();
    void on_editTilesButton_clicked();

    void on_aStarButton_clicked();
    void on_thetaStarButton_clicked();
    void on_hpaStarButton_clicked();
    void on_hptStarButton_clicked();

private:
    Ui::MainWindow *ui;

    TileMap editorTileMap;
    TileMapFile tileMapFile;

    ScenarioFile scenarioFile;

    SearchTask selectedTask;

    QGraphicsTileMapScene* const scene;

    static const qreal MINIMUM_SCALE, MAXIMUM_SCALE;

    QBrush itemBackgroundColor(const std::pair<Position, Position>& positions) const;

    void initCheckableButtons();

    void updateToolButtons();

    void updateAlgorithmButtons();

    virtual Qt::MouseButtons acceptedButtonsForNode() {
        return Qt::LeftButton | Qt::RightButton;
    }

    virtual void onNodeClick(const int& x, const int& y, QGraphicsNodeItem *const node, const Qt::MouseButton& button) {
        static QGraphicsNodeItem *startNode(0), *goalNode(0);

        if(editState == EditState::problemEditing)
        {
            if(button==Qt::RightButton) {
                if(startNode) {
                    startNode->setStart(false);
                    startNode->update();
                }

                selectedTask.setStart(QPoint(x,y));
                startNode = node;
                startNode->setStart(true);
            }
            else {
                if(goalNode) {
                    goalNode->setGoal(false);
                    goalNode->update();
                }

                selectedTask.setGoal(QPoint(x,y));
                goalNode = node;
                goalNode->setGoal(true);
            }
        }

        if(selectedTask.isSpecified()) {
            searchManager.solveProblem(selectedAlgorithm);
        }
    }

    virtual Qt::MouseButtons acceptedButtonsForTile() {
        return Qt::LeftButton | Qt::RightButton;
    }

    virtual void onTileClick(const int& x, const int& y, const Qt::MouseButton& button) {
        if(editState == EditState::mapEditing)
            editorTileMap(x,y) = button == Qt::LeftButton;
    }

    enum class EditState {
        mapEditing,
        problemEditing
    };

    void setEditState(const EditState& state);
    void setSelectedAlgorithm(const SearchAlgorithmType& algorithm);

    EditState editState;
    SearchAlgorithmType selectedAlgorithm;


    SearchManager searchManager;
};

#endif // MAINWINDOW_H
