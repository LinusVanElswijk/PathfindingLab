#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    editorTileMap(10,10),
    tileMapFile(),
    scenarioFile(),
    selectedTask(),
    scene(new QGraphicsTileMapScene(editorTileMap, *this, this)),
    editState(EditState::problemEditing),
    selectedAlgorithm(SearchAlgorithmType::aStar),
    searchManager(this)
{
    this->setWindowTitle("Pathfinding Lab");
    ui->setupUi(this);
    ui->mapView->setScene(scene);

    scene->rebuild();

    initCheckableButtons();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLoad_Map_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Load Map"), "",
             tr("Map Files (*.map);;All Files (*)"));

    if(!fileName.isNull()) {
        tileMapFile.load(fileName.toStdString());
        editorTileMap = *tileMapFile.getTileMap();
        editorTileMap.rebuildGridGraph();

        scene->rebuild();

        ui->mapLabel->setText( fileName.split('/').back() );
    }

    this->selectedTask.setGoal(nullptr);
    this->selectedTask.setStart(nullptr);
}

void MainWindow::on_mapScaleSlider_valueChanged(int value)
{
    int max = this->ui->mapScaleSlider->maximum();
    int min = this->ui->mapScaleSlider->minimum();

    qreal zoomFactor = (qreal(value - min) / qreal(max - min)) * 100.0f;
    zoomFactor = 0.0001 * zoomFactor * zoomFactor;

    //if(tileMapFile.isLoaded())
    {
        qreal scale =        zoomFactor  * MAXIMUM_SCALE +
                      (1.0 - zoomFactor) * MINIMUM_SCALE;

        QTransform transform = ui->mapView->transform();
        transform.setMatrix(          scale, transform.m12(), transform.m13(),
                            transform.m21(),           scale, transform.m23(),
                            transform.m31(), transform.m32(), transform.m33()
                           );
        ui->mapView->setTransform(transform);

        ui->statusBar->showMessage(QString("Scale set to: %1").arg(scale));
    }
}

const qreal MainWindow::MINIMUM_SCALE = 0.1;
const qreal MainWindow::MAXIMUM_SCALE = 5.0;

void MainWindow::on_actionLoad_Scenario_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
             tr("Load Map"), "",
             tr("Map Files (*.scen);;All Files (*)"));

    if(!fileName.isNull()) {
        scenarioFile.load(fileName.toStdString());

        const Scenario& scenario = *scenarioFile.getScenario();

        ui->scenarioList->clear();
        for(unsigned int i = 0; i < scenario.size(); i++) {
            std::pair<Position, Position> pair = scenario.at(i);

            ui->scenarioList->addItem(QString("%1 : (%2, %3) to (%4, %5)").
                                      arg(i).arg(pair.first.x).arg(pair.first.y).arg(pair.second.x).arg(pair.second.y)
            );

            ui->scenarioList->item(i)->setBackground(itemBackgroundColor(pair));
        }

        ui->scenarioLabel->setText( fileName.split('/').back() );
    }
}

QBrush MainWindow::itemBackgroundColor(const std::pair<Position, Position>& positions) const
{
    if(positions.first.x < editorTileMap.getWidth() && positions.first.y < editorTileMap.getHeight() &&
       positions.second.x < editorTileMap.getWidth() && positions.second.y < editorTileMap.getHeight()
      )
    {
        return QBrush(Qt::green);
    }
    else
    {
        return QBrush(Qt::red);
    }
}

void MainWindow::initCheckableButtons() {
    ui->editTilesButton->setCheckable(true);
    ui->editProblemButton->setCheckable(true);

    ui->aStarButton->setCheckable(true);
    ui->thetaStarButton->setCheckable(true);
    ui->hpaStarButton->setCheckable(true);
    ui->hptStarButton->setCheckable(true);

    updateToolButtons();
    updateAlgorithmButtons();
}


void MainWindow::updateToolButtons()
{
    ui->editTilesButton->setChecked(editState == EditState::mapEditing);
    ui->editProblemButton->setChecked(editState == EditState::problemEditing);
}

void MainWindow::updateAlgorithmButtons()
{
    ui->aStarButton->setChecked(selectedAlgorithm == SearchAlgorithmType::aStar);
    ui->thetaStarButton->setChecked(selectedAlgorithm == SearchAlgorithmType::thetaStar);
    ui->hpaStarButton->setChecked(selectedAlgorithm == SearchAlgorithmType::hpaStar);
    ui->hptStarButton->setChecked(selectedAlgorithm == SearchAlgorithmType::hptStar);
}

void MainWindow::on_editProblemButton_clicked()
{
    setEditState(EditState::problemEditing);
}

void MainWindow::on_editTilesButton_clicked()
{
    setEditState(EditState::mapEditing);
}


void MainWindow::setEditState(const EditState& state) {
    if(editState != state) {
        editState = state;
        updateToolButtons();
    }
}

void MainWindow::setSelectedAlgorithm(const SearchAlgorithmType& algorithm) {
    if(selectedAlgorithm != algorithm) {
        selectedAlgorithm = algorithm;
        updateAlgorithmButtons();
    }
}

void MainWindow::on_aStarButton_clicked()
{
    setSelectedAlgorithm(SearchAlgorithmType::aStar);
}

void MainWindow::on_thetaStarButton_clicked()
{
    setSelectedAlgorithm(SearchAlgorithmType::thetaStar);
}

void MainWindow::on_hpaStarButton_clicked()
{
    setSelectedAlgorithm(SearchAlgorithmType::hpaStar);
}

void MainWindow::on_hptStarButton_clicked()
{
    setSelectedAlgorithm(SearchAlgorithmType::hptStar);
}
