#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

#include "string"
#include "iostream"
#include "sstream"

#include "QFileDialog"
#include "QPixmap"
#include "QImage"

//own files
#include "Graficadora.h"
#include "PGMImage.h"
#include "ImgProcessing.h"


using namespace std;

string path = "";
QGraphicsScene *scene;
QTextBrowser *output;

int exec(double epsilon, bool visAlgh) {

    // create image and process it
    PGMImage image(path);
    ImgProcessing imgP;
    imgP.getSkeleton(image.pixels);
    imgP.getPoints(image.pixels, 5);
    imgP.printLines();

    // decimate lines
    if (visAlgh)
        imgP.DecimateVisvalingam(epsilon);
    else
        imgP.DecimateLines(epsilon);

    imgP.printLines();

    // splines interpolation
    imgP.getSplinesLines();
    imgP.printLines();
    imgP.drawLines(image.pixels);

    // calculate error
    imgP.hausdorff();

    // OUTPUT ERROR
    string strout = "", maxstr, avgstr;
    stringstream ss;

    double max = 0, avg = 0;

    for (unsigned i = 0; i<imgP.errors.size(); i++){
        string num, pos;

        // max and avg calculation
        avg += imgP.errors[i];
        if (max < imgP.errors[i])
            max = imgP.errors[i];

        // cast to string
        ss << imgP.errors[i]; ss >> num; ss.clear();
        ss << i + 1 ; ss >> pos; ss.clear();

        strout+= "error segmento " + pos + ":\t" + num + "\n";
    }

    ss << max; ss >> maxstr; ss.clear();
    ss << avg/imgP.errors.size(); ss >> avgstr; ss.clear();

    strout+= "ERROR PROMEDIO:\t" + avgstr + "\n";
    strout+= "ERROR MAXIMO:\t" + maxstr + "\n";

    output->setText(QString::fromStdString(strout));


    // GENERATE OUTPUT IMAGE
    vector<vector<pixel>> original = imgP.getPixelsMatrix('O', image.pixels.size(), image.pixels[0].size());
    generateGraphics(image.pixels, original, imgP.criticPoints);

    // output image after skeletonization
    image.writeFile("Output/imgSk.pgm");

    return 0;
}



VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    output = ui->output;
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}


void VentanaPrincipal::on_loadButton_clicked()
{
    QFileDialog *qf = new QFileDialog(this);
    QString qpath = qf->getOpenFileName();
    if (qpath.compare("")!=0){
        path = qpath.toLocal8Bit().constData();
        qpath = "LOAD: " + qpath;
        ui->path_lb->setText(qpath);
    }
}

void VentanaPrincipal::on_startButton_clicked()
{
    bool visAlgh = ui->vis_radioButton->isChecked();
    double epsilon = ui->error_txt->text().toDouble();

    if (path.compare("")!=0){
        exec(epsilon, visAlgh);

        QImage qimage;
        qimage.load("GraficaP.png");

        //load scene
        scene = new QGraphicsScene(this);
        scene->addPixmap(QPixmap::fromImage(qimage));
        scene->setSceneRect(qimage.rect());

        // display image
        ui->graphicsView->setScene(scene);
    }
}
