#pragma once

namespace RayEngine
{
	class Keyboard
	{
	public:
		static void Update();

		inline static int KeyPressed() { return keyPressed; };
		static char CharPressed();
		inline static bool IsValidKeyPressed() { return validKey; }
		static bool IsValidCharPressed();
		inline static bool IsKeyRepeating() { return validKeyRepeating; };
		inline static bool IsKeyRepeatingACharacter() { return validKeyRepeating && validCharRepeating; }
		static int RepeatingKey();
		static char RepeatingChar();

		inline static bool IsValidKeyPressedOrRepeating() { return validKey || validKeyRepeating; }
		static bool IsValidCharPressedOrRepeating();

		static int GetKeyPressedOrRepeating();
		static char GetCharPressedOrRepeating();
	private:
		inline static int keyPressed = 0;
		inline static int charPressed = '\0';
		inline static int repeatingKey = 0;
		inline static int repeatingChar = '\0';
		inline static int lastKeyPressed = 0;
		inline static bool validChar = false;
		inline static bool validKey = false;
		inline static bool CapsLock = false;
		inline static bool charGot = false;
		inline static bool repeatCharGot = false;
		inline static bool repeatKeyGot = false;
		inline static bool validKeyRepeating = false;
		inline static bool validCharRepeating = false;
		inline static float repeatingKeyTimer = 0;
		inline static bool isRepeating = false;
		

		inline static const float KEY_REPEAT_START_UP_TIME = 0.35f;
		inline static const float KEY_REPEAT_DELAY = 0.045f;

		static void GetCharacter();
		static bool HandleSpecial();
		static void UpdateRepeatingKey();
	public:
		Keyboard() = delete;
		Keyboard(const Keyboard& k) = delete;
		Keyboard(const Keyboard&& k) = delete;
		Keyboard& operator=(const Keyboard& k) = delete;
		Keyboard& operator=(const Keyboard&& k) = delete;

	};
}


