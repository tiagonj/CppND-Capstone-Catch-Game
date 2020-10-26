#include "Metronome.h"

#include <cassert>
#include <chrono>
#include <cmath>
#include <thread>

#define MICROSECONDS_PER_SECOND ((float)1000000.0f)
#define MAX_HISTORIC_SAMPLES (100)

Metronome::Metronome(uint32_t minUpdatesPerSecond, uint32_t maxUpdatesPerSecond)
    : _minUpdatesPerSecond(minUpdatesPerSecond),
      _maxUpdatesPerSecond(maxUpdatesPerSecond),
      _updatesPerSecond(minUpdatesPerSecond),
      _executionDurationInUsAccumulator(0)
{
}

Metronome::Metronome(uint32_t updatesPerSecond)
{
    Metronome(updatesPerSecond, updatesPerSecond);
}

Metronome::~Metronome()
{
}

time_value_t Metronome::StartMeasurement()
{
    return std::chrono::system_clock::now();
}

void Metronome::StopMeasurementAndSleepIfApplicable(time_value_t& startTime)
{
    auto endTime = std::chrono::system_clock::now();

    long executionDurationInUs =
        std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();

    assert(executionDurationInUs >= 0);

    long targetDurationInUs = TargetDurationInUs();

    if (executionDurationInUs < targetDurationInUs)
    {
        long sleepDurationInUs = targetDurationInUs - executionDurationInUs;
        std::this_thread::sleep_for(std::chrono::microseconds(sleepDurationInUs));
    }

    AdjustInternals(executionDurationInUs);
}

uint32_t Metronome::UpdatesPerSecond()
{
    return _updatesPerSecond;
}

long Metronome::TargetDurationInUs()
{
    return std::lroundf(MICROSECONDS_PER_SECOND / _updatesPerSecond);
}

void Metronome::AdjustInternals(uint32_t executionDurationInUs)
{
    // Add new sample value and then remove the oldest value if the
    // maximum number of samples has been exceeded
    _historicExecutionDurationsInUs.push_back(executionDurationInUs);

    if (_historicExecutionDurationsInUs.size() > MAX_HISTORIC_SAMPLES)
    {
        auto oldestValueIterator = _historicExecutionDurationsInUs.begin();
        _executionDurationInUsAccumulator -= *oldestValueIterator;
        _historicExecutionDurationsInUs.erase(oldestValueIterator);
    }

    // Add the new sample value to the accumulator itself
    assert(_executionDurationInUsAccumulator <= UINT32_MAX - executionDurationInUs);
    _executionDurationInUsAccumulator += executionDurationInUs;

    // Nudge the number of updates per second (up or down) based on the average
    if (_historicExecutionDurationsInUs.size() == MAX_HISTORIC_SAMPLES)
    {
        double averageExecDurationInUs =
            (double)_executionDurationInUsAccumulator / MAX_HISTORIC_SAMPLES;

        long averageUpdatesPerSecond = lround(MICROSECONDS_PER_SECOND / averageExecDurationInUs);

        if (averageUpdatesPerSecond > _updatesPerSecond)
        {
            _updatesPerSecond = std::min(_updatesPerSecond + 1, _maxUpdatesPerSecond);
        }
        else if (averageUpdatesPerSecond < _updatesPerSecond)
        {
            _updatesPerSecond = std::max(_updatesPerSecond - 1, _minUpdatesPerSecond);
        }
    }
}

AutoMetronome::AutoMetronome(Metronome& m) : _metronome(m)
{
    _startTime = _metronome.StartMeasurement();
}

AutoMetronome::~AutoMetronome()
{
    _metronome.StopMeasurementAndSleepIfApplicable(_startTime);
}
