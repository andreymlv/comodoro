#!/usr/bin/python3

import sys
import time
from simpleaudio import WaveObject, PlayObject


def bell() -> PlayObject:
    return WaveObject.from_wave_file("bell.wav").play()


def parse_arguments(args: list[str]) -> int:
    if (len(args) != 3):
        print(
            'Using: python main.py <number of sections> <time of section> <time of relax>')
        return -1
    return 0


def sleep(t):
    i = 0
    while (i * 60 < t):
        time.sleep(60)
        i += 1
        print(i, flush=True, end=' ')


def start(t, s):
    sleep(t)
    end_of_section_bell = bell()
    input(s)
    end_of_section_bell.stop()


def main() -> int:
    args = sys.argv[1:]

    if (parse_arguments(args) == -1):
        return -1

    number_of_sections = int(args[0])
    time_of_section = int(args[1]) * 60
    time_of_relax = int(args[2]) * 60

    current_section = 0
    while (current_section < number_of_sections):
        start(
            time_of_section,
            'Section {} end! Relax time!'.format(
                current_section + 1))
        start(time_of_relax, 'Relax end! Section time!')
        current_section += 1
    print('No other sections! Congratz!')
    return 0


if __name__ == '__main__':
    sys.exit(main())
