from static.colors import *


def print_file(path, format, end="\n", width=80):
    print(format)
    with open(path, 'r') as file:
        for line in file.readlines():
            print(line.strip("\n").center(width), end=end)
    print(bcolors.ENDC)


def print_colored(path, width=80):
    output = ''
    centered = ''
    with open(path, 'r') as file:
        lines = file.readlines()
        for n, line in enumerate(lines):
            lines[n] = line.strip('\n').center(width)
        for c in '\n'.join(lines):
            if c in xterm_colors:
                output = output + xterm_colors[c] + ' ' + '\033[0m'
            else:
                output = output + c
    print('\n' + output + '\n')


def print_margin(i, width=5):
    if i % 20 == 2:
        margin = "\\O/"
    elif i % 20 == 3:
        margin = "|"
    elif i % 20 == 4:
        margin = "/ \\"
    elif i % 20 == 12:
        margin = "O"
    elif i % 20 == 13:
        margin = "/|\\"
    elif i % 20 == 14:
        margin = "/ \\"
    else:
        margin = ""
    print(bcolors.WARNING + margin.center(width) + bcolors.ENDC, end="")
