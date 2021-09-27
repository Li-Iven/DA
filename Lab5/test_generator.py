import string
import random

ALPHABET = string.ascii_lowercase 

def get_random_text(text_len):
    return "".join([random.choice(ALPHABET) for _ in range(text_len)])

NUMBER_OF_LINES = [100, 1000, 10000, 100000, 1000000]

length_of_list = len(NUMBER_OF_LINES)

for enum in range(length_of_list):
    with open(f'test_{NUMBER_OF_LINES[enum]}.t', 'w') as file:
        text = get_random_text(NUMBER_OF_LINES[enum])
        pattern_count = random.randint(1, 9)
        answer = ""
        file.write( "{}\n".format(text))
        for cnt in range(pattern_count):
            # Определяем, использовать ли настоящую подстроку или воображаемую.
            use_real_pattern = random.choice([True, False])
            if use_real_pattern:
                # Вычисляем позиции среза.
                start_pos = random.randint(0, len(text) - 3)
                end_pos= random.randint( start_pos+1, len(text) - 1)
                pattern = text[start_pos:end_pos]
            else:
                # Берём рандомную подстроку. Она может совпасть с существующей.
                pattern = get_random_text(random.randint(1, 10))
            answer += pattern
        file.write( "{}\n".format(answer))
