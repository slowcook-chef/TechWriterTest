#pragma once

#include "AchievementInterface.h"
#include <eos_stats.h>
class StatsInterface
{
public:
	StatsInterface();
	EOS_HStats GetStatsHandle(EOS_HPlatform* platformHandle);
	EOS_Stats_Stat* GetStats(EOS_HStats* statsHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid);
	//Ingest stats
	void IngestStat(EOS_HStats* statsHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid, const char* statName, int amount);
	void DisplayPlayerStats(EOS_Stats_Stat* playerStats);

private:
	static void EOS_CALL EOS_Stats_OnQueryStatsCompleteCallback(const EOS_Stats_OnQueryStatsCompleteCallbackInfo* Data);
	static void EOS_CALL EOS_Stats_OnIngestStatCompleteCallback(const EOS_Stats_IngestStatCompleteCallbackInfo* Data);
	static int statCount;
	static bool bQueryComplete;
	static bool bIngestComplete;
};