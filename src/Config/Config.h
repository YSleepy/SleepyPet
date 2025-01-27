#pragma once
#include <QFile>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>

#define NAME_SPACE_NS_SLEEPY_CONFIG_BEGAN namespace NS_SleepyConfig {
#define NAME_SPACE_NS_SLEEPY_CONFIG_END }

NAME_SPACE_NS_SLEEPY_CONFIG_BEGAN
const QString CONFIG_FILE_PATH = ":/Config/config/config.json";
const QString AI_CONFIG = "AiConfig";
const QString AI_APP_ID = "APPID";
const QString AI_API_KEY = "APIKey";
const QString AI_API_SECRET = "APISecret";
const QString AI_DOMAIN = "domain";
const QString AI_URL = "url";
using namespace std;
		
class SleepyConfig
{
public:
	SleepyConfig(const QString& filePath);
	void resetFile(const QString& filePath);
	bool openConfig(QIODevice::OpenMode mode = QIODevice::ReadOnly | QIODevice::Text);
	bool closeConfig();
	bool readAllToJson();
	bool getAiConfigObj();
	void configADragon();
	QString getAPPID();
	QString getAPIKey();
	QString getAPISecret();
	QString getDomain();
	QString getUrl();
private:
	QFile* file;
	QJsonDocument jsonDoc;
	QJsonObject aiConfig;

};

NAME_SPACE_NS_SLEEPY_CONFIG_END
