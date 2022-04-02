import subprocess
import os
import json
import time

from termcolor import colored
from colorama import init

init()


def PrintPink(colored_msg):
    print(colored(colored_msg, 'white', 'on_magenta'))


def PrintGreen(colored_msg):
    print(colored(colored_msg, 'white', 'on_green'))


def GetMiddleStr(content, startStr, endStr) -> str:
    startIndex = content.index(startStr)
    if startIndex >= 0:
        startIndex += len(startStr)
    endIndex = content.index(endStr)
    return content[startIndex:endIndex]


BASE_DIR = os.path.dirname(__file__)
CWD_DIR = os.getcwd()
print('cwd: ', CWD_DIR)

case_path_json = CWD_DIR + '/test.json'
case_path_txt = CWD_DIR + '/test.txt'
source = None

for root, dirs, files in os.walk(CWD_DIR):
    for item in files:
        if item.endswith('cpp'):
            source = root + '/' + item

        if item.endswith('txt'):
            case_path_txt = root + '/' + item

        if item.endswith('json'):
            case_path_txt = root + '/' + item
    break

if source is None:
    print('source not exists.')
    quit()

if os.path.exists(case_path_txt):
    with open(case_path_txt, 'r') as f:
        case = f.read()
        temp = case.split("==")
        case = []
        for item in temp:
            if item == '':
                continue
            temp = {
                'input': GetMiddleStr(item, '[\n', '\n]\n').split('\n'),
                'expect': GetMiddleStr(item, '{\n', '\n}\n').split('\n')
            }
            case.append(temp)
elif os.path.exists(case_path_json):
    with open(case_path_json, 'r') as f:
        case = f.read()
        case = json.loads(case)
else:
    print('case not exists.')
    quit()


def DoCmd(cmd, encoding='utf-8'):
    pro = subprocess.Popen(cmd, shell=True, stdout=subprocess.PIPE)
    res = ''
    line = pro.stdout.readlines()
    try:
        res += ''.join(item.decode(encoding) for item in line)
    except Exception as e:
        res = line
    return res


def Complie(source):
    complier = 'clang'
    temp_path = CWD_DIR + '/test.exe'

    if os.path.exists(temp_path):
        os.remove(temp_path)
        if os.path.exists(temp_path):
            print('test.exe still running')
            return

    cmd = '%s %s -o %s' % (complier, source, temp_path)
    res = DoCmd(cmd)
    if res == '':
        return temp_path
    print(res)
    return


def Test(exe):
    i = 0
    USING_ENCODING = 'utf-8'
    for item in case:
        print(i, '~~~~~~~~~~~~~~start')
        pro = subprocess.Popen(exe,
                               shell=True,
                               stdout=subprocess.PIPE,
                               stderr=subprocess.PIPE,
                               stdin=subprocess.PIPE)
        start = time.time()
        output = []
        for line in item['input']:
            pro.stdin.write(bytes(line, encoding=USING_ENCODING) + b'\n')
            pro.stdin.flush()
        for line in pro.stdout.readlines():
            line = str(line, encoding=USING_ENCODING)
            line = line.replace('\r\n', '')
            output.append(line)
        end = time.time()
        gap = end - start
        print(gap)
        if gap > 1:
            PrintPink('超时！！')
        print('input', item['input'])
        print('actual', output)

        if type(item['expect']) is str:
            item['expect'] = item['except'].split("\n")
        print('expect', item['expect'])
        if output == item['expect']:
            PrintGreen('OK')
        else:
            j = 0
            for line in output:
                if j >= len(item['expect']):
                    PrintPink(line)
                elif line != item['expect'][j]:
                    PrintPink(line)
                else:
                    print(line)
                j += 1
            PrintPink('\nWRONG!!!!!')
        print(i, '~~~~~~~~~~~~~~end\n')
        i += 1

    print('\n===========end===========')


print('using: ', source, '\n')
exe = Complie(source)

if exe is None:
    quit()

Test(exe)
