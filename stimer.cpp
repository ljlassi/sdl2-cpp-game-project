#include "stimer.h"

STimer::STimer()
{
    //Initialize the variables
    mStartTicks = 0;
    mPausedTicks = 0;
    mPaused = false;
    mStarted = false;
}
void STimer::start()
{
    //Start the timer
    mStarted = true;
    mPaused = false;

    //Get the current clock time
    mStartTicks = SDL_GetTicks();
}
void STimer::stop()
{
    //Stop the timer
    mStarted = false;
    mPaused = false;
}
void STimer::pause()
{
    //If the timer is running and isn't already paused
    if (mStarted && !mPaused)
    {
        //Pause the timer
        mPaused = true;

        //Calculate the paused ticks
        mPausedTicks = SDL_GetTicks() - mStartTicks;
    }
}
void STimer::unpause()
{
    //If the timer is running and is paused
    if (mStarted && mPaused)
    {
        //Unpause the timer
        mPaused = false;

        //Reset the starting ticks
        mStartTicks = SDL_GetTicks() - mPausedTicks;

        //Reset the paused ticks
        mPausedTicks = 0;
    }
}
Uint32 STimer::getTicks()
{
    //If the timer is running
    if (mStarted)
    {
        //If the timer is paused
        if (mPaused)
        {
            //Return the number of ticks when the timer was paused
            return mPausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - mStartTicks;
        }
    }

    //If the timer isn't running, return 0
    return 0;
}
bool STimer::isStarted()
{
    //Return whether the timer is started
    return mStarted;
}
bool STimer::isPaused()
{
    //Return whether the timer is paused
    return mPaused;
}
