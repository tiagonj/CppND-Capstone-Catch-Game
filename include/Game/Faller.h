#ifndef CATCH_GAME_FALLER_H
#define CATCH_GAME_FALLER_H

#include <cstdint>
#include <string>

// Interface/base class for Faller objects
class Faller
{
  public:
    ~Faller();
    virtual void Update(double timeDeltaInSeconds, float xAccelInUnitsPerSecSquared,
                        float yAccelInUnitsPerSecSquared); // Default update (can be overriden)
    float UpPosition() const;
    float DownPosition() const;
    float LeftPosition() const;
    float RightPosition() const;
    uint32_t RewardPoints() const;
    virtual std::string& Name() const = 0;

  protected:
    Faller(float width, float height, float x, float vx, float vy, uint32_t rewardPoints);
    void UpdatePosAndVel(double timeDeltaInSeconds, float& pos, float& vel, float accel);
    void UpdateXPosAndVel(double timeDeltaInSeconds, float accel);

  private:
    void AttemptXNaiveIntegration(double timeDeltaInSeconds, float accel, bool& exceedsLeftLimitPos,
                                  bool& exceedsRightLimitPos);
    static double GetBounceTimeDelta(double intervalInSeconds, float position, float limitPosition,
                                     float velocity, float accel);
    static void SolveQuadraticEq(double a, double b, double c, double& smallestSolution,
                                 double& largestSolution);
    Faller() = delete;
    Faller(Faller&) = delete;
    Faller(Faller&&) = delete;
    Faller& operator=(Faller&) = delete;
    Faller& operator=(Faller&&) = delete;

  protected:
    float _xPosition; // Note: positions are in normalised units (0.0 ~ 1.0)
    float _yPosition;
    float _xVelocityInUnitsPerSecond;
    float _yVelocityInUnitsPerSecond;
    uint32_t _rewardPoints;

  private:
    float _halfWidth{0.0f};
    float _halfHeight{0.0f};
};

#endif
