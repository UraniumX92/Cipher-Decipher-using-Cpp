#include<iostream>
#include<cctype>

constexpr int minAlphs_L = 97;   //min number for ASCII lower case Alphabets
constexpr int maxAlphs_L = 122;  //max number for ASCII lower case Alphabets
constexpr int spaceChar = 32;    //number for ASCII character for space
constexpr int nAlphs = 26;       //number of Alphabets

int keyMod(int);
int repTxt2C(int, int);
int repDci(int, int);
std::string ifUpper_toUpper(std::string, std::string);
std::string ciFunc(std::string, int[] , int);
std::string dciFunc(std::string, int[] , int);
std::string cipher(std::string);
std::string dCipher(std::string);
void cipherMain();

int main()
{
    std::cout << "~~~~~~ TWO LAYER CIPHER/DECIPHER BOT ~~~~~~\n"
              << "------Instructions to use 2 Layered cipher------\n"
              << "1. Only use 2 layered cipher for long messages (atleast 15 characters message),otherwise using 2 layer on smaller \n    messages would be ABSOLUTELY pointless.\n"
              << "2. Try to get LCM of 2 keysizes as high as possible,\n"
              << "    thats the whole point of 2 Layered cipher, 2 layers basically increases the length of your key based on keysizes\n    you provide "
              << "without actally having to make/remember and enter that long keys, PLZ do some basic Math _/\\_"
              << "\n"
              << "3. Key1[i] + key2[i] must not add up to 26 (or its multiples) consecutively\n"
              << "    for example: if your first number of key1 is 20,then yout first number for key2 must not be 6,\n    (which will make it 26, same as no cipher)\n"
              << "    it's ok if 1 or 2 cases of key1[i] + key2[i] adds up to 26 or its multiples, but it shouldnt be consecutive,\n    Better to have atmost 1 case.\n";

    system("pause");
    std::cout << std::endl
              << std::endl;
    cipherMain();
}

/*Definitions*/

/*Main menu function for whole program*/
void cipherMain()
{
    //to keep count of how many times the program is running
    static int count = 0;
    std::string text;
    int selectOpt;

    std::cout << "Enter Text" << std::endl;
    if(count == 0)
    {
        getline(std::cin, text);
    }
    /*input buffer is having empty character from first iteration, so we ignore 1 character then take input from user
    removing below lines will not take input after first iteration*/
    else
    {
        getline(std::cin.ignore(), text);
    }

    std::cout << "1.Cipher the text\n2.Decipher the text\n";
    std::cout << "Select your option: ";
    std::cin >> selectOpt;

    std::string cipheredText;
    std::string deCipheredText;

    switch (selectOpt)
    {
    case 1:
        cipheredText = cipher(text);
        std::cout << "Ciphered text is:\n\"" << cipheredText << "\"\n\n";
        break;

    case 2:
        deCipheredText = dCipher(text);
        std::cout << "Deciphered text is:\n\"" << deCipheredText << "\"\n\n";
        break;

    default:
        std::cout << "Invalid Input" << std::endl;
        break;
    }

    count++;

    char restart;
    std::cout << "Enter 'y' to restart the program or Enter any character to exit the program\n";
    std::cin >> restart;

    if(restart == 'y' || restart == 'Y')
    {
        system("cls");
        cipherMain();
    }
    else
    {
        return;
    }
}

/*if key[i] exceeds 26 , then this mod divides by 26 and returns the remainder.*/
int keyMod(int key)
{
    int keyRem;
    if(key > nAlphs)
    {
        keyRem = key % nAlphs;
    }
    else
    {
        keyRem = key;
    }
    return keyRem;
}

/*after adding `key[i]` to character, if value exceeds `maxAlphs` this function controls the value and returns the
actual number for ASCII character to be Ciphered
used in text to cipher*/
int repTxt2C(int charx, int key)
{
    int rem;

    if((charx + key) > maxAlphs_L)
    {
        rem = (charx + key) % maxAlphs_L;
    }
    int replace = ((minAlphs_L - 1) + rem);
    return replace;
}

/*after subtracting `key[i]` from character, if value falls below `minAlphs` this function controls the value and returns the 
actual number for ASCII character to be DeCiphered
used in DeCipher*/
int repDci(int charx, int key)
{
    int rem;

    if((charx - key) < minAlphs_L)
    {
        rem = minAlphs_L % (charx - key);
    }
    int replace = ((maxAlphs_L + 1) - rem);
    return replace;
}

/*if there are any upper case alphabets in input text, then this will convert the alphabets accordingly*/
std::string ifUpper_toUpper(std::string check, std::string convert)
{
    for (int i = 0; i < check.size(); i++)
    {
        if(isupper(check.at(i)))
        {
            convert.at(i) = toupper(convert.at(i));
        }
        else
        {
            convert.at(i) = convert.at(i);
        }
    }
    return convert;
}

/*Function for ciphering, takes text , pointer to the key,and keySize
then ciphers the text and returns it*/
std::string ciFunc(std::string text, int key[], int keySize)
{
    int keyIndex = 0;
    //Ciphering
    for (int i = 0; i < text.size(); i++)
    {
        //For key repetation if keySize < text size
        if(keyIndex == keySize)
        {
            keyIndex = 0;
        }

        if(text.at(i) == char(spaceChar))
        {
            text.at(i) = char(spaceChar);
            //decrement because key must not be used in spaces
            keyIndex--;
        }
        //Only Alphabets gets Ciphered, other characters like commas ,fullstop etc must remain as it is.
        else if(islower(text.at(i)) && (int(text.at(i)) + keyMod(key[keyIndex])) > maxAlphs_L)
        {
            text.at(i) = repTxt2C(int(text.at(i)), keyMod(key[keyIndex]));
        }
        else if(islower(text.at(i)))
        {
            text.at(i) = int(text.at(i) + keyMod(key[keyIndex]));
        }
        else
        {
            text.at(i) = text.at(i);
            //decrement because key must not be used in anything other than alphabets
            keyIndex--;
        }

        keyIndex++;
    }
    return text;
}

/*Function for deciphering, takes text , pointer to the key,and keySize
then deciphers the text and returns it*/
std::string dciFunc(std::string text, int key[], int keySize)
{
    int keyIndex = 0;
    //DeCiphering
    for (int i = 0; i < text.size(); i++)
    {
        //For key repetation if keySize < text size
        if(keyIndex == keySize)
        {
            keyIndex = 0;
        }

        if(text.at(i) == char(spaceChar))
        {
            text.at(i) = char(spaceChar);
            //decrement because key must not be used in spaces
            keyIndex--;
        }
        //Only Alphabets gets DeCiphered, other characters like commas ,fullstop etc must remain as it is.
        else if(islower(text.at(i)) && (int(text.at(i)) - keyMod(key[keyIndex])) < minAlphs_L)
        {
            text.at(i) = repDci(int(text.at(i)), keyMod(key[keyIndex]));
        }
        else if(islower(text.at(i)))
        {
            text.at(i) = int(text.at(i) - keyMod(key[keyIndex]));
        }
        else
        {
            text.at(i) = text.at(i);
            //decrement because key must not be used in anything other than alphabets
            keyIndex--;
        }

        keyIndex++;
    }
    return text;
}

std::string cipher(std::string text)
{
    unsigned int keySize;
    std::string ciphText_L1;
    std::string ciphText_L2;
    std::string tempTxt = text;

    //converting all characters to lower case
    for (int i = 0; i < text.size(); i++)
    {
        text.at(i) = tolower(text.at(i));
    }

    int layer;
askLayer:
    std::cout << "Enter the number of Layers of cipher (1 or 2) : ";
    std::cin >> layer;
    if(layer < 1 || layer > 2)
    {
        std::cout << "Invalid Input, Layers can be either 1 or 2\n";
        goto askLayer;
    }

    std::cout << "Enter key size (for key 1,if using 2 layers)" << std::endl;
    std::cin >> keySize;
    int *key = new int[keySize];

    std::cout << "Enter your key" << std::endl;

    for (int i = 0; i < keySize; i++)
    {
        std::cin >> key[i];
    }

    ciphText_L1 = ciFunc(text, key, keySize);
    delete[] key;

    if(layer == 2)
    {
        //Ciphering for layer 2

        int keySize2;
        std::cout << "Enter key size for 2nd key" << std::endl;
        std::cin >> keySize2;
        int *key2 = new int[keySize2];

        std::cout << "Enter your key" << std::endl;

        for (int i = 0; i < keySize2; i++)
        {
            std::cin >> key2[i];
        }

        ciphText_L2 = ciFunc(ciphText_L1, key2, keySize2);
        delete[] key2;
    }

    if(layer == 1)
    {
        ciphText_L1 = ifUpper_toUpper(tempTxt, ciphText_L1);
        return ciphText_L1;
    }
    else
    {
        ciphText_L2 = ifUpper_toUpper(tempTxt, ciphText_L2);
        return ciphText_L2;
    }
}

/*function for DeCipher, takes a string input from `int main()` and DeCiphers it according to the key provided by user*/
std::string dCipher(std::string text)
{
    unsigned int keySize;
    std::string deciphText_L1;
    std::string deciphText_L2;

    std::string tempTxt = text;
    //converting all characters to lower case
    for (int i = 0; i < text.size(); i++)
    {
        text.at(i) = tolower(text.at(i));
    }

    int layer;
askLayer_D:
    std::cout << "Enter the number of Layers of cipher (1 or 2) : ";
    std::cin >> layer;
    if(layer < 1 || layer > 2)
    {
        std::cout << "Invalid Input, Layers can be either 1 or 2\n";
        goto askLayer_D;
    }

    std::cout << "Enter key size (for key 1,if using 2 layers)" << std::endl;
    std::cin >> keySize;
    int *key = new int[keySize];

    std::cout << "Enter your key" << std::endl;

    for (int i = 0; i < keySize; i++)
    {
        std::cin >> key[i];
    }

    deciphText_L1 = dciFunc(text, key, keySize);

    if(layer == 2)
    {
        int keySize2;
        std::cout << "Enter key size for 2nd key" << std::endl;
        std::cin >> keySize2;
        int *key2 = new int[keySize2];

        std::cout << "Enter your key 2" << std::endl;

        for (int i = 0; i < keySize2; i++)
        {
            std::cin >> key2[i];
        }

        deciphText_L1 = dciFunc(text, key2, keySize2);
        deciphText_L2 = dciFunc(deciphText_L1, key, keySize);

        delete[] key;
        delete[] key2;
    }
    else if(layer == 1)
    {
        delete[] key;
    }

    if(layer == 1)
    {
        deciphText_L1 = ifUpper_toUpper(tempTxt, deciphText_L1);
        return deciphText_L1;
    }
    else
    {
        deciphText_L2 = ifUpper_toUpper(tempTxt, deciphText_L2);
        return deciphText_L2;
    }
}