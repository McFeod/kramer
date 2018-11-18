#!/usr/bin/python3

import random
import sys

FILENAME = 'input.txt'
SOLUTION = 'solution.txt'


def random_small_double():
    return random.randint(-1000, 1000) / 10


def random_row(size):
    return [random_small_double() for _ in range(size)]


def write_solution(row):
    with open(SOLUTION, 'w') as fil:
        for index, item in enumerate(row, start=1):
            fil.write(f'X{index} = {item}\n')


def create_equation(solution):
    result = random_row(len(solution))
    result.append(sum(a * b for a, b in zip(result, solution)))
    return result


def main():
    try:
        rank = int(sys.argv[1])
    except IndexError:
        rank = int(input('Число уравнений = '))
    solution = random_row(rank)
    write_solution(solution)
    with open(FILENAME, 'w') as fil:
        fil.write(f'{rank}\n')
        for _ in range(rank):
            fil.write(' '.join(str(i) for i in create_equation(solution)))
            fil.write('\n')


if __name__ == '__main__':
    main()
