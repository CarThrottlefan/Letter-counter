#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

void InputIn(std::string &lineMerger, int argc, char *argv[])
{
    std::string inputText;
    std::ifstream inFS;
    int i = 0;
    
    if(argc == 1)
    {
        while(!std::cin.eof())
        {
            std::getline(std::cin, inputText);
            for(i = 0; i < inputText.size(); i++)
            {
                lineMerger.push_back( inputText.at(i) );
            }
        }
    }
    else if(argc == 2)
    {
        inFS.open(argv[1]);
        if(inFS.is_open())
        {
            while(!inFS.eof())
        {
            std::getline(inFS, inputText);
            for(i = 0; i < inputText.size(); i++)
            {
                lineMerger.push_back( inputText.at(i) );
            }
        }
        }
        else
        {
            throw std::runtime_error("cannot open input file ");
        }
    }
    else
    {
        throw std::runtime_error("cannot handle parameter list");
    }
}

int sameLetterCount (char currentLetter)
{
    int letterCode;

    if(currentLetter >= 97)
    {
        letterCode = currentLetter - 32;
    }
    else 
    {
        letterCode = currentLetter;
    }

    return letterCode;
}

void frequencyVectorBuilder (std::vector <int> &freqVector, char currentLetter)
{
    int i;
    freqVector.at(sameLetterCount(currentLetter) - 65) ++;
}

void frequencyCalculator (std::vector <int> freqVector, char &mostFreq, int &howFreq)
{
    int i;
    int mostFreq_int = 0;
    howFreq = 0;

    for(i = 0; i < freqVector.size(); i++)
    {
        
        if (freqVector.at(i) > howFreq)
        {
            howFreq = freqVector.at(i);
            mostFreq_int = i;
        }
    }
    mostFreq_int = mostFreq_int + 97;
    mostFreq = mostFreq_int;
}

void testCASE (std::vector <int> freqVector, char &cons, char &vowel, int &consFreq, int &vowelFreq)
{
    int i = 65;
    int cons_int = 0;
    int vowel_int = 0;
    
    consFreq = 0;
    vowelFreq = 0;

   while(i <= 90)
    {
        if((i == 65) || (i == 69) || (i == 73) || (i == 79) || (i == 85))
        {
            if (freqVector.at(i - 65) > vowelFreq)
            {
                vowelFreq = freqVector.at(i - 65);
                vowel_int = i;
            }
        }
            
        else
        {
            if (freqVector.at(i - 65) > consFreq)
            {
                consFreq = freqVector.at(i - 65);
                cons_int = i;
            }
        }
        i ++;    
    }
    cons = cons_int + 32;
    vowel = vowel_int + 32;

}

void printOut (std::vector<int> freqVector, int outputcase)
{
    char vowel, cons, output;
    int vowelFreq, consFreq, frequency;

    testCASE(freqVector, cons, vowel, consFreq, vowelFreq);

    switch(outputcase)
    {
        case 0: 
            std::cout << "Most frequent vowel: " << (vowelFreq == 0 ? 'a' : vowel) << " (" << vowelFreq << " times)" << std::endl;
            break;
        
        case 1:
            std::cout << "Most frequent consonant: " << (consFreq == 0 ? 'b' : cons) << " (" << consFreq << " times)" << std::endl;
            break;
        
        case 2:
            frequencyCalculator(freqVector, output, frequency);
            std::cout << "Most frequent letter, overall: " << (frequency == 0 ? 'a' : output) << " (" << frequency << " times)" << std::endl;
            break;
    }  
}


int main(int argc, char* argv[])
{
    int i = 0;
    int count = 0;
    char mostFrequent;
    char vowel, cons, letter;
    std::ifstream inFS;
    
    std::vector <int> letterFreq(26, 0);
    std::string lineMerger;
    
    try
    {
        InputIn(lineMerger, argc, argv);

        for (i = 0; i < lineMerger.size(); i++)
        {
            if( ( (lineMerger.at(i) >= 65) && (lineMerger.at(i) <= 90) ) || ( (lineMerger.at(i) >= 97) && (lineMerger.at(i) <= 122) ) )
            {
                frequencyVectorBuilder( letterFreq, lineMerger.at(i) );
            } 
        }

        printOut(letterFreq, 0);
        printOut(letterFreq, 1);
        printOut(letterFreq, 2);

        inFS.close();
    }

    catch(std::runtime_error &excpt)
    {
        if(argc == 2)
        {
        std::cout << excpt.what() << argv[1] << std::endl;
        }
        else
        {
            std::cout << excpt.what() << std::endl;
        }

    }

    return 0;
}