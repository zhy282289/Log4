
#include "DsLog4plugs.h"
#include "log4cplus/loggingmacros.h"

#ifdef _DEBUG
#pragma	comment(lib, "log4cplusD.lib")
#else
#pragma	comment(lib, "log4cplus.lib")
#endif





CDsLog4plugs::CDsLog4plugs(void)
	:m_fileOutputState(State_Close)
	,m_consoleOutputState(State_Close)
	,m_fileOutputLevel(LogLevel_Info|LogLevel_Warning|LogLevel_Error)
	,m_consoleOutputLevel(LogLevel_Info|LogLevel_Warning|LogLevel_Error)
	,m_fileAppender(0)
	,m_consoleAppender(0)
	,m_layout(0)
{
	//SharedAppenderPtr pConsoleAppender(new ConsoleAppender());
	//
	//SharedAppenderPtr pFileAppender(new FileAppender(LOG4CPLUS_TEXT("d:\\log4plug.txt")));

	////RollingFileAppender(m_filePath, 10 * 1024 * 1024, 5);
	//pConsoleAppender->setLayout(std::auto_ptr<Layout>(new SimpleLayout()));
	//pFileAppender->setLayout(std::auto_ptr<Layout>(new SimpleLayout()));


	//Logger pTestLogger = Logger::getInstance(LOG4CPLUS_TEXT("loggerName"));


	//pTestLogger.setLogLevel(ALL_LOG_LEVEL);

	//pTestLogger.addAppender(pConsoleAppender);
	//pTestLogger.addAppender(pFileAppender);

	//LOG4CPLUS_DEBUG(pTestLogger, "LOG4CPLUS_DEBUG");
	//LOG4CPLUS_ERROR(pTestLogger, "LOG4CPLUS_ERROR");
}


CDsLog4plugs::~CDsLog4plugs(void)
{
}


bool CDsLog4plugs::Initialize( const char *logPath /*= ""*/ )
{
	if (logPath == NULL)
	{
		return false;
	}
	
	m_logPath = logPath;
	m_fileAppender = new RollingFileAppender(m_logPath, 10 * 1024 * 1024, 5);
	//m_consoleAppender = new ConsoleAppender();
	m_layout = std::auto_ptr<Layout>(new PatternLayout("%d{%Y-%m-%d %H:%M:%S} %m%n"));
	m_fileAppender->setLayout(m_layout);
	//m_consoleAppender->setLayout(m_layout);

	m_fileLogger = Logger::getInstance(LOG4CPLUS_TEXT("FileLogger"));
	m_fileLogger.addAppender(m_fileAppender);
	//m_logger.addAppender(m_consoleAppender);
	m_fileOutputState = State_Open;

	return true;
}


void CDsLog4plugs::Log( const char *log, OutputLevel level /*= LogLevel_Debug*/ )
{
	
	if (m_fileOutputState == State_Open && (m_fileOutputLevel & level))
	{
		if (level & LogLevel_Info)
		{
			LOG4CPLUS_DEBUG(m_fileLogger, LOG4CPLUS_TEXT(tstring("INFO: ") + tstring(log)));
		}
		else if (level & LogLevel_Warning)
		{
			LOG4CPLUS_WARN(m_fileLogger, LOG4CPLUS_TEXT(tstring("WARN: ") + tstring(log)));
		}
		else if (level & LogLevel_Error)
		{
			LOG4CPLUS_ERROR(m_fileLogger, LOG4CPLUS_TEXT(tstring("ERROR: ") + tstring(log)));
		}
		else
		{
			LOG4CPLUS_DEBUG(m_fileLogger, LOG4CPLUS_TEXT(tstring("DEBUG: ") + tstring(log)));
		}
	}

	if (m_consoleOutputState == State_Open && (m_consoleOutputLevel & level))
	{
		if (level & LogLevel_Info)
		{
			LOG4CPLUS_DEBUG(m_consoleLogger, LOG4CPLUS_TEXT(tstring("INFO: ") + tstring(log)));
		}
		else if (level & LogLevel_Warning)
		{
			LOG4CPLUS_WARN(m_consoleLogger, LOG4CPLUS_TEXT(tstring("WARN: ") + tstring(log)));
		}
		else if (level & LogLevel_Error)
		{
			LOG4CPLUS_ERROR(m_consoleLogger, LOG4CPLUS_TEXT(tstring("ERROR: ") + tstring(log)));
		}
		else
		{
			LOG4CPLUS_DEBUG(m_consoleLogger, LOG4CPLUS_TEXT(tstring("DEBUG: ") + tstring(log)));
		}
	}
}


void CDsLog4plugs::AddConsoleOutput()
{
	if (m_consoleAppender == NULL)
	{
		m_consoleLogger = Logger::getInstance("ConsoleLogger");
		m_consoleAppender = new ConsoleAppender();
		m_consoleAppender->setLayout(std::auto_ptr<Layout>(new PatternLayout("%d{%Y-%m-%d %H:%M:%S} %m%n")));
		m_consoleLogger.addAppender(m_consoleAppender);
		m_consoleOutputState = State_Open;
	}
}

void CDsLog4plugs::OperatorOutput( OutputDevice dev, int level )
{
	if (dev == Device_File)
	{
		m_fileOutputLevel = level;
	}
	else if (dev == Device_Console)
	{
		m_consoleOutputLevel = level;
	}
}

void CDsLog4plugs::OperatorDevice( OutputDevice dev, OutputState state )
{
	if (dev == Device_File)
	{
		m_fileOutputState = state;
	}
	else if (dev == Device_Console)
	{
		m_consoleOutputState = state;
	}
}



Log4* CreateLog4()
{
	return new CDsLog4plugs();
}