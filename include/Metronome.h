#ifndef CATCH_GAME_METRONOME_H
#define CATCH_GAME_METRONOME_H

#include <chrono>
#include <cstdint>
#include <deque>
#include <functional>

using time_value_t = std::chrono::system_clock::time_point;

// Regulates game loop time by throttling the number of updates per second
// based on the average value of the game loop execution duration
class Metronome
{
  public:
    Metronome(uint32_t minUpdatesPerSecond, uint32_t maxUpdatesPerSecond);
    Metronome(uint32_t updatesPerSecond);
    ~Metronome();

    time_value_t StartMeasurement();
    void StopMeasurementAndSleepIfApplicable(time_value_t& startTime);
    uint32_t UpdatesPerSecond();

  private:
    Metronome(Metronome&) = delete;
    Metronome(Metronome&&) = delete;
    Metronome& operator=(Metronome&) = delete;
    Metronome& operator=(Metronome&&) = delete;

    long TargetDurationInUs();
    void AdjustInternals(uint32_t executionDurationInUs);

  private:
    uint32_t _minUpdatesPerSecond{0};
    uint32_t _maxUpdatesPerSecond{0};
    uint32_t _updatesPerSecond{0};

    std::deque<uint32_t> _historicExecutionDurationsInUs;
    uint32_t _executionDurationInUsAccumulator{0};
};

// Provides clean encapsulation for the Metronome class behaviour
class AutoMetronome
{
  public:
    AutoMetronome(Metronome& m);
    ~AutoMetronome();

  private:
    AutoMetronome() = delete;
    AutoMetronome(AutoMetronome&) = delete;
    AutoMetronome(AutoMetronome&&) = delete;
    AutoMetronome& operator=(AutoMetronome&) = delete;
    AutoMetronome& operator=(AutoMetronome&&) = delete;

  private:
    Metronome& _metronome;
    time_value_t _startTime;
};

#endif
