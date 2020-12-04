#include "ventanaprincipal.h"

#include <QApplication>
#include "Graficadora.h"
#include "PGMImage.h"
#include "ImgProcessing.h"
#include "iostream"

using namespace std;

//int exec() {
//    PGMImage image("Input/27_gt.pgm");
//    //PGMImage image("Output/img1.pgm");
//    ImgProcessing imgP;
//    imgP.getSkeleton(image.pixels);
//    imgP.getPoints(image.pixels);
//    imgP.printLines();
//    imgP.DecimateLines(0.5);
//    imgP.printLines();
//    imgP.getSplinesLines();
//    imgP.printLines();
//    imgP.drawLines(image.pixels);

//    imgP.hausdorff();

//    cout << imgP.errors << endl;
//    image.writeFile("Output/img1.pgm");

//    vector<vector<pixel>> original = imgP.getPixelsMatrix('O', image.pixels.size(), image.pixels[0].size());

//    generateGraphics(image.pixels, original, imgP.criticPoints);
//    return 0;
//}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    VentanaPrincipal w;
    w.show();
    //exec();
    return a.exec();
}
