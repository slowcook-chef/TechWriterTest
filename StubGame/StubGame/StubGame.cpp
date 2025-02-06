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
#include "StatsInterface.h"
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
	AchievementInterface* achievementInterface = new AchievementInterface();
	EOS_HAchievements* achievementHandle = new EOS_HAchievements();
	*achievementHandle = achievementInterface->GetAchievementHandle(platformHandle);
	assert(achievementHandle != nullptr);

	//Get and Display all achievements definitions
	EOS_Achievements_DefinitionV2* definitionArray = achievementInterface->GetAchievementDefinitions(achievementHandle, platformHandle, puid);
	assert(definitionArray != nullptr);
	achievementInterface->DisplayAchievementDefinitions(definitionArray);

	//Unlock the first achievement manually
	EOS_Achievements_DefinitionV2* achievement = &definitionArray[0];
	std::cout << "Would you like to unlock " << achievement->LockedDisplayName << "? (y / n)" << std::endl;
	char input;
	std::cin >> input;
	if (input == 'y') {
		achievementInterface->ManualUnlockAchievement(achievementHandle, platformHandle, puid, achievement);
	}
	else {
		std::cout << "okay..." << std::endl;
	}

	//Display player achievement progression
	EOS_Achievements_PlayerAchievement* playerAchievements = achievementInterface->GetPlayerAchievements(achievementHandle, platformHandle, puid);
	achievementInterface->DisplayPlayerAchievements(playerAchievements);

	//Initialize stats interface and handle
	StatsInterface* statsInterface = new StatsInterface();
	EOS_HStats* statsHandle = new EOS_HStats();
	*statsHandle = statsInterface->GetStatsHandle(platformHandle);
	assert(statsHandle != nullptr);

	//Ingest stats (pancakes)
	bool breakout = false;
	while (!breakout)
	{
		std::cout << "Would you like to ingest a pancake? (y / n)" << std::endl;
		std::cin >> input;
		if (input == 'y') {
			statsInterface->IngestStat(statsHandle, platformHandle, puid, "Pancakes", 1);
			std::cout << "Oooh yummy +1 pancakes" << std::endl;
		}
		else {
			breakout = true;
			std::cout << "No more pancakes for you!" << std::endl;
		}
	}

	//Get stats
	EOS_Stats_Stat* playerStats = statsInterface->GetStats(statsHandle, platformHandle, puid);
	statsInterface->DisplayPlayerStats(playerStats);

	// Clean up
	std::cout << "\\------Ending Program------/" << std::endl;
	EOS_Platform_Release(*platformHandle);
	delete platformHandle;
	delete achievementHandle;
	delete config;
	delete puid;
}

