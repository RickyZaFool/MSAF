/*
void Setup(int sideLenght, float theta, bool ordered); DONE
void Move(int particle, int direction); DONE
int FindPosIndex(int x, int y); DONE
int FindXFromPos(int position); DONE
int FindYFromPos(int position); DONE
int ParticlePos(int particle); DONE
int ParticleX(int particle); DONE
int ParticleY(int particle); DONE
bool IsOccupied(int position); DONE
bool IsOccupied(int x, int y); DONE
*/
#include <iostream>
#include "grid_class.h"
#include <TRandom3.h>
#include <TH2D.h>
#include <TApplication.h>
#include <TCanvas.h>
#include <TSystem.h>


void GridMSAF::SetGridSeed(int seed){
    Rnd.SetSeed(seed);
}

void GridMSAF::Setup(int sideLenght, float theta, bool ordered){
    SideLenght = sideLenght;
    if(Seed == -1){
        Rnd.SetSeed(time(0));
    }else{Rnd.SetSeed(Seed);}

    NumberOfParticles = int(SideLenght*SideLenght*theta);
    Grid = std::vector<int>(SideLenght*SideLenght);
    ParticlesPositions = std::vector<int>(NumberOfParticles);
    if(ordered){
        if(theta <= 0.5){
            for(int i=0; i<NumberOfParticles; i++){
                if(SideLenght % 2 != 0){
                    Grid[2*i] = 1;
                    ParticlesPositions[i] = 2 * i;
                }
                else{
                    int tempIndex = 2 * i + 1 * ((i % (SideLenght/2)) ^ 1);
                    Grid[tempIndex] = 1;
                    ParticlesPositions[i] = tempIndex;
                }
            }
        }
        else{
            std::cout << "**********************************************************************************************" << std::endl;
            std::cout << "WARNING: Ordered grid for theta greater than half is not yet supported, switching to unordered" << std::endl;
            std::cout << "**********************************************************************************************" << std::endl;
            for(int i=0; i<NumberOfParticles; i++){
                int setupPos = int(Rnd.Rndm()*SideLenght*SideLenght);
                if(!Grid[setupPos]){
                    Grid[setupPos] = 1;
                    ParticlesPositions[i] = setupPos;
                }else{i--;}
            }
        }
    }
    else{
        for(int i=0; i<NumberOfParticles; i++){
            int setupPos = int(Rnd.Rndm()*SideLenght*SideLenght);
            if(!Grid[setupPos]){
                Grid[setupPos] = 1;
                ParticlesPositions[i] = setupPos;
            }else{i--;}
        }
    }
}

void GridMSAF::Move(int particle, int direction){
    int originPos = ParticlesPositions[particle];
    int originX = FindXFromPos(originPos);
    int originY = FindYFromPos(originPos);
    int newX, newY;
    switch (direction)
    {
    case 1:                   //UP
        newX = originX;
        newY = (originY - 1 + SideLenght)%SideLenght;
        break;
    case 2:                   //RIGHT
        newX = (originX + 1 + SideLenght)%SideLenght;
        newY = originY;
        break;
    case 3:                   //DOWN
        newX = originX;
        newY = (originY + 1 + SideLenght)%SideLenght;
        break;
    case 4:                   //LEFT
        newX = (originX - 1 + SideLenght)%SideLenght;
        newY = originY;
        break;
    }
    int newPos = FindPosIndex(newX, newY);
    Grid[originPos] = 0;
    Grid[newPos] = 1;
    ParticlesPositions[particle] = newPos;
}

int GridMSAF::FindPosIndex(int x, int y){
    return x + SideLenght * y;
}

int GridMSAF::FindXFromPos(int position){
    return position % SideLenght;
}

int GridMSAF::FindYFromPos(int position){
    return position / SideLenght;
}

bool GridMSAF::IsOccupied(int position){
    return bool(Grid[position]);
}

bool GridMSAF::IsOccupied(int x, int y){
    return bool(Grid[FindPosIndex(x,y)]);
}

int GridMSAF::ParticlePos(int particle){
    return ParticlesPositions[particle];
}

int GridMSAF::ParticleX(int particle){
    return FindXFromPos(ParticlesPositions[particle]);
}

int GridMSAF::ParticleY(int particle){
    return FindYFromPos(ParticlesPositions[particle]);
}

void GridMSAF::PaintTheGrid(){
    TCanvas *c = new TCanvas("c", "Canvas", 800, 600);
    TH2D *histo = new TH2D("histo", "Sim", SideLenght, 0.0, SideLenght, SideLenght, 0.0, SideLenght);
    for(int particle = 0; particle < NumberOfParticles; particle++){
        histo->SetBinContent(FindXFromPos(ParticlePos(particle))+1,FindYFromPos(ParticlePos(particle))+1,1);
    }
    histo->Draw("COLZ");
    gPad->Modified(); 
    gPad->Update();
}