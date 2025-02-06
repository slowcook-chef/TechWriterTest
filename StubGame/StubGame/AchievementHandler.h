#pragma once

#include <eos_sdk.h>
#include <eos_init.h>
#include <eos_achievements.h>
#include <eos_achievements_types.h>
#include <cassert>
class AchievementHandler {
public:
	AchievementHandler();

	EOS_HAchievements GetAchievementHandle(EOS_HPlatform platformHandle);
	EOS_Achievements_DefinitionV2* GetAchievementDefinitions(EOS_HAchievements achievementHandle, EOS_HPlatform platformHandle, EOS_ProductUserId puid);
	void Update();
private:
	static bool bQueryComplete;
	static void EOS_CALL EOS_Achievements_OnQueryDefinitionsCompleteCallback(const EOS_Achievements_OnQueryDefinitionsCompleteCallbackInfo* Data);
};