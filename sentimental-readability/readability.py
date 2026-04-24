from cs50 import get_string


text = get_string("Text: ")
length = len(text)

# Count letters
letters = 0
for i in range(length):
    if text[i].isalpha():
        letters += 1

# Count words
words = 1
for i in range(length):
    if text[i].isspace():
        words += 1

# Count sentences
sentences = 0
for i in range(length):
    if text[i] == "." or text[i] == "!" or text[i] == "?":
        sentences += 1

# Compute the Coleman-Liau index
L = letters / words * 100
S = sentences / words * 100
index = round(0.0588 * L - 0.296 * S - 15.8)

# Print result
if index < 1:
    print("Before Grade 1")
elif index >= 16:
    print("Grade 16+")
else:
    print("Grade", index)
