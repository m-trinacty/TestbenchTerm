#ifndef TIMEMANAGER_H
#define TIMEMANAGER_H


class timeManager
{
public:
    timeManager();
    template<typename F>
    static bool stopWatch(F f);
    static void sleep(int seconds);

};

#endif // TIMEMANAGER_H
