// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//DO NOT COMMIT THIS FILE WITH REAL CREDENTIALS
struct SDKConfig
{
	/** The product id for the running application, found on the dev portal */
	static constexpr char ProductId[] = "4cb30c27c9364b628cd781c04fb77041";

	/** The sandbox id for the running application, found on the dev portal */
	static constexpr char SandboxId[] = "96f26110e1d747fdba985339c10bf068";

	/** The deployment id for the running application, found on the dev portal */
	static constexpr char DeploymentId[] = "806a3ab115fd4d7a96b1eb6fb0d836bd";

	/** Client id of the service permissions entry, found on the dev portal */
	static constexpr char ClientCredentialsId[] = "xyza789148FtoZgpevFOPOLUMROVVfWL";

	/** Client secret for accessing the set of permissions, found on the dev portal */
	static constexpr char ClientCredentialsSecret[] = "vrfztgLMKrK4KtJr5B1J4qsb+L+aNC7G2N03SW372qo";

	/** Game name */
	static constexpr char GameName[] = "StubGame";

	/** Encryption key */
	static constexpr char EncryptionKey[] = "1111111111111111111111111111111111111111111111111111111111111111";

	/** Credential name in the DevAuthTool */
	static constexpr char CredentialName[] = "Slowcook";

	/** Host name in the DevAuthTool */
	static constexpr char Port[] = "localhost:1115"; 
};
