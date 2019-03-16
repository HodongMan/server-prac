#pragma once

enum MI_TimeIds
{
	MI_TIMEID_0,
	MI_TIMEID_1,
	MI_TIMEID_2,
	MI_TIMEID_3,
	MI_TIMEID_4,
	MI_TIMEID_5,
	MI_TIMEID_6,
	MI_TIMEID_7,

	NUM_MI_TIMEIDS
};


typedef unsigned __int64 MI_TimeUnit;

enum MI_TimerMethod
{
	MI_RDTSC,
	MI_TIMEGETTIME,
	MI_QPC,
};

class MI_Time
{
private:
	MI_Time();
	~MI_Time();

	static MI_Time* ourInstance;

	static MI_TimeUnit ourStartTimes[NUM_MI_TIMEIDS];

	double* ourInternalElapsedTimes;
	double ourInternalCurrentTime;

	int myCurrentTimeIndex;

	void Calibrate();

public:
	static bool Create();
	static void Destroy();

	static MI_Time* GetInstance() { return ourInstance; }

	static unsigned int GetSystemTime();	// Returns system time in ms

	static void GetExactTime(MI_TimeUnit* aReturnTime);
	static MI_TimeUnit GetExactTime() { MI_TimeUnit t; GetExactTime(&t); return t; }
	static float ConvertTimeToSeconds(const MI_TimeUnit& aTime);

	static void StartTimer(MI_TimeIds aTimerId);
	static MI_TimeUnit ReadTimer(MI_TimeIds aTimerId);

	static void GetDateAndTimeString(char* aResult255CharArray, bool aIncludeDate, bool aIncludeHours, bool aIncludeMin, bool aIncludeSecs);	// dev util: returns "20060801_18h17m00s"
	static void GetDateAndTime(int& aResultYear, int& aResultMonth, int& aResultDay, int& aResultHour, int& aResultMin, int& aResultSec, int& aResultMs);

	static float ourElapsedTime;		// Frame delta time, in seconds
	static float ourCurrentTime;		// Time elapsed since program start, in seconds

	static double ourRealElapsedTime;	// Not affected by FPS capping or pausing
	static double ourRealCurrentTime;	// Not affected by FPS capping or pausing

	static unsigned int ourCurrentSystemTime;	// In milliseconds since OS start (Note: don't cast this to a float, precision will be terrible! Subtract ints to get delta value, then cast to float if you must)

	static unsigned int ourFrameCounter;

	static bool ourUseAveragedTimeGetTime;
	static bool ourTimerProblemDetected;

	void ResetCurrentTime();
	void Update(); // call once each frame

	void SetMaxFPS(float aFPS = -1.0f);
	void SetMinFPS(float aFPS = -1.0f);

	void Pause(bool aState);
	bool IsPaused();

	void SetTimeScale(float aScaleFactor = 1.f); // premultiplier for time values (ourElapsedTime/ourCurrentTime)
	float GetTimeScale() const { return myTimeScale; }

	void EnforceMaxFPS();

	static void __stdcall GetRDTSC(MI_TimeUnit* aReturnTime);
	static bool GetQPC(MI_TimeUnit* aReturnTime);	// Returns false if a leap was detected

	float myMinElapsedTime;
	float myMaxElapsedTime;
	bool myPauseFlag;

	float myTimeScale;

	static MI_TimerMethod ourTimerMethod;

	static double (__cdecl* ourTimeUpdateOverrideCallback)(double);
};