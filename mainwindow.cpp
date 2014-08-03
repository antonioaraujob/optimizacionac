#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringListModel>

#include "individual.h"
#include "situationalknowledge.h"
#include "normativeknowledge.h"
#include "populationvariation.h"
#include "populationselection.h"

/*
// encabezados para graficas con qwt
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_grid.h>
#include <qwt_symbol.h>
#include <qwt_legend.h>
*/



// Funcion de comparacion de individuos con respecto al valor de desempeno
inline static bool x_less_than(Individual *p1, Individual *p2)
{
    return p1->getPerformanceValue() < p2->getPerformanceValue();
}




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedSize(600, 520);

    QValidator * validatorPopSize = new QIntValidator(1, 1000, this);
    ui->lineEditPopulationSize->setValidator(validatorPopSize);
    ui->lineEditPopulationSize->setToolTip("[1..1000]");

    QValidator * validatorGenerations = new QIntValidator(1, 50, this);
    ui->lineEditGenerationNumber->setValidator(validatorGenerations);
    ui->lineEditGenerationNumber->setToolTip("[1..50]");

    QValidator * validatorAcceptedPercentage = new QIntValidator(1, 100, this);
    ui->lineEditAceptationPercentage->setValidator(validatorAcceptedPercentage);
    ui->lineEditAceptationPercentage->setToolTip("[1..100]");

    QValidator * validatorMutationStd = new QIntValidator(1, 10, this);
    ui->lineEditMutationStd->setValidator(validatorMutationStd);
    ui->lineEditMutationStd->setToolTip("[1..10]");

    connect(ui->pushButtonRun, SIGNAL(clicked()), this, SLOT(executeAlgorithm()));

    generation = 0;
    maxGenerations = 0;
    acceptedPercentage = 0;
    population  = 0;
    numberOfAcceptedIndividuals = 0;
    mutationSTd = 0;

}

MainWindow::~MainWindow()
{
    delete ui;
}



QList<Individual *> MainWindow::initializePopulation(int nPopulation)
{
    QList<Individual *> populationList;
    Individual * individuo;

    // inicializacion de la poblacion
    for (int i=0; i<nPopulation; i++)
    {
        individuo = new Individual();
        //individuo->printIndividual();
        populationList.append(individuo);
    }
    qDebug("tamano de la poblacion: %d",populationList.count());
    return populationList;
}


void MainWindow::evaluatePopulation()
{
    Individual * ind;
    for (int i=0; i<populationList.count();i++)
    {
        ind = populationList.at(i);
        ind->calculatePerformanceValue();
    }
}


QList<Individual *> MainWindow::AcceptedPopulation()
{
    QList<Individual *> acceptedIndividualsList;

    for (int i=(populationList.count()-numberOfAcceptedIndividuals); i<(populationList.count()); i++)
    {
        acceptedIndividualsList.append(populationList.at(i));
    }
    return acceptedIndividualsList;
}


void MainWindow::printPopulation()
{
    for (int i=0; i<populationList.count();i++)
    {
        populationList.at(i)->printIndividual();
    }
}



int MainWindow::getGenerationCount()
{
    return generation;
}


int MainWindow::getMaxGenerations()
{
    return maxGenerations;
}


int MainWindow::getPopulationSize()
{
    return populationList.count();
}


double MainWindow::getAcceptedPercentage()
{
    return acceptedPercentage;
}


int MainWindow::getAcceptedIndividuals()
{
    return numberOfAcceptedIndividuals;
}

double MainWindow::getMutationStd()
{
    return mutationSTd;
}

bool MainWindow::validateFields()
{
    if ( (!ui->lineEditPopulationSize->text().isEmpty()) &&
         (!ui->lineEditGenerationNumber->text().isEmpty()) &&
         (!ui->lineEditAceptationPercentage->text().isEmpty()) &&
         (!ui->lineEditMutationStd->text().isEmpty()) )
        return true;
    else
        return false;
}


void MainWindow::executeAlgorithm()
{
    QMessageBox msgBox;
    if (!validateFields())
    {
        msgBox.setText("Los parametros del algoritmo no estan completos. Debe especificarlos.");
        msgBox.exec();
        return;
    }


    msgBox.setText("se debe ejecutar el algoritmo!.");
    msgBox.exec();

    qsrand((uint)QTime::currentTime().msec());


    // ************************************************************************
    // parametros de la ejecucion del algoritmo cultural

    // Contador de generaciones
    generation = 0;

    // Maximo numero de generacion
    maxGenerations = ui->lineEditGenerationNumber->text().toInt();

    // Porcentaje de aceptacion de individuos
    acceptedPercentage = ui->lineEditAceptationPercentage->text().toInt();

    // Numero de individuos de la poblacion
    population = ui->lineEditPopulationSize->text().toInt();

    mutationSTd = ui->lineEditMutationStd->text().toDouble();

    // ************************************************************************

    // Numero de individuos que se aceptaran por generacion
    numberOfAcceptedIndividuals = (population*acceptedPercentage)/100;

    // inicializacion de la poblacion

    // Lista para mantener la poblacion
    populationList = initializePopulation(population);

    // ordenamiento de la poblacion de menor a mayor valor de desempeno
    // la selecccion sera luego por el final de la cola
    qSort(populationList.begin(), populationList.end(), x_less_than);

    qDebug("  POBLACION INICIAL");

    for (int i=0; i<population; i++)
    {
        populationList.at(i)->printIndividual();
    }

    qDebug("tamano de la poblacion: %d",populationList.count());

    // limpiar la lista de mejores individuos por generacion
    bestGenerationIndividualList.clear();

    // ************************************************************************

    // inicializacion del espacio de creencias

    // Conocimiento situacional
    SituationalKnowledge * sKnowledge = new SituationalKnowledge();

    // para el conocimiento situacional se agregara el individuo con el mejor valor de
    // desempeno
    sKnowledge->addExemplarIndividual(populationList.at(populationList.count()-1));

    //qDebug("mejor ejemplar:");
    //sKnowledge->getExemplar(0)->printIndividual();
    //qDebug("numero de ejemplares en conocimiento situacional: %d",sKnowledge->getCountOfExemplars());


    // Conocimiento normativo
    NormativeKnowledge *nKnowledge = new NormativeKnowledge();

    //qDebug("cantidad de variables en conocimiento normativo: %d", nKnowledge->getCountOfVariables());

    // para el conocimiento normativo la inicializacion se ejecuta al crear las variables
    // con sus correspondientes valores de restricciones (constructor)

    //qDebug("++++++ conocimiento normativo inicial+++++");
    //nKnowledge->printNormativeKnowledge();
    //qDebug("++++++++++++++++++++++++++++++++++++++++++");



    // lista que mantiene los mejores individuos para el conocimiento situacional
    //QList<Individual *> bestGenerationIndividualList;

    // lista de individuos seleccionados para influenciar el espacio
    QList<Individual *> acceptedIndList;
    acceptedIndList = AcceptedPopulation();


    PopulationVariation * populationVariator;
    populationVariator = new PopulationVariation();

    PopulationSelection * populationSelector;
    populationSelector = new PopulationSelection();

    // la condicion de parada es que el numero de generaciones sea estrictamente menor que el maximo
    // numero de generaciones
    do
    {
        qDebug("***************************************************");
        qDebug("**************entra al lazo de generacion***********");


        // Evaluar la poblacion en el tiempo t
        evaluatePopulation();

        // realizar un ordenamiento de la poblacion con respecto al valor de desempeno

        // ordenamiento de la poblacion de menor a mayor valor de desempeno
        // la selecccion sera luego por el final de la cola
        qSort(populationList.begin(), populationList.end(), x_less_than);

        qDebug("  POBLACION ORDENADA");

        for (int i=0; i<population; i++)
        {
            populationList.at(i)->printIndividual();
        }

        // Ajustar el espacio de creencias con los individuos aceptados

        // actualizacion del conocimiento situacional
        bestGenerationIndividualList.append(populationList.at(populationList.count()-1));
        sKnowledge->updateSituationalKnowledge(bestGenerationIndividualList);
        qDebug("---------------------------------------------------------------");
        sKnowledge->getExemplar(0)->printIndividual();
        qDebug("numero de ejemplares en conocimiento situacional: %d",sKnowledge->getCountOfExemplars());
        qDebug("---------------------------------------------------------------");


        //acceptedIndList.append(populationList.at(populationList.count()-1));
        //acceptedIndList.append(populationList.at(populationList.count()-2));

        // actualizacion del conocimiento normativo
        nKnowledge->updateNormativeKnowledge(acceptedIndList);
        qDebug("++++++ conocimiento normativo actualizado+++++");
        nKnowledge->printNormativeKnowledge();
        qDebug("++++++++++++++++++++++++++++++++++++++++++++++");


        // Ejecutar variacion en la poblacion con la influencia del espacio de creencias
        populationVariator->doVariation(populationList, sKnowledge, nKnowledge, getMutationStd());

        qDebug("******");
        // nueva poblacion
        populationSelector->doSelection(populationVariator->getNewPopulation());

        qDebug("tamano de la poblacion %d", populationList.count());
        //populationList.clear(); // <--- prueba
        //qDebug("tamano de la poblacion despues de clear %d", populationList.count());

        qDebug("######################");
        printPopulation();

        //populationList.clear();
        qDebug("######################");


        populationList = populationSelector->getSelectedPopulation();


        printPopulation();
        qDebug("######################");

        qDebug("tamano de la poblacion despues de getSelectedPopulation %d", populationList.count());

        // seleccionar individuos
        // aqui se coloca en acceptedIndList el porcentaje de seleccionados
        acceptedIndList = AcceptedPopulation();


        generation++;
        qDebug("generacion: %d",generation);
    }while(generation < maxGenerations); // fin de la repeticion

    qDebug("---numero de individuos de la lista de mejores individuos por generacion %d",bestGenerationIndividualList.count());

    // mostrar los mejores individuos de las generaciones en ListView
    populateListView();

    qDebug("---");

    qDebug("*** evolucionaron %d generaciones",generation);
    qDebug("*** tamano de la poblacion final: %d", populationList.count());


    resultGenerationVsFo();

}



void MainWindow::resultGenerationVsFo()
{
    QFile file("/tmp/generacionVsFo.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;

    QTextStream out(&file);

    for (int z=0; z<bestGenerationIndividualList.count(); z++)
    {
        out << z+1 << " " << bestGenerationIndividualList.at(z)->getPerformanceValue() << "\n" ;
    }

}

void MainWindow::resultChannelVsTime()
{
    // iterar por los individuos
    for (int i=0; i<bestGenerationIndividualList.count(); i++)
    {
        QString fileName = "/tmp/fs";
        fileName.append(QString::number(i));

        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
                return;
        QTextStream out(&file);
        //out <<



    }

}


void MainWindow::populateListView()
{

    QStringList individuals;

    QString aux;
    for (int z=bestGenerationIndividualList.count()-1; z>=0; z-- )
    {
        aux.append(bestGenerationIndividualList.at(z)->getIndividualAsQString());
        individuals << aux;
        aux.clear();
    }

    QStringListModel *model = new QStringListModel();
    model->setStringList(individuals);

    ui->listViewBestIndividuals->setModel(model);

}





