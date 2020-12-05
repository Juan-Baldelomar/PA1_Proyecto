/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "Graficadora.h"
#include "cairo/cairo-features.h"
using namespace std;


void generateGraphics(vector<vector<pixel>> &pixels, vector<vector<pixel>> &originalPixels, vector<point> &biffPoints){
    int height = pixels.size();
    int width = height > -0? pixels[0].size() : 0;

    //GENERAR FORMATO DE IMAGEN
    cairo_surface_t *surface;
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
                cairo_arc(cr, j, i, 1, 0, 1 * M_PI);                                // y = i, x = j because we are using the transpose  of the pgm image
                cairo_fill(cr);
            }
        }
    }

    // draw biffurcation points
    for (point p : biffPoints){
        cairo_set_source_rgba(cr, 1.0, 0.3, 0.0, 0.6);
        cairo_arc(cr, p.y, p.x, 4, 0, 2 * M_PI);
        cairo_fill(cr);
    }


    cairo_surface_write_to_png(surface, "GraficaP.png");
}




