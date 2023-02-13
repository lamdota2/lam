import os
import sys
import subprocess
"""
useage:
    configure env PATH    C:\Program Files\7-Zip
    execute cmd:
        cd snapshot file
        python unzip.py Snapshot_20220926-182739_SBTS22R4_ENB_0000_000558_000000T1.zip
"""
if len(sys.argv) < 2:
    sys.exit("Please specify the dirctory ...")
read_path = sys.argv[1]
print('version: 1.01, Try to unzip archives recursively under the director ' + read_path) name = sys.argv[1]
file_name = os.path.splitext(name)[0]           
unzippath = os.path.join(file_name) print("Prepare to auto parse snapshot") if not os.path.exists(unzippath):
    os.mkdir(unzippath)
    print("Create directory:" + unzippath)
cmdline = '7z x -y -r -o' + '"' + unzippath + '" "' + os.path.join(name) + '"'
print("Unzip:" + cmdline)
sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
sub.wait() #3 refers to decompressing to the second level subdirectory, and multiple formats can be specified
while True:
    unzip_flag = False
    name = sys.argv[1]
    file_name = os.path.splitext(name)[0]
    for root, dirs, files in os.walk(file_name):
        # print(root, dirs, files)
        for name in files:
            if name.endswith('.zip') or name.endswith('.tar'): 
                unzip_flag = True
                file_name = os.path.splitext(name)[0]           
                unzippath = os.path.join(root,file_name)                 if not os.path.exists(unzippath):
                    os.mkdir(unzippath)
                    print("Create directory:" + unzippath)
                cmdline = '7z x -y -r -o' + '"' + unzippath + '" "' + os.path.join(root,name) + '"'
                print("Unzip:" + cmdline)
                sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
                sub.wait()
                cmdline = 'del /Q ' + '"' + os.path.join(root,name) + '"'
                print("Delete:" + cmdline)
                sub = subprocess.Popen(cmdline,shell=True,stdout=subprocess.PIPE)
                sub.wait()
    if not unzip_flag:
        break
