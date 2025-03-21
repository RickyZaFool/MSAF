/*
void Setup(int sideLenght, float theta, bool ordered); DONE
void Move(int particle, int direction);
int FindPosIndex(int x, int y);
int FindXFromPos(int position);
int FindYFromPos(int position);
int ParticlePos(int particle);
int ParticleX(int particle);
int ParticleY(int particle);
bool IsOccupied(int position);
bool IsOccupied(int x, int y);
*/
#include <TRandom3>


GridClass::void Setup(int sideLenght, float theta, bool ordered){
    SideLenght = sideLenght;
    if(Seed == -1){
        Rnd.SetSeed(time(0));
    }else{Rnd.SetSeed(Seed);}

    NumberOfParticles = int(SideLenght*SideLenght*theta);
    Grid = new std::vector<int>(SideLenght*SideLenght);
    if(ordered){
        if(theta < 0.5){
            for(int i=0; i<NumberOfParticles; i++){
                if(SideLenght % 2 != 0){
                    Grid[2*i] = 1;
                    ParticlesPositions[i] = 2 * i;
                }
                else{
                    int tempIndex = 2 * i + 1 * ((i % (SideLenght/2)) ^ 1);
                }
            }
        }
        else{
            cout << "**********************************************************************************************" << endl;
            cout << "WARNING: Ordered grid for theta greater than half is not yet supported, switching to unordered" << endl;
            cout << "**********************************************************************************************" << endl;
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

GridClass::void Move(int particle, int direction){
    int originPos = ParticlesPositions[particle];
    int originX = FindXFromPos(originPos);
    int originY = FindYFromPos(originPos);
    int newX, newY;
    switch (direction)
    {
    case 1                   //UP
        newX = originX;
        newY = (originY - 1 + l)%l;
        break;
    case 2                   //RIGHT
        newX = (originX + 1 + l)%l;
        newY = originY;
        break;
    case 3                   //DOWN
        newX = originX;
        newY = (originY + 1 + l)%l;
        break;
    case 4                   //LEFT
        newX = (originX - 1 + l)%l;
        newY = originY;
        break;
    }
    int newPos = FindPosIndex(newX, newY);
    Grid[originPos] = 0;
    Grid[newPos] = 1;
    ParticlesPositions[particle] = newPos;
}

GridClass::int FindPosIndex(int x, int y){
    return x + SideLenght * y;
}

GridClass::int FindXFromPos(int position){
    return position % SideLenght;
}

GridClass::int FindYFromPos(int position){
    return position / SideLenght;
}