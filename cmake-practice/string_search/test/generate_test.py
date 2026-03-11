# generate_large_test.py
import random

def generate_large_test(filename="test3.txt", num_cases=2000):
    with open(filename, "w", encoding="utf-8") as f:
        f.write("# Large auto-generated test set for string search\n")
        f.write("# Format: text | pattern | expected_position (-1 = not found)\n\n")

        base_texts = [
            "hello world hello world",
            "abababababababababab",
            "aaaaaaaabbbbbbbbccccccc",
            "mississippi river mississippi",
            "supercalifragilisticexpialidocious",
            "the quick brown fox jumps over the lazy dog",
            "this is a very long sentence with many repeated words like hello hello hello",
            "a" * 50 + "b" * 50 + "c" * 50,
        ]

        patterns = [
            "hello", "world", "ab", "aaa", "miss", "issi", "the", "fox", "dog", "lazy",
            "super", "fragilistic", "expiali", "docious", "brown", "quick", "jumps",
            "over", "sentence", "repeated", "long", "very", "many", "like", "words",
            "b", "c", "z", "xyz", "qqq", ""
        ]

        for _ in range(num_cases):
            # Choose random base text and extend it randomly
            text = random.choice(base_texts) * random.randint(1, 5)
            text += " " + "".join(random.choices("abcdefghijklmnopqrstuvwxyz ", k=random.randint(10, 60)))

            # Choose pattern
            pattern = random.choice(patterns)

            # Sometimes make pattern not exist
            if random.random() < 0.25:
                pattern = pattern.upper() + "XYZ"  # unlikely to appear

            # Find real position (for verification)
            pos = text.find(pattern)
            expected = pos if pos != -1 else -1

            f.write(f"{text} | {pattern} | {expected}\n")

    print(f"Generated {num_cases} test cases in {filename}")

# Change the number as you want
generate_large_test(num_cases=5000)