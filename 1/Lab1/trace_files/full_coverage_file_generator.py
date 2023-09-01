#! /usr/bin/env python3 

"""
NOTE: This file is for TA purposes only. It automatically generates random trace files for integration tests.
Feel free to play around with it if you want, but don't worry about it.
"""

import argparse
from inspect import trace
import itertools

def generate_trace_files(num_lines: int):

    permutations = list(itertools.product(["Insert: ", "Remove: "],
                                               repeat=num_lines))

    for idx, cur_purmutation in enumerate(permutations):

        next_inserted_value = 0
        inserted_values = []

        with open("trace_file_" + str(idx), "w") as cur_trace_file:

            cur_trace_file.write("5\n")

            for instruction in cur_purmutation:

                if ("Insert" in instruction):
                    instruction += f"{str(next_inserted_value)},{str(next_inserted_value)}"
                    inserted_values.append(next_inserted_value)
                    next_inserted_value += 1

                if ("Remove" in instruction):
                    # In this case we haven't inserted anything, so remove a value we know isn't
                    # in the list
                    if (len(inserted_values) == 0):
                        instruction += f"{str(-1)}"
                    # We need to look for the value that was just inserted, which is going to
                    # be next_inserted_value - 1
                    else:
                        instruction += f"{str(inserted_values.pop())}"

                cur_trace_file.write(instruction + "\n")


if __name__ == "__main__":

    parser = argparse.ArgumentParser()

    parser.add_argument('num_lines',
                        type=int,
                        help="The number of lines to add")

    args = parser.parse_args()

    generate_trace_files(args.num_lines)
