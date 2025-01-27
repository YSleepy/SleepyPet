#pragma once
#include <QDebug>

#define CHECK_RETURN_RET_LOG(cond, ret, log) \
	do {									 \
    	if (!(cond)) {						 \
            qDebug() << log;				 \
            return ret;						 \
    	}									 \
    } while (0)
