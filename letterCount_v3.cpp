#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>

std::string processInput (std::istream& input)
{
   int i;
   std::string inputText;
   std::string lineMerger;

   while (!input.eof())
    {
        std::getline(input, inputText);
        for (i = 0; i < inputText.size(); i++)
        {
            lineMerger.push_back (inputText.at(i));
        }
    }
    
    return lineMerger;
}


std::string inputIn (int argc, char *argv[])
{
    std::string inputText;
    std::ifstream inFS;
    int i = 0;
    
    if (argc == 1)
    {
        return processInput(std::cin);

    }
    else if (argc == 2)
    {
        inFS.open(argv[1]);
        if (inFS.is_open())
        {
            return processInput(inFS);
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

    if (currentLetter >= 97)
    {
        letterCode = currentLetter - 32;
    }
    else 
    {
        letterCode = currentLetter;
    }

    return letterCode;
}

void frequencyVectorBuilder (std::vector <int> &freqVector, int argc, char* argv[], std::string lineMerger)
{
    int i;
    for (i = 0; i < lineMerger.size(); i++)
    {
        if (((lineMerger.at(i) >= 65) && (lineMerger.at(i) <= 90)) || ((lineMerger.at(i) >= 97) && (lineMerger.at(i) <= 122)))
        {
            freqVector.at(sameLetterCount(lineMerger.at(i)) - 65) ++;
        } 
    }
}

char mostFrequentLetter (std::vector <int> freqVector)
{
    int i;
    int howFreq = 0;
    int mostFreq_int = 0;
    char mostFreq;

    for (i = 0; i < freqVector.size(); i++)
    {
        
        if (freqVector.at(i) > howFreq)
        {
            mostFreq_int = i;
            howFreq = freqVector.at(i);
        }
    }
    
    mostFreq = mostFreq_int + 97;

    return mostFreq;
}

int howFrequentLetter (std::vector <int> freqVector)
{
    int i = 0;
    int howFreq = 0;

    for (i = 0; i < freqVector.size(); i++)
    {
        if (freqVector.at(i) > howFreq)
        {
            howFreq = freqVector.at(i);
        }
    }

    return howFreq;
}

char mostFrequentVowel (std::vector <int> freqVector)
{
    int i = 65;
    int vowel_int = 0;
    int vowelFreq = 0;
    char vowel;

    while (i <= 85)
    {
        if ((i == 65) || (i == 69) || (i == 73) || (i == 79) || (i == 85))
        {
            if (freqVector.at(i - 65) > vowelFreq)
            {
                vowelFreq = freqVector.at(i - 65);
                vowel_int = i;
            }
        }
        i ++;
    }
    vowel = vowel_int + 32;
    
    return vowel;
}

int howFrequentVowel (std::vector <int> freqVector)
{
    int i = 65;
    int vowelFreq = 0;

    while (i <= 85)
    {
        if ((i == 65) || (i == 69) || (i == 73) || (i == 79) || (i == 85))
        {
            if (freqVector.at(i - 65) > vowelFreq)
            {
                vowelFreq = freqVector.at(i - 65);
            }
        }
        i ++;
    }
    
    return vowelFreq;
}

char mostFrequentConsonant (std::vector <int> freqVector)
{
    int i = 65;
    int cons_int = 0;
    int consFreq = 0;
    char cons;
    
   while (i <= 90)
    {       
        if (!((i == 65) || (i == 69) || (i == 73) || (i == 79) || (i == 85)))
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
    
    return cons;
}

int howFrequentConsonant (std::vector <int> freqVector)
{
    int i = 65;
    int consFreq = 0;

    while (i <= 90)
    {
        if (!((i == 65) || (i == 69) || (i == 73) || (i == 79) || (i == 85)))
        {
            if (freqVector.at(i - 65) > consFreq)
            {
                consFreq = freqVector.at(i - 65);
            }
        }
        i ++;
    }
    
    return consFreq;
}

void printOut (std::vector<int> freqVector, int outputcase)
{
    char vowel, cons, output;
    int vowelFreq, consFreq, frequency;

    output = mostFrequentLetter(freqVector);
    frequency = howFrequentLetter(freqVector);

    vowel = mostFrequentVowel(freqVector);
    vowelFreq = howFrequentVowel(freqVector);

    cons = mostFrequentConsonant(freqVector);
    consFreq = howFrequentConsonant(freqVector);

    switch(outputcase)
    {
        case 0: 
            std::cout << "Most frequent vowel: " << (vowelFreq == 0 ? 'a' : vowel) << " (" << vowelFreq << " times)" << std::endl;
            break;
        
        case 1:
            std::cout << "Most frequent consonant: " << (consFreq == 0 ? 'b' : cons) << " (" << consFreq << " times)" << std::endl;
            break;
        
        case 2:
            std::cout << "Most frequent letter, overall: " << (frequency == 0 ? 'a' : output) << " (" << frequency << " times)" << std::endl;
            break;
    }  
}


int main (int argc, char* argv[])
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
        lineMerger = inputIn(argc, argv);

        frequencyVectorBuilder(letterFreq, argc, argv, lineMerger); 

        printOut(letterFreq, 0);
        printOut(letterFreq, 1);
        printOut(letterFreq, 2);

        inFS.close();
    }

    catch(std::runtime_error &excpt)
    {
        if (argc == 2)
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
