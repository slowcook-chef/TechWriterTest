#include "AchievementHandler.h"
#include <iostream>

bool AchievementHandler::bQueryComplete = false;

AchievementHandler::AchievementHandler()
{
}

EOS_HAchievements AchievementHandler::GetAchievementHandle(EOS_HPlatform PlatformHandle)
{
	EOS_HAchievements achievementsHandle = EOS_Platform_GetAchievementsInterface(PlatformHandle);
	return achievementsHandle;
}

EOS_Achievements_DefinitionV2* AchievementHandler::GetAchievementDefinitions(EOS_HAchievements achievementHandle, EOS_HPlatform platformHandle, EOS_ProductUserId puid) {
	assert(puid != nullptr);
	//Define query options
	EOS_Achievements_QueryDefinitionsOptions queryDefinitionOptions = {};
	queryDefinitionOptions.ApiVersion = EOS_ACHIEVEMENTS_QUERYDEFINITIONS_API_LATEST;
	queryDefinitionOptions.LocalUserId = puid;

	//Query EOS and wait
	EOS_Achievements_QueryDefinitions(achievementHandle, &queryDefinitionOptions, puid, EOS_Achievements_OnQueryDefinitionsCompleteCallback);

	while (!bQueryComplete) {
		EOS_Platform_Tick(platformHandle);
	}

	EOS_Achievements_CopyAchievementDefinitionV2ByIndexOptions copyOptions = {};
	copyOptions.ApiVersion = EOS_ACHIEVEMENTS_COPYACHIEVEMENTDEFINITIONV2BYINDEX_API_LATEST;
	copyOptions.AchievementIndex = 0;

	EOS_Achievements_DefinitionV2* definitions = {};
	EOS_EResult result = EOS_Achievements_CopyAchievementDefinitionV2ByIndex(achievementHandle, &copyOptions, &definitions);
	assert(result == EOS_EResult::EOS_Success);
	assert(definitions != nullptr);



	return definitions;
}

void EOS_CALL AchievementHandler::EOS_Achievements_OnQueryDefinitionsCompleteCallback(const EOS_Achievements_OnQueryDefinitionsCompleteCallbackInfo* Data) {
	assert(Data != NULL);

	if (Data->ResultCode == EOS_EResult::EOS_Success)
	{
		std::cout << "Query Located!" << std::endl;
		bQueryComplete = true;
		return;
	}
	else
	{
		std::cout << "Query Failed, terminate manually" << std::endl;
		return;
	}
}
void AchievementHandler::Update() {
	//Tick the server
}