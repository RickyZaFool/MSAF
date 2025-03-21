/*

CONVENTIONS USED
all internal variables start with capital letters and have capitals to separate words
all functions start with capital letters
all temporary variables and function parameters start with low letters and have capitals to separate words

*/
#include <TRandom3.h>

class GridMSAF
{
public:
    void Setup(int sideLenght, float theta, bool ordered);
    void Move(int particle, int direction);
    void SetGridSeed(int seed);
    int FindPosIndex(int x, int y);
    int FindXFromPos(int position);
    int FindYFromPos(int position);
    int ParticlePos(int particle);
    int ParticleX(int particle);
    int ParticleY(int particle);
    bool IsOccupied(int position);
    bool IsOccupied(int x, int y);


private:
    int SideLenght;
    int Seed = -1;
    TRandom3 Rnd;
    int NumberOfParticles;
    int SideLenght;
    std::vector<int> Grid;
    std::vector<int> ParticlesPositions;
}