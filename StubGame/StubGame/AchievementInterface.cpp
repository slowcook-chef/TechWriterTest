#include "AchievementInterface.h"
#include <iostream>

bool AchievementInterface::bQueryComplete = false;
bool AchievementInterface::bUnlockComplete = false;
bool AchievementInterface::bQueryPlayerAchievementsComplete = false;
int AchievementInterface::achievementCount = 0;
AchievementInterface::AchievementInterface()
{
}

EOS_HAchievements AchievementInterface::GetAchievementHandle(EOS_HPlatform* platformHandle)
{
	EOS_HAchievements achievementsHandle = EOS_Platform_GetAchievementsInterface(*platformHandle);
	return achievementsHandle;
}

EOS_Achievements_DefinitionV2* AchievementInterface::GetAchievementDefinitions(EOS_HAchievements* achievementHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid) {
	assert(puid != nullptr);
	//Define query options
	EOS_Achievements_QueryDefinitionsOptions queryDefinitionOptions = {};
	queryDefinitionOptions.ApiVersion = EOS_ACHIEVEMENTS_QUERYDEFINITIONS_API_LATEST;
	queryDefinitionOptions.LocalUserId = *puid;

	//Query EOS and wait
	EOS_Achievements_QueryDefinitions(*achievementHandle, &queryDefinitionOptions, puid, EOS_Achievements_OnQueryDefinitionsCompleteCallback);

	while (!bQueryComplete) {
		EOS_Platform_Tick(*platformHandle);
	}

	//Get definition count, and set static count
	EOS_Achievements_GetAchievementDefinitionCountOptions definitionCountOptions = {};
	definitionCountOptions.ApiVersion = EOS_ACHIEVEMENTS_GETACHIEVEMENTDEFINITIONCOUNT_API_LATEST;
	int count = EOS_Achievements_GetAchievementDefinitionCount(*achievementHandle, &definitionCountOptions);
	achievementCount = count;

	//Copy cached definitions and add them to array to return
	EOS_Achievements_DefinitionV2* definitionsArray = new EOS_Achievements_DefinitionV2[count]; //Initialize array
	EOS_Achievements_DefinitionV2* definition = {}; //Cache definition
	EOS_Achievements_CopyAchievementDefinitionV2ByIndexOptions copyOptions = {}; //Cache copy options
	copyOptions.ApiVersion = EOS_ACHIEVEMENTS_COPYACHIEVEMENTDEFINITIONV2BYINDEX_API_LATEST;
	for (int i = 0; i < count; i++) {
		copyOptions.AchievementIndex = i;
		EOS_Achievements_CopyAchievementDefinitionV2ByIndex(*achievementHandle, &copyOptions, &definition);
		assert(definition != nullptr);
		definitionsArray[i] = *definition;
	}

	//Set static count, and return array
	
	return definitionsArray;
}
EOS_Achievements_PlayerAchievement* AchievementInterface::GetPlayerAchievement(EOS_HAchievements* achievementHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid) {
	assert(puid != nullptr);
	//Query player achievements and cache them locally
	EOS_Achievements_QueryPlayerAchievementsOptions playerAchievementOptions = {};
	playerAchievementOptions.ApiVersion = EOS_ACHIEVEMENTS_QUERYPLAYERACHIEVEMENTS_API_LATEST;
	playerAchievementOptions.TargetUserId = *puid;
	playerAchievementOptions.LocalUserId = *puid;
	EOS_Achievements_QueryPlayerAchievements(*achievementHandle, &playerAchievementOptions, puid, EOS_Achievements_OnQueryPlayerAchievementsCompleteCallback);
	while (!bQueryPlayerAchievementsComplete) {
		EOS_Platform_Tick(*platformHandle);
	}

	//Get achievement count
	EOS_Achievements_GetPlayerAchievementCountOptions playerAchievementCountOptions = {};
	playerAchievementCountOptions.ApiVersion = EOS_ACHIEVEMENTS_GETPLAYERACHIEVEMENTCOUNT_API_LATEST;
	playerAchievementCountOptions.UserId = *puid;
	int count = EOS_Achievements_GetPlayerAchievementCount(*achievementHandle, &playerAchievementCountOptions);
	achievementCount = count;

	//Copy player achievement by index
	EOS_Achievements_PlayerAchievement* playerAchievementArray = new EOS_Achievements_PlayerAchievement[count];
	EOS_Achievements_PlayerAchievement* playerAchievement = {};
	EOS_Achievements_CopyPlayerAchievementByIndexOptions copyOptions = {};
	copyOptions.ApiVersion = EOS_ACHIEVEMENTS_COPYPLAYERACHIEVEMENTBYINDEX_API_LATEST;
	copyOptions.TargetUserId = *puid;
	copyOptions.LocalUserId = *puid;
	for (int i = 0; i < count; i++) {
		copyOptions.AchievementIndex = i;
		EOS_Achievements_CopyPlayerAchievementByIndex(*achievementHandle, &copyOptions, &playerAchievement);
		playerAchievementArray[i] = *playerAchievement;
	}
	assert(playerAchievementArray != nullptr);

	return playerAchievementArray;
}
void AchievementInterface::ManualUnlockAchievement(EOS_HAchievements* achievementHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid, EOS_Achievements_DefinitionV2* definition) {
	assert(definition != nullptr);
	//Define unlock options
	EOS_Achievements_UnlockAchievementsOptions unlockOptions = {};
	unlockOptions.ApiVersion = EOS_ACHIEVEMENTS_UNLOCKACHIEVEMENTS_API_LATEST;
	unlockOptions.UserId = *puid;
	unlockOptions.AchievementIds = &definition->AchievementId;
	unlockOptions.AchievementsCount = 1;
	bUnlockComplete = false;

	//Unlock achievement and wait for response
	EOS_Achievements_UnlockAchievements(*achievementHandle, &unlockOptions, puid, EOS_Achievements_OnUnlockAchievementsCompleteCallback);
	while (!bUnlockComplete) {
		EOS_Platform_Tick(*platformHandle);
	}
	
}

void EOS_CALL AchievementInterface::EOS_Achievements_OnQueryDefinitionsCompleteCallback(const EOS_Achievements_OnQueryDefinitionsCompleteCallbackInfo* Data) {
	assert(Data != NULL);

	if (Data->ResultCode == EOS_EResult::EOS_Success)
	{
		std::cout << "Game Achievements Located!" << std::endl;
		bQueryComplete = true;
		return;
	}
	else
	{
		std::cout << "Query Failed, terminate manually" << std::endl;
		return;
	}
}
void EOS_CALL AchievementInterface::EOS_Achievements_OnUnlockAchievementsCompleteCallback(const EOS_Achievements_OnUnlockAchievementsCompleteCallbackInfo* Data) {
	assert(Data != NULL);
	if (Data->ResultCode == EOS_EResult::EOS_Success)
	{
		std::cout << "Achievement Unlocked!" << std::endl;
		bUnlockComplete = true;
		return;
	}
	else
	{
		std::cout << "Achievement Unlock Failed, terminate manually" << std::endl;
		return;
	}
}
void EOS_CALL AchievementInterface::EOS_Achievements_OnQueryPlayerAchievementsCompleteCallback(const EOS_Achievements_OnQueryPlayerAchievementsCompleteCallbackInfo* Data) {
	assert(Data != NULL);
	if (Data->ResultCode == EOS_EResult::EOS_Success)
	{
		std::cout << "Player Achievements Located!" << std::endl;
		bQueryPlayerAchievementsComplete = true;
		return;
	}
	else
	{
		std::cout << "Player Achievements Query Failed, terminate manually" << std::endl;
		return;
	}
}