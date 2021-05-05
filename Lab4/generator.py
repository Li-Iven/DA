import random
import string
from random import choice

def main():
    pattern_size = random.randint(3, 15)
    pattern = []
    text = []
    words_in_pattern = ["dog", "cat", "bird"]
    words_in_text = ["dog", "cat", "bird", "Who", "Yatty", "AttackHelicopter", "doctor", "parzival", "Nyaaa", "tyan"]
    for i in range(pattern_size):
        pattern.append(choice(words_in_pattern))
    count = 0
    while (count < 10):
        rand = random.randint(1, 100)
        if (rand > 90):
            for i in pattern:
                text.append(i)
            count  = count + pattern_size
        else:
            text.append(choice(words_in_text))
            count = count + 1

    test_file = open('test01.t', 'w')
    for i in range(len(pattern)):
        if (i == len(pattern) - 1):
            test_file.write(pattern[i] + '\n')
        else:
            test_file.write(pattern[i] + ' ')
    
    # test_file.write('\n')
    for i in text:
        rand = random.randint(1, 100)
        if (rand > 85):
            test_file.write('\n')
        test_file.write(i + ' ')
    
    test_file.close()

    print('Pattern = ', pattern)


main()
