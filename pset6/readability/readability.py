from cs50 import get_string

letters = 0
words = 0
sentences = 0
sample = get_string("Text: ")
L = 0
S = 0
index = 0


def count_letters(text):

    Ccount = 0
    i = 0
    
    while i < len(text):
        if (ord(text[i]) >= 65 and ord(text[i]) <= 90):
            Ccount += 1
        elif (ord(text[i]) >= 97 and ord(text[i]) <= 122):
            Ccount += 1
        i += 1
    return Ccount
    

def count_words(text):

    Wcount = 0
    i = 0
    
    while i < len(text):
        if (text[i] == ' '):
            Wcount += 1
        i += 1
    Wcount += 1

    return Wcount


def count_sentences(text):

    Scount = 0
    i = 0
    
    while i < len(text):
        if (text[i] == '?' or text[i] == '!' or text[i] == '.'):
            Scount += 1
        i += 1
    return Scount
    

if len(sample) >= 1:
    letters = count_letters(sample)
    words = count_words(sample)
    sentences = count_sentences(sample)
    L = (letters / words) * 100
    S = (sentences / words) * 100
    index = (0.0588 * L) - (0.296 * S) - 15.8

    if index < 1:
        print("Before Grade 1\n")
    elif index >= 16:
        print("Grade 16+\n")
    else:
        print(f"Grade {round(index)}")

