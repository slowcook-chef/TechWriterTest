// Copyright Epic Games, Inc. All Rights Reserved.

#include <Windows.h>
#include <iostream>
#include <Windows/eos_Windows.h>
#include <eos_init.h>
#include <eos_logging.h>
#include <eos_common.h>
#include <eos_auth.h>
#include <eos_connect.h>
#include <eos_sdk.h>
#include <cassert>
#include <string.h>
#include "SDKConfig.h"
#include "PlatformHandler.h"
#include "AuthHandler.h"
#include "AchievementInterface.h"

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	// Run the above line to look for memory leaks ^
	
	// Initialize config and platform
	SDKConfig* config = new SDKConfig;
	PlatformHandler* platformInitializer = new PlatformHandler();
	EOS_HPlatform* platformHandle = new EOS_HPlatform();
	*platformHandle = platformInitializer->InitializePlatform(config);
	assert(platformHandle != nullptr);

	// Login and retrieve a PUID
	AuthHandler* auth = new AuthHandler();
	EOS_ProductUserId* puid = new EOS_ProductUserId();
	*puid = auth->Login(config, *platformHandle);
	assert(puid != nullptr);
	std::cout << "Logged in and PUID is: " << puid << std::endl;

	//Initialize the achievement interface and handle
	AchievementInterface* achievementIniterface = new AchievementInterface();
	EOS_HAchievements* achievementHandle = new EOS_HAchievements();
	*achievementHandle = achievementIniterface->GetAchievementHandle(platformHandle);
	assert(achievementHandle != nullptr);

	//Display all StubGame locked achievements
	EOS_Achievements_DefinitionV2* definitionArray = achievementIniterface->GetAchievementDefinitions(achievementHandle, platformHandle, puid);
	assert(definitionArray != nullptr);
	EOS_Achievements_DefinitionV2* iterator = definitionArray;
	std::cout << "/------StubGame Locked Achievements------\\" << std::endl;
	for (int i = 0; i < achievementIniterface->achievementCount; i++)
	{
		iterator = &definitionArray[i];
		std::cout << "Achievement: " << iterator->LockedDisplayName << std::endl;
		iterator++;
	}

	//Unlock the first achievement manually, or not
	EOS_Achievements_DefinitionV2* achievement = &definitionArray[0];
	std::cout << "Would you like to unlock an achievement? (y/n)" << std::endl;
	char input;
	std::cin >> input;
	if (input == 'y') {
		achievementIniterface->ManualUnlockAchievement(achievementHandle, platformHandle, puid, achievement);
	}
	else {
		std::cout << "okay..." << std::endl;
	}

	//Display player achievement progression
	EOS_Achievements_PlayerAchievement* playerAchievementArray = achievementIniterface->GetPlayerAchievement(achievementHandle, platformHandle, puid);
	assert(playerAchievementArray != nullptr);
	EOS_Achievements_PlayerAchievement* playerAchievementIterator = playerAchievementArray;
	std::cout << "/------Player Achievements------\\" << std::endl;
	for (int i = 0; i < achievementIniterface->achievementCount; i++)
	{
		playerAchievementIterator = &playerAchievementArray[i];
		std::cout << "Achievement: " << playerAchievementIterator->DisplayName << std::endl;
		playerAchievementIterator++;
	}

	// Clean up
	std::cout << "\\------Ending Program------/" << std::endl;
	EOS_Platform_Release(*platformHandle);
	delete platformHandle;
	delete achievementHandle;
	delete config;
	delete puid;
}
