
#ifndef DSLOG4PLUGS_H_H
#define DSLOG4PLUGS_H_H

#include <string>
using std::string;

#include <log4cplus/logger.h>//定义Log对象
#include <log4cplus/consoleappender.h>//输出到控制台
#include <log4cplus/fileappender.h>//输出到文件
#include <log4cplus/layout.h>//输出格式

using namespace log4cplus;
using namespace log4cplus::helpers;

#include "Log4plugsInterface.h"

class CDsLog4plugs : public Log4
{
public:
	CDsLog4plugs(void);
	~CDsLog4plugs(void);

	virtual bool Initialize(const char *logPath = "");
	virtual void Log(const char *log, OutputLevel level = LogLevel_Info);

	virtual void AddConsoleOutput();
	virtual void OperatorOutput(OutputDevice dev, int level);
	virtual void OperatorDevice(OutputDevice dev, OutputState state);

private:
	SharedAppenderPtr	m_consoleAppender;
	SharedAppenderPtr	m_fileAppender;

	std::auto_ptr<Layout>	m_layout;


	Logger		m_fileLogger;
	Logger		m_consoleLogger;
	string		m_logPath;

	OutputState		m_fileOutputState;
	OutputState		m_consoleOutputState;
	int			m_fileOutputLevel;
	int			m_consoleOutputLevel;

};




#endif