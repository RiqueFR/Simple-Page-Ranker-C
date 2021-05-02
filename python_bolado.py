import unicodedata
import string
import sys

def remove_accents(input_str):
    nfkd_form = unicodedata.normalize('NFKD', input_str)
    return u"".join([c for c in nfkd_form if not unicodedata.combining(c)])


if __name__ == '__main__':
    for line in sys.stdin:
        line = line.strip().translate(str.maketrans('', '', string.punctuation))
        print(remove_accents(line))