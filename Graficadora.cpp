/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Graficadora.h"
#include "cairo/cairo-features.h"
using namespace std;

double height = 900;
double width = 1440;


void graficarRegion(double a, double b, double (*f)(double)) {
    int n = 100000 + (b-a)*10000;
    int ratio = 10;
    int gridRatio = 40;


    double x, y;
    double fMax = MIN;
    double fMin = MAX;

    //get max and min
    for (int i = 0; i < n; i++) {
        x = a + i * (b - a) / n;
        y = f(x);
        if (fMax < y && y != INFINITY)
            fMax = y;

        if (fMin >  y &&  y != -INFINITY)
            fMin = y;
    }

    cout << "max is " << fMax << endl;

    cout << "min is " << fMin << endl;


    //GRAFICAR
    cairo_surface_t *surface;
    cairo_pattern_t *pat;
    cairo_t *cr;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);

    pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
    cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.9, 0.9, 0.9);
    cairo_pattern_add_color_stop_rgb(pat, 1.0, 0.6, 0.6, 0.6);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_set_source(cr, pat);
    cairo_fill(cr);

    //GRID 
    double origenx = width / ratio;
    double origeny = height / ratio;
    double endx = width - width / ratio;
    double endy = height - height / ratio;

    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_set_line_width(cr, 3.0);

    cairo_move_to(cr, origenx, origeny);
    cairo_line_to(cr, origenx, endy);
    cairo_move_to(cr, origenx, endy);
    cairo_line_to(cr, endx, endy);

    cairo_stroke(cr);

    double metrica_ejex = (endx - origenx) / gridRatio;
    double metrica_ejey = (endy - origeny) / gridRatio;

    for (int i = 0; i <= gridRatio; i++) {
        cairo_set_source_rgb(cr, 0.4, 0.4, 0.4);
        cairo_set_line_width(cr, 0.5);

        cairo_move_to(cr, (origenx + (metrica_ejex * i)), origeny);
        cairo_line_to(cr, (origenx + (metrica_ejex * i)), endy);

        cairo_move_to(cr, origenx, (origeny + (metrica_ejey * (i))));
        cairo_line_to(cr, endx, (origeny + (metrica_ejey * (i))));
        cairo_stroke(cr);
    }


    //LABELS
    double xlabelSkip = (b - a) / gridRatio;
    double ylabelSkip = (fMax - fMin) / gridRatio;

    // labels for x axis
    for (int i = 0; i < gridRatio; i++) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10.0);
        cairo_move_to(cr, origenx + metrica_ejex*i, endy + 10);
        cairo_save(cr);
        cairo_rotate(cr, 45.0);

        char cad[10];
        snprintf(cad, 10, "%.2f", a + xlabelSkip * i);
        cairo_show_text(cr, cad);
        cairo_restore(cr);
    }

    //labels for y axis
    for (int i = 0; i < gridRatio; i++) {
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 10.0);
        cairo_move_to(cr, origenx - 40, endy - metrica_ejey * i);
        cairo_save(cr);

        char cad[10];
        snprintf(cad, 10, "%.2f", fMin + ylabelSkip * i);
        cairo_show_text(cr, cad);
        cairo_restore(cr);
    }


    cairo_set_source_rgba(cr, 1, 0.2, 0.2, 0.6);
    cairo_set_line_width(cr, 3.0);
    
    //EJES

    //graficar ejes de ser necesario
    if (a <= 0 && b >= 0) {
        //graficar eje y
        double ejex = origenx + ((0 - a) / (b - a))*(endx - origenx);

        cairo_move_to(cr, ejex, origeny);
        cairo_line_to(cr, ejex, endy);
    }

    if (fMin <= 0 && fMax >= 0) {
        // graficar eje x 
        double ejey = origeny + ((fMax - 0) / (fMax - fMin))*(endy - origeny);

        cairo_move_to(cr, origenx, ejey);
        cairo_line_to(cr, endx, ejey);

    }

    cairo_stroke(cr);


    // PLOT POINTS
    double prevxValue = a + (b - a) / n * 0;
    double prevyValue = f(prevxValue);

    //color de puntos
    cairo_set_source_rgb(cr, 0.0, 00, 1.0);
    
    // obtener coordenadas x y y en pixeles
    for (int i = 0; i < n; i++) {
        double valx = a + (b - a) / n*i;
        double valy = f(valx);
        double pendiente = (valy - prevyValue) / (valx - prevxValue);
        
        // evaluar si es necesario plotear mas puntos por cambios muy bruscos en la pendiente
        if (valx != prevxValue && fabs(pendiente) > (b-a)) {
            for (double j = i - 1; j < i; j = (j + 1.00/100.00)) {
                double valx_j = a + (b - a) / n*j;
                double valy_j = endy - (f(valx_j) - fMin) / (fMax - fMin)*(endy - origeny);
                valx_j = origenx + (valx_j - a) / (b - a)*(endx - origenx);
                
                cairo_arc(cr, valx_j, valy_j, 0.3, 0, 1 * M_PI);
                cairo_fill(cr);
            }
        }
        
        // actualizar valores previos
        prevxValue = valx;
        prevyValue = valy;

        // calcular posicion en canvas
        valy = endy - (f(valx) - fMin) / (fMax - fMin)*(endy - origeny);
        valx =origenx + (valx - a) / (b - a)*(endx - origenx);

        //dibujar el punto
        cairo_set_source_rgb(cr, 0.0, 00, 1.0);
        cairo_arc(cr, valx, valy, 0.3, 0, 1 * M_PI);
        cairo_fill(cr);

    }

    cairo_surface_write_to_png(surface, "GraficaP.png");

}

void generateGraphics(vector<vector<pixel>> &pixels, vector<vector<pixel>> &originalPixels, vector<point> &biffPoints){
    int height = pixels.size();
    int width = height > -0? pixels[0].size() : 0;

    //GENERAR FORMATO DE IMAGEN
    cairo_surface_t *surface;
    cairo_pattern_t *pat;
    cairo_t *cr;

    surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
    cr = cairo_create(surface);

    //pat = cairo_pattern_create_linear(width / 2, 0.0, width / 2, height);
    //cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.0, 0.0, 0.0);
    //cairo_pattern_add_color_stop_rgb(pat, 0.0, 0.0, 0.0, 0.0);
    cairo_rectangle(cr, 0, 0, width, height);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_stroke(cr);

    //color de puntos
    //cairo_set_source_rgb(cr, 255.0, 255.0, 255.0);

    // draw splines curve
    for (int i = 0; i<width; i++){
        for (int j = 0; j<height; j++){
            if (pixels[i][j] == 255)
                cairo_set_source_rgb(cr, 1, 1, 1);
            else
                cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);

            cairo_arc(cr, j, i, 1, 0, 1 * M_PI);
            cairo_fill(cr);
        }
    }

    // draw original thin curve
    for (int i = 0; i<width; i++){
        for (int j = 0; j<height; j++){
            if (originalPixels[i][j] == 255){
                cairo_set_source_rgba(cr, 0.93, 0.99, 0.06, 1);
                cairo_arc(cr, j, i, 1, 0, 1 * M_PI);
                cairo_fill(cr);
            }
        }
    }

    // draw biffurcation points
    for (point p : biffPoints){
        cairo_set_source_rgba(cr, 1.0, 0.0, 0.0, 0.6);
        cairo_arc(cr, p.y, p.x, 4, 0, 2 * M_PI);
        cairo_fill(cr);
    }


    cairo_surface_write_to_png(surface, "GraficaP.png");
}




