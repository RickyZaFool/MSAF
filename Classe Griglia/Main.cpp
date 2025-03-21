#include "grid_class.h"
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>
using namespace std;

GridMSAF Grid;

int main(){
    int Seed = -1;
    TRandom3 rand;
    int MCS = 100000;
    int sideLenght = 50;
    if(Seed != -1){
        rand.SetSeed(Seed);
        Grid.SetGridSeed(Seed);
    }else{rand.SetSeed(time(0));}

    TApplication app("app",0,NULL);
    Grid.Setup(sideLenght, 0.5 ,false);
    Grid.PaintTheGrid();
    for (int mcs = 0; mcs < MCS; mcs++)
    {
        for(int step = 0; step < Grid.GetNumberOfParticles(); step++){
            int RandomParticle = rand.Rndm()*Grid.GetNumberOfParticles();
            int RandomDirection = rand.Rndm()*3;

            int selectedX = Grid.FindXFromPos(Grid.ParticlePos(RandomParticle));
            int selectedY = Grid.FindYFromPos(Grid.ParticlePos(RandomParticle));
            int newX, newY;
            switch (RandomDirection)
            {
            case 0:                   //UP
                newX = selectedX;
                newY = (selectedY - 1 + sideLenght)%sideLenght;
                break;
            case 1:                   //RIGHT
                newX = (selectedX + 1 + sideLenght)%sideLenght;
                newY = selectedY;
                break;
            case 2:                   //DOWN
                newX = selectedX;
                newY = (selectedY + 1 + sideLenght)%sideLenght;
                break;
            case 3:                   //LEFT
                newX = (selectedX - 1 + sideLenght)%sideLenght;
                newY = selectedY;
                break;
            }
            int RandomDestination = Grid.FindPosIndex(newX,newY);

            if(Grid.CheckNeighbors(Grid.ParticlePos(RandomParticle)) > Grid.CheckNeighbors(RandomDestination)){
                Grid.Move(RandomParticle, RandomDirection);
            }
        }
    }
    
    Grid.PaintTheGrid();

    app.Run();
    return 0;
}