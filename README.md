# TechWriterTest
Test for tech writer position at Epic Games

# EOS Tech Writer Coding Exercise
[2025-jan-24]

## Prerequisites
Before you start, make sure you have the following:
- The project you are going to work on, downloaded and unzipped. 
- Download it from Box.com at epicgames.box.com/~. 
- A Windows PC with Visual Studio 2022 (visualstudio.microsoft.com) installed. 
- An Epic Games account. 
  - You set up an Epic Games account in the Epic Games Developer Portal (dev.epicgames.com/portal). 
  - As part of this you must set up an organization in the Epic Games Developer Portal. The organization can be whatever name you choose.
  - You do not need to configure the organization.
  - If you already have an Epic Games account, you can reuse it, you do not need to set up a new one.
- A product in the Epic Games Developer Portal (dev.epicgames.com/portal).
  - You do not need to configure the product.
  - You will need the various IDs associated with your product and organization for EOS SDK configuration.
  - These IDs are available from your product’s Product Settings page in the Developer Portal. (Documentation: Product Management.)
- The EOS SDK in C downloaded from the Epic Games Developer Portal (dev.epicgames.com/portal).
  - The project you are going to work on uses EOS SDK v1.16.4.

## Task

You are provided with a project to work on. The project is a simple C++ console application that already implements the EOS SDK for authentication. You are to configure and implement EOS achievements in the project.

Note: The first time you build the project you need to copy EOSSDK-Win64-Shipping.dll
from StubGame/StubGame/sdk/Bin into the StubGame/x64/Debug directory.

You will need to:

- Create a means to tick the EOS platform using the EOS Platform Interface. (Documentation: Platform Interface.)
- Implement the EOS Achievements Interface.
  (Documentation: Achievements Interface and Achievements Interface API Reference.)
- Send a request to manually unlock an achievement and log a message when this is successfully sent.
- Receive a notification and log a message when an achievement is unlocked.
- Implement the EOS Stats Interface and unlock an achievement via ingesting a stat. (Documentation: Stats Interface and Stats Interface API Reference.)

## Guidance

- You are free to refer to online resources, the EOS documentation, and EOS SDK samples (available with the EOS SDK download).
- Please refrain from copying and pasting substantial blocks of code from external sources.

