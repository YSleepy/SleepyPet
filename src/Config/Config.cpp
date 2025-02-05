#include "Config.h"

#include "Base/SleepyTool.h"
#include <QDebug>

using namespace NS_SleepyConfig;
SleepyConfig::SleepyConfig(const QString& filePath)
{
	file = new QFile(filePath);
}

void SleepyConfig::resetFile(const QString& filePath)
{
	delete file;
	file = new QFile(filePath);
}



bool SleepyConfig::openConfig(QIODevice::OpenMode mode)
{
	CHECK_RETURN_RET_LOG(file != nullptr, false, "file is null");
	if (file->isOpen())
	{
		qDebug() << "File is already open!";
		return true;
	}
	return file->open(mode);
}

bool SleepyConfig::closeConfig()
{
	if (file->isOpen())
	{
		file->close();
	}
	return true;
}

bool SleepyConfig::readAllToJson()
{
	QByteArray fileContent = file->readAll();
	if (fileContent.isEmpty()) return false;
	jsonDoc = QJsonDocument::fromJson(fileContent);
	if (jsonDoc.isNull() || !jsonDoc.isObject()) {
		qWarning() << "Invalid JSON format or not an object";
		return false;
	}
	return true;
}

bool SleepyConfig::getAiConfigObj()
{
	if (jsonDoc.isNull()) return false;
	QJsonObject rootObj = jsonDoc.object();
	if (!rootObj.contains("AiConfig") || !rootObj["AiConfig"].isObject()) {
		qWarning() << "Missing AiConfig node or formatting error!";
		return false;
	}
	aiConfig = rootObj[AI_CONFIG].toObject();
	return true;
}

void SleepyConfig::configADragon()
{
	CHECK_RETURN_LOG(openConfig(), "open file failed");
	CHECK_RETURN_LOG(readAllToJson(), "read file failed");
	CHECK_RETURN_LOG(getAiConfigObj(), "get ai config failed");
}

QString SleepyConfig::getAPPID()
{
	return aiConfig.value(AI_APP_ID).toString();
}

QString SleepyConfig::getAPIKey()
{
	return aiConfig.value(AI_API_KEY).toString();
}

QString SleepyConfig::getAPISecret()
{
	return aiConfig.value(AI_API_SECRET).toString();
}

QString SleepyConfig::getDomain()
{
	return aiConfig.value(AI_DOMAIN).toString();
}

QString SleepyConfig::getUrl()
{
	return aiConfig.value(AI_URL).toString();
}
