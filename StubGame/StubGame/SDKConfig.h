// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

struct SDKConfig
{
	/** The product id for the running application, found on the dev portal */
	static constexpr char ProductId[] = "";

	/** The sandbox id for the running application, found on the dev portal */
	static constexpr char SandboxId[] = "";

	/** The deployment id for the running application, found on the dev portal */
	static constexpr char DeploymentId[] = "";

	/** Client id of the service permissions entry, found on the dev portal */
	static constexpr char ClientCredentialsId[] = "";

	/** Client secret for accessing the set of permissions, found on the dev portal */
	static constexpr char ClientCredentialsSecret[] = "";

	/** Game name */
	static constexpr char GameName[] = "";

	/** Encryption key */
	static constexpr char EncryptionKey[] = "1111111111111111111111111111111111111111111111111111111111111111";

	/** Credential name in the DevAuthTool */
	static constexpr char CredentialName[] = "";

	/** Host name in the DevAuthTool */
	static constexpr char Port[] = "";
};
