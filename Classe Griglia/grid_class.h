/*

CONVENTIONS USED
all internal variables start with capital letters and have capitals to separate words
all functions start with capital letters
all temporary variables and function parameters start with low letters and have capitals to separate words

*/


class GridMSAF
{
public:
    void Setup(int sideLenght, float theta, bool ordered);
    void Move(int particle, int direction);
    int FindPosIndex(int x, int y);
    int ParticlePos(int particle);
    int ParticleX(int particle);
    int ParticleY(int particle);
    bool IsOccupied(int position);
    bool IsOccupied(int x, int y);


private:
    int NumberOfParticles;
    int SideLenght;
    std::vector<int> Grid;
    std::vector<int> ParticlesPositions;
}