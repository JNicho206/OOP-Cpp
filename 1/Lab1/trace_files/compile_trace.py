"""
NOTE: This file is for TA purposes only. It automatically generates C++ integration tests from the trace files. 
Feel free to play around with it if you want, but don't worry about it.
"""

from sys import argv
import re

filename = argv[1]

if (match := re.match(r'trace_(\d).txt', filename)):
    trace_number, = match.groups()
else:
    raise SystemExit(f'Could not parse trace number from file {filename}!')

lines = list(open(filename))[1:]

generated_lines: list[str] = []

def do_get(key: str, lines: list[str], expect_fail=False):
    new_lines = f'''
if (!list.get_value({key}).has_value())
{{
    std::cout << "GET failed for key={key}\\n";
    {"return 1;" if not expect_fail else ""}
}}
else
{{
    std::cout << "GET succeeded for key={key}\\n";
    {"return 1;" if expect_fail else ""}
}}
'''.strip().split('\n')

    lines += new_lines
    
def do_insert(key: str, value: str, lines: list[str]):
    new_lines = f'''
std::cout << "Inserting key={key}, value={value}\\n";
list.insert({key}, {value});    
'''.strip().split('\n')
    
    lines += new_lines
    
def do_remove(key: str, lines: list[str], expect_fail=False):
    new_lines = f'''
if (!list.remove({key}))
{{
    std::cout << "REMOVE failed for key={key}\\n";
    {"return 1;" if not expect_fail else ""}
}}
else
{{
    std::cout << "REMOVE succeeded for key={key}\\n";
    {"return 1;" if expect_fail else ""}
}}
'''.strip().split('\n')

    lines += new_lines


keys: set[str] = set()
for line in lines:
    if (match := re.match(r'(Insert|Get|Remove): (\d+(?:,\d+)?)', line)):
        command, arg_str = match.groups()
        args = arg_str.split(',')
        if command == 'Insert': 
            assert len(args) == 2, f'Error in trace: {line} (`Insert` expects 2 arguments, received {len(args)})'
        else:
            assert len(args) == 1, f'Error in trace: {line} (`{command}` expects 1 argument, received {len(args)})'
        
        if command == 'Insert':
            do_insert(args[0], args[1], generated_lines)
            keys.add(args[0])
            # generated_lines += [
            #     f'std::cout << "Inserting {args[0]}: {args[1]}\\n";',
            #     f'list.insert({args[0]}, {args[1]});'
            # ]
        elif command == 'Get':
            do_get(args[0], generated_lines, args[0] not in keys)
            
            # generated_lines += [
            #     f'if (!list.get_value({args[0]}).has_value())',
            #      '{',
            #     f'    std::cout << "Expected {args[0]} to be in list but it wasn\'t\\n";'
            #     f'    return 1;'
            #      '}',
            #      'else',
            #      '{',
            #     f'    std::cout << "Successfully retrieved {args[0]}\\n";'
            #     '}'
            # ]
        elif command == 'Remove':
            
            do_remove(args[0], generated_lines, args[0] not in keys)
            if args[0] in keys: keys.remove(args[0])
            
            # generated_lines += [
            #     f'if (!list.remove({args[0]}))',
            #      '{',
            #     f'    std::cout << "Failed to remove {args[0]} from list\\n";'
            #     f'    return 1;'
            #      '}'
            #      'else'
            #      '{'
            #     f'    std::cout << "Successfully removed {args[0]}\\n";'
            #     '}'
            # ]
    else:
        raise SystemExit(f'Syntax error in trace {filename}: {line}')      
            

generated_code = '\n    '.join(generated_lines)

template = f'''

#include <iostream>
#include "hash_list.h"

int trace_{trace_number}()
{{
    std::cout << "Running trace {trace_number}\\n";
    
    hash_list list;
    {generated_code}
    
    return 0;
}}

'''

open(filename.replace('txt', 'cpp'), 'w').write(template)