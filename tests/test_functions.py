import subprocess
import os
from static.colors import bcolors


def print_ok():
    print("{} OK{}".format(bcolors.OKGREEN + bcolors.BOLD, bcolors.ENDC))


def execute_cmd(cmd):
    proc = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, universal_newlines=True)
    return proc


def execute_file(file, db):
    print("Executing \"{}\" ...".format(os.path.basename(file)), end="")
    execute_cmd('psql -d {} -f {}'.format(db, file))
    print_ok()


def get_all_files(path):
    f_list = []
    if os.listdir(path):
        for item in os.listdir(path):
            item = path + '/' + item
            f_list.append(item)
    return f_list


def get_source_all_files(path):
    source = ''
    for source_file in get_all_files(path):
        for line in open(source_file, 'r').readlines():
            if "#" not in line:
                source += line
    return source


def execute_cmd_cmp(cmd):
    result = execute_cmd('../42sh -c \"' + cmd + '\"')
    ref = execute_cmd(cmd)
    if ref.stdout == result.stdout and ref.stderr == result.stderr and ref.returncode == result.returncode:
        return 0
    print("--> " + bcolors.FAIL + "FAILURE")
    print("ref:", end=" ")
    print("stdout: \"" + ref.stdout + "\" returncode: " + str(ref.returncode) + " stderr: \"" + ref.stderr.strip(
        "\n") + "\"")
    print("got:", end=" ")
    print("stdout: \"" + result.stdout + "\" returncode: " + str(result.returncode) + " stderr: \"" + result.stderr.strip(
        "\n") + "\"" + bcolors.ENDC)
    return 1
