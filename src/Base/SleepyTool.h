#pragma once
#include <QDebug>

enum class LOG_LEVEL
{
	DEBUG,
	WARNING,
	CRITICAL,
	FATAL
};

//void Q_LOG()
//{
//	
//}

#define CHECK_RETURN_RET_LOG(cond, ret, log) \
	do {									 \
    	if (!(cond)) {						 \
            qDebug() << (log);				 \
            return ret;						 \
    	}									 \
    } while (0)

#define CHECK_RETURN_LOG(cond, log)			 \
	do {									 \
    	if (!(cond)) {						 \
            qDebug() << (log);				 \
            return;							 \
    	}									 \
    } while (0)
