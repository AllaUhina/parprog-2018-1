import subprocess as pr
import sys
import os

build_path = './build/'
bin_path = './bin/'
log_path = './log-files'
answ_path = bin_path + "answers/"
rep_path = bin_path + "reports/"
res_path = bin_path + "results/"
task_path = bin_path + "tasks/"


if not os.path.exists(build_path):
    os.makedirs(build_path)

if not os.path.exists(bin_path):
    os.makedirs(bin_path)

if not os.path.exists(log_path):
    os.makedirs(log_path)

if not os.path.exists(answ_path):
    os.makedirs(answ_path)

if not os.path.exists(rep_path):
    os.makedirs(rep_path)

if not os.path.exists(res_path):
    os.makedirs(res_path)

if not os.path.exists(task_path):
    os.makedirs(task_path)

os.chdir(build_path)
print("building is doing...")
code = pr.call(["cmake", "-j2",".."])
code = pr.call("make")
if code != 0:
    print("building fail")
    sys.exit()
else:
    print("building is done.")

os.chdir('../pyscripts/')

ind = 1
if (len(sys.argv) > 1):
    ind = int(sys.argv[1])

if (ind == 0):
    code = pr.call(["python3", "./full_cycle_of_checks.py"])
    if code != 0:
        print("error of checker")
else:
    code = pr.call(["python3", "./checker.py"])
    if code != 0:
        print("error of checker")
