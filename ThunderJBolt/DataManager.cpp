#include "DataManager.h"

static DataManager* _dataManager = nullptr;

DataManager* DataManager::getDataManager()
{
	if (!_dataManager)
	{
		_dataManager = new DataManager();
	}
	return _dataManager;
}

void DataManager::init()
{
	setLevel();
	setPlayerHP();
	setScore();
	setDefeatEnemyNum();
}

DataManager::DataManager()
{
	m_playerHP = MAX_HP;
	m_score = 0;
	m_level = 1;
	m_defeatEnemy = 0;
}

DataManager::~DataManager()
{
}
