#include "pch.h"
#include "Keyboard.h"

#include "GameTime.h"

void RayEngine::Keyboard::Update()
{
    keyPressed = GetKeyPressed();
    charPressed = keyPressed;
    validKey = (charPressed != '\0');
    charGot = false;
    repeatCharGot = false;
    repeatKeyGot = false;
    if (!validKey) validChar = false;
    else
    {
        if (lastKeyPressed != keyPressed)
        {
            isRepeating = false;
            repeatingKeyTimer = 0;
        }
        lastKeyPressed = keyPressed;
    }

    UpdateRepeatingKey();
}

char RayEngine::Keyboard::CharPressed()
{
    if (!charGot)
    {
        if (validKey)
            GetCharacter();
        charGot = true;
    }
    return charPressed;
}

bool RayEngine::Keyboard::IsValidCharPressed()
{
    if (!charGot)
    {
        CharPressed();
    }
    return validChar;
}

void RayEngine::Keyboard::GetCharacter()
{
    validChar = false;
    if (charPressed == (int)KeyboardKey::KEY_BACKSPACE) return;
    if (charPressed >= (int)KeyboardKey::KEY_KP_0 && charPressed <= (int)KeyboardKey::KEY_KP_9)
    {
        charPressed -= 320;
        charPressed += '0';
        validChar = true;
        return;
    }

    if (HandleSpecial())
    {
        validChar = true;
        return;
    }

    if (charPressed < 32) return;
    if (charPressed > 126) return;
    if (charPressed == (int)KeyboardKey::KEY_CAPS_LOCK)
    {
        CapsLock = !CapsLock;
        return;
    }


    bool shift = ::IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || ::IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT);

    if (!shift && isalpha(((char)charPressed)))
        charPressed += ('a' - 'A');

    if (shift && isdigit((char)charPressed))
        switch (charPressed)
        {
        case '0':
            charPressed = '(';
            break;
        case '1':
            charPressed = '!';
            break;
        case '2':
            charPressed = '@';
            break;
        case '3':
            charPressed = '#';
            break;
        case '4':
            charPressed = '$';
            break;
        case '5':
            charPressed = '%';
            break;
        case '6':
            charPressed = '^';
            break;
        case '7':
            charPressed = '&';
            break;
        case '9':
            charPressed = '(';
            break;
        default:
            break;
        }

    validChar = charPressed != '\0';
}

bool RayEngine::Keyboard::HandleSpecial()
{
    if (keyPressed == '\0') return false;

    int check = charPressed;

    if (charPressed == (int)KeyboardKey::KEY_SPACE)
    {
        charPressed = ' ';
        return true;
    }

    if (charPressed == (int)KeyboardKey::KEY_KP_DECIMAL) charPressed = '.';
    else if (charPressed == (int)KeyboardKey::KEY_KP_DIVIDE) charPressed = '/';
    else if (charPressed == (int)KeyboardKey::KEY_KP_MULTIPLY) charPressed = '*';
    else if (charPressed == (int)KeyboardKey::KEY_KP_SUBTRACT) charPressed = '-';
    else if (charPressed == (int)KeyboardKey::KEY_KP_ADD) charPressed = '+';
    else if (charPressed == (int)KeyboardKey::KEY_KP_EQUAL) charPressed = '=';

    if (check != charPressed) return true;

    bool shift = (::IsKeyDown(KeyboardKey::KEY_LEFT_SHIFT) || ::IsKeyDown(KeyboardKey::KEY_RIGHT_SHIFT));
    switch (charPressed)
    {
    case (int)KeyboardKey::KEY_COMMA:
        charPressed = shift ? '>' : ',';
        break;
    case (int)KeyboardKey::KEY_PERIOD:
        charPressed = shift ? '>' : '.';
        break;
    case (int)KeyboardKey::KEY_SLASH:
        charPressed = shift ? '?' : '/';
        break;
    case (int)KeyboardKey::KEY_SEMICOLON:
        charPressed = shift ? ':' : ';';
        break;
    case (int)KeyboardKey::KEY_APOSTROPHE:
        charPressed = shift ? '\"' : '\'';
        break;
    case (int)KeyboardKey::KEY_MINUS:
        charPressed = shift ? '_' : '-';
        break;
    case (int)KeyboardKey::KEY_LEFT_BRACKET:
        charPressed = shift ? '{' : '[';
        break;
    case (int)KeyboardKey::KEY_RIGHT_BRACKET:
        charPressed = shift ? '}' : ']';
        break;
    case (int)KeyboardKey::KEY_EQUAL:
        charPressed = shift ? '+' : '=';
        break;
    }

    return check != charPressed;
}

int RayEngine::Keyboard::RepeatingKey()
{
    if (repeatCharGot || repeatKeyGot) return repeatingKey;
    if (!validKeyRepeating) return 0;
    repeatingKey = lastKeyPressed;
    repeatKeyGot = true;    
}

char RayEngine::Keyboard::RepeatingChar()
{
    if (!validKeyRepeating) return '\0';
    if (repeatCharGot) return (char)repeatingChar;
    if (!repeatKeyGot) RepeatingKey();

    bool tempValidChar = validChar;
    char tempCharPressed = charPressed;

    charPressed = repeatingKey;
    GetCharacter();
    validCharRepeating = validChar;

    repeatCharGot = true;
    repeatingChar = charPressed;

    validChar = tempValidChar;
    charPressed = tempCharPressed;

    if (validCharRepeating)  return (char)repeatingChar;
    return '\0';
}

bool RayEngine::Keyboard::IsValidCharPressedOrRepeating()
{
    if (IsValidCharPressed()) return true;
    if (!repeatCharGot) RepeatingChar();
    return validCharRepeating;
}

int RayEngine::Keyboard::GetKeyPressedOrRepeating()
{
    if (validKey) return KeyPressed();
    if (validKeyRepeating) return RepeatingKey();

    return 0;
}

char RayEngine::Keyboard::GetCharPressedOrRepeating()
{
    if (validChar) return CharPressed();
    return RepeatingChar();
}

void RayEngine::Keyboard::UpdateRepeatingKey()
{
    repeatingKey = 0;
    validKeyRepeating = false;
    validCharRepeating = false;

    if (isRepeating)
    {
        if (!IsKeyDown(lastKeyPressed))
        {
            isRepeating = false;
            validKeyRepeating = false;
            repeatingKeyTimer = 0;
            return;
        }

        repeatingKeyTimer += Time::DeltaTime();
        if (repeatingKeyTimer < KEY_REPEAT_DELAY) return;

        validKeyRepeating = true;
        repeatingKeyTimer = 0;
    }
    else if (IsKeyDown(lastKeyPressed))
    {
        repeatingKeyTimer += Time::DeltaTime();
        if (repeatingKeyTimer < KEY_REPEAT_START_UP_TIME) return;

        isRepeating = true;
        repeatingKeyTimer = 0;
        validKeyRepeating = true;
    }
    else
    {
        repeatingKeyTimer = 0;
        isRepeating = false;
    }
}
