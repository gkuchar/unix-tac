#!/usr/bin/env python3

import random
import sys

ADJECTIVES = [
    "quick", "lazy", "sleepy", "noisy", "hungry", "bright", "dark", "curious",
    "elegant", "brave", "calm", "eager", "fancy", "gentle", "happy", "jolly",
    "kind", "lively", "merry", "nice", "polite", "proud", "silly", "witty",
    "zealous", "ancient", "modern", "clever", "graceful", "serious",
    "thoughtful", "careful", "fearless", "honest", "loyal", "bold"
]

NOUNS = [
    "dog", "cat", "student", "teacher", "engineer", "scientist", "artist",
    "musician", "runner", "chef", "driver", "pilot", "doctor", "lawyer",
    "child", "parent", "neighbor", "friend", "manager", "developer",
    "writer", "reader", "player", "coach", "actor", "director",
    "designer", "researcher", "photographer", "gardener",
    "city", "river", "mountain", "forest", "car", "computer",
    "book", "phone", "house", "school"
]

VERBS = [
    "builds", "creates", "observes", "analyzes", "teaches", "learns",
    "writes", "reads", "drives", "flies", "runs", "walks", "jumps",
    "solves", "designs", "develops", "tests", "fixes", "explores",
    "discovers", "improves", "explains", "discusses", "organizes",
    "manages", "prepares", "studies", "plans", "leads", "supports",
    "helps", "guides", "encourages", "examines", "builds", "calculates"
]

ADVERBS = [
    "quickly", "slowly", "carefully", "easily", "quietly", "loudly",
    "gracefully", "happily", "sadly", "eagerly", "calmly", "boldly",
    "clearly", "politely", "seriously", "thoughtfully", "efficiently",
    "frequently", "rarely", "occasionally", "regularly", "suddenly",
    "unexpectedly", "smoothly", "precisely", "accurately"
]

EXTRAS = [
    "during the meeting", "at the park", "in the office",
    "on a sunny day", "before the deadline", "after lunch",
    "during the lecture", "at the conference", "in the classroom",
    "over the weekend", "late at night", "early in the morning",
    "near the river", "on the mountain", "in the city",
    "while working", "while studying", "during practice",
    "before the exam", "after the event"
]

PROPER_NOUNS = [
    "Alice", "Bob", "Charlie", "Diana", "Edward", "Fiona", "George",
    "Hannah", "Ian", "Julia", "Kevin", "Laura", "Michael", "Nina",
    "Oliver", "Paula", "Quentin", "Rachel", "Samuel", "Tina",
    "Ursula", "Victor", "Wendy", "Xavier", "Yvonne", "Zachary",
    "Texas", "Paris", "London", "Tokyo", "Berlin", "Sydney",
    "Amazon", "Google", "Microsoft", "OpenAI"
]


def make_sentence():
    patterns = [
        lambda: f"The {random.choice(ADJECTIVES)} {random.choice(NOUNS)} "
                f"{random.choice(VERBS)} {random.choice(ADVERBS)} {random.choice(EXTRAS)}.",

        lambda: f"{random.choice(PROPER_NOUNS)} {random.choice(VERBS)} "
                f"the {random.choice(ADJECTIVES)} {random.choice(NOUNS)}.",

        lambda: f"The {random.choice(NOUNS)} {random.choice(VERBS)} "
                f"{random.choice(PROPER_NOUNS)} {random.choice(ADVERBS)}.",

        lambda: f"{random.choice(PROPER_NOUNS)} and {random.choice(PROPER_NOUNS)} "
                f"{random.choice(VERBS)} together {random.choice(EXTRAS)}.",

        lambda: f"A {random.choice(ADJECTIVES)} {random.choice(NOUNS)} "
                f"{random.choice(VERBS)} {random.choice(EXTRAS)}."
    ]

    return random.choice(patterns)()


def generate_file(filename, target_size_bytes):
    total_bytes = 0
    sentence_count = 0

    with open(filename, "w", encoding="utf-8") as f:
        while total_bytes < target_size_bytes:
            sentence = make_sentence()
            line = sentence + "\n"
            f.write(line)
            total_bytes += len(line.encode("utf-8"))
            sentence_count += 1

    print(f"Generated {filename}")
    print(f"  Size: {total_bytes} bytes")
    print(f"  Sentences: {sentence_count}")


def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} output_file size_in_bytes")
        sys.exit(1)

    filename = sys.argv[1]
    size = int(sys.argv[2])
    generate_file(filename, size)


if __name__ == "__main__":
    main()