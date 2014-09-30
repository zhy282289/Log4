#ifndef LOG4PLUGSINTERFACE_H_H 
#define LOG4PLUGSINTERFACE_H_H



#ifdef LOG4PLUGSINTERFACE_EXT
#define LOG4PLUGSINTERFACE_EXPORT __declspec(dllexport)
#else
#define LOG4PLUGSINTERFACE_EXPORT __declspec(dllimport)
#endif

enum OutputDevice
{
	Device_File = 0x1,
	Device_Console = 0x2,
};
enum OutputState
{
	State_Close,
	State_Open,
};
enum OutputLevel
{
	LogLevel_Info = 0x1, 
	LogLevel_Warning = 0x2, 
	LogLevel_Error = 0x4,
};



class LOG4PLUGSINTERFACE_EXPORT Log4
{
public:
	virtual bool Initialize(const char *logPath = "") = 0;
	virtual void Log(const char *log, OutputLevel level = LogLevel_Info) = 0;

	virtual void AddConsoleOutput() = 0;
	virtual void OperatorOutput(OutputDevice dev, int level) = 0;
	virtual void OperatorDevice(OutputDevice dev, OutputState state) = 0;
	

};



LOG4PLUGSINTERFACE_EXPORT Log4* CreateLog4();




















#endif