#ifndef TIMER_HPP
#define TIMER_HPP

#define FPS_TARGET 60.0f
#define SEC_TO_MS 1000.0f
#define DEFAULT_DELTATIME 1.5f

class Timer
{
    public:
        inline static Timer* Instance() { return _timer = _timer != nullptr ? _timer : new Timer(); }
    
    public:
        void Tick();
        float GetDeltaTime();
        inline float GetFrameTime() { return _frameTime; }

    private:
        Timer();
        static Timer* _timer;
        float _frameTime;
        float _lastFrameTime;
};

#endif