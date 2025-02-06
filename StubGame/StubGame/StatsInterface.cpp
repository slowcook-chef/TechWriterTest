#include "StatsInterface.h"
#include <iostream>


bool StatsInterface::bQueryComplete = false;
bool StatsInterface::bIngestComplete = false;
int StatsInterface::statCount = 0;
StatsInterface::StatsInterface()
{
}

EOS_HStats StatsInterface::GetStatsHandle(EOS_HPlatform* platformHandle)
{
	EOS_HStats statsHandle = EOS_Platform_GetStatsInterface(*platformHandle);
	return statsHandle;
}


void StatsInterface::IngestStat(EOS_HStats* statsHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid, const char* statName, int amount)
{
	assert(puid != nullptr);
	//Define ingest data options
	EOS_Stats_IngestData ingestData = {};
	ingestData.ApiVersion = EOS_STATS_INGESTDATA_API_LATEST;
	ingestData.StatName = statName;
	ingestData.IngestAmount = amount;
	EOS_Stats_IngestData ingestDataArray[1] = { ingestData };

	//Define ingest stat options
	EOS_Stats_IngestStatOptions ingestOptions = {};
	ingestOptions.ApiVersion = EOS_STATS_INGESTSTAT_API_LATEST;
	ingestOptions.LocalUserId = *puid;
	ingestOptions.Stats = ingestDataArray;
	ingestOptions.StatsCount = 1;
	ingestOptions.TargetUserId = *puid;

	//Ingest and wait for response
	EOS_Stats_IngestStat(*statsHandle, &ingestOptions, puid, EOS_Stats_OnIngestStatCompleteCallback);
	bIngestComplete = false;
	while (!bIngestComplete) {
		EOS_Platform_Tick(*platformHandle);
	}
}

EOS_Stats_Stat* StatsInterface::GetStats(EOS_HStats* statsHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid)
{
	assert(puid != nullptr);
	//Define query stat options
	const char* statNames[] = { "Pancakes" };
	EOS_Stats_QueryStatsOptions statsOptions = {};
	statsOptions.ApiVersion = EOS_STATS_QUERYSTATS_API_LATEST;
	statsOptions.TargetUserId = *puid;
	statsOptions.LocalUserId = *puid;
	statsOptions.StatNames = statNames;
	statsOptions.StatNamesCount = 1;
	statsOptions.StartTime = EOS_STATS_TIME_UNDEFINED;
	statsOptions.EndTime = EOS_STATS_TIME_UNDEFINED;

	//Query player stats and cache them locally
	EOS_Stats_QueryStats(*statsHandle, &statsOptions, puid, EOS_Stats_OnQueryStatsCompleteCallback);
	bQueryComplete = false;
	while (!bQueryComplete) {
		EOS_Platform_Tick(*platformHandle);
	}

	//Get stat count
	EOS_Stats_GetStatCountOptions statCountOptions = {};
	statCountOptions.ApiVersion = EOS_STATS_GETSTATCOUNT_API_LATEST;
	statCountOptions.TargetUserId = *puid;
	statCount = EOS_Stats_GetStatsCount(*statsHandle, &statCountOptions);

	//Copy cached stats and add them to array to return
	EOS_Stats_Stat* statsArray = new EOS_Stats_Stat[statCount]; //Initialize array
	EOS_Stats_CopyStatByIndexOptions copyOptions = {}; //Cache copy options
	EOS_Stats_Stat* stats = {};
	copyOptions.ApiVersion = EOS_STATS_COPYSTATBYINDEX_API_LATEST;
	copyOptions.TargetUserId = *puid;
	for (int i = 0; i < statCount; i++) {
		copyOptions.StatIndex = i;
		EOS_Stats_CopyStatByIndex(*statsHandle, &copyOptions, &stats);
		assert(stats != nullptr);
		statsArray[i] = *stats;
	}

	return statsArray;
}

void StatsInterface::DisplayPlayerStats(EOS_Stats_Stat* playerStats)
{
	assert(playerStats != nullptr);
	std::cout << "/------Player Stats------\\" << std::endl;
	for (int i = 0; i < statCount; i++)
	{
		std::cout << "Stat: " << playerStats[i].Name << " Value: " << playerStats[i].Value << std::endl;
	}
}

void EOS_CALL StatsInterface::EOS_Stats_OnQueryStatsCompleteCallback(const EOS_Stats_OnQueryStatsCompleteCallbackInfo* Data)
{
	assert(Data != NULL);
	if (Data->ResultCode == EOS_EResult::EOS_Success)
	{
		std::cout << "Player Stats Located!" << std::endl;
		bQueryComplete = true;
		return;
	}
	else
	{
		std::cout << "Query Failed, terminate manually" << std::endl;
		return;
	}
}

void EOS_CALL StatsInterface::EOS_Stats_OnIngestStatCompleteCallback(const EOS_Stats_IngestStatCompleteCallbackInfo* Data)
{
	assert(Data != NULL);
	if (Data->ResultCode == EOS_EResult::EOS_Success)
	{
		std::cout << "Stat Ingested!" << std::endl;
		bIngestComplete = true;
		return;
	}
	else
	{
		std::cout << "Ingest Failed, terminate manually" << std::endl;
		return;
	}
}