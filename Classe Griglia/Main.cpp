#include "grid_class.h"
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>
using namespace std;

GridMSAF Grid;

int main(){
    TApplication app("app",0,NULL);
    Grid.SetGridSeed(1492);
    Grid.Setup(100, 0.5 ,false);
    Grid.PaintTheGrid();
    app.Run();
    return 0;
}