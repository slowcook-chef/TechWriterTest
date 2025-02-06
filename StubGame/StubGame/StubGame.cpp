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

int main()
{
	// Initialize config and platform
	SDKConfig* config = new SDKConfig;
	PlatformHandler* platformInitializer = new PlatformHandler();
	EOS_HPlatform platformHandle = nullptr;
	platformHandle = platformInitializer->InitializePlatform(config);
	assert(platformHandle != nullptr);

	// Login and retrieve a PUID
	AuthHandler* auth = new AuthHandler();
	EOS_ProductUserId puid = nullptr;
	puid = auth->Login(config, platformHandle);
	assert(puid != nullptr);

	std::cout << "Logged in and PUID is: " << puid << std::endl;
}
