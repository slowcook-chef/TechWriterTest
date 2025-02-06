#pragma once

#include <eos_sdk.h>
#include <eos_init.h>
#include <eos_achievements.h>
#include <eos_achievements_types.h>
#include <cassert>
class AchievementInterface {
public:
	AchievementInterface();
	EOS_HAchievements GetAchievementHandle(EOS_HPlatform* platformHandle);
	EOS_Achievements_DefinitionV2* GetAchievementDefinitions(EOS_HAchievements* achievementHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid);
	EOS_Achievements_PlayerAchievement* GetPlayerAchievements(EOS_HAchievements* achievementHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid);
	void ManualUnlockAchievement(EOS_HAchievements* achievementHandle, EOS_HPlatform* platformHandle, EOS_ProductUserId* puid, EOS_Achievements_DefinitionV2* definition);
	void DisplayPlayerAchievements(EOS_Achievements_PlayerAchievement* playerAchievements);
	void DisplayAchievementDefinitions(EOS_Achievements_DefinitionV2* definitions);
	
private:
	static void EOS_CALL EOS_Achievements_OnQueryDefinitionsCompleteCallback(const EOS_Achievements_OnQueryDefinitionsCompleteCallbackInfo* Data);
	static void EOS_CALL EOS_Achievements_OnUnlockAchievementsCompleteCallback(const EOS_Achievements_OnUnlockAchievementsCompleteCallbackInfo* Data);
	static void EOS_CALL EOS_Achievements_OnQueryPlayerAchievementsCompleteCallback(const EOS_Achievements_OnQueryPlayerAchievementsCompleteCallbackInfo* Data);
	static int achievementCount;
	static bool bQueryComplete;
	static bool bUnlockComplete;
	static bool bQueryPlayerAchievementsComplete;
};