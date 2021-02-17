#pragma once


class Engine
{
    public:
        void start() { isrunning = true;}
        void stop() { isrunning = false;}
        bool isRunning() {return isrunning;}



    private:
        bool isrunning = false;
};
