#pragma once


class Engine
{
    public:
        Engine();
        ///~Engine();
        void start() { isrunning = true;}
        void stop() { isrunning = false;}
        bool isRunning() {return isrunning;}



    private:
        bool isrunning = false;
};
