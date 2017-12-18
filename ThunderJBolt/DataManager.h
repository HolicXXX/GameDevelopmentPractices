#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#define MAX_HP 1000

class DataManager
{
public:
	static DataManager* getDataManager();

	void init();

	int getPlayerHP(){ return m_playerHP; }
	void setPlayerHP(int hp = MAX_HP){ m_playerHP = hp; }
	int getScore(){ return m_score; }
	void setScore(int s = 0){ m_score = s; }
	int getLevel(){ return m_level; }
	void setLevel(int l = 1){ m_level = l; }
	int getDefeatEnemyNum(){ return m_defeatEnemy; }
	void setDefeatEnemyNum(int n = 0){ m_defeatEnemy = n; }

private:
	DataManager();
	~DataManager();
	int m_playerHP;
	int m_score;
	int m_level;
	int m_defeatEnemy;
};



#endif