import os
import re
import subprocess
from static.colors import bcolors


def print_ok():
    print("{} OK{}".format(bcolors.OKGREEN + bcolors.BOLD, bcolors.ENDC))


def execute_cmd(cmd):
    proc = subprocess.run(cmd, shell=True, stdout=subprocess.PIPE,
                          stderr=subprocess.PIPE, universal_newlines=True)
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


def execute_cmd_cmp(cmd, code=False):
    result = execute_cmd('../42sh -c \"' + cmd + '\"')
    ref = execute_cmd(cmd)
    ref.stdout = ref.stdout.replace("/bin/sh", "42sh")
    if code and ref.returncode == result.returncode:
        return 0
    if ref.stdout == result.stdout and ref.stderr == result.stderr and ref.returncode == result.returncode:
        return 0
    print("*********************" + bcolors.FAIL)
    print(cmd)
    print("ref:", end=" ")
    print("stdout: \"" + ref.stdout + "\" returncode: " + str(
        ref.returncode) + " stderr: \"" + ref.stderr.strip(
        "\n") + "\"")
    print("got:", end=" ")
    print(
        "stdout: \"" + result.stdout + "\" returncode: " + str(
            result.returncode) + " stderr: \"" + result.stderr.strip(
            "\n") + "\"" + bcolors.ENDC)
    return 1


def get_committers():
    proc = execute_cmd("git shortlog -s -n --email")
    committers = list()
    lines = proc.stdout.splitlines()
    p = re.compile(r'(\s*)([0-9]*)(\t)([A-Za-z]*)(\s*)([A-Za-z]*)(\s*)(<)([A-Za-z0-9_]*)(@)([A-Za-z.]*)(>)')
    for line in lines:
        match = re.search(p, line)
        if match:
            groups = match.groups()
            committer = {'commits': groups[1],
                         'firstname': groups[3],
                         'lastname': groups[5],
                         'login': groups[8]
                         }
            committers.append(committer)
    return committers


def get_git_tree_html():
    colors = dict()
    colors['[31m'] = 'red'
    colors['[33m'] = 'yellow'
    colors['[32m'] = 'green'
    colors['[1;34m'] = 'blue'
    proc = execute_cmd("git log"
                       " --graph"
                       " --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr)%Creset"
                       " %C(bold blue)[%an]%Creset' --abbrev-commit")
    html = "<div>\n\t<p>\n"
    for line in proc.stdout.splitlines():
        line = line.replace("[31m", "<font color = \"red\">")
        line = line.replace("[33m", "<font color = \"yellow\">")
        line = line.replace("[32m", "<font color = \"green\">")
        line = line.replace("[1;34m", "<font color = \"blue\">")
        line = line.replace("[m", "</font>")
        html += "\t\t{}<br>\n".format(line)
    html += "\t</p>\n</div>\n"
    return html

def sanity_test_cmd(test):
    res = execute_cmd(
        "valgrind --leak-check=full --error-exitcode=42 " + test)
    if "no leaks are possible" in res.stderr and res.returncode != 42:
        print(
            "--> " + bcolors.OKGREEN + "SANITY OK " + bcolors.ENDC, end = '')
        return True
    else:
        print(
            "--> " + bcolors.FAIL + "UNSAIN TEST " + bcolors.ENDC, end='')
        return False