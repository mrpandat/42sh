from os import listdir
from os.path import isdir, isfile, join, splitext
import os


def get_all_files(path):
    f_list = []
    if listdir(path):
        for item in listdir(path):
            item = join(path, item)
            if isfile(item):
                f_list.append(item)
            elif isdir(item):
                f_list += get_all_files(item)
    return f_list


def get_files_of_type(path, extensions):
    file_list = sorted(get_all_files(path), key=str.lower)
    file_list = [file for file in file_list if splitext(file)[1] in extensions]
    return file_list


def check_lines(path):
    with open(path, 'r') as file:
        lines = file.readlines()
        counter = 0
        counterfuncs = 0
        for i, line in enumerate(lines):
            if line[0] == '{':
                counter = 0
                if i > 0 and 'static' not in lines[i - 1]:
                    counterfuncs += 1
            if line[0] == '}':
                if counter - 1 > 25:
                    print("** Function too long detected in file {} near line {} ({} lines)."
                          .format(path, i + 1, counter - 1))
                counter = 0
            if line != '\n' and '/*' not in line and '*/' not in line:
                counter += 1
        if counterfuncs > 5:
            print('** Too much functions ({}) in file {}.'.format(counterfuncs, path))


if __name__ == "__main__":
    os.chdir(os.path.dirname(os.path.realpath(__file__)))
    files = get_files_of_type('src/', ['.c'])
    for file in files:
        check_lines(file)
