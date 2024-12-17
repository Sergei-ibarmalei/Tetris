#include <chrono>



class Timer 
{
    private:
    std::chrono::steady_clock::time_point startTime;
    int duration; // продолжительность в секундах
    bool isRunning;

    public:
        Timer() : startTime(), duration(0), isRunning(false) {}



    void start(int seconds) 
    {
        duration = seconds;
        startTime = std::chrono::steady_clock::now();
        isRunning = true;
    }



    bool hasElapsed() {

        if (!isRunning) return false;



        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(
            currentTime - startTime).count();

        if (elapsedTime >= duration) 
        {
            // Если время прошло, сбрасываем таймер
            isRunning = false;
            return true;
        }
        return false;
    }



    void reset() {
        isRunning = false;
    }


};